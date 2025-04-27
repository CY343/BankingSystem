#include"Customers.hpp"
#include<iostream>
#include<string>

Customers::Customers(){
         customers_name_ = "NONE";
         customers_email_ = "NONE";
         customers_phone_number_ = "NONE";
         customers_age_ = 0;
}

Customers::Customers(const std::string& name, const std::string& email, const std::string& phone_number, int age)
: customers_name_(name), customers_email_(email), customers_phone_number_(phone_number), customers_age_(age)
{
    setAge(age);
    if (!setName(name)) {
        customers_name_ = "NONE";
    }
    if (!setEmail(email)) {
        customers_email_ = "NONE";
    }
    if (!setPhoneNumber(phone_number)) {
        customers_phone_number_ = "NONE";
    }
}

Customers::~Customers() {}

std::string Customers::getName()const
{
    return customers_name_;
}

bool Customers::setName(const std::string& name)
{
    
    for(size_t i = 0; i < name.size(); i++)
    {
        if(!isalpha(name[i]))
        {
            std::cout << "Please enter a valid name!" << std::endl;
            return false;
        }
    }  

    customers_name_ = name;
    for(size_t i = 0; i < name.size()&& isalpha(name[i]); i++)
    {
        customers_name_[i] = std::toupper(customers_name_[i]);
       
    }
    
    return true;
    
}

std::string Customers::getEmail()const
{
    return customers_email_;
}

bool Customers::setEmail(const std::string& email)
{
    if(email.find('@') == std::string::npos||email.find('.') == std::string::npos)
    {
        std::cout << "Please enter a vaild email." << std::endl;
        return false;
    }
    customers_email_ = email;
    for(size_t i = 0; i < customers_email_.size(); i++)
    {
        if(customers_email_[i] >= 'a' && customers_email_[i] <= 'z')
        {
            customers_email_[i] = std::toupper(customers_email_[i]);
        }
    }
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
    
        if(phone_number[0] != '1' || phone_number.empty()|| phone_number.size() != 10)
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
    account_ = account;
}

std::shared_ptr<BankAccount> Customers::getAccount()const
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
