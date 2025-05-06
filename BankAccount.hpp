#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include"Transaction.hpp"
/**
 * @brief forward declaration
 */
class CreditCard;
class DebitCard;

/**
 * @brief Bankaccount class is the base class for all bank accounts
 *        - Manages account balance
 *        - Tracks transactions (deposits/withdrawals)
 *        - Auto-generates account numbers (for security)
 *        - Handle interest rate 
 *        - Enforces low balance check  
 */       
class BankAccount
{
private:
    double deposit_; // A double corresponding to the deposit of BankAccount
    double withdrawal_; // A double corresponding to the withdrawal of BankAccount
    double account_balance_; // A double corresponding to the balance of BankAccount
    bool hasLowBalance_; // A flag respresenting account that has low balance
    const int account_number_; // A const integer corresponding to account number of BankAccount



    /**
     * @brief A shared pointer to a DebitCard associated with this BankAccount
     *      - Manage ownership of debit card linked to this account using
     *        shared ownership semantics. Automatically handles memory deallocation
     *        when no longer reference
     *      - Nullptr indicates no debit card issued
     *      - Exclusive to checking accounts in proper banking practice
     *      - Requires validation before transaction processing
     */
    std::shared_ptr<DebitCard> debitCard_; 



    /**
     * @brief A vector containing the transaction history of the BankAccount
     *        Chronological record of all the financial activities including:
     *        - Deposits
     *        - Withdrawals
     *        - Interest accruals
     *        - Fee assessments
     */
    std::vector<Transaction> transactions_;


    static int next_account_number_; // A static integer tracking the next available unique account number generated for BankAccount


    /**
     * @brief Sets the hasLowBalance_ flag based on the current account_balance
     *        Typically used to mark the account as having a low balance if it falls below a predefined threshold
     */
    void setLowBalance(); 
                        
protected:
    double interest_rate_; // A protected double attribute corresponding the interest rate of BankAccount

public:
    /**
     * @brief Default constructor for the BankAccount class.
     * 
     * Initializes a BankAccount object with default values for deposit, withdrawal,
     * account balance, and other associated attributes.
     */
    BankAccount();

        /**
     * @brief Parameterized constructor for the BankAccount class.
     * 
     * @param deposit The initial deposit amount for the account.
     * @param withdrawal The initial withdrawal amount for the account.
     * @param account_balance The starting balance of the account.
     * @param interest_rate The interest rate applied to the account.
     * 
     * Initializes a BankAccount object with specified values for deposit, withdrawal,
     * balance, and interest rate.
     */
    BankAccount(const double &deposit, const double &withdrawal, const double &account_balance, const double &interest_rate);

    /**
     * @brief Retrieves unique account identifier(account number)
     * 
     * @return Int permanent account number assgined during account creation
     */
    int getAccountNumber() const;

    /**
     * @brief Retrieves the current account balance
     * 
     * @return The current account balance (double)
     */
    double getAccountBalance() const;

    /**
     * @brief Retrieves the Interest Rate for the account
     * 
     * @return The interest rate applied to this account (double)
     */
    double getInterestRate() const;


    /**
     * @brief Checks if the account has a low balance.
     * 
     * @return true if the account balance is considered low, false otherwise.
     */
    bool isLowBalance() const;

     /**
     * @brief Sets the earning interest rate for the bank account.
     * 
     * @param interest_rate The new interest rate to be set.
     * @return true if the interest rate was successfully set, false otherwise.
     */
    bool setEarningInterestRate(const double &interest_rate);
    
    /**
     * @brief Applies a deposit for the account
     * 
     * @param amount 
     * @return True if deposit was successful, otherwise false
     */
    bool applyDeposit(const double &amount);

    /**
     * @brief Applies a withdrawal for the account
     * 
     * @param amount 
     * @return True if withdrawal was successful, false otherwise
     */
    virtual bool applyWithdraw(const double &amount);

    /**
     * @brief Add a transaction record to the bank account
     * 
     * @param type (e.g., Deposit, withdrawal)
     * @param amount (the amount involved in the transaction)
     * @param timestamp (The time when the transaction occurs)
     */
    void addTransaction(Transaction::Type type, double amount, time_t timestamp);
};

#endif