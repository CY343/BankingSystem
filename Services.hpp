#ifndef SERVICES_HPP
#define SERVICES_HPP
#include<iostream>
#include<vector>
#include"Customers.hpp"
#include"BankAccount.hpp"
#include<unordered_set>
#include"CreditCard.hpp"
#include"SavingAccount.hpp"
#include<memory>

class Services{
    private:
        std::vector<std::shared_ptr<Customers>> customers_;
        std::vector<std::shared_ptr<BankAccount>> all_accounts_;

    public:
        Services();
        bool addCustomers(const std::vector<std::shared_ptr<Customers>>& NewCustomers);
        bool deleteCustomers(const std::vector<std::shared_ptr<Customers>>& CustomersToDelete);

      
        const std::vector<std::shared_ptr<Customers>>& getCustomers() const;

        template<typename T, typename...Args>
        std::shared_ptr<T> openAccount(std::shared_ptr<Customers> customer, Args&&...args)
        {static_assert(std::is_base_of_v<BankAccount, T>, "T must be derived from BankAccount");

            if(customer->getAge() < 18)
            {
                throw std::invalid_argument("Customers must be at least 18 years old.");
            }
            auto new_account = std::make_shared<T>(std::forward<Args>(args)...);
            all_accounts_.push_back(new_account);
            customer->linkAccount(new_account);
            return new_account;
        };

        bool closeAccount(int account_number);
        
    
};


#endif
