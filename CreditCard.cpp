#include "CreditCard.hpp"
#include <iostream>
#include <string>

CreditCard::CreditCard():Card("None", "None", "None", false), credit_limit_(0){}


CreditCard::CreditCard(const std::string &number, const std::string &expiration, const std::string &cvv, const bool &isActivated, const double &credit_limit)
    : Card(number, expiration, cvv, isActivated), credit_limit_(credit_limit){}

CreditCard::~CreditCard() {}

bool CreditCard::setCreditLimit(double &limit)
{
    if (limit >= 0)
    {
        credit_limit_ = limit;
        return true;
    }
    else
        throw std::invalid_argument("Credit limit is invaild. ");
}

double CreditCard::getCreditLimit()const
{
    return credit_limit_;
}

bool CreditCard::validate() const
{
    if(!Card::validate())
    {
        return false;
    }

    return credit_limit_ > 0;
}

bool CreditCard::processPayment(double amount)
{
    if(!isActivated() || amount > credit_limit_)
    {
        return false;
    }

    return true;
}
