#include "BankAccount.hpp"
#include "CreditCard.hpp"
#include <iostream> 
#include <string>

// A static integer to generate unique account numbers for each bank account
// Starts at 1000 and increments with each new account created
int BankAccount::next_account_number_ = 1000;

/**
 * @brief Default constructor for the BankAccount class
 *        Initializes deposit_, withdrawal_, account_balance_ to 0.0
 *        Automatically assigns a unique account number by incrementing the static next_account_number_
 */
BankAccount::BankAccount():deposit_(0.0), withdrawal_(0.0),account_balance_(0.0),
 account_number_(next_account_number_++){}

/**
 * @brief Parameterized constructor for the BankAccount class
 * 
 * @param deposit Initial deposit amount
 * @param withdrawal Initial withdrawal amount
 * @param account_balance Initial account balance
 * @param interest_rate Initial interest rate
 * 
 * Initializes the BankAccount with provided values, assigns a unique
 * account number by incrementing next_account_number_, and calls
 * setLowBalance() to update the low balance flag based on the initial balance
 */
BankAccount::BankAccount(const double &deposit, const double &withdrawal, const double &account_balance, const double &interest_rate)
    : deposit_(deposit), withdrawal_(withdrawal), account_balance_(account_balance),account_number_(next_account_number_++), interest_rate_(interest_rate)
    {
        setLowBalance();
    }

/**
 * @brief Retrieves the account balance for the bank account
 * 
 * @return account_balance_ as a double
 */
double BankAccount::getAccountBalance() const
{
    return account_balance_;
}

/**
 * @brief Deposit a specific amount into the bank account
 * 
 * Adds the given amount to the account balance, record a deposit transaction,
 * and update the low balance status
 * 
 * @param a const reference amount 
 * @return ture if deposit was successful, false if the amount is invalid
 */
bool BankAccount::applyDeposit(const double &amount)
{
    if (amount <= 0)
    {
        return false;
    }
    account_balance_ += amount;
    transactions_.emplace_back(Transaction::DEPOSIT, amount, std::time(nullptr));
    setLowBalance();
    return true;
}

/**
 * @brief Withdraw a specific amount from the bank account
 * 
 * Subtracts the given amount from the account balance if sufficient funds exist,
 * records a withdrawal transaction, and update the low balance status
 * 
 * @param a const reference amount. The amount to withdraw. 
 * Must be greater than 0 and less than or equal to current balance
 * 
 * @return true if withdrawal was successful, false if the amount is invalid or insufficient funds
 */
bool BankAccount::applyWithdraw(const double &amount)
{
    if (amount <= 0 || account_balance_ < amount)
    {
        return false;
    }
    account_balance_ -= amount;
    transactions_.emplace_back(Transaction::WITHDRAW, amount, std::time(nullptr));
    setLowBalance();
    return true;
}


/**
 * @brief Retrieves account number for the bank account
 * 
 * @return account_number_ as a int
 */
int BankAccount::getAccountNumber() const
{

    return account_number_;
}

/**
 * @brief Set the low balance flag_ for the bank account
 * 
 * This function checks if the account balance is below the threshold (500.0)
 * and update the hasLowBalance() accordingly
 * 
 */
void BankAccount::setLowBalance()
{   
    hasLowBalance_ = (account_balance_ < 500.0);
    
}

/**
 * @brief Checks if the account has a low balance
 * 
 * This function returns whether the account balance is below the threshold (500.0)
 * It uses 'hasLowBalance_' flag to determine the status
 *
 * @return True if the account balance is below the threshold, false otherwise
 */
bool BankAccount::isLowBalance() const
{
    return hasLowBalance_;
}

/**
 * @brief Retrieves the interest rate for the bank account
 * 
 * @return interest_rate_ as a double
 */
double BankAccount::getInterestRate() const
{
    return interest_rate_;
}

/**
 * @brief Sets the interest rate for the bank account
 * 
 * This function allows you to set a new interest rate for the bank account
 * The interest rate can be used for calculations related to interest earned on the account balance
 * @param a const double reference interes_rate 
 * 
 * @return True if the interest rate was successfully updated, false otherwise 
 */
bool BankAccount::setEarningInterestRate(const double &interes_rate)
{
    interest_rate_ = interes_rate;
    return true;
}

/**
 * @brief Adds a transaction record to the bank account
 * 
 * This function records a transaction of a specific type (e.g., deposit or withdrawal),
 * the transaction amount, the time its occurred. The transaction is then stored in 
 * the account's transaction record
 * 
 * @param type 
 * @param amount 
 * @param timestamp 
 */
void BankAccount::addTransaction(Transaction::Type type, double amount, time_t timestamp)
{   

    transactions_.emplace_back(type, amount, timestamp);
    
}