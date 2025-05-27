#include"DebitCard.hpp"
#include"CheckingAccount.hpp"
#include"SecurityHelper.hpp"
#include <openssl/rand.h>
#include<iostream>
#include<string>

DebitCard::DebitCard():Card(false, false), 
                       salt_(""),                                  
                       pin_hash_(""),
                       daily_withdrawal_limit_(0.0), 
                       daily_spend_amount_(0.0),  
                       contactless_enable_(false){}

DebitCard::DebitCard(std::shared_ptr<CheckingAccount> account,
                        double daily_withdrawal_limit,
                        const std::string& pin)
                        : Card("4", true),  // Auto-generate Visa card
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
 

double DebitCard::getDailyWithdrawalLimit() const
{
    return daily_withdrawal_limit_;
}


double DebitCard::getDailySpendAmount() const
{
    return daily_spend_amount_;
}


std::weak_ptr<CheckingAccount> DebitCard::getLinkedAccount() const
{
    return linked_debit_card_account_;
}


bool DebitCard::SetDailySpendAmount(const double &amount)
{
    daily_spend_amount_ = amount;
    return true;
}

bool DebitCard::SetDailyWithdrawalLimit(const double &limit)
{
    daily_withdrawal_limit_ = limit;
    return true;
}

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

bool DebitCard::changePin(const std::string old_pin, const std::string new_pin)
{
    if (!verifyPin(old_pin)) {
        std::cerr << "Old PIN verification failed\n";
        return false;
    }
    return setPin(new_pin);
}

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

bool DebitCard::validate() const
{
    return Card::validate() && !pin_hash_.empty() && daily_withdrawal_limit_ > 0;
}

bool DebitCard::checkIfExpired()
{
    return isExpired();
}

bool DebitCard::isContactlessEnabled() const {
    return contactless_enable_;
}

void DebitCard::enableContactless(bool enable) {
    contactless_enable_ = enable;
}
bool DebitCard::verifyPin(const std::string& attempt)const {

    if (failed_attempts_ >= 3) {
        std::cerr << "Card locked due to too many failed attempts\n";
        return false;
    }

    const std::string attempt_hash = SecurityHelper::hashPin(attempt, salt_);
    
    if (attempt_hash != pin_hash_) {
        failed_attempts_++;
        return false;
    }

    failed_attempts_ = 0;
    return true;
}