#include"Transaction.hpp"
#include<ctime>
#include<iomanip>
#include<sstream>

Transaction::Transaction():accountNumber_("None"),
                           type_(DEPOSIT), 
                           amount_(0.0), 
                           timestamp_(std::time(nullptr)){}

Transaction::Transaction(const std::string &accountNumber,
                         Type type, 
                         double amount, 
                         time_t timestamp):
                         accountNumber_(accountNumber),
                         type_(type), 
                         amount_(amount), 
                         timestamp_(timestamp){}

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

std::string Transaction:: getAccountNumber() const
{
    return accountNumber_;
}

std::string Transaction::stringToType(Type type)
{
   switch(type)
    {
        case Transaction::DEPOSIT:
            return "DEPOSIT";
        case Transaction::WITHDRAWAL:
            return "WITHDRAWAL";
        case Transaction::INTEREST:
            return "INTEREST";
        case Transaction::FEE:
            return "FEE";
        case Transaction::PURCHASE:
            return "PURCHASE";
        default:
            return "UNKNOWN";
    }

}

Transaction::Type Transaction::stringToType(const std::string &str)
{
    if(str == "DEPOSIT") return DEPOSIT;
    if(str == "WITHDRAWAL") return WITHDRAWAL;
    if(str == "INTEREST") return INTEREST;
    if(str == "FEE") return FEE;
    return UNKNOWN;
}
