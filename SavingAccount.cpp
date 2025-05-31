#include"SavingAccount.hpp"
#include<iostream>
#include<string>


/**
 * @file SavingAccount.cpp
 * @brief Implementation of the SavingAccount class.
 */


 /**
 * @brief Default constructor.
 * Initializes min_balance_ to 500.0 and withdrawal_times_this_month_ to 0.
 */
SavingAccount::SavingAccount():BankAccount(), 
               min_balance_(500.0), 
               withdrawal_times_this_month_(0){}



/**
 * @brief Parameterized constructor.
 * Initializes the account with provided values and forwards appropriate values to the base BankAccount constructor.
 * 
 * @param deposit Initial deposit amount.
 * @param withdrawal Initial withdrawal amount.
 * @param account_balance Initial account balance.
 * @param interest_rate Interest rate for the account.
 * @param min_balance Minimum required balance for the savings account.
 * @param withdrawal_times Number of withdrawals already made this month.
 */
SavingAccount::SavingAccount(const double &deposit, 
                             const double &withdrawal, 
                             const double &account_balance, 
                             const double &interest_rate, 
                             double min_balance, 
                             int withdrawal_times):
                             BankAccount(deposit, withdrawal, account_balance, interest_rate), 
                             min_balance_(min_balance), 
                             withdrawal_times_this_month_(withdrawal_times) {}



/**
 * @brief Attempts to withdraw a specified amount from the account.
 * 
 * Ensures that the withdrawal does not violate the minimum balance requirement
 * and does not exceed the monthly withdrawal limit (6 withdrawals per month).
 * 
 * @param amount Amount to withdraw.
 * @return True if withdrawal is successful, false otherwise.
 * @throws std::runtime_error if minimum balance would be violated or withdrawal limit exceeded.
 */
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


/**
 * @brief Applies monthly interest to the account.
 * 
 * Calculates interest based on the current balance and the annual interest rate divided by 12.
 * Adds the interest to the balance and records it as an interest transaction.
 */
void SavingAccount::applyMonthlyInterest()
{
    double interest = getAccountBalance() * (interest_rate_ / 12);
    applyDeposit(interest);
    
    // Record as transaction type
    addTransaction(Transaction::INTEREST, interest, std::time(nullptr));
}


/**
 * @brief Resets the count of monthly withdrawals to zero.
 */
void SavingAccount::resetMonthlyWithdrawals()
{
    withdrawal_times_this_month_ = 0;
}


/**
 * @brief Retrieves the minimum balance requirement for the savings account.
 * @return The minimum balance.
 */
double SavingAccount::getMinBalance() const
{
    return min_balance_;
}


/**
 * @brief Retrieves the interest rate for the savings account.
 * @return The interest rate.
 */
double SavingAccount::getInterestRate() const
{
    return interest_rate_;
}


/**
 * @brief Applies interest to the account.
 * 
 * Calculates monthly interest and deposits it into the account balance.
 * Records the interest as a transaction.
 */
void SavingAccount::applyInterest() {
    const double monthly_interest = getAccountBalance() * (getInterestRate() / 12.0);
    applyDeposit(monthly_interest);
    addTransaction(Transaction::INTEREST, monthly_interest, std::time(nullptr));
}