#include"Services.hpp"
#include<algorithm>


Services::Services(){};

Services::~Services() = default;



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

bool Services::openAccount()
{
    std::shared_ptr<BankAccount> newAccount = std::make_shared<BankAccount>();
    accounts_.push_back(newAccount);
    return true;
}

bool Services::closeAccount(size_t index)
{
   if(index >= accounts_.size())
   {
    return false;
   }
   accounts_.erase(accounts_.begin() + index);
   return true;
    
}

void Services::issueCreditCardToCustomers(std::shared_ptr<Customers> customers, std::shared_ptr<BankAccount> account, const std::string &cardNumber, const std::string &expiration, const std::string &cvv, double creditLimit, bool isActivated)
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

    accounts[0]->addCreditCard(cardNumber, expiration, cvv, creditLimit, isActivated, account);
    
}
