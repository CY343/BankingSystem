#ifndef SAVINGACCOUNT_HPP
#define SAVINGACCOUNT_HPP
#include"BankAccount.hpp"
#include<iostream>
#include<string>



/**
 * @class SavingAccount
 * @brief Represents a savings account, derived from BankAccount, 
 *        with minimum balance requirements and limited monthly withdrawals.
 */
class SavingAccount: public BankAccount
{
    private:
        /**
         * @brief The minimum balance required to maintain the savings account.
         */
        double min_balance_;

        /**
         * @brief Number of withdrawals made from the account this month.
         */
        int withdrawal_times_this_month_;

    public:
        /**
         * @brief Default constructor for SavingAccount.
         */
        SavingAccount();

        /**
         * @brief Parameterized constructor for SavingAccount.
         * @param deposit The initial deposit amount.
         * @param withdrawal The initial withdrawal amount.
         * @param account_balance The initial account balance.
         * @param interest_rate The interest rate for the account.
         * @param min_balance The minimum balance required.
         * @param withdrawal_times Number of withdrawals already made this month.
         */
        SavingAccount(const double &deposit, 
                      const double &withdrawal, 
                      const double &account_balance, 
                      const double &interest_rate, 
                      double min_balance, 
                      int withdrawal_times);
         /**
         * @brief Attempts to withdraw a specified amount from the account.
         * @param amount The amount to withdraw.
         * @return True if the withdrawal is successful, false otherwise.
         */
        bool applyWithdraw(const double& amount)override;

        /**
         * @brief Applies monthly interest to the account balance.
         */
        void applyMonthlyInterest();

         /**
         * @brief Resets the count of monthly withdrawals to zero.
         */
        void resetMonthlyWithdrawals();

        /**
         * @brief Retrieves the minimum balance requirement for the account.
         * @return The minimum balance.
         */
        double getMinBalance() const;

        /**
         * @brief Retrieves the interest rate for the account.
         * @return The interest rate.
         */
        double getInterestRate() const;

        /**
         * @brief Applies interest to the account balance.
         */
        void applyInterest() override;



};



#endif