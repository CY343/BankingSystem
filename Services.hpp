#ifndef SERVICES_HPP
#define SERVICES_HPP
#include<iostream>
#include<string>
#include<vector>
#include"Customers.hpp"
#include"BankAccount.hpp"
#include<unordered_set>
#include"CreditCard.hpp"

class Services{
    private:
        std::vector<Customers*> customers_;
        std::vector<BankAccount*> accounts_;

    public:
        Services();
        ~Services();
        bool addCustomers(const std::vector<Customers*>& NewCustomers);
        bool deleteCustomers(const std::vector<Customers*>& CustomersToDelete);
        const std::vector<Customers*>& getCustomers() const;
        bool openAccount();
        void issueCreditCardToCustomers(Customers* customers, BankAccount* account, const std::string& cardNumber, const std::string& expiration, const std::string& cvv, double creditLimit, bool isActivated);


    
};


#endif