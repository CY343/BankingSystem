#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#include<vector>
#include<iostream>
#include<string>
#include<ctime>

class Transaction{
    public:
        enum Type {DEPOSIT, WITHDRAW, INTEREST, FEE, PURCHASE};
        Transaction();
        Transaction(Type type, double amount, time_t timestamp);
        Type getType() const ;
        double getAmount() const;
        time_t getTimeStamp() const;
        std::string toString() const;

    private:  
        Type type_;
        double amount_;
        long timestamp_;
    
};

#endif