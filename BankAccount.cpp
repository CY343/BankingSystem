#include "BankAccount.hpp"
#include "CreditCard.hpp"
#include <iostream> 
#include <string>

int BankAccount::next_account_number_ = 1000;

BankAccount::BankAccount():deposit_(0.0), withdrawal_(0.0),account_balance_(0.0),
 account_number_(next_account_number_++) {}


BankAccount::BankAccount(const double &deposit, const double &withdrawal, const double &account_balance, const double &earning_interest_rate)
    : deposit_(deposit), withdrawal_(withdrawal), account_balance_(account_balance), earning_interest_rate_(earning_interest_rate), account_number_(next_account_number_++)
    {
        setLowBalance();
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
    transactions_.emplace_back(Transaction::DEPOSIT, amount, std::time(nullptr));
    setLowBalance();
    return true;
}

bool BankAccount::applyWithdraw(const double &amount)
{
    if (amount <= 0 || account_balance_ < amount)
    {
        return false;
    }
    account_balance_ -= amount;
    transactions_.emplace_back(Transaction::WITHDRAW, amount, std::time(nullptr));
    setLowBalance();
    return true;
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

void BankAccount::addTransaction(Transaction::Type type, double amount, time_t timestamp)
{   

    transactions_.emplace_back(type, amount, timestamp);
    
}