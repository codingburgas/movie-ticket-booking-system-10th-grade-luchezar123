#include "pch.h"
#include "Customer.h"
#include "misc.h"
void Customer::customerLogIn() {

    string userNameUser;
    string passWordUser;
    cout << "                      You have chosen customer menu!" << endl;
    cout << "You have to log in to use customer menu!" << endl << "Username: ";
    cin >> userNameUser;
    if (userNameUser == "user") {
        cout << "Password: ";
        cin >> passWordUser;
        if (passWordUser == "user") {
            clearscreen();
            cout << "                      You have logged in successfully!" << endl;
        }
        else {
            cout << "Incorrect password!";
            exit(0);
        }
    }
    else {
        cout << "Incorrect username!";
        exit(0);
    }
}

void Customer::customerMenu() {
    customerLogIn();
    while (true) {
        clearscreen();
        cout << "=== CUSTOMER MENU ===\n";
        cout << "1. Book a movie\n";
        cout << "2. Cancel a booking\n";
        cout << "3. Return to main menu\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;


        switch (choice) {
        case 1: bookMovie(); break;
        case 2: cancelBooking(); break;
        case 3: return;
        default: cout << "Invalid choice." << endl; break;
        }
        cout << "\nPress Enter to continue...";

        cin.get();
    }
}

void Customer::bookMovie() {
    clearscreen();
    vector<Movie> allMovies = loadMoviesFromFile();
    vector<Show> allShows = loadShowsFromFile();
    vector<Booking> allBookings = loadBookingsFromFile();

    if (allMovies.empty()) { cout << "No movies available." << endl; return; }

    showMovies(allMovies);

    cout << "Enter movie number to book: ";
    int movieChoice;
    cin >> movieChoice;
    if (movieChoice < 1 || movieChoice > allMovies.size()) {
        cout << "Invalid movie choice." << endl; return;
    }
    string selectedMovieTitle = allMovies[movieChoice - 1].title;

    clearscreen();
    showShowsForMovie(selectedMovieTitle, allShows);

    cout << "\nEnter show's ID to book: ";
    int showIdChoice;
    cin >> showIdChoice;

    Show selectedShow;
    bool showFound = false;
    for (const auto& show : allShows) {
        if (show.id == showIdChoice && show.movieTitle == selectedMovieTitle) {
            selectedShow = show;
            showFound = true;
            break;
        }
    }
    if (!showFound) { cout << "Show with this ID not found for the selected movie." << endl; return; }


    cout << "\nSelect seat type:\n1. Silver (base price)\n2. Gold (+5.00 BGN)\n3. Platinum (+10.00 BGN)\nChoice: ";
    int seatTypeChoice;
    cin >> seatTypeChoice;
    double finalPrice = selectedShow.price;
    string seatTypeStr = "Silver";
    if (seatTypeChoice == 2) { finalPrice += 5.0; seatTypeStr = "Gold"; }
    else if (seatTypeChoice == 3) { finalPrice += 10.0; seatTypeStr = "Platinum"; }


    cout << "Enter hall number (1-4): ";
    int hallNum;
    cin >> hallNum;
    if (hallNum < 1 || hallNum > 4) { hallNum = 1; }


    const int HALL_ROWS = 5;
    const int HALL_COLS = 8;
    bool seats[HALL_ROWS][HALL_COLS] = { {false} };
    for (const auto& booking : allBookings) {
        if (booking.showId == selectedShow.id) {
            seats[booking.seatRow][booking.seatCol] = true;
        }
    }

    clearscreen();
    cout << "--- SEAT SELECTION (X = booked) ---\n";
    for (int i = 0; i < HALL_ROWS; ++i) {
        for (int j = 0; j < HALL_COLS; ++j) {
            cout << (seats[i][j] ? "[X]" : "[ ]");
        }
        cout << endl;
    }

    int row, col;
    while (true) {
        cout << "\nEnter seat row: "; cin >> row;
        cout << "Enter seat column: "; cin >> col;
        if (row >= 0 && row < HALL_ROWS && col >= 0 && col < HALL_COLS) {
            if (!seats[row][col]) break;
            else cout << "Seat is already booked. Please choose another." << endl;
        }
        else {
            cout << "Invalid coordinates." << endl;
        }
    }


    // string placeholder;
    // cout << "\n--- Payment Information (simulation) ---\n";
    // cout << "Enter placeholder first name: "; cin >> placeholder;
    // cout << "Enter placeholder last name: "; cin >> placeholder;
    // cout << "Enter credit card number: "; cin >> placeholder;
    // cout << "Enter expiration date: "; cin >> placeholder;
    // cout << "Enter cvv: "; cin >> placeholder;


    Booking newBooking;
    newBooking.bookingId = time(0);
    newBooking.showId = selectedShow.id;
    newBooking.finalPrice = finalPrice;
    newBooking.seatType = seatTypeStr;
    newBooking.hallNum = hallNum;
    newBooking.seatRow = row;
    newBooking.seatCol = col;

    allBookings.push_back(newBooking);
    saveBookingsToFile(allBookings);

    cout << "\nBooking successful! Your ticket is confirmed." << endl;
}

void Customer::cancelBooking() {
    clearscreen();
    vector<Booking> allBookings = loadBookingsFromFile();
    if (allBookings.empty()) {
        cout << "No bookings available to cancel." << endl;
        return;
    }

    cout << "--- YOUR BOOKINGS ---" << endl;
    cout << left << setw(12) << "Booking ID" << setw(10) << "Show ID" << setw(10) << "Hall"
        << setw(10) << "Seat" << setw(12) << "Type" << "Price" << endl;
    cout << "----------------------------------------------------------------" << endl;
    for (const auto& b : allBookings) {
        cout << left << setw(12) << b.bookingId
            << setw(10) << b.showId
            << setw(10) << b.hallNum
            << setw(10) << ("(" + to_string(b.seatRow) + "," + to_string(b.seatCol) + ")")
            << setw(12) << b.seatType
            << fixed << setprecision(2) << b.finalPrice << endl;
    }

    cout << "\nEnter data for cancellation:" << endl;
    cout << "Enter Show ID: ";
    int showIdToCancel;
    cin >> showIdToCancel;

    cout << "Enter seat row: ";
    int rowToCancel;
    cin >> rowToCancel;

    cout << "Enter seat column: ";
    int colToCancel;
    cin >> colToCancel;

    bool found = false;
    for (auto it = allBookings.begin(); it != allBookings.end(); ++it) {
        if (it->showId == showIdToCancel && it->seatRow == rowToCancel && it->seatCol == colToCancel) {
            allBookings.erase(it);
            found = true;
            break;
        }
    }

    if (found) {
        saveBookingsToFile(allBookings);
        cout << "\nBooking for seat (" << rowToCancel << "," << colToCancel << ") for show "
            << showIdToCancel << " has been canceled." << endl;
    }
    else {
        cout << "\nBooking not found with the specified details." << endl;
    }
}