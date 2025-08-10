#ifndef CARD_HPP
#define CARD_HPP
#include"CardGenerator.hpp"
#include"SecurityHelper.hpp"
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<ctime>
#include <openssl/rand.h>

class Card{
    
    private:
        std::string card_number_; // A string representing card number
        std::string expiration_; // A string representing the expiration date of the card
        std::string cvv_; // A string representing the cvv of the card.
        bool isActivated_; // A boolean indicates whether the card is currently activate
        bool isExpired_; // A boolean indicates whether the card is currently expired
    
    protected:
    /**
     * @brief Generates a future expiry date for a card
     * 
     * This static helper function creates an expiry date string based on 
     * the current date, adding the specified number of valid years
     * 
     * @param ValidYears number of years the card will remain valid. Defalut to 3 years.
     * @return A string represting the expiry date in MM/YY format.
     * 
     */
    static std::string generateExpiryDate(int validYears = 3);

    /**
     * @brief Generates a random 3-digit cvv code for a card
     * 
     * This static helper function returns a string containing a randomly generated
     * cvv (card Verification value) for card security
     * 
     * @return A string representing the 3-digit cvv.
     */
    static std::string generateCVV();
    
    /**
     * @brief Protected construtor for card, with optional automatic card detail generation.
     * 
     * Initializes a new Card instance, setting its activation and expiration status to false.
     * if @p auto_generate is true, this constructor will automatically generate the card number,
     * expiration date, and cvv using the provided @p bin_prefix
     * 
     * @param bin_prefix The Bank Identification Number (BIN) prefix to use when generating the card number
     * @param auto_generate A boolean flag indicating whether to auto_generate card detail upon creation.  
     * 
     * @note This constructor is protected and intended for use within card hierarchy
     */
    Card(const std::string& bin_prefix, bool auto_generate) : isActivated_(false), isExpired_(false) 
    {
        if(auto_generate) {
            card_number_ = CardGenerator::generate(bin_prefix);
            expiration_ = generateExpiryDate();
            cvv_ = generateCVV();
        }
    }
    
    /**
     * @brief Get the Expiration date of the card
     * 
     * @return A string representing card's expiration date
     */
    std::string getExpiration() const;

    /**
     * @brief Get the Cvv of the card
     * 
     * @return A string representing card's CVV
     */
    std::string getCvv()const;


    public:
        /**
         * @brief Default constructor for Card
         * 
         * Initializes a card with default values
         */
        Card(); 

        /**
         * @brief Parameterized constructor constructs a Card with speified activation and and expiration status
         * 
         * @param isActivated A boolean indicating whether the card is activated
         * @param isExpired A boolean indicating whether the card is expired
         */
        Card(const bool isActivated, 
             const bool isExpired);

        /**
         * @brief Checks if the card activated
         * 
         * @return true if the card is activated, false otherwise
         */
        bool isActivated() const;

        /**
         * @brief Set the activation status of the card
         * 
         * @param isActivate  A boolean indicating whether to activate or deactivate the card
         * 
         */
        void setActivated(bool isActivate);

        /**
         * @brief Pure virtual function to process a payment
         * 
         * @note: This function must be implemented by derived classes 
         * 
         * @param amount a double amount to charged to the card

         * @return true if the payment was processed successfully, false otherwise

         */
        virtual bool processPayment(double amount) = 0; 

        /**
         * @brief Vaildates the card's information
         * 
         * @note: Can be overrided by derived classes to provide specific validation logic
         * 
         * @return true if the card is valid, false otherwise
         */
        virtual bool validate() const;

        /**
         * @brief Get the Card Number
         * 
         * @return A string represening card's number
         */
        std::string getCardNumber() const;

        /**
         * @brief checks if the card is expired
         * @note: Can be overrided by derived classes to provide specific validation logic
         * @return true if the card is expired, false otherwise
         */
        virtual bool isExpired() const;

        /**
         * @brief Pure virtual function to check if the card has expired
         * @note: This function must be implemented by derived classes
         * @return true if the card has expired, otherwise false
         */
        virtual bool checkIfExpired() = 0;

        /**
         * @brief Marks the card expired
         * 
         * sets the internal expiration flag to true
         */
        void markExpired();

        // for gtest only
        void setCardNumber(const std::string& number);
        void setExpiration(const std::string& expiration) ;
        void setCvv(const std::string& cvv) ;
};


#endif