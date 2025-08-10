#include "Customers.hpp"
#include "SavingAccount.hpp"
#include "CheckingAccount.hpp"
#include <gtest/gtest.h>


// Helper for creating a basic SavingAccount
std::shared_ptr<SavingAccount> createSaving(double balance = 1000.0) {
    return std::make_shared<SavingAccount>(balance, 0.01); // interest rate = 1%
}

// Helper for creating a basic CheckingAccount
std::shared_ptr<CheckingAccount> createChecking(double balance = 1000.0) {
    return std::make_shared<CheckingAccount>(balance);
}

// Test default constructor
TEST(CustomersTest, DefaultConstructor) {
    Customers c;
    EXPECT_EQ(c.getName(), "");
    EXPECT_EQ(c.getEmail(), "");
    EXPECT_EQ(c.getPhoneNumber(), "");
    EXPECT_EQ(c.getAge(), 0);
    EXPECT_EQ(c.getAddress(), "");
    EXPECT_FALSE(c.hasCreditCard());
    EXPECT_TRUE(c.getAccount().empty());
    EXPECT_TRUE(c.getCreditCard().empty());
}

// Test parameterized constructor and accessors
TEST(CustomersTest, ParameterizedConstructor) {
    Customers c("John Doe", "john@example.com", "1234567890", 30, "123 Test Ave");
    EXPECT_EQ(c.getName(), "JOHN DOE"); // assuming setName uppercases
    EXPECT_EQ(c.getEmail(), "JOHN@EXAMPLE.COM");
    EXPECT_EQ(c.getPhoneNumber(), "1234567890");
    EXPECT_EQ(c.getAge(), 30);
    EXPECT_EQ(c.getAddress(), "123 TEST AVE");
}

// Test setting name with invalid input
TEST(CustomersTest, SetNameInvalid) {
    Customers c;
    EXPECT_FALSE(c.setName("John123"));  // Invalid due to digits
    EXPECT_FALSE(c.setName(""));         // Empty
    EXPECT_FALSE(c.setName("   "));      // Only spaces
}

// Test setting valid name
TEST(CustomersTest, SetNameValid) {
    Customers c;
    EXPECT_TRUE(c.setName("Jane Smith"));
    EXPECT_EQ(c.getName(), "JANE SMITH");
}

// Test email validation
TEST(CustomersTest, SetEmail) {
    Customers c;
    EXPECT_TRUE(c.setEmail("test@domain.com"));
    EXPECT_EQ(c.getEmail(), "TEST@DOMAIN.COM");

    EXPECT_FALSE(c.setEmail("invalid-email"));
    EXPECT_EQ(c.getEmail(), "TEST@DOMAIN.COM");  // Should remain unchanged
}

// Test phone number
TEST(CustomersTest, SetPhoneNumber) {
    Customers c;
    EXPECT_TRUE(c.setPhoneNumber("9876543210"));
    EXPECT_EQ(c.getPhoneNumber(), "9876543210");

    EXPECT_FALSE(c.setPhoneNumber("abc"));
}

// Test age validation
TEST(CustomersTest, SetAge) {
    Customers c;
    EXPECT_TRUE(c.setAge(25));
    EXPECT_EQ(c.getAge(), 25);

    EXPECT_FALSE(c.setAge(-5));
}

// Test address
TEST(CustomersTest, SetAddress) {
    Customers c;
    std::string address = "456 Nowhere Blvd";
    EXPECT_TRUE(c.setAddress(address));
    EXPECT_EQ(c.getAddress(), "456 NOWHERE BLVD");
}

// Test link account and getSavingAccount / getCheckingAccount
TEST(CustomersTest, LinkAndGetAccounts) {
    Customers c;

    auto s1 = createSaving();
    auto c1 = createChecking();
    c.linkAccount(s1);
    c.linkAccount(c1);

    auto saving = c.getSavingAccount();
    auto checking = c.getCheckingAccount();

    EXPECT_EQ(saving.size(), 1);
    EXPECT_EQ(checking.size(), 1);
}

// Test remove account by number
TEST(CustomersTest, RemoveAccount) {
    Customers c;
    auto acc = createChecking();
    int acc_num = acc->getAccountNumber();
    c.linkAccount(acc);

    EXPECT_TRUE(c.removeAccount(acc_num));
    EXPECT_FALSE(c.removeAccount(acc_num)); // already removed
}


