#ifndef CREDITCARD_HPP
#define CREDITCARD_HPP
#include<iostream>
#include<string>
#include<vector>

class CreditCard{
    private:
        std::string credit_card_number_;
        std::string expiration_;
        std::string cvv_;
        double credit_limit_;
        bool isActivated_;

    public:
        CreditCard();
        CreditCard(const std::string& credit_card_number, const std::string& expiration, const std::string& cvv, double& credit_limit,bool isActivated);
        ~CreditCard();
        std::string getCreditCardNum()const;
        std::string getExpiration()const;
        std::string getCvv()const;
        double getCreditLimit()const;
        bool isActivated()const;

        bool setCreditLimit(double& limit);
        void setActivated(bool isActivate);
};












#endif