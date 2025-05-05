#include"Transaction.hpp"
#include<ctime>
#include<iomanip>
#include<sstream>

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

std::string Transaction::toString() const
{
    std::tm* ptm = std::localtime(&timestamp_);
    char buffer[32];
    std::strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);
    return std::string(buffer) + " - " + (type_ == DEPOSIT ? "Deposit: $": "Withdraw: $") + std::to_string(amount_);
            

}