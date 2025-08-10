#ifndef CHECKINGACCOUNT_HPP
#define CHECKINGACCOUNT_HPP
#include"BankAccount.hpp"
#include"DebitCard.hpp"
#include"CreditCard.hpp"
#include<memory>

/**
 * @class CheckingAccount
 * @brief Represents a checking account derived from the BankAccount class.
 * 
 * This class extends core banking functionality by adding checking account-specific
 * features such as overdraft protection, monthly maintenance fees, transaction tracking,
 * and debit/credit card management. It also supports business account designation and
 * customizable withdrawal limits.
 * 
 * @details 
 * Key features include:
 * - Overdraft limit management and optional overdraft protection via a backup account.
 * - Monthly maintenance fee with optional waiver based on minimum balance.
 * - Linked debit and credit card management.
 * - Daily ATM/cash withdrawal limits.
 * - Tracking of monthly transaction counts.
 * - Ability to convert the account to a business account type.
 * 
 * @note Inherits from the BankAccount base class and overrides certain methods
 * such as applyWithdraw() to implement account-specific transaction behavior.
 */
class CheckingAccount:public BankAccount
{   
    private:
        // core checking account features

            /**
         * @brief The maximum overdraft amount allowed for the account.
         * 
         * Transactions that exceed the current balance up to this limit may still be approved
         * if overdraft protection is enabled.
         */
        double overdraft_limit_;

            /**
         * @brief The monthly maintenance fee charged to the account.
         * 
         * This fee may be waived if the account maintains a minimum required balance.
         */
        double monthly_maintenance_fee_;

            /**
         * @brief The minimum account balance required to waive the monthly maintenance fee.
         */
        double minimum_balance_waiver_;

            /**
         * @brief Indicates whether overdraft protection is enabled for the account.
         * 
         * If true, transactions exceeding the balance up to the overdraft limit (or a linked backup account)
         * may still be processed.
         */
        bool has_overdraft_protection_;

            /**
         * @brief The number of transactions performed in the current month.
         * 
         * Used to track free or fee-based transactions.
         */
        int monthly_transaction_count_; 

        /**
         * @brief List of debit cards associated with this checking account.
         */
        //std::vector<std::shared_ptr<DebitCard>> debit_cards_;

            
         /**
         * @brief List of credit cards associated with this checking account.
         */
        std::vector<std::shared_ptr<CreditCard>> credit_cards_;



        // Security feature
        // ATM or cash withdrawal limit
         /**
         * @brief Maximum amount allowed for ATM or cash withdrawals in a single day.
         */
        double daily_withdrawal_limit_;

        // Account type
         /**
         * @brief Flag indicating whether this account is a business account.
         */
        //bool is_business_account_;

            /**
         * @brief A weak pointer to a backup bank account for overdraft protection.
         * 
         * If overdraft protection is enabled, this backup account may be used
         * to cover transactions exceeding the account balance.
         */
        std::weak_ptr<BankAccount> overdraft_backup_account_; 

        double initial_balance_;

    protected:

            /**
         * @brief Notification hook called when a maintenance fee is waived.
         * 
         * This method can be overridden or extended by derived classes to provide
         * custom behavior or logging when the account qualifies for a maintenance fee waiver.
         */
        virtual void onFeeWaived() const;  // Notification hook

     public:
                        /**
             * @brief Constructs a new CheckingAccount object with optional configuration.
             * 
             * @param overdraft_limit The maximum allowed overdraft amount. Default is 0.0.
             * @param monthly_fee The monthly maintenance fee for the account. Default is 10.0.
             * @param fee_wavier_balance The minimum balance to qualify for a fee waiver. Default is 1500.0.
             * @param daily_withdrawal_limit The daily ATM/cash withdrawal limit. Default is 500.0.
             */
            CheckingAccount(double overdraft_limit = 0.0, 
                            double monthly_fee = 10.0, 
                            double fee_wavier_balance = 1500.00,
                            double daily_withdrawal_limit = 500.0,
                            double initial_balance = 0.0);
            // In CheckingAccount.hpp
         CheckingAccount(int id, double balance, const std::string& accountType)
         :BankAccount(id, balance, accountType),  // Pass to base class
         overdraft_limit_(0.0),
         monthly_maintenance_fee_(0.0),
         minimum_balance_waiver_(1500.0),
         has_overdraft_protection_(false),
         is_business_account_(false) {}

