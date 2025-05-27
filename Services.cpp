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

void Services::processTransaction(std::shared_ptr<BankAccount> account,  Transaction::Type type,  double amount) {
try {
        if(type == Transaction::DEPOSIT)
     {
        account->applyDeposit(amount);
     }
         else 
         {
             account->applyWithdraw(amount);
         }
                                              } 
        catch(const std::exception& e) 
        {
             std::cerr << "Transaction failed: " << e.what() << "\n";
        // Log to error system
        }
}

std::shared_ptr<Card> Services::replaceCard(std::shared_ptr<Card> old_card) {
    if (!old_card || !old_card->validate()) return nullptr;

    // Deactivate old card
    old_card->setActivated(false);
    old_card->markExpired();  // Mark as expired

    // Create new card with same properties
    if (auto debit = std::dynamic_pointer_cast<DebitCard>(old_card)) {
        auto account = debit->getLinkedAccount().lock();
        if (!account) return nullptr;
        
        auto new_debit = std::make_shared<DebitCard>(
            account,  // Must come first
            debit->getDailyWithdrawalLimit(),
            "0000"  // PIN
            // isActivated defaults to true
        );
        return new_debit;
    }
    else if (auto credit = std::dynamic_pointer_cast<CreditCard>(old_card)) {
        auto account = credit->getLinkedAccount().lock();
        if (!account) return nullptr;

        auto new_credit = std::make_shared<CreditCard>(
            credit->getCreditLimit(),
            true,  // isActivated
            account
        );
        return new_credit;
    }
    return nullptr;
}

void Services::applyMonthlyInterestToAll() {
    for (auto& account : all_accounts_) {
        if (auto savings = std::dynamic_pointer_cast<SavingAccount>(account)) {
            savings->applyInterest();
        }
    }
}

void Services::processMonthlyFees() {
    for (auto& account : all_accounts_) {
        if (auto checking = std::dynamic_pointer_cast<CheckingAccount>(account)) {
            checking->applyMonthlyMaintenanceFee();
        }
    }
}