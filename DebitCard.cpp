#include"DebitCard.hpp"
#include"CheckingAccount.hpp"
#include"SecurityHelper.hpp"
#include <openssl/rand.h>
#include<iostream>
#include<string>

/**
 * @brief Default constructor for DebitCard.
 * 
 * Initializes a new debit card with default values:
 * - Inactive and unvalidated card (via base Card constructor)
 * - Empty salt and PIN hash
 * - Daily withdrawal limit and spend amount set to 0
 * - Contactless payment disabled
 * - No linked checking account
 */
DebitCard::DebitCard():Card(false, false), 
                       salt_(""),                                  
                       pin_hash_(""),
                       daily_withdrawal_limit_(0.0), 
                       daily_spend_amount_(0.0),  
                       contactless_enable_(false){}


/**
 * @brief Parameterized constructor for DebitCard.
 * 
 * Creates a new DebitCard linked to a specified CheckingAccount, with a daily withdrawal limit 
 * and a user-provided PIN. The constructor auto-generates a card number prefix for Visa cards.
 * It ensures there’s enough entropy for secure PIN hashing and sets the PIN.
 * If the provided PIN is invalid, a default PIN "0000" is set instead.
 * 
 * @param account Shared pointer to the CheckingAccount this debit card is linked to.
 * @param daily_withdrawal_limit The allowed maximum withdrawal per day.
 * @param pin The desired card PIN as a string.
 * 
 * @throws std::runtime_error If there’s insufficient system entropy for secure operations,
 * or if setting a default PIN fails after an invalid PIN attempt.
 */
DebitCard::DebitCard(std::shared_ptr<CheckingAccount> account,
                        double daily_withdrawal_limit,
                        const std::string& pin)
                        : Card("4", true),  // Auto-generate Visa card, 5 mastercard, 3 AE, 6 Discover
                        daily_withdrawal_limit_(daily_withdrawal_limit),
                        daily_spend_amount_(0.0),  // Initialize to default
                        contactless_enable_(true),  // Default to contactless enabled
                        linked_debit_card_account_(account) 
 {
    if (!RAND_status()) 
    {
        throw std::runtime_error("Insufficient entropy for secure operations");
    }
    
    if (!setPin(pin))
    {
        std::cerr << "Invalid PIN! Setting default PIN\n";

        if (!setPin("0000"))
         {
            throw std::runtime_error("Failed to set default PIN");
         }
    }

 }
 

 /**
 * @brief Gets the daily withdrawal limit.
 * @return The current daily withdrawal limit.
 */
double DebitCard::getDailyWithdrawalLimit() const
{
    return daily_withdrawal_limit_;
}


/**
 * @brief Gets the current daily spend amount.
 * @return The current daily spend amount.
 */
double DebitCard::getDailySpendAmount() const
{
    return daily_spend_amount_;
}


/**
 * @brief Gets the linked checking account.
 * @return A weak pointer to the linked CheckingAccount.
 */
std::weak_ptr<CheckingAccount> DebitCard::getLinkedAccount() const
{
    return linked_debit_card_account_;
}


/**
 * @brief Sets the daily spend amount.
 * @param amount The new daily spend amount.
 * @return True if successfully set.
 */
bool DebitCard::SetDailySpendAmount(const double &amount)
{
    daily_spend_amount_ = amount;
    return true;
}


/**
 * @brief Sets the daily withdrawal limit.
 * @param limit The new withdrawal limit.
 * @return True if successfully set.
 */
bool DebitCard::SetDailyWithdrawalLimit(const double &limit)
{
    daily_withdrawal_limit_ = limit;
    return true;
}


/**
 * @brief Sets the card PIN securely with salt and hash.
 * @param pin The new PIN (4-6 digits).
 * @return True if successfully set, false if invalid.
 * @throws std::runtime_error if salt generation fails.
 */
bool DebitCard::setPin(const std::string pin)
{
    if(pin.size() < 4 || pin.size() > 6)
    {
        std::cout << "The pin must be within 4 to 6 digits" << std::endl;
        return false;
    }

    unsigned char new_salt[16];
    if (RAND_bytes(new_salt, sizeof(new_salt)) != 1) {
        throw std::runtime_error("Failed to generate secure salt");
    }
    salt_ = std::string(reinterpret_cast<char*>(new_salt), sizeof(new_salt));

    // Hash with new salt
    pin_hash_ = SecurityHelper::hashPin(pin, salt_);
    return true;
}


/**
 * @brief Changes the PIN after verifying the old one.
 * @param old_pin The current PIN.
 * @param new_pin The new PIN to set.
 * @return True if successfully changed.
 */
bool DebitCard::changePin(const std::string old_pin, const std::string new_pin)
{
    if (!verifyPin(old_pin)) {
        std::cerr << "Old PIN verification failed\n";
        return false;
    }
    return setPin(new_pin);
}


/**
 * @brief Processes a payment from the linked checking account.
 * @param amount The amount to withdraw.
 * @return True if payment is successful, false if not enough balance or card inactive.
 */
bool DebitCard::processPayment(double amount)
{
    if(!isActivated()) {return false;}
    auto account = linked_debit_card_account_.lock();
    if(!account || amount > account->getAccountBalance())
    {
        return false;
    }
    return account->applyWithdraw(amount);
}


/**
 * @brief Validates the card status and PIN hash.
 * @return True if card is valid.
 */
bool DebitCard::validate() const
{
    return Card::validate() && !pin_hash_.empty() && daily_withdrawal_limit_ > 0;
}


/**
 * @brief Checks if the card is expired.
 * @return True if expired.
 */
bool DebitCard::checkIfExpired()
{
    return isExpired();
}


/**
 * @brief Checks if contactless payment is enabled.
 * @return True if enabled.
 */
bool DebitCard::isContactlessEnabled() const {
    return contactless_enable_;
}


/**
 * @brief Enables or disables contactless payment.
 * @param enable True to enable, false to disable.
 */
void DebitCard::enableContactless(bool enable) {
    contactless_enable_ = enable;
}


/**
 * @brief Verifies a PIN attempt against the stored hashed PIN.
 *        Allows maximum of 3 failed attempts before locking.
 * @param attempt The entered PIN.
 * @return True if PIN matches, false otherwise.
 */
bool DebitCard::verifyPin(const std::string& attempt)const {

    if (failed_attempts_ >= 3) {
        std::cerr << "Card locked due to too many failed attempts\n";
        return false;
    }

    const std::string attempt_hash = SecurityHelper::hashPin(attempt, salt_);
    
    if (attempt_hash != pin_hash_) {
        failed_attempts_++;
        
        if(failed_attempts_ >= 3)
        {
            std::cerr << "Card locked due to too many failed attempts" << std::endl;
            const_cast<DebitCard*>(this)->setActivated(false);

        }
            return false;
    }

    failed_attempts_ = 0;
    return true;
}