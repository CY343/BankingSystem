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
                     customers_name_("NONE"), 
                     customers_email_("NONE"), 
                     customers_phone_number_("NONE"), 
                     customers_id_(generate_uuid()),
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

/**
 * @brief Retrieves the customer's name.
 * 
 * @return The name of the customer as a std::string.
 */
std::string Customers::getName()const
{
    return customers_name_;
}


/**
 * @brief Sets the customer's name after validating and formatting it.
 * 
 * Validates that the name contains only alphabetic characters and spaces.
 * Converts all alphabetic characters to uppercase before setting.
 * 
 * @param name The new name to set.
 * @return true if the name is valid and set successfully, false otherwise.
 */
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


/**
 * @brief Retrieves the customer's email address.
 * 
 * @return The email address of the customer as a std::string.
 */
std::string Customers::getEmail()const
{
    return customers_email_;
}


/**
 * @brief Sets the customer's email after validating its format.
 * 
 * Uses a regular expression to verify that the email is in a valid format.
 * If valid, sets the customer's email; otherwise, returns false.
 * 
 * @param email The email address to set.
 * @return true if the email format is valid and set successfully, false otherwise.
 */
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

/**
 * @brief Retrieves the customer's phone number.
 * 
 * @return The phone number of the customer as a std::string.
 */
std::string Customers::getPhoneNumber()const
{
    return customers_phone_number_;
}


/**
 * @brief Sets the customer's phone number after cleaning and validating it.
 * 
 * Removes all non-digit characters from the input and checks that
 * the resulting number contains exactly 10 digits.
 * 
 * @param phone_number The raw phone number string input.
 * @return true if the phone number is valid and set successfully, false otherwise.
 */
bool Customers::setPhoneNumber(const std::string& phone_number)
{
    std::string clean_number;
    /// Remove all non-digit characters first
    for(char c : phone_number) {
        if(isdigit(c)) clean_number += c;
    }
    
    /// Then validate length
    if(clean_number.length() != 10) {
        std::cerr << "Invalid phone number length\n";
        return false;
    }
    
    customers_phone_number_ = clean_number;
    return true;
}


/**
 * @brief Retrieves the customer's age.
 * 
 * @return The age of the customer as an integer.
 */
int Customers::getAge()const
{
    return customers_age_;
}


/**
 * @brief Sets the customer's age.
 * 
 * Throws an exception if the age is negative.
 * 
 * @param age The age to set.
 * @return true if the age is valid and set successfully.
 * @throws std::invalid_argument if the age is negative.
 */
bool Customers::setAge(const int age)
{
    if(age < 0)
    {
        throw std::invalid_argument("Age cannot be negative.");
    }
    customers_age_ = age;
    return true;
}


/**
 * @brief Displays the customer's details to the standard output.
 * 
 * Prints the customer's name, email, phone number, and age.
 */
void Customers::display() const
{

    std::cout << "Customer Details:" << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Email: " << getEmail() << std::endl;
    std::cout << "Phone Number: " << getPhoneNumber()<< std::endl;
    std::cout << "Age: " << getAge() << std::endl;
}


/**
 * @brief Links a bank account to the customer.
 * 
 * Adds the given shared pointer to a BankAccount to the customer's account list.
 * 
 * @param account A shared pointer to the BankAccount to link.
 */
void Customers::linkAccount(std::shared_ptr<BankAccount> account)
{
    account_.push_back(account);
}


/**
 * @brief Retrieves the list of bank accounts linked to the customer.
 * 
 * @return A constant reference to a vector of shared pointers to BankAccount objects.
 */
const std::vector<std::shared_ptr<BankAccount>> &Customers::getAccount()const
{
    return account_;
}


/**
 * @brief Sets the customer's credit card list.
 * 
 * Copies the provided vector of shared pointers to CreditCard objects
 * into the customer's credit card collection.
 * 
 * @param card A reference to a vector of shared pointers to CreditCard objects.
 */
void Customers::setCreditCard(std::vector<std::shared_ptr<CreditCard>> &card)
{
    creditCard_ = card;
}


/**
 * @brief Checks if the customer has any credit cards linked.
 * 
 * @return true if the customer has one or more credit cards, false otherwise.
 */
bool Customers::hasCreditCard() const
{
    return !creditCard_.empty();
}


/**
 * @brief Retrieves the customer's list of credit cards.
 * 
 * @return A reference to a vector of shared pointers to CreditCard objects.
 */
std::vector<std::shared_ptr<CreditCard>> &Customers::getCreditCard()
{
    return creditCard_;
}


/**
 * @brief Retrieves all linked SavingAccount objects.
 * 
 * Iterates through all linked BankAccount objects, filters those that are
 * SavingAccount instances using dynamic_pointer_cast, and returns them in a vector.
 * 
 * @return A vector of shared pointers to SavingAccount objects.
 */
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


/**
 * @brief Retrieves all linked CheckingAccount objects.
 * 
 * Iterates through all linked BankAccount objects, filters those that are
 * CheckingAccount instances using dynamic_pointer_cast, and returns them in a vector.
 * 
 * @return A vector of shared pointers to CheckingAccount objects.
 */
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
