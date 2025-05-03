#include"Transaction.hpp"

Transaction::Transaction():type_(DEPOSIT), amount_(0.0), timestamp_(std::time(nullptr)){}

Transaction::Transaction(Type type, double amount, time_t timestamp):type_(type), amount_(amount), timestamp_(timestamp){}

Transaction::Type Transaction::getType() const
{
    return type_;
}

double Transaction::getAmount() const
{
    return amount_;
}

time_t Transaction::getTimeStamp() const
{
    return timestamp_;
}