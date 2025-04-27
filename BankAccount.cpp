#include "BankAccount.hpp"
#include <iostream>
#include <string>

BankAccount::BankAccount()
{
    deposit_ = 0.0;
    withdrawal_ = 0.0;
    account_balance_ = 0.0;
    hasLowBalance_ = false;
    earning_interest_rate_ = 0.0;
    account_number_ = 0;
}

BankAccount::BankAccount(const double &deposit, const double &withdrawal, const double &account_balance, const double &earning_interest_rate, const int &account_number)
    : deposit_(deposit), withdrawal_(withdrawal), account_balance_(account_balance), earning_interest_rate_(earning_interest_rate), account_number_(account_number), customers() 
    {
        setLowBalance();
    }

BankAccount::~BankAccount()
{
}

double BankAccount::getDeposit() const
{
    return deposit_;
}

bool BankAccount::setDeposit(const double &deposit)
{
    deposit_ = deposit;
    return true;
}

double BankAccount::getWithdrawal() const
{
    return withdrawal_;
}

bool BankAccount::setWithdrawal(const double &withdrawal)
{
    if (account_balance_ < withdrawal)
    {
        std::cout << " You have insuffcient funds." << std::endl;
        return false;
    }
    withdrawal_ = withdrawal;
    return true;
}

double BankAccount::getAccountBalance() const
{
    return account_balance_;
}

bool BankAccount::applyDeposit(const double &amount)
{
    if (amount <= 0)
    {
        return false;
    }
    account_balance_ += amount;
    setLowBalance();
    return true;
}

bool BankAccount::applyWithdraw(const double &amount)
{
    if (amount <= 0 || account_balance_ <= amount)
    {
        return false;
    }
    account_balance_ -= amount;
    setLowBalance();
    return true;
}

void BankAccount::addCreditCard(const std::string &credit_card_num, const std::string &expiration_date, const std::string &cvv_num, double creditLimit, bool isActivated)
{
    creditCards_.emplace_back(std::make_shared<CreditCard>(credit_card_num, expiration_date, cvv_num, creditLimit, isActivated));
}

int BankAccount::getAccountNumber() const
{
    return account_number_;
}

void BankAccount::setLowBalance()
{   
    hasLowBalance_ = (account_balance_ < 500.0);
    
    
}

bool BankAccount::isLowBalance() const
{
    return hasLowBalance_;
}

double BankAccount::getInterestRate() const
{
    return earning_interest_rate_;
}

bool BankAccount::setEarningInterestRate(const double &earning_interes_rate)
{
    earning_interest_rate_ = earning_interes_rate;
    return true;
}
