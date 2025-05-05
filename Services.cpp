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


bool Services::closeAccount(int account_number)
{
    /* delete account by looking for its account number
       return false if not found.
     */
   auto it = std::find_if(all_accounts_.begin(), all_accounts_.end(), [account_number](const std::shared_ptr<BankAccount>& acc)
   {
    return acc->getAccountNumber() == account_number;
   });

   if(it == all_accounts_.end()) {return false;}

    all_accounts_.erase(it);
    return true;
    
}

