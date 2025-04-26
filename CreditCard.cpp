#include "CreditCard.hpp"
#include<iostream>
#include<string>

CreditCard::CreditCard()
{
     credit_card_number_ = "NONE";
     expiration_ = "NONE";
     cvv_ = "NONE";
     credit_limit_ = 0;
     isActivated_ = false;
}

CreditCard::CreditCard(const std::string &credit_card_number, const std::string &expiration, const std::string &cvv, double &credit_limit, bool isActivated)
:credit_card_number_(credit_card_number), expiration_(expiration), cvv_(cvv), credit_limit_(credit_limit), isActivated_(isActivated) {}

CreditCard::~CreditCard() {}

std::string CreditCard::getCreditCardNum() const
{
    return credit_card_number_;
}

std::string CreditCard::getExpiration() const
{
    return expiration_;
}

std::string CreditCard::getCvv() const
{
    return cvv_;
}

double CreditCard::getCreditLimit() const
{
    return credit_limit_;
}

bool CreditCard::isActivated()const
{
    return isActivated_;
}

void CreditCard::setActivated(bool isActivated)
{
    isActivated_ = isActivated;
}

bool CreditCard::setCreditLimit(double& limit)
{
    if(limit >= 0)
    {
        credit_limit_ = limit;
        return true;
    }
     else
         throw std:: invalid_argument("Credit limit is invaild. ");
}