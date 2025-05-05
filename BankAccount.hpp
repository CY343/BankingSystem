#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include"Transaction.hpp"

class CreditCard;
class DebitCard;


class BankAccount
{
private:
    double deposit_;
    double withdrawal_;
    double account_balance_;
    bool hasLowBalance_;
    double earning_interest_rate_;
    const int account_number_;
    std::vector<std::shared_ptr<CreditCard>> creditCards_;
    std::shared_ptr<DebitCard> debitCard_;
    std::vector<Transaction> transactions_;

    static int next_account_number_;
    void setLowBalance();

public:
    BankAccount();
    BankAccount(const double &deposit, const double &withdrawal, const double &account_balance, const double &earning_interest_rate);
    double getDeposit() const;
    bool setDeposit(const double &deposit);
    double getWithdrawal() const;
    bool setWithdrawal(const double &withdrawal);
    double getAccountBalance() const;
    bool isLowBalance() const;
    double getInterestRate() const;
    bool setEarningInterestRate(const double &interest_rate);
    bool applyDeposit(const double &amount);
    virtual bool applyWithdraw(const double &amount);
    void addCreditCard(const std::string &credit_card_num, const std::string &expiration_date, const std::string &cvv_num, double creditLimit, bool isActivated, std::shared_ptr<BankAccount> account, const bool isExpired);
    int getAccountNumber() const;
    void addTransaction(Transaction::Type type, double amount, time_t timestamp);
};

#endif