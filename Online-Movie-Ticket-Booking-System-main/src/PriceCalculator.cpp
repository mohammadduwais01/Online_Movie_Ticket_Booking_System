#pragma once

#include <vector>

using namespace std;

// Forward declaration
class ShowSeat;

class PriceCalculator {
public:
    double calculateTotal(const vector<ShowSeat*>& seats) const {
        double total = 0.0;
        for (const ShowSeat* showSeat : seats) {
            total += showSeat->getSeat()->getPrice();
        }
        return total;
    }
};