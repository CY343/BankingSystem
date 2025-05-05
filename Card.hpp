#ifndef CARD_HPP
#define CARD_HPP
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<ctime>

class Card{
    private:
        std::string card_number_;
        std::string expiration_;
        std::string cvv_;
        bool isActivated_;
        bool isExpired_;

    protected:
    void setCardNumber(const std::string& number);
    virtual void setExpiration(const std::string& expiration);
    std::string getExpiration() const;
    void setCvv(const std::string& cvv);
    std::string getCvv()const;

    public:
        Card(); 
        Card(const std::string& number, const std::string& expiration, const std::string cvv, const bool isActivated, const bool isExpired);
        bool isActivated() const;
        void setActivated(bool isActivate);
        virtual bool processPayment(double amount) = 0; 
        virtual bool validate() const;
        std::string getCardNumber() const ;
        virtual bool isExpired() const;
        virtual bool checkIfExpired() = 0;


};


#endif