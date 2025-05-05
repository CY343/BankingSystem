#ifndef CHECKINGACCOUNT_HPP
#define CHECKINGACCOUNT_HPP
#include"BankAccount.hpp"
#include"DebitCard.hpp"
#include"CreditCard.hpp"
#include<memory>

class CheckingAccount:public BankAccount
{   
    private:
        // core checking account features
        double overdraft_limit_;
        double monthly_maintenance_fee_;
        double minimum_balance_waiver_;
        bool has_overdraft_protection_;

        // Transaction tracking
        // Free transaction limits
        int monthly_transaction_count_; 

        // Linked service
        // Associted with debit card
        std::vector<std::shared_ptr<DebitCard>> debit_cards_;

        std::vector<std::shared_ptr<CreditCard>> credit_cards_;



        // Security feature
        // ATM or cash withdrawal limit
        double daily_withdrawal_limit_;

        // Account type
        bool is_business_account_;

       

        public:
            // constructor
            CheckingAccount(double overdraft_limit = 0.0, double monthly_fee = 10.0, double fee_wavier_balance = 1500.00,
            double daily_withdrawal_limit = 500.0);

            // Key methods
            // overdraft management
            bool setOverdraftLimit(double limit);
            double getOverdraftLimit() const;

            // Fee handling 
            void applyMonthlyMantenanceFee();
            bool qualifiesForFeeWaier() const;

            // Debit card operations.
            // Issue a debit card
            void issueDebitCard(const std::string& card_number, const std::string& expiration, const std::string& cvv);

           // bool blockDebitCard();

            // Transaction override
            bool applyWithdraw(const double& amount) override;

            // Account type management
            void convertTOBusinessAccount(bool is_business = true);

            //------getters-------
            double getMonthlyfee() const;
            double getDailyWithdrawalLimit() const;
            int getMonthlyTransactionCount() const;

            /// @brief add a credit card to linked account.
            /// @param cardnumber 
            /// @param expiration 
            /// @param cvv 
            /// @param creditLimit 
            /// @param isActivated 
            /// @param linked_account 
            /// @param isExpired 
            void addCreditCard(const std::string& cardnumber, const std::string& expiration, const std::string& cvv, double creditLimit, bool isActivated,std::shared_ptr<BankAccount> linked_account, bool isExpired);
            //void addDebitCard(const std::string& cardnumber, const std::string& expiration, const std::string& cvv, bool isActivated, bool isExpired);
        
};


#endif