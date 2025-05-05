#ifndef SAVINGACCOUNT_HPP
#define SAVINGACCOUNT_HPP
#include"BankAccount.hpp"
#include<iostream>
#include<string>

class SavingAccount: public BankAccount
{
    private:
        double min_balance_;
        int withdrawal_times_this_month_;

    public:
        SavingAccount();
        SavingAccount(const double &deposit, const double &withdrawal, const double &account_balance, const double &interest_rate, double min_balancen, int withdrawal_times);
        bool applyWithdraw(const double& amount)override;

        void applyMonthlyInterest();
        void resetMonthlyWithdrawals();

        double getMinBalance() const;
        double getInterestRate() const;
        



};



#endif