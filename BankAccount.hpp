#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP
#include<vector>
#include<iostream>
#include<string>
#include"CreditCard.hpp"

class Customers;


class BankAccount{
    private:
        double deposit_;
        double withdrawal_;
        double account_balance_;
        bool hasLowBalance_;
        double earning_interest_rate_;
        std::vector<Customers*> customers;
        std::vector<CreditCard*> creditCards_;
        // std::vector<Transaction*> transaction_;

    public:
        BankAccount();
        BankAccount(const double& deposit, const double& withdrawal = 0.0, const double& account_balance = 0.0, const bool& hasLowBalance = false, const double& earning_interest_rate = 0.0);
        ~BankAccount();
        double getDeposit()const;
        bool setDeposit(const double& deposit);
        double getWithdrawal()const;
        bool setWithdrawal(const double& withdrawal);
        double getAccountBalance() const;
        void setLowBalance(const bool& flag);
        bool isLowBalance()const;
        double getInterestRate()const;
        bool setEarningInterestRate(const double& interest_rate);
        bool applyDeposit(double& amount);
        bool applyWithdraw(double& amount);
        void addCreditCard(const std::string& credit_card_num, const std::string& expiration_date, const std::string& cvv_num, double& creditLimit, bool& isActivated);






};



#endif