#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP
#include <vector>
#include <iostream>
#include <string>
#include <memory>

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
    int account_number_;
    std::vector<std::shared_ptr<CreditCard>> creditCards_;
    std::shared_ptr<DebitCard> debitCard_;
    // std::vector<Transaction*> transaction_;

public:
    BankAccount();
    BankAccount(const double &deposit, const double &withdrawal, const double &account_balance, const double &earning_interest_rate, const int &account_number);
    double getDeposit() const;
    bool setDeposit(const double &deposit);
    double getWithdrawal() const;
    bool setWithdrawal(const double &withdrawal);
    double getAccountBalance() const;
    void setLowBalance();
    bool isLowBalance() const;
    double getInterestRate() const;
    bool setEarningInterestRate(const double &interest_rate);
    bool applyDeposit(const double &amount);
    bool applyWithdraw(const double &amount);
    void addCreditCard(const std::string &credit_card_num, const std::string &expiration_date, const std::string &cvv_num, double creditLimit, bool isActivated, std::shared_ptr<BankAccount> account, const bool isExpired);
    int getAccountNumber() const;
};

#endif