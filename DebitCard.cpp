#include"DebitCard.hpp"
#include"BankAccount.hpp"
#include<iostream>
#include<string>

DebitCard::DebitCard():Card("None", "None", "NONE", false), daily_withdrawal_limit_(0.0), daily_spend_amount_(0.0), pin_("None"), contactless_enable_(false){}

DebitCard::DebitCard(const std::string &number, const std::string &expiration, const std::string &cvv, const bool &isActivated,
const double& daily_withdrawal_limit, const double& daily_spend_amount, const std::string& pin, const bool enable,std::shared_ptr<BankAccount> account)
:Card(number, expiration, cvv, isActivated),daily_withdrawal_limit_(daily_withdrawal_limit), daily_spend_amount_(daily_spend_amount), contactless_enable_(enable), linked_debit_card_account_(account)
 {
    if(!setPin(pin))
    {
        std::cout << "INVALID PIN! " << std::endl;
        pin_ = "0000";
    }
 }
 
DebitCard::~DebitCard(){}

double DebitCard::getDailyWithdrawalLimit() const
{
    return daily_withdrawal_limit_;
}

double DebitCard::getDailySpendAmount() const
{
    return daily_spend_amount_;
}

std::string DebitCard::getPin() const
{
    return pin_;
}

std::weak_ptr<BankAccount> DebitCard::getLinkedAccount() const
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

bool DebitCard::setPin(const std::string &pin)
{
    if(pin.size() < 4 || pin.size() > 6)
    {
        std::cout << "The pin must be within 4 to 6 digits" << std::endl;
        return false;
    }

    pin_ = pin;
    return true;
}

bool DebitCard::changePin(const std::string &old_pin, const std::string &new_pin)
{
    if(old_pin != pin_ )
    {
        std::cout << "Error: YOUR OLD PIN DOESN'T MATCH! " << std::endl;
        return false;
    }
    
    if(new_pin.empty() || !setPin(new_pin))
    {
        std::cout << "Erorr: Your NEW PIN IS INVALID! " << std::endl;
        return false;
    }
    return true;
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
    return Card::validate() && !pin_.empty() && daily_withdrawal_limit_ > 0;
}

bool DebitCard::isContactlessEnabled() const {
    return contactless_enable_;
}

void DebitCard::enableContactless(bool enable) {
    contactless_enable_ = enable;
}