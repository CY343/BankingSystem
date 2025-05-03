#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#include<vector>
#include<iostream>
#include<string>
#include<ctime>

class Transaction{
    public:
        enum Type {DEPOSIT, WITHDRAW};
        Transaction();
        Transaction(Type type, double amount, time_t tamestamp);
        Type getType() const ;
        double getAmount() const;
        time_t getTimeStamp() const;

    private:  
        Type type_;
        double amount_;
        time_t timestamp_;
    
};

#endif