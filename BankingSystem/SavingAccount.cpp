#include "SavingAccount.hpp"
#include <stdexcept>
#include <ctime>

/**
 * @brief Default constructor.
 * Initializes min_balance_ to 500.0, withdrawal_times_this_month_ to 0,
 * and interest_rate_ to 0.0.
 */
SavingAccount::SavingAccount()
    : BankAccount(),
      min_balance_(500.0),
      withdrawal_times_this_month_(0),
      interest_rate_(0.0)
{}

/**
 * @brief Constructor that initializes balance and interest rate.
 * Sets min_balance_ to 500.0 and resets withdrawal count.
 * 
 * @param initial_balance Initial account balance.
 * @param interest_rate Interest rate (e.g., 0.02 for 2%).
 */
SavingAccount::SavingAccount(double initial_balance, double interest_rate)
    : BankAccount(0, initial_balance, ""),  // accountNumber=0, customerId empty string
      min_balance_(500.0),
      withdrawal_times_this_month_(0),
      interest_rate_(interest_rate)
{}

/**
 * @brief Constructor with explicit accountNumber, balance, and customerId.
 * Initializes min_balance_ to 500.0, withdrawal count 0, and interest_rate_ to 0.0.
 */
SavingAccount::SavingAccount(int accountNumber, double balance, const std::string& customerId)
    : BankAccount(accountNumber, balance, customerId),
      min_balance_(500.0),
      withdrawal_times_this_month_(0),
      interest_rate_(0.0)
{}

/**
 * @brief Attempts to withdraw amount ensuring minimum balance and withdrawal limit.
 * Throws std::runtime_error if constraints violated.
 */
bool SavingAccount::applyWithdraw(const double& amount)
{
    if ((getAccountBalance() - amount) < min_balance_)
    {
        throw std::runtime_error("Withdrawal violates minimum balance requirements");
    }

    if (withdrawal_times_this_month_ >= 6)
    {
        throw std::runtime_error("Maximum monthly withdrawal exceeded.");
    }

    if (BankAccount::applyWithdraw(amount))
    {
        withdrawal_times_this_month_++;
        return true;
    }

    return false;
}

/**
 * @brief Applies monthly interest to the account.
 * Calculates interest, deposits it, and records the transaction.
 */
void SavingAccount::applyMonthlyInterest()
{
    double interest = getAccountBalance() * (interest_rate_ / 12);
    applyDeposit(interest);
    addTransaction(Transaction::INTEREST, interest, std::time(nullptr));
}

/**
 * @brief Resets the withdrawal count for the month.
 */
void SavingAccount::resetMonthlyWithdrawals()
{
    withdrawal_times_this_month_ = 0;
}

/**
 * @brief Returns the minimum balance required.
 */
double SavingAccount::getMinBalance() const
{
    return min_balance_;
}

/**
 * @brief Returns the interest rate.
 */
double SavingAccount::getInterestRate() const
{
    return interest_rate_;
}

/**
 * @brief Applies interest monthly, deposits, and records transaction.
 */
void SavingAccount::applyInterest()
{
    double monthly_interest = getAccountBalance() * (getInterestRate() / 12.0);
    applyDeposit(monthly_interest);
    addTransaction(Transaction::INTEREST, monthly_interest, std::time(nullptr));
}

/**
 * @brief Returns number of withdrawals made this month.
 */
int SavingAccount::getWithdrawalTimesThisMonth() const
{
    return withdrawal_times_this_month_;
}
