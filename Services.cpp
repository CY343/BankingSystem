#include"Services.hpp"
#include<algorithm>


Services::Services(){};

Services::~Services() {
    for (Customers* cust : customers_) {
        delete cust; // Manually free memory
    }
}


bool Services::addCustomers(const std::vector<Customers*>& NewCustomers)
{
    customers_.insert(customers_.end(), NewCustomers.begin(), NewCustomers.end());
    return true;
}

const std::vector<Customers*>& Services::getCustomers() const
{
    return customers_;
}

bool Services::deleteCustomers(const std::vector<Customers*>& CustomersToDelete)
{
    if(customers_.empty() || CustomersToDelete.empty())
    {
        return false;
    }

    std::unordered_set<Customers*> toDeleteSet(CustomersToDelete.begin(), CustomersToDelete.end());
    
    bool removeAny = false;
    auto it = customers_.begin();
    while(it != customers_.end())
    {
        if(toDeleteSet.find(*it) != toDeleteSet.end())
        {
            delete *it;
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
    BankAccount* newAccount = new BankAccount();
    accounts_.push_back(newAccount);
    return true;
}

void Services::issueCreditCardToCustomers(Customers *customers, BankAccount* account, const std::string &cardNumber, const std::string &expiration, const std::string &cvv, double creditLimit, bool isActivated)
{
    if(!customers)
    {
        std:: cout << "Error: invaild " << std::endl;
        return;
    }

    auto accounts = customers->getAccount();
    if(accounts.empty())
    {
        std::cerr << "Error: Customer has no linked account" << std::endl;
        return;
    }

    accounts[0]->addCreditCard(cardNumber, expiration, cvv, creditLimit, isActivated);
    
}
