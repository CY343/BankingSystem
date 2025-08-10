#ifndef DEBITCARD_HPP
#define DEBITCARD_HPP
#include"CheckingAccount.hpp"
#include"SecurityHelper.hpp"
#include"Card.hpp"
#include<iostream>
#include<string>
#include<memory>


class CheckingAccount;
class BankAccount;


/**
 * @class DebitCard
 * @brief Represents a debit card linked to a checking account.
 * 
 * This class manages debit card details including PIN security,
 * daily withdrawal and spend limits, contactless payment settings,
 * and linkage to a CheckingAccount.
 */
class DebitCard : public Card{
    private:
        std::string salt_; ///< Salt used for hashing the PIN.
        std::string pin_hash_; ///< Hashed PIN for secure verification.
        double daily_withdrawal_limit_; ///< Maximum allowed withdrawal per day.
        double daily_spend_amount_; ///< Amount spent so far today.
        bool contactless_enable_; ///< Indicates if contactless payment is enabled.
        mutable int failed_attempts_ = 0; ///< Number of failed PIN attempts (mutable for const methods).
        std::weak_ptr<CheckingAccount> linked_debit_card_account_; /// @brief Debit card linked to a checking account (weak pointer to avoid ownership cycles).
        std::string pin_;
    protected:
        virtual void onPinChange();
    public:
        /**
         * @brief Default constructor for DebitCard.
         */
        DebitCard();

        /**
         * @brief Parameterized constructor.
         * 
         * @param account Shared pointer to the linked CheckingAccount.
         * @param daily_withdrawal_limit The daily withdrawal limit amount.
         * @param pin The initial PIN for the debit card.
         */
        DebitCard(std::shared_ptr<CheckingAccount> account,
                  double daily_withdrawal_limit,
                  const std::string& pin);
        
        /**
         * @brief Gets the daily withdrawal limit.
         * 
         * @return The daily withdrawal limit as a double.
         */        
        double getDailyWithdrawalLimit() const;

        /**
         * @brief Gets the amount spent today.
         * 
         * @return The daily spend amount.
         */
        double getDailySpendAmount() const;

        /**
         * @brief Gets the linked CheckingAccount.
         * 
         * @return Weak pointer to the linked CheckingAccount.
         */
        std::weak_ptr<CheckingAccount> getLinkedAccount() const;

        /**
         * @brief Checks if contactless payments are enabled.
         * 
         * @return True if contactless payments are enabled, false otherwise.
         */
        bool isContactlessEnabled() const;

        /**
         * @brief Enables or disables contactless payments.
         * 
         * @param enable True to enable, false to disable.
         */
        void enableContactless(bool enable);

        /**
         * @brief Sets the daily spend amount.
         * 
         * @param amount The new daily spend amount.
         * @return True if set successfully.
         */
        bool SetDailySpendAmount(const double& amount);

        /**
         * @brief Sets the daily withdrawal limit.
         * 
         * @param limit The new daily withdrawal limit.
         * @return True if set successfully.
         */
        bool SetDailyWithdrawalLimit(const double& limit);

        /**
         * @brief Sets the PIN (hashed and salted internally).
         * 
         * @param pin The new PIN as a string.
         * @return True if the PIN was set successfully.
         */
        bool setPin(const std::string pin);

         /**
         * @brief Changes the PIN after verifying the old PIN.
         * 
         * @param old_pin The current PIN.
         * @param new_pin The new PIN to set.
         * @return True if the PIN was changed successfully.
         */
        bool changePin(const std::string old_pin, const std::string new_pin );
        
        /**
         * @brief Processes a payment (overrides Card::processPayment).
         * 
         * @param amount The payment amount.
         * @return True if the payment was successful.
         */
        bool processPayment(double amount) override;

        /**
         * @brief Validates the debit card's state.
         * 
         * @return True if the card is valid.
         */
        bool validate() const override;

        /**
         * @brief Checks if the debit card has expired.
         * 
         * @return True if the card is expired.
         */
        virtual bool checkIfExpired() override;

        /**
         * @brief Verifies the PIN against the stored hash.
         * 
         * @param attempt The PIN attempt string.
         * @return True if the PIN matches, false otherwise.
         */
        bool verifyPin(const std::string& attempt) const;

        
        std::string generateCardNumberWithPrefix(const std::string& prefix);


        std::string getPin() const;
};






#endif