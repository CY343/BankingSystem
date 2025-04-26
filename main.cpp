#include"Customers.hpp"
#include "Services.hpp"
#include <iostream>
#include <vector>

int main() {
    Services service;

    // Create a new customer
    Customers* customer = new Customers("Wayne", "wayne@gmail.com", "1234567890", 30);
    std::vector<Customers*> newCustomers = { customer };
    service.addCustomers(newCustomers);

    // Open a bank account
    BankAccount* account = new BankAccount(500.0);  // initial deposit
    std::vector<BankAccount*> accounts = { account };
    customer->linkAccount(accounts);  // link the account to the customer

    // Issue a credit card
    service.issueCreditCardToCustomers(customer, account, "4111111111111111", "12/26", "123", 1000.0, true);

    // Display customer details
    customer->display();

    // Test deposit
    double depositAmount = 200.0;
    if (account->applyDeposit(depositAmount)) {
        std::cout << "Deposit successful. New balance: $" << account->getAccountBalance() << std::endl;
    }

    // Test withdraw
    double withdrawAmount = 100.0;
    if (account->applyWithdraw(withdrawAmount)) {
        std::cout << "Withdrawal successful. New balance: $" << account->getAccountBalance() << std::endl;
    }

    // Clean up manually (to match your raw pointer design)
    delete account;
    delete customer;

    return 0;
}
