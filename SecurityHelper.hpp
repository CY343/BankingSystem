#ifndef SECURITYHELPER_HPP
#define SECURITYHELPER_HPP
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>



class SecurityHelper{
        public:
            
            struct EncryptedData 
            {
                std::string ciphertext;
                std::string iv;
                std::string key;
            };
            // Encryption/Decryption
            static EncryptedData encrypt(const std::string& plaintext);
            static std::string decrypt(const EncryptedData& data);
            
            // Hashing
            static std::string hashPin(const std::string& pin, const std::string& salt);
            
            // Key Management
            static void generateKey(unsigned char* buffer, int length);
            static std::string generateRandomSalt(size_t length = 16);
            
            // Validation
            static bool validatePassword(const std::string& password);

            struct RotatedKeys {
                EncryptedData new_data;
                std::string new_key;
                std::string new_iv;
            };
    
            static RotatedKeys rotateKeys(const EncryptedData& old_data,
                                          const std::string& old_key,
                                          const std::string& old_iv);
                                          struct SessionToken {
                                            std::string token;
                                            std::time_t expiration;
                                        };
                                    
            static SessionToken generateSessionToken(int validity_seconds = 3600);

    private:
            static void secureClean(void* data, size_t length);
};

#endif