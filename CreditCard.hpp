#ifndef CREDITCARD_HPP
#define CREDITCARD_HPP
#include<iostream>
#include<string>
#include"Card.hpp"

class CreditCard: public Card{
    private:
        double credit_limit_;
        
    public:
        CreditCard();
        CreditCard(const std::string& credit_card_number, const std::string& expiration, const std::string& cvv, const bool& isActivated, const double& credit_limit);
        ~CreditCard();
        double getCreditLimit()const;
        bool setCreditLimit(double& limit);
        virtual bool validate() const override;
        virtual bool processPayment(double amount) override;
};
#endif