#include"Card.hpp"

Card::Card():card_number_("NONE"), expiration_("NONE"), cvv_("None"), isActivated_(false), isExpired_(false){}

Card::Card(const std::string& number, const std::string& expiration, const std::string cvv, const bool isActivated, const bool isExpired):
card_number_(number), expiration_(expiration), cvv_(cvv), isActivated_(isActivated), isExpired_(isExpired){}


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

bool Card::isExpired() const
{
    // GET CURRENT DATE
    time_t t = time(0); // CURRENT TIME
    struct tm* now = localtime(&t);
    
    int expiredMonth;
    int expiredYear;
    std::sscanf(expiration_.c_str(), "%2d/%2d", &expiredMonth, &expiredYear);
    expiredYear += 2000; // adjusting for YY to YYYY

    // CHECK IF CARD EXPIRED
    if(expiredYear < (now->tm_year + 1900)) {return true;} // EXPIRED IF YEAR LESS THAN 
    // EXPIRED IF SAME YEAR BUT MONTH LESS
    else if (expiredYear == (now->tm_year + 1900) && expiredMonth < (now->tm_mon +1)) {return true;}

    return false;
}

void Card::setExpiration(const std::string &expiration)
{
    std::regex patten(R"(^(0[1-9]1[0-2])\/\d{2}$)");

    if(std::regex_match(expiration, patten))
    {
        expiration_ = expiration;
    }
    else
    {
        std::cout << "INVLID EXPIRATION DATE! " << std::endl;
    }
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
