#include "CreditCard.hpp"
#include"BankAccount.hpp"
#include <iostream>
#include <string>

/**
 * @brief Default constructor for CreditCard.
 * 
 * Initializes the credit card with zero credit limit and balance,
 * and calls the base Card constructor with default inactive states.
 */
CreditCard::CreditCard():Card( false, false), 
                         credit_limit_(0.0),
                         current_balance_(0.0),
                         linked_account(){}

 /**
 * @brief Constructs a CreditCard with specified credit limit, activation status, and linked bank account.
 * 
 * Initializes the card with a BIN prefix "5" (e.g., Visa), sets the credit limit and current balance,
 * and links it to the provided BankAccount. The activation status is set via setActivated().
 * 
 * @param credit_limit The credit limit for this credit card.
 * @param isActivated Whether the card is initially activated.
 * @param linked_account Shared pointer to the linked BankAccount.
 */
CreditCard::CreditCard(double credit_limit,
                       bool isActivated,
                       std::shared_ptr<BankAccount> linked_account) :
                        Card("5", true),
                        credit_limit_(credit_limit),
                        current_balance_(0.0),
                        linked_account(linked_account)
     {
         setActivated(isActivated);
     }

/**
 * @brief Retrieves the current outstanding balance on the credit card.
 * 
 * @return The current balance owed on the credit card.
 */
double CreditCard::getCurrentBalance() const
{
    return current_balance_;
}


/**
 * @brief Sets the credit limit for the credit card.
 * 
 * @param limit The new credit limit to set.
 * @return true if the limit is valid and successfully set.
 * @throws std::invalid_argument if the limit is negative.
 */
bool CreditCard::setCreditLimit(double limit) 
{
    if (limit < 0)
        throw std::invalid_argument("Credit limit is invalid.");

    credit_limit_ = limit;
    return true;
}


/**
 * @brief Retrieves a weak pointer to the linked bank account.
 * 
 * @return std::weak_ptr<BankAccount> The linked bank account.
 */
std::weak_ptr<BankAccount> CreditCard::getLinkedAccount()
{
    return linked_account;
}

/**
 * @brief Retrieves the credit limit of the credit card.
 * 
 * @return The current credit limit.
 */
double CreditCard::getCreditLimit()const
{
    return credit_limit_;
}


/**
 * @brief Calculates the credit utilization percentage.
 * 
 * Utilization is defined as (current balance / credit limit) * 100.
 * Returns 0 if credit limit or balance is non-positive.
 * 
 * @return The utilization percentage, or 0 if invalid.
 */
double CreditCard::getUtilizationPercentage() const
{
    if (credit_limit_ <= 0 || current_balance_ <= 0) return 0.0;
    return (current_balance_ / credit_limit_) * 100.0;
}

/**
 * @brief Validates the credit card.
 * 
 * Calls the base Card validation and additionally ensures
 * the credit limit is greater than zero.
 * 
 * @return true if the card is valid, false otherwise.
 */
bool CreditCard::validate() const
{
    if(!Card::validate())
    {
        return false;
    }

    return credit_limit_ > 0;
}

bool CreditCard::processPayment(double amount)
{
    return charge(amount);
}


/**
 * @brief Checks if the credit card has expired.
 * 
 * Calls the inherited `isExpired()` method from the base class.
 * 
 * @return true if the card is expired, false otherwise.
 */
bool CreditCard::checkIfExpired()
{
    return isExpired();
}


/**
 * @brief Attempts to charge the credit card a specified amount.
 * 
 * The charge is successful only if the card is activated,
 * the amount is positive, and the new balance does not exceed the credit limit.
 * 
 * @param amount The amount to charge.
 * @return true if the charge was successful, false otherwise.
 */
bool CreditCard::charge(double amount)
{
    if(!isActivated() || amount <= 0 || current_balance_ + amount > credit_limit_)
    {
        return false;
    }
    current_balance_ += amount;
    return true;
}


/**
 * @brief Makes a payment to reduce the current balance on the credit card.
 * 
 * @param amount The payment amount; must be positive.
 * @return true if the payment is accepted, false otherwise.
 */
bool CreditCard::makePayment(double amount)
{
    if(amount <= 0)
    {
        return false;
    }
    current_balance_ -= amount;
    return true;
}

