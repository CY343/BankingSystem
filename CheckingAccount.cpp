#include"CheckingAccount.hpp"
#include<stdexcept>

CheckingAccount::CheckingAccount(double overdraft_limit, 
                                 double monthly_fee, 
                                 double fee_waiver_balance, 
                                 double daily_Withdrawal_limit):
                                 BankAccount(0.0, 0.0, 0.0, 0.0), 
                                 overdraft_limit_(overdraft_limit), 
                                 monthly_maintenance_fee_(monthly_fee),
                                 minimum_balance_waiver_(fee_waiver_balance),
                                 has_overdraft_protection_(false),
                                 monthly_transaction_count_(0), 
                                 daily_withdrawal_limit_(daily_Withdrawal_limit), 
                                 is_business_account_(false){}

bool CheckingAccount::setOverdraftLimit(double limit)
{
    overdraft_limit_ = limit;
    return true;
}

double CheckingAccount::getOverdraftLimit() const
{
    return overdraft_limit_;
}

/* bool CheckingAccount::blockCreditCard()
{
    if(credit_cards_)
} */

bool CheckingAccount::applyWithdraw(double const &amount)
{
    if((getAccountBalance() - amount) < overdraft_limit_)
    {
        throw std::runtime_error("Overdraft limit exceeded");
    }

    monthly_transaction_count_++;
    return BankAccount::applyWithdraw(amount);
}

void CheckingAccount::applyMonthlyMaintenanceFee()
{
    if(!qualifiesForFeeWaiver())
    {
        BankAccount::applyWithdraw(monthly_maintenance_fee_);
    }
}

bool CheckingAccount::qualifiesForFeeWaiver() const
{
    return getAccountBalance() >= minimum_balance_waiver_;
}

void CheckingAccount::addCreditCard(const std::string& cardnumber, const std::string& expiration, const std::string& cvv,
     double creditLimit, bool isActivated, std::shared_ptr<BankAccount> linked_account, bool isExpired)
     {
        if(creditLimit > getAccountBalance() * 2)
        {
            throw std::invalid_argument("Credit limit exceeds 2 times account balance.");
        }

        credit_cards_.emplace_back(std::make_shared<CreditCard>(cardnumber, expiration, cvv, creditLimit, isActivated, linked_account, isExpired));
     }