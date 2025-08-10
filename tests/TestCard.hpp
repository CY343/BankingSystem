#ifndef TESTCARD_HPP
#define TESTCARD_HPP

#include "Card.hpp"

class TestCard : public Card {
public:
    TestCard() : Card() {}
    TestCard(bool activated, bool expired) : Card(activated, expired) {}

    // Expose protected getters
    std::string getTestExpiration() const { return getExpiration(); }
    std::string getTestCvv() const { return getCvv(); }

    // Expose protected static generators
    static std::string generateTestExpiryDate(int validYears = 3) {
        return generateExpiryDate(validYears);
    }
    static std::string generateTestCVV() {
        return generateCVV();
    }

    // Implement abstract functions (dummy)
    bool processPayment(double amount) override { return true; }
    bool checkIfExpired() override { return isExpired(); }
};

#endif
