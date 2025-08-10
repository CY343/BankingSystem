
#ifndef SAVINGACCOUNT_HPP
#define SAVINGACCOUNT_HPP

#include "BankAccount.hpp"
#include <iostream>
#include <string>

/**
 * @class SavingAccount
 * @brief Represents a savings account, derived from BankAccount,
 *        with minimum balance requirements and limited monthly withdrawals.
 */
class SavingAccount : public BankAccount
{
private:
    double min_balance_;               ///< Minimum required balance
    int withdrawal_times_this_month_; ///< Number of withdrawals this month
    double interest_rate_;             ///< Interest rate for the savings account

public:
    // Default constructor
    SavingAccount();

    // Constructor initializing balance and interest rate
    SavingAccount(double initial_balance, double interest_rate);

    // Constructor with account number, balance, and customerId
    SavingAccount(int accountNumber, double balance, const std::string& customerId);

    // Override withdraw method to enforce min balance and withdrawal limit
    bool applyWithdraw(const double& amount) override;

    // Apply monthly interest
    void applyMonthlyInterest();

    // Reset monthly withdrawal count
    void resetMonthlyWithdrawals();

    // Get minimum balance requirement
    double getMinBalance() const;

    // Get interest rate
    double getInterestRate() const;

    // Apply interest (override)
    void applyInterest() override;

    // Get number of withdrawals this month
    int getWithdrawalTimesThisMonth() const;
};

#endif // SAVINGACCOUNT_HPP
