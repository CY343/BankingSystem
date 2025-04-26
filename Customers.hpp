#ifndef CUSTOMERS_HPP
#define CUSTOMERS_HPP
#include<iostream>
#include<string>
#include<memory>
#include<vector>

class BankAccount;


class Customers{
    private:
        std::string customers_name_;
        std::string customers_email_;
        std::string customers_phone_number_;
        int customers_age_;
        std::vector<BankAccount*> account_;

    public:
        Customers();
        Customers(const std::string& name, const std::string& email, const std::string& phone_number, int age);
        ~Customers();
        std::string getName() const;
        bool setName(const std::string& name);
        std::string getEmail()const;
        bool setEmail(const std::string& email);
        std::string getPhoneNumber()const;
        bool setPhoneNumber(const std::string& phone_number);
        int getAge() const;
        bool setAge(const int age);
        void display() const;
        void linkAccount(std::vector<BankAccount*> account);
        std::vector<BankAccount*> getAccount() const;
        


};




#endif
