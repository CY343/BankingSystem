#include"BankAccount.hpp"
#include<iostream>
#include<string>

BankAccount::BankAccount()
{
         deposit_ = 0.0;
         withdrawal_ = 0.0;
         account_balance_ = 0.0;
         hasLowBalance_ = false;
         earning_interest_rate_ = 0.0;
         
}

BankAccount::BankAccount(const double& deposit, const double& withdrawal, const double& account_balance, const bool& hasLowBalance, const double& earning_interest_rate)
:deposit_(deposit), withdrawal_(withdrawal), account_balance_(account_balance), hasLowBalance_(hasLowBalance), earning_interest_rate_(earning_interest_rate),customers()
{}

BankAccount::~BankAccount()
{
}

double BankAccount::getDeposit()const
{
    return deposit_;
}

bool BankAccount::setDeposit(const double& deposit)
{
    deposit_ = deposit;
    return true;
}

double BankAccount::getWithdrawal()const
{
    return withdrawal_;
}

bool BankAccount::setWithdrawal(const double& withdrawal)
{
    if(account_balance_ < withdrawal)
    {
        std::cout <<" You have insuffcient funds." << std::endl;
        return false;
    }
    withdrawal_ = withdrawal;
    return true;
}

double BankAccount::getAccountBalance() const
{   
    return account_balance_;
}

bool BankAccount::applyDeposit(double& amount)
{
    if(amount <= 0)
    {
        return false;
    }
    account_balance_ += amount;
    return true;

}

bool BankAccount::applyWithdraw(double& amount)
{
    if(amount <= 0 || account_balance_ <= amount)
    {
        return false;
    }
    account_balance_ -= amount;
    return true;
}

void BankAccount::addCreditCard(const std::string &credit_card_num, const std::string &expiration_date, const std::string &cvv_num, double &creditLimit, bool& isActivated)
{
    creditCards_.push_back(new CreditCard(credit_card_num, expiration_date, cvv_num, creditLimit, isActivated));
}

void BankAccount::setLowBalance(const bool& flag)
{
    hasLowBalance_ = flag;
}

bool BankAccount::isLowBalance()const
{
    return hasLowBalance_;
}

double BankAccount::getInterestRate()const
{
    return earning_interest_rate_;
}

bool BankAccount::setEarningInterestRate(const double& earning_interes_rate)
{
    earning_interest_rate_ = earning_interes_rate;
    return true;
}

