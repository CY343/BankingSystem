#ifndef SERVICES_HPP
#define SERVICES_HPP
#include<iostream>
#include<vector>
#include"Customers.hpp"
#include"BankAccount.hpp"
#include<unordered_set>
#include"CreditCard.hpp"
#include<memory>

class Services{
    private:
        std::vector<std::shared_ptr<Customers>> customers_;
        std::vector<std::shared_ptr<BankAccount>> accounts_;

    public:
        Services();
        ~Services();
        bool addCustomers(const std::vector<std::shared_ptr<Customers>>& NewCustomers);
        bool deleteCustomers(const std::vector<std::shared_ptr<Customers>>& CustomersToDelete);
        const std::vector<std::shared_ptr<Customers>>& getCustomers() const;
        bool openAccount();
        void issueCreditCardToCustomers(std::shared_ptr<Customers> customers, std::shared_ptr<BankAccount> account, const std::string& cardNumber, const std::string& expiration, const std::string& cvv, double creditLimit, bool isActivated);


    
};


#endif