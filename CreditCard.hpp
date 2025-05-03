#ifndef CREDITCARD_HPP
#define CREDITCARD_HPP
#include<iostream>
#include<string>
#include<memory>
#include"Card.hpp"

class BankAccount;

class CreditCard: public Card{
    private:
        double credit_limit_;
        std::weak_ptr<BankAccount> linked_credit_card_account;
    public:
        CreditCard();
        CreditCard(const std::string& number, const std::string& expiration, const std::string& cvv, const bool& isActivated, const double& credit_limit,std::shared_ptr<BankAccount> account, const bool isExpired);
        double getCreditLimit()const;
        bool setCreditLimit(double limit);
        std::weak_ptr<BankAccount> getLinkedAccount();
        virtual bool validate() const override;
        virtual bool processPayment(double amount) override;
        virtual bool checkIfExpired() override;

};
#endif