#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

#include "Types.cpp"
#include "Movie.cpp"
#include "Seat.cpp"
#include "ShowSeat.cpp"
#include "Screen.cpp"
#include "Show.cpp"
#include "Cinema.cpp"
#include "Customer.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "PriceCalculator.cpp"
#include "Booking.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"

// Returns a vector of original global indices matching the selected movie
vector<int> displayShows(const vector<Show>& shows, const vector<Movie>& movies, int movieIndex) {
    vector<int> matchingShowIndices;
    cout << "\n===== SHOWS =====\n";
    
    int displayIndex = 1;
    for (size_t i = 0; i < shows.size(); ++i) {
        if (shows[i].getMovie() != nullptr &&
            shows[i].getMovie()->getTitle() == movies[movieIndex].getTitle()) {
            
            cout << displayIndex << ". Screen " 
                 << shows[i].getScreen()->getScreenNumber() 
                 << " | " << shows[i].getStartTime() << "\n";
                 
            matchingShowIndices.push_back(i); // Save the actual global index
            displayIndex++;
        }
    }
    
    if (matchingShowIndices.empty()) {
        cout << "No shows available for this movie.\n";
    }
    
    return matchingShowIndices;
}

int readInteger(const string& message) {
    int value;
    while (true) {
        cout << message;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    // =========================
    // CREATE CINEMA
    // =========================
    Cinema cinema("Online Movie Ticket Booking Cinema");

    // =========================
    // CREATE MOVIES
    // =========================
    vector<Movie> movies;
    movies.emplace_back("3 Idiots", "Hindi", 170);
    movies.emplace_back("Interstellar", "English", 169);

    // =========================
    // CREATE SCREEN
    // =========================
    Screen screen1(1);
    screen1.addSeat(Seat("A1", SeatType::SILVER));
    screen1.addSeat(Seat("A2", SeatType::SILVER));
    screen1.addSeat(Seat("B1", SeatType::GOLD));
    screen1.addSeat(Seat("B2", SeatType::GOLD));
    screen1.addSeat(Seat("C1", SeatType::PLATINUM));
    cinema.addScreen(screen1);

    // =========================
    // CREATE SHOWS
    // =========================
    vector<Show> shows;
    shows.emplace_back(&movies[0], &cinema.getScreens()[0], "06:00 PM");
    shows.emplace_back(&movies[0], &cinema.getScreens()[0], "09:30 PM");
    shows.emplace_back(&movies[1], &cinema.getScreens()[0], "07:00 PM");

    // =========================
    // CREATE CUSTOMER
    // =========================
    Customer customer("Satvik", "9876543210");

    // =========================
    // CREATE BOOKING SERVICE
    // =========================
    BookingService bookingService;

    // =========================
    // MAIN MENU
    // =========================
    while (true) {
        cout << "\n\n====================================\n";
        cout << "    ONLINE MOVIE TICKET BOOKING\n";
        cout << "====================================\n";
        cout << "1. List Movies\n";
        cout << "2. List Shows\n";
        cout << "3. Display Seat Layout\n";
        cout << "4. Book Ticket\n";
        cout << "5. Cancel Booking\n";
        cout << "6. Exit\n";
        cout << "====================================\n";
        
        int choice = readInteger("Enter your choice: ");

        // 1. LIST MOVIES
        if (choice == 1) {
            cinema.listMovies(movies);
        }
        // 2. LIST SHOWS
        else if (choice == 2) {
            cinema.listMovies(movies);
            int movieChoice = readInteger("Select movie number: ");
            if (movieChoice < 1 || movieChoice > static_cast<int>(movies.size())) {
                cout << "Invalid movie selection.\n";
                continue;
            }
            displayShows(shows, movies, movieChoice - 1);
        }
        // 3. DISPLAY SEAT LAYOUT
        else if (choice == 3) {
            cinema.listMovies(movies);
            int movieChoice = readInteger("Select movie number: ");
            if (movieChoice < 1 || movieChoice > static_cast<int>(movies.size())) {
                cout << "Invalid movie selection.\n";
                continue;
            }
            vector<int> validShowIndices = displayShows(shows, movies, movieChoice - 1);
            if (validShowIndices.empty()) continue;

            int showChoice = readInteger("Select show number: ");
            if (showChoice < 1 || showChoice > static_cast<int>(validShowIndices.size())) {
                cout << "Invalid show selection.\n";
                continue;
            }

            int actualIndex = validShowIndices[showChoice - 1];
            shows[actualIndex].displaySeats();
        }
        // 4. BOOK TICKET
        else if (choice == 4) {
            cinema.listMovies(movies);
            int movieChoice = readInteger("Select movie number: ");
            if (movieChoice < 1 || movieChoice > static_cast<int>(movies.size())) {
                cout << "Invalid movie selection.\n";
                continue;
            }
            vector<int> validShowIndices = displayShows(shows, movies, movieChoice - 1);
            if (validShowIndices.empty()) continue;

            int showChoice = readInteger("Select show number: ");
            if (showChoice < 1 || showChoice > static_cast<int>(validShowIndices.size())) {
                cout << "Invalid show selection.\n";
                continue;
            }

            // Correct mapping to global array
            int actualIndex = validShowIndices[showChoice - 1];
            Show& selectedShow = shows[actualIndex];
            selectedShow.displaySeats();

            int numberOfSeats = readInteger("How many seats do you want to book? ");
            if (numberOfSeats < 1) {
                cout << "At least one seat must be selected.\n";
                continue;
            }

            vector<string> seatNumbers;
            for (int i = 0; i < numberOfSeats; ++i) {
                string seatNumber;
                cout << "Enter seat " << i + 1 << ": ";
                cin >> seatNumber;
                seatNumbers.push_back(seatNumber);
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // PAYMENT METHOD
            cout << "\n===== PAYMENT METHOD =====\n";
            cout << "1. UPI\n";
            cout << "2. Card\n";
            cout << "3. Cash\n";
            int paymentChoice = readInteger("Select payment method: ");

            Payment* payment = nullptr;
            UpiPayment upiPayment("");
            CardPayment cardPayment("");
            CashPayment cashPayment;

            if (paymentChoice == 1) {
                string upiId;
                cout << "Enter UPI ID: ";
                cin >> upiId;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                upiPayment = UpiPayment(upiId);
                payment = &upiPayment;
            }
            else if (paymentChoice == 2) {
                string cardNumber;
                cout << "Enter card number: ";
                cin >> cardNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cardPayment = CardPayment(cardNumber);
                payment = &cardPayment;
            }
            else if (paymentChoice == 3) {
                payment = &cashPayment;
            }
            else {
                cout << "Invalid payment method.\n";
                continue;
            }

            bookingService.bookTicket(&customer, selectedShow, seatNumbers, payment);
        }
        // 5. CANCEL BOOKING
        else if (choice == 5) {
            int bookingId = readInteger("Enter booking ID: ");
            bookingService.cancelBooking(bookingId);
        }
        // 6. EXIT
        else if (choice == 6) {
            cout << "\nThank you for using Online Movie Ticket Booking System!\n";
            break;
        }
        else {
            cout << "Invalid menu choice. Please select 1-6.\n";
        }
    }
    return 0;
}