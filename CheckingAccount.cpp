#include"CheckingAccount.hpp"
#include<stdexcept>


/**
 * @brief Constructs a new CheckingAccount object with specified parameters.
 * 
 * This constructor initializes a new CheckingAccount by setting up
 * overdraft limits, monthly fees, waiver balances, and withdrawal limits.
 * It also initializes base class BankAccount with zero values.
 * 
 * @param overdraft_limit The maximum amount allowed to be overdrawn.
 * @param monthly_fee The monthly maintenance fee for the account.
 * @param fee_waiver_balance The minimum balance required to waive the monthly fee.
 * @param daily_Withdrawal_limit The maximum amount allowed for daily withdrawals.
 */
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


/**
 * @brief Sets the overdraft limit for the checking account.
 * 
 * Updates the overdraft limit to the specified value if it is non-negative.
 * 
 * @param limit The new overdraft limit to be set.
 * @return true If the limit is valid (non-negative) and was successfully set.
 * @return false If the provided limit is negative.
 */
bool CheckingAccount::setOverdraftLimit(double limit)
{   
    if (limit < 0)
         return false;

    overdraft_limit_ = limit;
         return true;
}

/**
 * @brief Retrieves the current overdraft limit of the checking account.
 * 
 * @return The current overdraft limit.
 */
double CheckingAccount::getOverdraftLimit() const
{
    return overdraft_limit_;
}

/* bool CheckingAccount::blockCreditCard()
{
    if(credit_cards_)
} */

/**
 * @brief Attempts to withdraw an amount from the checking account.
 * 
 * If the withdrawal would exceed the overdraft limit, the function checks
 * if overdraft protection is enabled. If so, it attempts to withdraw from 
 * the linked backup account. If successful, it deposits the amount into 
 * this account and proceeds with the withdrawal.
 * 
 * If the withdrawal exceeds the overdraft limit and no overdraft protection
 * is available, the function throws a runtime error and catches it internally,
 * reporting the failure.
 * 
 * @param amount The amount to withdraw.
 * @return true If the withdrawal (and any necessary overdraft protection actions) succeeds.
 * @return false If the withdrawal fails due to insufficient funds or backup account issues.
 */
