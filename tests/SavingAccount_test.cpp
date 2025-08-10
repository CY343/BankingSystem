#include "gtest/gtest.h"
#include "SavingAccount.hpp"
#include <memory>
#include <stdexcept>

class SavingAccountTest : public ::testing::Test {
protected:
    std::unique_ptr<SavingAccount> account;

    void SetUp() override {
        account = std::make_unique<SavingAccount>(500.0, 0);
        account->applyDeposit(2000.0);  // Deposit some initial balance
    }
};

// Test initial state
TEST_F(SavingAccountTest, InitialValuesAreCorrect) {
    EXPECT_DOUBLE_EQ(account->getMinBalance(), 500.0);
    EXPECT_EQ(account->getWithdrawalTimesThisMonth(), 0);
    EXPECT_DOUBLE_EQ(account->getAccountBalance(), 2000.0);
}

// Test successful withdrawal under limits
TEST_F(SavingAccountTest, ApplyWithdrawSucceedsWithinLimits) {
    EXPECT_NO_THROW({
        bool result = account->applyWithdraw(100.0);
        EXPECT_TRUE(result);
    });
    EXPECT_EQ(account->getWithdrawalTimesThisMonth(), 1);
    EXPECT_DOUBLE_EQ(account->getAccountBalance(), 1900.0);
}

// Test withdrawal below minimum balance throws
TEST_F(SavingAccountTest, ApplyWithdrawFailsIfBelowMinBalance) {
    EXPECT_THROW(account->applyWithdraw(1600.0), std::runtime_error);
}

// Test withdrawal limit exceeded throws
TEST_F(SavingAccountTest, ApplyWithdrawFailsIfWithdrawalLimitExceeded) {
    // Simulate 6 withdrawals already done
    for (int i = 0; i < 6; ++i) {
        account->applyWithdraw(10.0);
    }
    EXPECT_THROW(account->applyWithdraw(10.0), std::runtime_error);
}

// Test reset monthly withdrawals resets count
TEST_F(SavingAccountTest, ResetMonthlyWithdrawalsWorks) {
    account->applyWithdraw(100.0);
    EXPECT_EQ(account->getWithdrawalTimesThisMonth(), 1);
    account->resetMonthlyWithdrawals();
    EXPECT_EQ(account->getWithdrawalTimesThisMonth(), 0);
}

// Test apply monthly interest increases balance correctly
TEST_F(SavingAccountTest, ApplyMonthlyInterestIncreasesBalance) {
    double oldBalance = account->getAccountBalance();
    double interest = oldBalance * (account->getInterestRate() / 12.0);

    account->applyMonthlyInterest();

    EXPECT_NEAR(account->getAccountBalance(), oldBalance + interest, 0.01);
}

// Test apply interest method (alias)
TEST_F(SavingAccountTest, ApplyInterestIncreasesBalance) {
    double oldBalance = account->getAccountBalance();
    double interest = oldBalance * (account->getInterestRate() / 12.0);

    account->applyInterest();

    EXPECT_NEAR(account->getAccountBalance(), oldBalance + interest, 0.01);
}

