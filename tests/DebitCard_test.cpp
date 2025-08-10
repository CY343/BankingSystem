#include "gtest/gtest.h"
#include "DebitCard.hpp"
#include "CheckingAccount.hpp"
#include <memory>


class DebitCardTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a CheckingAccount with $1000 balance
        linked_account = std::make_shared<CheckingAccount>(
            0.0, 0.0, 0.0, 500.0, 0.0  // <-- Initially zero balance, change to 0.0 here
        );
        // Explicitly set balance to 1000 after construction if constructor doesn't do it
        linked_account->setAccountBalance(1000.0);

        // Default DebitCard (inactive, no linked account)
        default_card = std::make_shared<DebitCard>();

        // Custom DebitCard with linked account, withdrawal limit and valid PIN
        custom_card = std::make_shared<DebitCard>(linked_account, 500.0, "1234");
    }

    std::shared_ptr<CheckingAccount> linked_account;
    std::shared_ptr<DebitCard> default_card;
    std::shared_ptr<DebitCard> custom_card;
};


// --- Constructor Tests ---
TEST_F(DebitCardTest, DefaultConstructorInitializesCorrectly) {
    EXPECT_FALSE(default_card->isActivated());
    EXPECT_FALSE(default_card->checkIfExpired());
    EXPECT_EQ(default_card->getDailyWithdrawalLimit(), 0.0);
    EXPECT_EQ(default_card->getDailySpendAmount(), 0.0);
    EXPECT_FALSE(default_card->isContactlessEnabled());
    EXPECT_TRUE(default_card->getLinkedAccount().expired());
}

TEST_F(DebitCardTest, ParameterizedConstructorInitializesCorrectly) {
    EXPECT_TRUE(custom_card->isActivated());
    EXPECT_EQ(custom_card->getDailyWithdrawalLimit(), 500.0);
    EXPECT_EQ(custom_card->getDailySpendAmount(), 0.0);
    EXPECT_TRUE(custom_card->isContactlessEnabled());
    EXPECT_FALSE(custom_card->getLinkedAccount().expired());
}

// --- PIN Setting and Validation ---
TEST_F(DebitCardTest, SetPinValidLengthReturnsTrue) {
    EXPECT_TRUE(default_card->setPin("1234"));
    EXPECT_TRUE(default_card->setPin("123456"));  // max length
}

TEST_F(DebitCardTest, SetPinInvalidLengthReturnsFalse) {
    EXPECT_FALSE(default_card->setPin("123"));
    EXPECT_FALSE(default_card->setPin("1234567"));
}

// --- Change PIN ---
TEST_F(DebitCardTest, ChangePinSucceedsWithCorrectOldPin) {
    EXPECT_TRUE(custom_card->changePin("1234", "5678"));
    EXPECT_TRUE(custom_card->verifyPin("5678"));
}

TEST_F(DebitCardTest, ChangePinFailsWithWrongOldPin) {
    EXPECT_FALSE(custom_card->changePin("0000", "5678"));
}

// --- Process Payment ---
TEST_F(DebitCardTest, ProcessPaymentFailsIfInactive) {
    EXPECT_FALSE(default_card->processPayment(100.0));
}

TEST_F(DebitCardTest, ProcessPaymentFailsIfNoAccount) {
    default_card->setActivated(true);
    EXPECT_FALSE(default_card->processPayment(100.0));
}

TEST_F(DebitCardTest, ProcessPaymentFailsIfInsufficientBalance) {
    custom_card->setActivated(true);
    EXPECT_FALSE(custom_card->processPayment(1500.0));  // more than 1000 balance
}

TEST_F(DebitCardTest, ProcessPaymentSucceedsIfValid) {
    custom_card->setActivated(true);
    EXPECT_TRUE(custom_card->processPayment(500.0));
    // Optionally check linked_account balance decreased if getter exists:
    // EXPECT_EQ(linked_account->getAccountBalance(), 500.0);
}

// --- Validate ---
TEST_F(DebitCardTest, ValidateFailsIfNoPinOrLimit) {
    EXPECT_FALSE(default_card->validate());
}

TEST_F(DebitCardTest, ValidatePassesWithPinAndLimit) {
    EXPECT_TRUE(custom_card->validate());
}

// --- Contactless Payment ---
TEST_F(DebitCardTest, ContactlessEnableToggleWorks) {
    custom_card->enableContactless(false);
    EXPECT_FALSE(custom_card->isContactlessEnabled());
    custom_card->enableContactless(true);
    EXPECT_TRUE(custom_card->isContactlessEnabled());
}

// --- PIN Verification and Lockout ---
TEST_F(DebitCardTest, VerifyPinReturnsTrueIfCorrect) {
    EXPECT_TRUE(custom_card->verifyPin("1234"));
}

TEST_F(DebitCardTest, VerifyPinReturnsFalseIfWrong) {
    EXPECT_FALSE(custom_card->verifyPin("0000"));
}

TEST_F(DebitCardTest, CardLocksAfterThreeFailedAttempts) {
    custom_card->setActivated(true);
    EXPECT_FALSE(custom_card->verifyPin("0000")); // fail 1
    EXPECT_FALSE(custom_card->verifyPin("1111")); // fail 2
    EXPECT_FALSE(custom_card->verifyPin("2222")); // fail 3 -> card locked

    EXPECT_FALSE(custom_card->verifyPin("1234")); // should fail because card locked
    EXPECT_FALSE(custom_card->isActivated());    // card should be deactivated
}