bool CheckingAccount::applyWithdraw(double const &amount)
{
    try 
    {
        if((getAccountBalance() - amount) < overdraft_limit_)
        {
            if(has_overdraft_protection_)
            {
                auto backup = overdraft_backup_account_.lock();
                if(backup && backup->applyWithdraw(amount))
                {
                    applyDeposit(amount);
                    return BankAccount::applyWithdraw(amount);
                }
            }
                throw std::runtime_error("Over limit exceeded");
        }   
            return BankAccount::applyWithdraw(amount);
    }   
        catch(const std::exception& e)
    {
        std::cerr <<" Withdrawal failed: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief Toggles the account type between business and personal.
 * 
 * Flips the value of the is_business_account_ flag.
 * If it was a business account, it becomes a personal account, and vice versa.
 */
void CheckingAccount::convertTOBusinessAccount()
{
    is_business_account_ = !is_business_account_;
}

/**
 * @brief Retrieves the monthly maintenance fee for the checking account.
 * 
 * @return The current monthly maintenance fee.
 */
double CheckingAccount::getMonthlyfee() const
{
    return monthly_maintenance_fee_;
}

/**
 * @brief Retrieves the daily withdrawal limit for the checking account.
 * 
 * @return The current daily withdrawal limit.
 */
double CheckingAccount::getDailyWithdrawalLimit() const
{
    return daily_withdrawal_limit_;
}

/**
 * @brief Retrieves the number of transactions made in the current month.
 * 
 * @return The current monthly transaction count.
 */
int CheckingAccount::getMonthlyTransactionCount() const
{
    return monthly_transaction_count_;
}

/**
 * @brief Applies the monthly maintenance fee to the checking account if applicable.
 * 
 * If the account does not qualify for a fee waiver, the monthly maintenance fee
 * is withdrawn from the account and recorded as a fee transaction.
 * If the account qualifies for the waiver, the onFeeWaived() handler is called.
 */
void CheckingAccount::applyMonthlyMaintenanceFee()
{
    if(!qualifiesForFeeWaiver())
    {
        BankAccount::applyWithdraw(monthly_maintenance_fee_);
        addTransaction(Transaction::FEE, monthly_maintenance_fee_, time(nullptr));
    }
    else
    {
        onFeeWaived();
    }
}

/**
 * @brief Notifies that the monthly maintenance fee has been waived.
 * 
 * Prints a message to standard output indicating that the fee was waived,
 * along with the account number and current balance.
 */
void CheckingAccount::onFeeWaived() const
{
    std::cout << "Fee waived for account #" << getAccountNumber()
              << " (Balance: $" << getAccountBalance() << ")\n";
}

/**
 * @brief Checks if the account qualifies for a monthly fee waiver.
 * 
 * Determines whether the current account balance meets or exceeds
 * the minimum balance required to waive the monthly maintenance fee.
 * 
 * @return true If the balance is sufficient to waive the fee.
 * @return false Otherwise.
 */
bool CheckingAccount::qualifiesForFeeWaiver() const
{
    return getAccountBalance() >= minimum_balance_waiver_;
}

/* Need to be implemented later */
void CheckingAccount::issueDebitCard(const std::string &card_number, const std::string &expiration, const std::string &cvv)
{
    return;
}


/**
 * @brief Adds a new credit card linked to this checking account.
 * 
 * Validates that the requested credit limit does not exceed twice the current
 * account balance. Throws std::invalid_argument if validation fails.
 * 
 * If valid, creates a new CreditCard with the specified credit limit, activation
 * status, and linked bank account, then adds it to the list of credit cards.
 * 
 * @param creditLimit The credit limit for the new credit card.
 * @param isActivated Whether the credit card is initially activated.
 * @param linked_account A shared pointer to the linked bank account.
 * 
 * @throws std::invalid_argument If creditLimit exceeds twice the account balance.
 */
void CheckingAccount::addCreditCard(double creditLimit, bool isActivated, std::shared_ptr<BankAccount> linked_account) 
{
    if(creditLimit > getAccountBalance() * 2)
     {
         throw std::invalid_argument("Credit limit exceeds 2 times account balance.");
     }

    // Auto-generate credit card with BIN prefix for Visa/Mastercard
    credit_cards_.emplace_back
    (
    std::make_shared<CreditCard>(
        creditLimit, 
        isActivated, 
        linked_account)
    );
}


/**
 * @brief Links a backup bank account for overdraft protection.
 * 
 * Stores a weak reference to the provided backup account and enables
 * overdraft protection on this checking account.
 * 
 * @param backup Shared pointer to the backup bank account used for overdraft protection.
 */
void CheckingAccount::linkOverdraftProtection(std::shared_ptr<BankAccount> backup)
{   
    overdraft_backup_account_ = backup;
    has_overdraft_protection_ = true;
}


/**
 * @brief Checks if overdraft protection is enabled on this account.
 * 
 * @return true If overdraft protection is currently enabled.
 * @return false Otherwise.
 */
bool CheckingAccount::hasOverdraftProtection() const
{
    return has_overdraft_protection_;
}

/**
 * @brief Retrieves a shared pointer to the overdraft backup account.
 * 
 * Attempts to lock the weak pointer to the backup account and return
 * a shared pointer. If the backup account no longer exists, returns nullptr.
 * 
 * @return std::shared_ptr<BankAccount> Shared pointer to the backup account, or nullptr if expired.
 */

std::shared_ptr<BankAccount> CheckingAccount::getBackupAccount()const
{
    return overdraft_backup_account_.lock();
}

