#include "SecurityHelper.hpp"
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <regex>
#include <chrono>
#include <algorithm>


struct OpenSSLInit {
    OpenSSLInit() {
        OpenSSL_add_all_algorithms();
        RAND_poll();
    }
    ~OpenSSLInit() {
        EVP_cleanup();
    }
};
static OpenSSLInit ssl_init;

SecurityHelper::EncryptedData SecurityHelper::encrypt(const std::string& plaintext) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("Failed to create cipher context");

    struct ContextGuard {
        EVP_CIPHER_CTX* ctx;
        ~ContextGuard() { EVP_CIPHER_CTX_free(ctx); }
    } guard{ctx};

    // Generate random key and IV
    unsigned char key[32];
    unsigned char iv[16];
    if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(iv, sizeof(iv))) {
        throw std::runtime_error("Failed to generate cryptographic parameters");
    }

    // Initialize encryption
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv)) {
        throw std::runtime_error("Encryption initialization failed");
    }

    // Prepare output buffer
    std::vector<unsigned char> ciphertext(plaintext.size() + EVP_CIPHER_block_size(EVP_aes_256_cbc()));
    int len = 0, ciphertext_len = 0;

    // Process plaintext
    if (1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &len, 
                              reinterpret_cast<const unsigned char*>(plaintext.data()), 
                              plaintext.size())) {
        throw std::runtime_error("Encryption update failed");
    }
    ciphertext_len = len;

    // Finalize encryption
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len)) {
        throw std::runtime_error("Encryption finalization failed");
    }
    ciphertext_len += len;

    // Build return object
    EncryptedData result;
    result.ciphertext = std::string(ciphertext.begin(), ciphertext.begin() + ciphertext_len);
    result.iv = std::string(reinterpret_cast<char*>(iv), sizeof(iv));
    result.key = std::string(reinterpret_cast<char*>(key), sizeof(key));

    // Secure cleanup
    secureClean(key, sizeof(key));
    secureClean(iv, sizeof(iv));

    return result;
}

std::string SecurityHelper::decrypt(const EncryptedData& data) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("Failed to create cipher context");

    struct ContextGuard {
        EVP_CIPHER_CTX* ctx;
        ~ContextGuard() { EVP_CIPHER_CTX_free(ctx); }
    } guard{ctx};

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr,
                               reinterpret_cast<const unsigned char*>(data.key.data()),
                               reinterpret_cast<const unsigned char*>(data.iv.data()))) {
        throw std::runtime_error("Decryption initialization failed");
    }

    std::vector<unsigned char> plaintext(data.ciphertext.size() + EVP_CIPHER_block_size(EVP_aes_256_cbc()));
    int len = 0, plaintext_len = 0;

    if (1 != EVP_DecryptUpdate(ctx, plaintext.data(), &len,
                              reinterpret_cast<const unsigned char*>(data.ciphertext.data()),
                              data.ciphertext.size())) {
        throw std::runtime_error("Decryption update failed");
    }
    plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len)) {
        throw std::runtime_error("Decryption finalization failed");
    }
    plaintext_len += len;

    return std::string(plaintext.begin(), plaintext.begin() + plaintext_len);
}

std::string SecurityHelper::hashPin(const std::string& pin, const std::string& salt) {
    std::string salted = salt + pin;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(salted.data()), salted.size(), hash);
    return std::string(reinterpret_cast<char*>(hash), SHA256_DIGEST_LENGTH);
}

void SecurityHelper::generateKey(unsigned char* buffer, int length) {
    if (!RAND_bytes(buffer, length)) {
        throw std::runtime_error("Key generation failed");
    }
}

std::string SecurityHelper::generateRandomSalt(size_t length) {
    std::vector<unsigned char> salt(length);
    if (!RAND_bytes(salt.data(), length)) {
        throw std::runtime_error("Salt generation failed");
    }
    return std::string(salt.begin(), salt.end());
}

bool SecurityHelper::validatePassword(const std::string& password) {
    const std::regex pattern(
        "^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    return std::regex_match(password, pattern);
}

void SecurityHelper::secureClean(void* data, size_t length) {
    if (data && length > 0) {
        volatile unsigned char* p = static_cast<volatile unsigned char*>(data);
        while (length--) *p++ = 0;
    }
}
 SecurityHelper::RotatedKeys SecurityHelper::rotateKeys(
    const EncryptedData& old_data,
    const std::string& old_key,
    const std::string& old_iv) 
{
    // 1. Decrypt with old keys
    std::string plaintext = decrypt({old_data.ciphertext, old_key, old_iv});

    // 2. Generate new keys
    unsigned char new_key[32], new_iv[16];
    generateKey(new_key, sizeof(new_key));
    generateKey(new_iv, sizeof(new_iv));

    // 3. Re-encrypt with new keys
    EncryptedData new_data = encrypt(plaintext);

    // 4. Secure wipe sensitive data
    secureClean(&plaintext[0], plaintext.size());
    secureClean(const_cast<void*>(static_cast<const void*>(old_key.data())), 
    old_key.size());
    secureClean(const_cast<void*>(static_cast<const void*>(old_iv.data())), 
    old_iv.size());

    return {
        new_data,
        std::string(reinterpret_cast<char*>(new_key), sizeof(new_key)),
        std::string(reinterpret_cast<char*>(new_iv), sizeof(new_iv))
    };
}

SecurityHelper::SessionToken SecurityHelper::generateSessionToken(int validity_seconds) {
    SessionToken token;
    
    // Generate random bytes
    unsigned char random[32];
    RAND_bytes(random, sizeof(random));
    
    // Get current time
    auto now = std::chrono::system_clock::now();
    token.expiration = std::chrono::system_clock::to_time_t(
        now + std::chrono::seconds(validity_seconds)
    );
    
    // Combine random bytes with timestamp
    std::string raw_token(reinterpret_cast<char*>(random), sizeof(random));
    raw_token += std::to_string(token.expiration);
    
    // Hash the combination
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(raw_token.data()), 
          raw_token.size(), hash);
    
    // Convert to hex string
    std::stringstream ss;
    for(unsigned char c : hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    }
    
    token.token = ss.str();
    return token;
}