#pragma once

class Seat;
enum class SeatStatus;

class ShowSeat {
private:
    Seat* seat;
   
    SeatStatus status;

public:
    explicit ShowSeat(Seat* seat)
        : seat(seat), status(SeatStatus::AVAILABLE) {}

    bool isAvailable() const {
        return status == SeatStatus::AVAILABLE;
    }

    bool bookSeat() {
        if (!isAvailable())
            return false;

        status = SeatStatus::BOOKED;
        return true;
    }

    void releaseSeat() {
        status = SeatStatus::AVAILABLE;
    }

    Seat* getSeat() const {
        return seat;
    }

    SeatStatus getStatus() const {
        return status;
    }
};