
#ifndef CUSTOMERS_HPP
#define CUSTOMERS_HPP
#include<iostream>
#include<string>
#include<memory>
#include<vector>
#include<regex>
#include"SavingAccount.hpp"
#include"CheckingAccount.hpp"

class BankAccount;
class CreditCard;


class Customers{
    private:
        std::string customers_name_;
        std::string customers_email_;
        std::string customers_phone_number_;
        int customers_age_;
        std::vector<std::shared_ptr<BankAccount>> account_; // customers can hold any types of accounts (saving or checking, both)
        std::vector<std::shared_ptr<CreditCard>> creditCard_;

    public:
        Customers();
        Customers(const std::string& name, const std::string& email, const std::string& phone_number, int age);
        std::string getName() const;
        bool setName(const std::string& name);
        std::string getEmail()const;
        bool setEmail(const std::string& email);
        std::string getPhoneNumber()const;
        bool setPhoneNumber(const std::string& phone_number);
        int getAge() const;
        bool setAge(const int age);
        void display() const;
        void linkAccount(std::shared_ptr<BankAccount> account);
        const std::vector<std::shared_ptr<BankAccount>>& getAccount() const;
        void setCreditCard(std::vector<std::shared_ptr<CreditCard>>& card);
        bool hasCreditCard()const;
        std::vector<std::shared_ptr<CreditCard>>& getCreditCard();
        std::vector<std::shared_ptr<SavingAccount>> getSavingAccount() const;
        std::vector<std::shared_ptr<CheckingAccount>> getCheckingAccount() const;
        
};
#endif
