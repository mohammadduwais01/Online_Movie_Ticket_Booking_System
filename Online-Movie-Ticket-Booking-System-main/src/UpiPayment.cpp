#pragma once

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Payment;

class UpiPayment : public Payment {
private:
    string upiId;

public:
    explicit UpiPayment(const string& upiId)
        : upiId(upiId) {}

    bool pay(double amount) override {
        if (upiId.empty())
            return false;

        cout << "UPI payment of Rs. " << fixed << setprecision(2) << amount 
             << " successful using " << upiId << ".\n";
        return true;
    }
};