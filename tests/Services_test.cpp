#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <string>

#include "Services.hpp"
#include "Customers.hpp"
#include "SavingAccount.hpp"
#include "CheckingAccount.hpp"
#include "DebitCard.hpp"
#include "CreditCard.hpp"
#include "Transaction.hpp"

// Helper to create a sample customer
std::shared_ptr<Customers> createSampleCustomer() {
    return std::make_shared<Customers>(
        "Alice Smith", 
        "alice@example.com", 
        "555-0001", 
        35, 
        "101 Park Ave"
    );
}

// Helper to create a sample SavingAccount with initial balance and interest
std::shared_ptr<SavingAccount> createSampleSavingAccount() {
    return std::make_shared<SavingAccount>(1000.0, 0.02);  // balance=1000, interest=2%
}

// Helper to create a sample CheckingAccount with initial balance and overdraft limit
std::shared_ptr<CheckingAccount> createSampleCheckingAccount() {
    // Adjust constructor parameters if needed
    return std::make_shared<CheckingAccount>(500.0, 200.0);
}

// Test fixture for Services tests
class ServicesTest : public ::testing::Test {
protected:
    Services services;
    std::shared_ptr<Customers> customer;
    std::shared_ptr<SavingAccount> savingAccount;
    std::shared_ptr<CheckingAccount> checkingAccount;

    void SetUp() override {
        services = Services();

        customer = createSampleCustomer();

        savingAccount = createSampleSavingAccount();
        checkingAccount = createSampleCheckingAccount();

        // Link accounts to customer by their actual account numbers
        customer->addAccount(savingAccount->getAccountNumber());
        customer->addAccount(checkingAccount->getAccountNumber());

        // Add customer and accounts to services
        services.addCustomers({customer});
        services.addAccount(savingAccount);
        services.addAccount(checkingAccount);
    }
};

// Test adding customers and retrieving them
TEST_F(ServicesTest, AddAndGetCustomers) {
    const auto& customers = services.getCustomers();
    ASSERT_EQ(customers.size(), 1);

    // Adjust this check to actual behavior of getName()
    EXPECT_EQ(customers[0]->getName(), "Alice Smith");
}

// Test deleting existing and non-existing customers
TEST_F(ServicesTest, DeleteCustomers) {
    std::vector<std::shared_ptr<Customers>> toDelete = { customer };
    bool deleted = services.deleteCustomers(toDelete);
    EXPECT_TRUE(deleted);

    // Deleting again should fail (already deleted)
    bool deletedAgain = services.deleteCustomers(toDelete);
    EXPECT_FALSE(deletedAgain);

    // Deleting from empty services returns false
    Services emptyServices;
    EXPECT_FALSE(emptyServices.deleteCustomers(toDelete));
}

// Test closing an account that exists and doesn't exist
TEST_F(ServicesTest, CloseAccount) {
    int accNum = savingAccount->getAccountNumber();

    // Close account successfully
    bool closed = services.closeAccount(accNum);
    EXPECT_TRUE(closed);

    // Closing again should fail (account removed)
    bool closedAgain = services.closeAccount(accNum);
    EXPECT_FALSE(closedAgain);

    // Closing a non-existent account returns false
    EXPECT_FALSE(services.closeAccount(999999));
}

// Test deposit and withdrawal transactions
TEST_F(ServicesTest, ProcessTransaction) {
    EXPECT_TRUE(services.processTransaction(savingAccount, Transaction::DEPOSIT, 100.0));
    EXPECT_DOUBLE_EQ(savingAccount->getAccountBalance(), 1100.0);

    EXPECT_TRUE(services.processTransaction(savingAccount, Transaction::WITHDRAWAL, 50.0));
    EXPECT_DOUBLE_EQ(savingAccount->getAccountBalance(), 1050.0);

    // Withdraw more than balance should fail
    EXPECT_FALSE(services.processTransaction(savingAccount, Transaction::WITHDRAWAL, 100000.0));
}

// Test replacing a valid DebitCard
TEST_F(ServicesTest, ReplaceDebitCard) {
    auto debitCard = std::make_shared<DebitCard>(checkingAccount, 500.0, "1234567890123456");
    debitCard->setActivated(true);

    auto newCard = services.replaceCard(debitCard);
    ASSERT_NE(newCard, nullptr);
    EXPECT_NE(newCard->getCardNumber(), debitCard->getCardNumber());
    EXPECT_FALSE(debitCard->isActivated());
    EXPECT_TRUE(newCard->isActivated());
}

// Test replacing a valid CreditCard
TEST_F(ServicesTest, ReplaceCreditCard) {
    auto creditCard = std::make_shared<CreditCard>(10000.0, true, checkingAccount);
    creditCard->setActivated(true);

    auto newCard = services.replaceCard(creditCard);
    ASSERT_NE(newCard, nullptr);
    EXPECT_FALSE(creditCard->isActivated());
    EXPECT_TRUE(newCard->isActivated());
}

// Test applying monthly interest to all savings accounts
TEST_F(ServicesTest, ApplyMonthlyInterestToAll) {
    double oldBalance = savingAccount->getAccountBalance();
    services.applyMonthlyInterestToAll();
    EXPECT_GT(savingAccount->getAccountBalance(), oldBalance);
}

// Test processing monthly fees on checking accounts
TEST_F(ServicesTest, ProcessMonthlyFees) {
    double oldBalance = checkingAccount->getAccountBalance();
    services.processMonthlyFees();
    EXPECT_LT(checkingAccount->getAccountBalance(), oldBalance);
}
