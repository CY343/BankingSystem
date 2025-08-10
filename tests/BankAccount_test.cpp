// BankAccount_test.cpp
#include <gtest/gtest.h>
#include "BankAccount.hpp"
#include <stdexcept>

// Minimal concrete subclass to allow instantiation of BankAccount (because applyInterest is pure virtual)
class TestBankAccount : public BankAccount {
public:
    using BankAccount::BankAccount; // inherit constructors

    void applyInterest() override {
        // Stub: no actual implementation needed for this test
    }
};

// Test suite
TEST(BankAccountTest, InitialBalanceAndAccountNumber) {
    TestBankAccount account1(0, 0, 1000.0, 0.05, "Savings");
    TestBankAccount account2(0, 0, 2000.0, 0.05, "Checking");

    EXPECT_EQ(account1.getAccountBalance(), 1000.0);
    EXPECT_EQ(account2.getAccountBalance(), 2000.0);
    EXPECT_NE(account1.getAccountNumber(), account2.getAccountNumber()); // Different account numbers
}

TEST(BankAccountTest, DepositWorks) {
    TestBankAccount account(0, 0, 1000.0, 0.05, "Savings");

    EXPECT_TRUE(account.applyDeposit(500.0));
    EXPECT_DOUBLE_EQ(account.getAccountBalance(), 1500.0);

    // Depositing zero or negative amount should fail
    EXPECT_FALSE(account.applyDeposit(0));
    EXPECT_FALSE(account.applyDeposit(-100));
}

TEST(BankAccountTest, WithdrawWorks) {
    TestBankAccount account(0, 0, 1000.0, 0.05, "Savings");

    EXPECT_TRUE(account.applyWithdraw(400.0));
    EXPECT_DOUBLE_EQ(account.getAccountBalance(), 600.0);

    // Withdraw negative amount throws invalid_argument
    EXPECT_THROW(account.applyWithdraw(-10.0), std::invalid_argument);

    // Withdraw more than balance throws runtime_error
    EXPECT_THROW(account.applyWithdraw(2000.0), std::runtime_error);
}

TEST(BankAccountTest, LowBalanceFlag) {
    TestBankAccount account(0, 0, 600.0, 0.05, "Savings");
    EXPECT_FALSE(account.isLowBalance());

    // Withdraw to get below low balance threshold (500.0)
    account.applyWithdraw(200.0);
    EXPECT_TRUE(account.isLowBalance());

    // Deposit to get above threshold again
    account.applyDeposit(200.0);
    EXPECT_FALSE(account.isLowBalance());
}


