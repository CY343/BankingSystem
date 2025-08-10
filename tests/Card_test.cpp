// Card_test.cpp
#include <gtest/gtest.h>
#include "TestCard.hpp"

// Test default constructor
TEST(CardTest, DefaultConstructor) {
    TestCard card;
    EXPECT_EQ(card.getCardNumber(), "NONE");
    EXPECT_EQ(card.getTestExpiration(), "NONE");
    EXPECT_EQ(card.getTestCvv(), "None");
    EXPECT_FALSE(card.isActivated());
    EXPECT_FALSE(card.isExpired());
}

// Test parameterized constructor
TEST(CardTest, ParameterizedConstructor) {
    TestCard card(true, false);
    EXPECT_TRUE(card.isActivated());
    EXPECT_FALSE(card.isExpired());
}

// Test setActivated and isActivated
TEST(CardTest, Activation) {
    TestCard card;
    card.setActivated(true);
    EXPECT_TRUE(card.isActivated());
    card.setActivated(false);
    EXPECT_FALSE(card.isActivated());
}

// Test validate with empty/default card
TEST(CardTest, ValidateFailsForDefaultCard) {
    TestCard card;
    EXPECT_FALSE(card.validate());
}

// Test markExpired behavior
TEST(CardTest, MarkExpired) {
    TestCard card(true, false);
    card.markExpired();
    EXPECT_TRUE(card.isExpired());
    EXPECT_FALSE(card.isActivated());
    EXPECT_EQ(card.getTestExpiration(), "00/00");
}

// Test generateExpiryDate format
TEST(CardTest, ExpiryDateFormat) {
    std::string expiry = TestCard::generateTestExpiryDate(2);
    EXPECT_EQ(expiry.length(), 5);
    EXPECT_EQ(expiry[2], '/');
}

// Test generateCVV
TEST(CardTest, CVVFormat) {
    std::string cvv = TestCard::generateTestCVV();
    EXPECT_EQ(cvv.length(), 3);
    int cvv_num = std::stoi(cvv);
    EXPECT_GE(cvv_num, 100);
    EXPECT_LE(cvv_num, 999);
}

// Test expiration logic (mocked expiration date)
TEST(CardTest, ExpiredCardCheck) {
    TestCard card(true, false);
    card.markExpired(); // sets expiration to "00/00"
    EXPECT_TRUE(card.isExpired());
}
