#pragma once

#include <iostream>
#include <iomanip>

using namespace std;

// Forward declaration of base class Payment
class Payment;

class CashPayment : public Payment {
public:
    CashPayment() = default;

    bool pay(double amount) override {
        cout << "Cash payment of Rs. " << fixed << setprecision(2) << amount << " received.\n";
        return true;
    }
};