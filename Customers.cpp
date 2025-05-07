#include"Customers.hpp"
#include<iostream>
#include<string>
#include <stdexcept>

// UUID
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


/**
 * @brief A helper function to generate customer id.
 * 
 * @return A string (unique customer id)
 */
std::string generate_uuid()
{
    boost::uuids::random_generator generator;
    return boost::uuids::to_string(generator());
}


/**
 * @brief Creates an unauthenticated customer profile
 * 
 * Initializes all fields to invalid defaults:
 * - Name: "NONE"
 * - Email: "NONE"
 * - Phone: "NONE"
 * - Age: 0
 * 
 * @note Use for temporary placeholder customers
 * @warning Not suitable for banking operations - requires field updates
 */
Customers::Customers(): customers_name_("NONE"), 
                        customers_email_("NONE"), 
                        customers_phone_number_("NONE"), 
                        customers_id_(generate_uuid()), 
                        customers_age_(0){}


/**
 * @brief Creates validated customer profile
 * 
 * Initializes fields through validation chain:
 * 1. Validates/uppercases name via setName()
 * 2. Validates email format via setEmail()
 * 3. Validates phone number via setPhoneNumber()
 * 4. Validates age via setAge() (throws on invalid)
 * 
 * @param name Alphabetic+space chars only
 * @param email RFC 5322 pattern
 * @param phone_number 10-digit US format
 * @param age Non-negative integer
 * 
 * @throws std::invalid_argument If age < 0
 * 
 * @note Invalid string parameters set to "NONE"
 * @warning Name validation converts valid input to UPPERCASE
 * 
 * @code
 * Valid: Customers("John Doe", "john@doe.com", "1234567890", 30)
 * Invalid: Customers("User123", "bad-email", "short", -5) 
 *   // Name=NONE, Email=NONE, Phone=NONE, Age=0 (exception thrown)
 * @endcode
 */
Customers::Customers(const std::string& name, 
                     const std::string& email, 
                     const std::string& phone_number, 
                     int age):
                     customers_id_(generate_uuid()), 
                     customers_name_("NONE"), 
                     customers_email_("NONE"), 
                     customers_phone_number_("NONE"), 
                                        customers_age_(0)
    {

    if (setName(name)) {
        customers_name_ = name;
    }
    if (setEmail(email)) {
        customers_email_ = email;
    }
    if (setPhoneNumber(phone_number)) {
        customers_phone_number_ = phone_number;
    }
    setAge(age);
    }


std::string Customers::getName()const
{
    return customers_name_;
}

bool Customers::setName(const std::string& name)
{
    for(char c : name)
    {
        if(!isalpha(c) && c != ' ')
        {
            return false;
        }
    }
    customers_name_ = name;

    for(char& c : customers_name_)
    {
        if(isalpha(c))
        {
            c = toupper(c);
        }
    }
   
    return true;
}

std::string Customers::getEmail()const
{
    return customers_email_;
}

bool Customers::setEmail(const std::string& email)
{
    std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if(!std::regex_match(email, pattern))
    {
        return false;
    }
    customers_email_ = email;
    return true;
}

std::string Customers::getPhoneNumber()const
{
    return customers_phone_number_;
}

bool Customers::setPhoneNumber(const std::string& phone_number)
{
    for(size_t i = 0; i < phone_number.size(); i++)
    {
        if(!isdigit(phone_number[i]))
        {
            std::cout << "Phone number must be digits" << std::endl;
            return false;
        }
    }
    
        if(phone_number.empty()||phone_number[0] != '1' || phone_number.size() != 10)
        {
            std::cout << "Phone number is invalid" << std::endl;
            return false;
        }
        
    customers_phone_number_ = phone_number;
    return true;
   
}

int Customers::getAge()const
{
    return customers_age_;
}

bool Customers::setAge(const int age)
{
    if(age < 0)
    {
        throw std::invalid_argument("Age cannot be negative.");
    }
    customers_age_ = age;
    return true;
}

void Customers::display() const
{

    std::cout << "Customer Details:" << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Email: " << getEmail() << std::endl;
    std::cout << "Phone Number: " << getPhoneNumber()<< std::endl;
    std::cout << "Age: " << getAge() << std::endl;
}

void Customers::linkAccount(std::shared_ptr<BankAccount> account)
{
    account_.push_back(account);
}

const std::vector<std::shared_ptr<BankAccount>> &Customers::getAccount()const
{
    return account_;
}

void Customers::setCreditCard(std::vector<std::shared_ptr<CreditCard>> &card)
{
    creditCard_ = card;
}

bool Customers::hasCreditCard() const
{
    return !creditCard_.empty();
}

std::vector<std::shared_ptr<CreditCard>> &Customers::getCreditCard()
{
    return creditCard_;
}

std::vector<std::shared_ptr<SavingAccount>> Customers::getSavingAccount() const
{
    std::vector<std::shared_ptr<SavingAccount>> result;
    for(const auto& acc : account_)
    {
        if(auto sa = std::dynamic_pointer_cast<SavingAccount>(acc))
        {
            result.push_back(sa);
        }
    }
    return result;
}

std::vector<std::shared_ptr<CheckingAccount>> Customers::getCheckingAccount() const
{
    std::vector<std::shared_ptr<CheckingAccount>> result;
    for(const auto& acc : account_)
    {
        if(auto ca = std::dynamic_pointer_cast<CheckingAccount>(acc))
        {
            result.push_back(ca);
        }
    }
    return result;
}
