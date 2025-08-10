#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include "CheckingAccount.hpp"

class CheckingAccountTest : public ::testing::Test {
protected:
    std::shared_ptr<CheckingAccount> account;

    void SetUp() override {
        // Overdraft limit negative means how far below zero it can go./
        account = std::make_shared<CheckingAccount>(
            -500.0,  // overdraft limit (negative)
            15.0,    // monthly fee
            1000.0,  // waiver balance (fee waived if balance >= this)
            400.0    // daily withdrawal limit
        );
        account->applyDeposit(1000.0);
    }
};

TEST_F(CheckingAccountTest, InitialValues) {
    EXPECT_DOUBLE_EQ(account->getAccountBalance(), 1000.0);
    EXPECT_DOUBLE_EQ(account->getOverdraftLimit(), -500.0);
    EXPECT_DOUBLE_EQ(account->getMonthlyfee(), 15.0);
    EXPECT_DOUBLE_EQ(account->getDailyWithdrawalLimit(), 400.0);
    EXPECT_EQ(account->getMonthlyTransactionCount(), 0);
    EXPECT_FALSE(account->hasOverdraftProtection());
}

TEST_F(CheckingAccountTest, SetOverdraftLimit_ValidNegative) {
    EXPECT_TRUE(account->setOverdraftLimit(-1000.0));
    EXPECT_DOUBLE_EQ(account->getOverdraftLimit(), -1000.0);
}

TEST_F(CheckingAccountTest, SetOverdraftLimit_InvalidPositive) {
    EXPECT_FALSE(account->setOverdraftLimit(100.0));
    EXPECT_DOUBLE_EQ(account->getOverdraftLimit(), -500.0);  // Should remain unchanged
}

TEST_F(CheckingAccountTest, DepositIncreasesBalance) {
    account->applyDeposit(200.0);
    EXPECT_DOUBLE_EQ(account->getAccountBalance(), 1200.0);
}

TEST_F(CheckingAccountTest, WithdrawWithinBalance) {
    EXPECT_TRUE(account->applyWithdraw(500.0));
    EXPECT_DOUBLE_EQ(account->getAccountBalance(), 500.0);
}

TEST_F(CheckingAccountTest, WithdrawWithinOverdraftLimit) {
    // Withdraw more than balance but within overdraft limit (-500)
    EXPECT_TRUE(account->applyWithdraw(1400.0)); // 1000 - 1400 = -400 (allowed)
    EXPECT_DOUBLE_EQ(account->getAccountBalance(), -400.0);
}

TEST_F(CheckingAccountTest, WithdrawBeyondOverdraftLimitFails) {
    EXPECT_FALSE(account->applyWithdraw(1600.0)); // Would exceed overdraft (-500)
    EXPECT_DOUBLE_EQ(account->getAccountBalance(), 1000.0); // Balance unchanged
}

TEST_F(CheckingAccountTest, ConvertToBusinessAccountToggle) {
    // Initially false (personal)
    // You should add a public getter for is_business_account_ in your class, e.g.:
    // bool isBusinessAccount() const { return is_business_account_; }
    // For now, let's assume you add that and test with it:

    // Assuming you added:
    // bool CheckingAccount::isBusinessAccount() const { return is_business_account_; }

    EXPECT_FALSE(account->isBusinessAccount());
    account->convertTOBusinessAccount();
    EXPECT_TRUE(account->isBusinessAccount());
    account->convertTOBusinessAccount();
    EXPECT_FALSE(account->isBusinessAccount());
}

TEST_F(CheckingAccountTest, MonthlyFeeWaivedIfBalanceHighEnough) {
    account->applyMonthlyMaintenanceFee();
    EXPECT_DOUBLE_EQ(account->getAccountBalance(), 1000.0);  // Fee waived
}

TEST_F(CheckingAccountTest, MonthlyFeeAppliedIfBalanceTooLow) {
    account->applyWithdraw(950.0); // Reduce balance to 50
    account->applyMonthlyMaintenanceFee();
    EXPECT_DOUBLE_EQ(account->getAccountBalance(), 35.0);  // 50 - 15 fee
}

TEST_F(CheckingAccountTest, LinkAndUseOverdraftProtection) {
    auto backup = std::make_shared<CheckingAccount>(-200.0, 10.0, 500.0, 300.0);
    backup->applyDeposit(200.0);
    account->linkOverdraftProtection(backup);
    EXPECT_TRUE(account->hasOverdraftProtection());

    // Withdraw amount that requires backup (1600 needs 100 from backup)
    EXPECT_TRUE(account->applyWithdraw(1600.0));
    
    // Main account should be at overdraft limit
    EXPECT_DOUBLE_EQ(account->getAccountBalance(), -500.0);
    
    // Backup account should have provided 100
    EXPECT_DOUBLE_EQ(backup->getAccountBalance(), 100.0);
}
TEST_F(CheckingAccountTest, WithdrawFailsIfBackupInsufficient) {
    // Create backup account with NO overdraft capability
    auto backup = std::make_shared<CheckingAccount>(
        0.0,       // overdraft limit = 0 (no overdraft allowed)
        10.0,       // monthly fee
        500.0,      // waiver balance
        300.0       // daily withdrawal limit
    );
    backup->applyDeposit(50.0);  // Only 50 available (no overdraft)
    account->linkOverdraftProtection(backup);

    // Attempt withdrawal that requires 100 from backup
    EXPECT_FALSE(account->applyWithdraw(1600.0));
    
    // Balances should remain unchanged
    EXPECT_DOUBLE_EQ(account->getAccountBalance(), 1000.0);
    EXPECT_DOUBLE_EQ(backup->getAccountBalance(), 50.0);
}

TEST_F(CheckingAccountTest, AddCreditCardThrowsIfLimitTooHigh) {
    EXPECT_THROW(
        account->addCreditCard(2500.0, true, account),
        std::invalid_argument
    );
}

TEST_F(CheckingAccountTest, AddCreditCardSucceedsWithValidLimit) {
    EXPECT_NO_THROW(
        account->addCreditCard(1500.0, true, account)
    );
}

TEST_F(CheckingAccountTest, IssueDebitCard) {
    // Should not throw and add a debit card
    // (You might add a getter for debit_cards_ or test by side effects)
    EXPECT_NO_THROW(
        account->issueDebitCard()
    );
}

TEST_F(CheckingAccountTest, BlockDebitCard) {
    account->issueDebitCard();
    // Assuming you have a way to get a card number from debit_cards_
    // For this example, just block by a fake card number and expect failure:
    EXPECT_FALSE(account->blockDebitCard("nonexistent_card_number"));
}

