#include"Card.hpp"
#include <openssl/rand.h>
#include <chrono>
#include <iomanip>
#include <sstream>

/**
 * @brief Default constructor for Card 
 * 
 * Initializes the card number, expiration date, and cvv to "NONE",
 * and sets the acivation and expiration to false
 * 
 */
Card::Card():card_number_("NONE"), 
             expiration_("NONE"),
             cvv_("None"), 
             isActivated_(false), 
             isExpired_(false){}

/**
 * @brief Paramenterized constructor for Card class
 * 
 * @param isActivated boolean flag to set the card's Activation status
 * @param isExpired bool flag to set the card's Expiration status
 * 
 * Initializes the activation and expiration flag with provided values
 * 
 */
Card::Card(const bool isActivated, 
           const bool isExpired):
           isActivated_(isActivated), 
           isExpired_(isExpired){}


/**
* @brief Gnereates a card expiry date string in the format "MM/YY"
* 
* This function creates an expiration date by randomly selecting a month (01 to 12)
* and calculating the year as the current year plus the specified number of valid year,
* formatted as the last two dighits of the year
*
* @param validYears An integer number of years from the current date until the card expires
* @return A string representing the expiry date in "MM/YY" format
*/
std::string Card::generateExpiryDate(int validYears) 
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time);

    // Generate random month (1-12)
    unsigned char month_byte;
    RAND_bytes(&month_byte, 1);
    int month = 1 + (month_byte % 12);

    // Calculate expiry year
    int year = (now_tm->tm_year + 1900 + validYears) % 100;

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << month << "/"
        << std::setw(2) << std::setfill('0') << year;
    return ss.str();
}
/**
 * @brief Generates a random 3-digit CVV (Card Verification Value) as a string
 * 
 * Uses a cryptographically secure random number generator to create a random 
 * number between 100 and 999, and returns it as a string. If secure random 
 * number generation fails, a runtime error it thrown
 * 
 * @return A string representing the generated 3-digit CVV
 * @threw: std::runtime_error if the secure random number generation fails
 * 
 */
std::string Card::generateCVV() {
    unsigned char cvv_bytes[3];
    if (RAND_bytes(cvv_bytes, sizeof(cvv_bytes)) != 1) {
        throw std::runtime_error("Failed to generate secure CVV");
    }
    return std::to_string(100 + (cvv_bytes[0] % 900));
}

/**
 * @brief checks if the card is currently activated
 * 
 * @return true if the card is activated, false otherwise
 */
bool Card::isActivated() const
{
    return isActivated_;
}

/**
 * @brief sets the activation status of the card 
 * 
 * @param isActivate boolean value to set the card's activation status
 */
void Card::setActivated(bool isActivate)
{
    isActivated_ = isActivate;
}

/**
 * @brief Validates whether the card has all required fields populated.
 * 
 * Checks if the card number, expiration date, and CVV are non-empty.
 * @return True if all essential fields are set; false otherwise.
 */
bool Card::validate() const
{
    return (!card_number_.empty() && !expiration_.empty() && !cvv_.empty());
}

/**
 * @brief gets the card's number
 * 
 * @return A string representing card's number
 */
std::string Card::getCardNumber() const
{
    return card_number_;
}

/**
 * @brief Checks if the card is expired based on the current date.
 * 
 * Parses the card's expiration date in "MM/YY" format, converts it to a full year,
 * and compares it against the current system date. The card is considered expired
 * if the expiration year is less than the current year, or if it is the same year
 * but the expiration month is earlier than the current month.
 * 
 * @return true if the card is expired, false otherwise
 */
bool Card::isExpired() const
{
    // GET CURRENT DATE
    time_t t = time(0); // CURRENT TIME
    struct tm* now = localtime(&t);
    
    int expiredMonth;
    int expiredYear;
    std::sscanf(expiration_.c_str(), "%2d/%2d", &expiredMonth, &expiredYear);
    expiredYear += 2000; // adjusting for YY to YYYY

    // CHECK IF CARD EXPIRED
    if(expiredYear < (now->tm_year + 1900)) {return true;} // EXPIRED IF YEAR LESS THAN 
    // EXPIRED IF SAME YEAR BUT MONTH LESS
    else if (expiredYear == (now->tm_year + 1900) && expiredMonth < (now->tm_mon +1)) {return true;}

    return false;
}

/**
 * @brief Marks the card as expired.
 * 
 * Sets the card's expiration date to "00/00" to indicate it is invalid,
 * updates the expiration status flag to true, and deactivates the card
 * by setting its activation status to false.
 */
void Card::markExpired()
{
    // Set expiration to a clearly invalid date
    expiration_ = "00/00";
    isExpired_ = true;
    setActivated(false);  // Deactivate when expired
}

/**
 * @brief gets the expiration date
 * 
 * @return A string representing the expiration date of the card
 */
std::string Card::getExpiration() const
{
    return expiration_;
}

/**
 * @brief get the card's CVV
 * 
 * @return A string representing the card's CVV
 */
std::string Card::getCvv() const
{
    return cvv_;
}
