# Online Movie Ticket Booking System

A console-based Online Movie Ticket Booking System built with C++, featuring movie listings, showtime management, seat selection, ticket booking, and booking management through a structured and user-friendly interface.

## Features

* List movies with title, language and duration
* List shows with screen and time
* Display seat number, type and AVAILABLE/BOOKED status
* Book one or more seats
* Reject invalid, duplicate and already-booked seats without changing seat state
* Silver ₹150, Gold ₹250, Platinum ₹400 pricing
* UPI, Card and Cash payment
* Failed payment does not confirm a booking
* Print ticket after successful payment
* Cancel confirmed bookings and release seats
* Input validation

## Project Structure

```text
Online-Movie-Ticket-Booking-System/
├── README.md
├── .gitignore
├── src/
│   ├── Booking.cpp
│   ├── BookingService.cpp
│   ├── CardPayment.cpp
│   ├── CashPayment.cpp
│   ├── Cinema.cpp
│   ├── Customer.cpp
│   ├── Movie.cpp
│   ├── Payment.cpp
│   ├── PriceCalculator.cpp
│   ├── Screen.cpp
│   ├── Seat.cpp
│   ├── Show.cpp
│   ├── ShowSeat.cpp
│   ├── TicketPrinter.cpp
│   ├── Types.cpp
│   ├── UpiPayment.cpp
│   └── main.cpp
├── docs/
└── demo/