#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#include<vector>
#include<iostream>
#include<string>
#include<ctime>

class Transaction{
    public:
        enum Type {DEPOSIT, WITHDRAWAL, INTEREST, FEE, PURCHASE, UNKNOWN};
        Transaction();
        Transaction(const std::string &accountNumber, Type type, double amount, time_t timestamp);
        Transaction(Type type, double amount, time_t timestamp) :
        type_(type), amount_(amount), timestamp_(timestamp) {}
        Type getType() const ;
        double getAmount() const;
        time_t getTimeStamp() const;
        std::string toString() const;
        std::string getAccountNumber() const;
        static std::string stringToType(Type type);
        static Type stringToType(const std::string& str);

    private:  
        std::string accountNumber_;
        Type type_;
        double amount_;
        long timestamp_;
    
};

#endif