#ifndef DEBITCARD_HPP
#define DEBITCARD_HPP
#include"CheckingAccount.hpp"
#include"Card.hpp"
#include<iostream>
#include<string>
#include<memory>


class CheckingAccount;
class BankAccount;

class DebitCard : public Card{
    private:
        double daily_withdrawal_limit_;
        double daily_spend_amount_;
        std::string pin_;
        bool contactless_enable_;

        /// @brief debit card linked to checking account
        std::weak_ptr<CheckingAccount> linked_debit_card_account_;
    public:
        DebitCard();
        DebitCard(const std::string& number, 
                  const std::string& expiration, 
                  const std::string& cvv, 
                  const bool& isActivated,
                  const double& daily_withdrawal_limit, 
                  const double& daily_spend_amount, 
                  const std::string& pin, 
                  const bool enable, std::shared_ptr<CheckingAccount> account, 
                  const bool isExpired);

        double getDailyWithdrawalLimit() const;
        double getDailySpendAmount() const;
        std::string getPin() const;
        std::weak_ptr<CheckingAccount> getLinkedAccount() const;
        bool isContactlessEnabled() const;
        void enableContactless(bool enable);

        bool SetDailySpendAmount(const double& amount);
        bool SetDailyWithdrawalLimit(const double& limit);
        bool setPin(const std::string& pin);
        bool changePin(const std::string& old_pin, const std::string& new_pin );
        
        bool processPayment(double amount) override;
        bool validate() const override;
        virtual bool checkIfExpired() override;



};






#endif