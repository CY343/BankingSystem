#ifndef CREDITCARD_HPP
#define CREDITCARD_HPP
#include<iostream>
#include<string>
#include<memory>
#include"Card.hpp"

class BankAccount;


/**
 * @class CreditCard
 * @brief Represents a credit card linked to a bank account.
 * 
 * Manages credit limit, balance, and interactions with a linked bank account.
 * Inherits from the Card base class.
 */
class CreditCard: public Card{
    private:
        double credit_limit_; ///< Maximum credit allowed on the card
        double current_balance_;  ///< Current outstanding balance on the card
        std::weak_ptr<BankAccount> linked_account; ///< Weak pointer to linked bank account
    public:
        /**
         * @brief Default constructor.
         */
        CreditCard();
        /**
         * @brief Constructs a CreditCard with given parameters.
         * @param credit_limit The credit limit assigned to the card.
         * @param isActivated Initial activation status of the card.
         * @param linked_account Shared pointer to the linked BankAccount.
         */
        CreditCard(double credit_limit,
                   bool isActivated,
                   std::shared_ptr<BankAccount> linked_account);


        // ================= getters =================  

        /**
         * @brief Gets the current outstanding balance.
         * @return The current balance on the credit card.
         */                     
        double getCurrentBalance() const;

        /**
         * @brief Gets the credit limit.
         * @return The credit limit of the card.
         */
        double getCreditLimit()const;

        /**
         * @brief Calculates the utilization percentage of the credit card.
         * @return Credit utilization as a percentage of the credit limit.
         */
        double getUtilizationPercentage() const;


        //==================== setter and other functions ====================

         /**
         * @brief Sets the credit limit.
         * @param limit The new credit limit to set.
         * @return true if the limit is valid and set successfully, false otherwise.
         */
        bool setCreditLimit(double limit);

        /**
         * @brief Retrieves a weak pointer to the linked bank account.
         * @return Weak pointer to the linked BankAccount.
         */
        std::weak_ptr<BankAccount> getLinkedAccount();

        /**
         * @brief Validates the credit card (override from Card).
         * @return true if the card is valid, false otherwise.
         */
        virtual bool validate() const override;

        /**
         * @brief Processes a payment on the credit card (override from Card).
         * @param amount The amount to process.
         * @return true if payment was successful, false otherwise.
         */
        virtual bool processPayment(double amount) override;

        /**
         * @brief Checks if the credit card is expired (override from Card).
         * @return true if expired, false otherwise.
         */
        virtual bool checkIfExpired() override;

         /**
         * @brief Charges a given amount to the credit card.
         * @param amount The amount to charge.
         * @return true if the charge is successful, false if it exceeds the limit.
         */
        bool charge(double amount);

        /**
         * @brief Makes a payment to reduce the balance on the credit card.
         * @param amount The payment amount.
         * @return true if payment is successful, false otherwise.
         */
        bool makePayment(double amount);


};
#endif