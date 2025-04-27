#include "Customers.hpp"
#include "BankAccount.hpp"
#include "CreditCard.hpp"
#include "Services.hpp"

int main()
{
    // Create some customers
    std::shared_ptr<Customers> customer1 = std::make_shared<Customers>("Alice", "alice@example.com", "", 30);
    std::shared_ptr<Customers> customer2 = std::make_shared<Customers>("Bob", "bob@example.com", "1987654321", 40);

    // Display customer details
    customer1->display();
    customer2->display();

    // Create a BankAccount for Alice
    std::shared_ptr<BankAccount> aliceAccount = std::make_shared<BankAccount>(1000.0, 200.0, 800.0,5.0, 101);
    customer1->linkAccount(aliceAccount); // Linking account to Alice

    // Create Credit Card for Alice
    std::shared_ptr<CreditCard> aliceCreditCard = std::make_shared<CreditCard>("1234-5678-9876-5432", "12/24", "123", 5000.0, true);
    std::vector<std::shared_ptr<CreditCard>> aliceCards = {aliceCreditCard};
    customer1->setCreditCard(aliceCards); // Assign credit card to Alice

    // Create BankAccount for Bob
    std::shared_ptr<BankAccount> bobAccount = std::make_shared<BankAccount>(500.0, 100.0, 400.0, 3.0, 102);
    customer2->linkAccount(bobAccount); // Linking account to Bob
    
    // Create Credit Card for Bob
    std::shared_ptr<CreditCard> bobCreditCard = std::make_shared<CreditCard>("4321-8765-5678-1234", "11/23", "321", 3000.0, true);
    std::vector<std::shared_ptr<CreditCard>> bobCards = {bobCreditCard};
    customer2->setCreditCard(bobCards); // Assign credit card to Bob

    // Check if the credit card is activated.
    std::cout << "Is Bob's credit card activated? " << (bobCreditCard->isActivated() ? "Yes" : "No") << std::endl;

    // Issue a Credit Card using Services class
    Services bankService;
    bankService.issueCreditCardToCustomers(customer1, aliceAccount, "5678-1234-4321-8765", "10/25", "456", 8000.0, true);

    // Print customers again to see changes
    customer1->display();
    customer2->display();

    // Show account balances
    std::cout << "Alice's account balance: " << aliceAccount->getAccountBalance() << std::endl;
    std::cout << "Bob's account balance: " << bobAccount->getAccountBalance() << std::endl;

    // Withdraw money from Alice's account
    aliceAccount->applyWithdraw(150.0);
    std::cout << "Alice's account balance after withdrawal: " << aliceAccount->getAccountBalance() << std::endl;

    // Deposit money into Bob's account
    bobAccount->applyDeposit(50.0);
    std::cout << "Bob's account balance after deposit: " << bobAccount->getAccountBalance() << std::endl;

    // Check if customers have credit cards
    std::cout << "Does Alice have a credit card? " << (customer1->hasCreditCard() ? "Yes" : "No") << std::endl;
    std::cout << "Does Bob have a credit card? " << (customer2->hasCreditCard() ? "Yes" : "No") << std::endl;
    
    // Check if low balance
    std::cout << "Does Bob have a low balance? " << (bobAccount->isLowBalance() ? "Yes" : "No") << std::endl;
    return 0;
}
