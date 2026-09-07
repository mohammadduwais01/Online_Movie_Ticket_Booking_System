#pragma once

#include <string>

using namespace std;

// Forward references to types defined in Types.cpp
enum class SeatType;
extern const double SILVER_PRICE;
extern const double GOLD_PRICE;
extern const double PLATINUM_PRICE;

class Seat {
private:
    string seatNumber;
    SeatType seatType;
    double price;

    double calculatePrice(SeatType type) const {
        if (type == SeatType::SILVER)
            return SILVER_PRICE;

        if (type == SeatType::GOLD)
            return GOLD_PRICE;

        return PLATINUM_PRICE;
    }
    
public:
    // 'this' keyword or initializer list distinguishes attributes from constructor parameters.
    Seat(const string& seatNumber, SeatType seatType)
        : seatNumber(seatNumber),
          seatType(seatType),
          price(calculatePrice(seatType)) {}

    string getSeatNumber() const {
        return seatNumber;
    }

    SeatType getSeatType() const {
        return seatType;
    }

    double getPrice() const {
        return price;
    }
};