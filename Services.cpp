#include"Services.hpp"
#include<algorithm>
#include <stdexcept>


Services::Services(){};


bool Services::addCustomers(const std::vector<std::shared_ptr<Customers>>& NewCustomers)
{
    customers_.insert(customers_.end(), NewCustomers.begin(), NewCustomers.end());
    return true;
}

const std::vector<std::shared_ptr<Customers>>& Services::getCustomers() const
{
    return customers_;
}

bool Services::deleteCustomers(const std::vector<std::shared_ptr<Customers>>& CustomersToDelete)
{
    if(customers_.empty() || CustomersToDelete.empty())
    {
        return false;
    }

    std::unordered_set<std::shared_ptr<Customers>> toDeleteSet(CustomersToDelete.begin(), CustomersToDelete.end());
    
    bool removeAny = false;
    auto it = customers_.begin();
    while(it != customers_.end())
    {
        if(toDeleteSet.find(*it) != toDeleteSet.end())
        {
            it = customers_.erase(it);
            removeAny = true;
        }
        else
            ++it;
    }

        return removeAny;
   
}

std::shared_ptr<BankAccount> Services::openAccount(std::shared_ptr<Customers> customer)
{
    if(customer->getAge() < 18)
    {
        throw std::invalid_argument("Customers must be at least 18 years old.");
    }
    std::shared_ptr<BankAccount> newAccount = std::make_shared<BankAccount>();
    accounts_.push_back(newAccount);
    return newAccount;
}

bool Services::closeAccount(int account_number)
{
    /* delete account by looking for its account number
       return false if not found.
     */
   auto it = std::find_if(accounts_.begin(), accounts_.end(), [account_number](const std::shared_ptr<BankAccount>& acc)
   {
    return acc->getAccountNumber() == account_number;
   });

   if(it == accounts_.end()) {return false;}

    accounts_.erase(it);
    return true;
    
}

void Services::issueCreditCardToCustomers(std::shared_ptr<Customers> customers, std::shared_ptr<BankAccount> account, const std::string &cardNumber, const std::string &expiration, const std::string &cvv, double creditLimit, bool isActivated, const bool isExpired)
{
    if(!customers)
    {
        std:: cout << "Error: invalid " << std::endl;
        return;
    }

    auto accounts = customers->getAccount();
    if(!account)
    {
        std::cerr << "Error: Customer has no linked account" << std::endl;
        return;
    }

    accounts[0]->addCreditCard(cardNumber, expiration, cvv, creditLimit, isActivated, account, isExpired);
    
}

/* issue a debit card to customer */

std::shared_ptr<SavingAccount> Services::openSavingAccount(std::shared_ptr<Customers> customer, double min_balance, double interest_rate)
{
    if((customer->getAge()) < 18)
    {
        throw std::invalid_argument("Customers must be at least 18 years old.");
    }

    auto new_account = std::make_shared<SavingAccount> (min_balance, interest_rate);
    accounts_.push_back(new_account);

    //Link to a customer
    customer->linkAccount({new_account});
    return new_account;
}