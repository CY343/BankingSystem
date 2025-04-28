#include"Card.hpp"

Card::Card():card_number_("NONE"), expiration_("NONE"), cvv_("None"), isActivated_(false){}

Card::Card(const std::string& number, const std::string& expiration, const std::string cvv, const bool isActivated):
card_number_(number), expiration_(expiration), cvv_(cvv), isActivated_(isActivated) {}

Card::~Card() {}

bool Card::isActivated() const
{
    return isActivated_;
}

void Card::setActivated(bool isActivate)
{
    isActivated_ = isActivate;
}

bool Card::validate() const
{
    return (!card_number_.empty() && !expiration_.empty() && !cvv_.empty());
}

void Card::setCardNumber(const std::string& number)
{
    card_number_ = number;
}

std::string Card::getCardNumber() const
{
    return card_number_;
}

void Card::setExpiration(const std::string &expiration)
{
    expiration_ = expiration;
}

std::string Card::getExpiration() const
{
    return expiration_;
}

void Card::setCvv(const std::string &cvv)
{   
    cvv_ = cvv;
}

std::string Card::getCvv() const
{
    return cvv_;
}
