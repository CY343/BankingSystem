#include "gtest/gtest.h"
#include "CreditCard.hpp"
#include "CheckingAccount.hpp" // concrete BankAccount subclass
#include <memory>
#include <stdexcept>

class CreditCardTest : public ::testing::Test {
protected:
    void SetUp() override {
        linked_account = std::make_shared<CheckingAccount>(
            0.0,    // overdraft limit
            0.0,    // monthly maintenance fee
            0.0,    // minimum balance waiver
            1000.0  // initial balance
        );

        default_card = std::make_shared<CreditCard>();
        custom_card = std::make_shared<CreditCard>(5000.0, true, linked_account);

        // Set valid card details for validation and expiry tests
        SetValidCardFields(custom_card);
    }

    void SetValidCardFields(std::shared_ptr<CreditCard> card) {
        card->setCardNumber("5123456789012345");  // Example valid card number
        card->setExpiration("12/30");              // Future expiration date (MM/YY)
        card->setCvv("123");                        // Example CVV
    }

    std::shared_ptr<CheckingAccount> linked_account;
    std::shared_ptr<CreditCard> default_card;
    std::shared_ptr<CreditCard> custom_card;
};

// --- Constructor Tests ---
TEST_F(CreditCardTest, DefaultConstructorSetsDefaults) {
    EXPECT_EQ(default_card->getCreditLimit(), 0.0);
    EXPECT_EQ(default_card->getCurrentBalance(), 0.0);
    EXPECT_TRUE(default_card->getLinkedAccount().expired()); // no linked account
}

TEST_F(CreditCardTest, ParameterizedConstructorSetsValues) {
    EXPECT_EQ(custom_card->getCreditLimit(), 5000.0);
    EXPECT_EQ(custom_card->getCurrentBalance(), 0.0);
    EXPECT_FALSE(custom_card->getLinkedAccount().expired());
}

// --- Credit Limit Tests ---
TEST_F(CreditCardTest, SetCreditLimitValid) {
    EXPECT_TRUE(default_card->setCreditLimit(2000.0));
    EXPECT_EQ(default_card->getCreditLimit(), 2000.0);
}

TEST_F(CreditCardTest, SetCreditLimitNegativeThrows) {
    EXPECT_THROW(default_card->setCreditLimit(-500.0), std::invalid_argument);
}

// --- Utilization Tests ---
TEST_F(CreditCardTest, UtilizationZeroWhenNoBalanceOrLimit) {
    EXPECT_EQ(custom_card->getUtilizationPercentage(), 0.0);
}

TEST_F(CreditCardTest, UtilizationCalculatedCorrectly) {
    custom_card->setActivated(true);
    custom_card->charge(1000.0);
    EXPECT_DOUBLE_EQ(custom_card->getUtilizationPercentage(), (1000.0 / 5000.0) * 100.0);
}

// --- Charge Tests ---
TEST_F(CreditCardTest, ChargeFailsIfInactive) {
    EXPECT_FALSE(default_card->charge(100.0));
    EXPECT_EQ(default_card->getCurrentBalance(), 0.0);
}

TEST_F(CreditCardTest, ChargeFailsIfAmountNonPositive) {
    custom_card->setActivated(true);
    EXPECT_FALSE(custom_card->charge(0.0));
    EXPECT_FALSE(custom_card->charge(-50.0));
}

TEST_F(CreditCardTest, ChargeFailsIfOverLimit) {
    custom_card->setActivated(true);
    EXPECT_FALSE(custom_card->charge(6000.0));
}

TEST_F(CreditCardTest, ChargeSucceedsIfValid) {
    custom_card->setActivated(true);
    EXPECT_TRUE(custom_card->charge(1500.0));
    EXPECT_EQ(custom_card->getCurrentBalance(), 1500.0);
}

// --- Payment Tests ---
TEST_F(CreditCardTest, PaymentFailsIfNonPositive) {
    EXPECT_FALSE(custom_card->makePayment(0.0));
    EXPECT_FALSE(custom_card->makePayment(-100.0));
}

TEST_F(CreditCardTest, PaymentReducesBalance) {
    custom_card->setActivated(true);
    custom_card->charge(1000.0);
    EXPECT_TRUE(custom_card->makePayment(200.0));
    EXPECT_EQ(custom_card->getCurrentBalance(), 800.0);
}

// --- ProcessPayment Tests ---
TEST_F(CreditCardTest, ProcessPaymentDelegatesToCharge) {
    custom_card->setActivated(true);
    EXPECT_TRUE(custom_card->processPayment(300.0));
    EXPECT_EQ(custom_card->getCurrentBalance(), 300.0);
}

// --- Validate Tests ---
TEST_F(CreditCardTest, ValidateFailsIfBaseCardInvalid) {
    EXPECT_FALSE(default_card->validate()); // default card not activated / limit 0
}

TEST_F(CreditCardTest, ValidatePassesIfBaseValidAndLimitPositive) {
    custom_card->setActivated(true);
    EXPECT_TRUE(custom_card->validate());
}

// --- Expiry Tests ---
TEST_F(CreditCardTest, CheckIfExpiredUsesBaseCard) {
    EXPECT_FALSE(custom_card->checkIfExpired());
}
