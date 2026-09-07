#pragma once

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


class Payment;

class CardPayment : public Payment {
private:
    string cardNumber;

public:
    explicit CardPayment(const string& cardNumber)
        : cardNumber(cardNumber) {}

    bool pay(double amount) override {
        bool valid = cardNumber.size() >= 4;
        if (valid) {
            cout << "Card payment of Rs. " << fixed << setprecision(2) << amount << " successful.\n";
        } else {
            cout << "Card payment failed: Invalid card number.\n";
        }
        return valid;
    }
};