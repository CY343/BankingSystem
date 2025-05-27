#include"SavingAccount.hpp"
#include<iostream>
#include<string>

SavingAccount::SavingAccount():BankAccount(), 
               min_balance_(500.0), 
               withdrawal_times_this_month_(0){}


SavingAccount::SavingAccount(const double &deposit, 
                             const double &withdrawal, 
                             const double &account_balance, 
                             const double &interest_rate, 
                             double min_balance, 
                             int withdrawal_times):
                             BankAccount(deposit, withdrawal, account_balance, interest_rate), 
                             min_balance_(min_balance), 
                             withdrawal_times_this_month_(withdrawal_times) {}

bool SavingAccount::applyWithdraw(const double& amount)
{
    // Check min balance rule
    if((getAccountBalance() -amount) < min_balance_)
    {
        throw std::runtime_error("Withdrawal violates minimum balance requirements");
    }

    // Limit monthly withdrawal 
    if(withdrawal_times_this_month_ >= 6) 
    {
        throw std::runtime_error("Maximum monthly withdrawal exceeded.");
    }

    if(BankAccount::applyWithdraw(amount))
    {
        withdrawal_times_this_month_++;
        return true;
    }
    
    return false;
}

void SavingAccount::applyMonthlyInterest()
{
    double interest = getAccountBalance() * (interest_rate_ / 12);
    applyDeposit(interest);
    
    // Record as transaction type
    addTransaction(Transaction::INTEREST, interest, std::time(nullptr));
}

void SavingAccount::resetMonthlyWithdrawals()
{
    withdrawal_times_this_month_ = 0;
}

double SavingAccount::getMinBalance() const
{
    return min_balance_;
}

double SavingAccount::getInterestRate() const
{
    return interest_rate_;
}

void SavingAccount::applyInterest() {
    const double monthly_interest = getAccountBalance() * (getInterestRate() / 12.0);
    applyDeposit(monthly_interest);
    addTransaction(Transaction::INTEREST, monthly_interest, std::time(nullptr));
}