            // overdraft management
            /**
             * @brief Sets a new overdraft limit for the account.
             * 
             * @param limit The new overdraft limit value.
             * @return True if the limit was successfully set, false otherwise.
             */
            bool setOverdraftLimit(double limit);

              /**
             * @brief Retrieves the current overdraft limit.
             * 
             * @return The overdraft limit value.
             */
            double getOverdraftLimit() const;

            // Fee handling 
            /**
             * @brief Applies the monthly maintenance fee to the account if applicable.
             * 
             * If the account qualifies for a fee waiver based on its balance, no fee is applied.
             */            
            void applyMonthlyMaintenanceFee();

            /**
             * @brief Checks if the account qualifies for a maintenance fee waiver.
             * 
             * @return True if the current balance meets or exceeds the waiver threshold, false otherwise.
             */           
            bool qualifiesForFeeWaiver() const;

            // Debit card operations.
            // Issue a debit card
            /**
             * @brief Issues a new debit card associated with this account.
             * 
             * @param card_number The card number.
             * @param expiration The expiration date in MM/YY format.
             * @param cvv The card's CVV code.
             */           
            void issueDebitCard();

            bool blockDebitCard(const std::string& cardNumber);

            // Transaction override
            /**
             * @brief Attempts to withdraw a specified amount from the account.
             * 
             * Overrides the base class withdraw method to include overdraft protection 
             * and daily withdrawal limit checks.
             * 
             * @param amount The amount to withdraw.
             * @return True if the withdrawal is successful, false otherwise.
             */
            bool applyWithdraw(const double& amount) override;

            // Account type management
            /**
             * @brief Converts the account to a business account or reverts it to personal.
             * 
             * 
             */
            void convertTOBusinessAccount();

            //------getters-------
            /**
             * @brief Retrieves the monthly maintenance fee.
             * 
             * @return The monthly fee amount.
             */
            double getMonthlyfee() const;


            /**
             * @brief Retrieves the daily ATM/cash withdrawal limit.
             * 
             * @return The daily withdrawal limit.
             */
            double getDailyWithdrawalLimit() const;

            /**
             * @brief Retrieves the number of transactions performed this month.
             * 
             * @return The transaction count.
             */           
            int getMonthlyTransactionCount() const;

            /**
             * @brief Adds a credit card to the account.
             * 
             * @param creditLimit The credit limit for the new card.
             * @param isActivated Whether the card is activated upon creation.
             * @param linked_account The bank account linked to the credit card.
             */
            void addCreditCard( double creditLimit, bool isActivated,std::shared_ptr<BankAccount> linked_account);
            //void addDebitCard(const std::string& cardnumber, const std::string& expiration, const std::string& cvv, bool isActivated, bool isExpired);
                
            // Overdraft protection methods
            /**
             * @brief Links a backup bank account for overdraft protection.
             * 
             * @param backup The backup BankAccount shared pointer.
             */
            void linkOverdraftProtection(std::shared_ptr<BankAccount> backup);

            /**
             * @brief Checks if overdraft protection is enabled.
             * 
             * @return True if protection is enabled, false otherwise.
             */
            bool hasOverdraftProtection() const;

            /**
             * @brief Retrieves the linked backup account for overdraft protection.
             * 
             * @return A shared pointer to the backup BankAccount.
             */
            std::shared_ptr<BankAccount> getBackupAccount() const;

            void applyInterest() override;
            // Checking accounts usually don't accrue interest.
            // You can leave it empty or log a message.
            // For now, just a placeholder.
            
              bool is_business_account_; // should be private
             std::vector<std::shared_ptr<DebitCard>> debit_cards_;  // should be private
             // In CheckingAccount.hpp class definition, add:

    bool isBusinessAccount() const;
    void setAccountBalance(double amount);
            
};


#endif