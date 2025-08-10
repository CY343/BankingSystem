#include "Services.hpp"
#include <algorithm>
#include <stdexcept>
#include <random>
#include <unordered_set>
#include <iostream>

// Custom hash and equality for shared_ptr<Customers> based on customer ID
struct CustomerPtrHash {
    size_t operator()(const std::shared_ptr<Customers>& c) const {
        return std::hash<std::string>()(c->getCustomerId());
    }
};

struct CustomerPtrEqual {
    bool operator()(const std::shared_ptr<Customers>& lhs, const std::shared_ptr<Customers>& rhs) const {
        return lhs->getCustomerId() == rhs->getCustomerId();
    }
};

// Generate a random 4-digit PIN string
static std::string generateRandomPIN() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, 9);

    std::string pin;
    for (int i = 0; i < 4; ++i) {
        pin += std::to_string(dist(gen));
    }
    return pin;
}

Services::Services() {}

bool Services::addCustomers(const std::vector<std::shared_ptr<Customers>>& NewCustomers) {
    customers_.insert(customers_.end(), NewCustomers.begin(), NewCustomers.end());
    return true;
}

const std::vector<std::shared_ptr<Customers>>& Services::getCustomers() const {
    return customers_;
}

bool Services::deleteCustomers(const std::vector<std::shared_ptr<Customers>>& CustomersToDelete) {
    if(customers_.empty() || CustomersToDelete.empty()) {
        return false;
    }

    std::unordered_set<std::shared_ptr<Customers>, CustomerPtrHash, CustomerPtrEqual> toDeleteSet(
        CustomersToDelete.begin(), CustomersToDelete.end()
    );
    
    bool removeAny = false;
    auto it = customers_.begin();
    while(it != customers_.end()) {
        if(toDeleteSet.find(*it) != toDeleteSet.end()) {
            it = customers_.erase(it);
            removeAny = true;
        } else {
            ++it;
        }
    }
    return removeAny;
}

bool Services::closeAccount(int account_number) {
    bool unlinked = false;
    for (auto& customer : customers_) {
        std::cout << "Checking customer " << customer->getName() << std::endl;
        if (customer->removeAccount(account_number)) {
            std::cout << "Unlinked account " << account_number << " from customer.\n";
            unlinked = true;
        }
    }
    if (!unlinked) {
        std::cerr << "Account #" << account_number << " not found in any customer profiles\n";
        return false;
    }

    auto it = std::find_if(all_accounts_.begin(), all_accounts_.end(),
        [account_number](const auto& acc) {
            return acc->getAccountNumber() == account_number;
        }
    );
    
    if (it == all_accounts_.end()) {
        std::cerr << "Account #" << account_number << " not found in system registry\n";
        return false;
    }

    all_accounts_.erase(it);
    return true;
}


bool Services::processTransaction(std::shared_ptr<BankAccount> account, Transaction::Type type, double amount) {
    try {
        if(type == Transaction::DEPOSIT) {
            account->applyDeposit(amount);
        } else {
            account->applyWithdraw(amount);
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Transaction failed: " << e.what() << "\n";
        return false;
    }
}

std::shared_ptr<Card> Services::replaceCard(std::shared_ptr<Card> old_card) {
    if (!old_card || !old_card->validate()) return nullptr;

    // Deactivate old card
    old_card->setActivated(false);
    old_card->markExpired();  // Mark as expired

    // Create new card with same properties but generate random PIN
    if (auto debit = std::dynamic_pointer_cast<DebitCard>(old_card)) {
        auto account = debit->getLinkedAccount().lock();
        if (!account) return nullptr;
        
        auto new_debit = std::make_shared<DebitCard>(
            account,
            debit->getDailyWithdrawalLimit(),
            generateRandomPIN()
        );
        return new_debit;
    }
    else if (auto credit = std::dynamic_pointer_cast<CreditCard>(old_card)) {
        auto account = credit->getLinkedAccount().lock();
        if (!account) return nullptr;

        auto new_credit = std::make_shared<CreditCard>(
            credit->getCreditLimit(),
            true,
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

const std::vector<std::shared_ptr<BankAccount>>& Services::getAllAccounts() const
{
    return all_accounts_;
}

bool Services::addAccount(std::shared_ptr<BankAccount> account) 
{
    all_accounts_.push_back(account);
    return true;
}