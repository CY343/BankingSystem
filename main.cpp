/* #include <iostream>
#include <memory>
#include "Card.hpp"
#include "CreditCard.hpp"
#include "DebitCard.hpp"
#include "BankAccount.hpp"
#include "Customers.hpp"
#include "Services.hpp"

void testCard() {
    std::cout << "\n=== TESTING CARD BASE CLASS ===\n";
    // Can't instantiate Card directly (abstract), but test through derived classes
    std::cout << "Card is abstract - tested via CreditCard/DebitCard\n";
}

void testCreditCard() {
    std::cout << "\n=== TESTING CREDIT CARD ===\n";
    
    // Test constructor
    auto account1 = std::make_shared<CheckingAccount>(); // create a checking account with a credit card
    auto cc = std::make_shared<CreditCard>("4111111111111111", "12/25", "123", true, 5000.0, account1, false);
    
    // Test getters
    std::cout << "Card Number: " << cc->getCardNumber() << "\n";
    std::cout << "Credit Limit: $" << cc->getCreditLimit() << "\n";
    std::cout << "Activated: " << (cc->isActivated() ? "Yes" : "No") << "\n";
    
    // Test validation
    std::cout << "Valid: " << (cc->validate() ? "Yes" : "No") << "\n";
    
    // Test payment processing
    std::cout << "Process $100 payment: " 
              << (cc->processPayment(100.0) ? "Success" : "Failed") << "\n";
    
    // Activate and retest
    cc->setActivated(true);
    std::cout << "After activation - Process $100 payment: " 
              << (cc->processPayment(100.0) ? "Success" : "Failed") << "\n";

    // Test limit change
    try {
        cc->setCreditLimit(3000.0);
        std::cout << "New limit set to $" << cc->getCreditLimit() << "\n";
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void testDebitCard() {
    std::cout << "\n=== TESTING DEBIT CARD ===\n";
    
    // Create bank account first
    auto account = std::make_shared<CheckingAccount>();
    account->applyDeposit(1000.0);
    
    // Test constructor
    auto dc = std::make_shared<DebitCard>("5222222222222222", "06/26", "456", true, 
                                        1000.0, 0.0, "2345", true, account, false);
    
                                      
    std::cout << "Is the card expired ? " << (dc->checkIfExpired() ? "Yes" : "No") << std::endl;
    // Test getters
    std::cout << "Card Number: " << dc->getCardNumber() << "\n";
    std::cout << "Daily Limit: $" << dc->getDailyWithdrawalLimit() << "\n";
    std::cout << "Linked Account Balance: $" 
              << dc->getLinkedAccount().lock()->getAccountBalance() << "\n";
    std::cout << "Daily Spend Amount: $" << dc->getDailySpendAmount() << std::endl;

    // Test payment processing
    std::cout << "Process $200 payment: " 
              << (dc->processPayment(200.0) ? "Success" : "Failed") << "\n";
    std::cout << "New Balance: $" 
              << dc->getLinkedAccount().lock()->getAccountBalance() << "\n";
    
    // Test PIN change
    std::cout << "Change PIN (2345->7770): " 
              << (dc->changePin("2345", "7770") ? "Success" : "Failed") << "\n";
    std::cout << "Wrong PIN change attempt: " 
              << (dc->changePin("90909", "0000") ? "Success" : "Failed") << "\n";

}

void testBankAccount() {
    std::cout << "\n=== TESTING BANK ACCOUNT ===\n";
    
    auto account = std::make_shared<BankAccount>();
    
    // Test deposits
    account->applyDeposit(500.0);
    std::cout << "Balance after $500 deposit: $" << account->getAccountBalance() << "\n";
    
    // Test withdrawals
    std::cout << "Withdraw $200: " 
              << (account->applyWithdraw(200.0) ? "Success" : "Failed") << "\n";
    std::cout << "Balance: $" << account->getAccountBalance() << "\n";
    
    // Test low balance
    std::cout << "Low Balance: " << (account->isLowBalance() ? "Yes" : "No") << "\n";
    
}

void testCustomer() {
    std::cout << "\n=== TESTING CUSTOMER ===\n";
    
    auto customer = std::make_shared<Customers>("John Doe", "john@example.com", "1555123456", 30);
    
    // Test display
    customer->display();
    
    // Test account linking
    auto account = std::make_shared<BankAccount>();
    account->applyDeposit(1500.0);
    customer->linkAccount({account});
    
    std::cout << "Linked Account Balance: $" 
              << customer->getAccount()[0]->getAccountBalance() << "\n";
    
    // Test credit card
    std::vector<std::shared_ptr<CreditCard>> cards;
    cards.push_back(std::make_shared<CreditCard>("4111111111111111", "12/25", "123", true, 5000.0, account, false));
    customer->setCreditCard(cards);

    
    std::cout << "Has Credit Card: " << (customer->hasCreditCard() ? "Yes" : "No") << "\n";
}

void testServices() {
    std::cout << "\n=== TESTING SERVICES ===\n";
    
    Services bankServices;
    
    // Create customers
    auto customer1 = std::make_shared<Customers>("Alice", "alice@bank.com", "1555111222", 28);
    auto customer2 = std::make_shared<Customers>("Bob", "bob@bank.com", "1555333444", 35);
    
    // Test adding customers
    std::vector<std::shared_ptr<Customers>> newCustomers = {customer1, customer2};
    bankServices.addCustomers(newCustomers);
    std::cout << "Customer Count: " << bankServices.getCustomers().size() << "\n";
    
    // Test account opening (checking account)
    auto acc1 = bankServices.openAccount<CheckingAccount>(customer1);
    // Test account closing
    bankServices.closeAccount(1);
    // Test credit card issuance
    auto account = std::make_shared<BankAccount>();
    account->applyDeposit(2000.0);
    customer1->linkAccount({account});
    
    
    // Test customer deletion
    std::vector<std::shared_ptr<Customers>> toDelete = {customer2};
    bankServices.deleteCustomers(toDelete);
    std::cout << "After deletion - Customer Count: " 
              << bankServices.getCustomers().size() << "\n";
}

int main() {
    std::cout << "=== BANKING SYSTEM TEST ===\n";
    
   testCard();
    testCreditCard();
    testDebitCard();
    testBankAccount();
    testCustomer();
     testServices(); 
    
    std::cout << "\n=== ALL TESTS COMPLETED ===\n";
    return 0;
} */

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <iostream>

int main() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* conn;

    driver = sql::mysql::get_mysql_driver_instance();
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "wayne970911");

    conn->setSchema("BankingSystem");

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM accounts"));

    while (res->next()) {
        std::cout << "Account Number: " << res->getString("account_number") << std::endl;
    }

    delete conn;
    return 0;
}
