
#include "pch.h"
#include <stdlib.h>
#include "misc.h"
void clearscreen() {
    system("cls");
}



vector<Movie> loadMoviesFromFile() {
    vector<Movie> movies;
    ifstream inFile("movies.txt");
    if (!inFile.is_open()) return movies;

    Movie m;
    while (getline(inFile, m.title) && getline(inFile, m.language) && getline(inFile, m.genre) && getline(inFile, m.releaseDate))
    {
        if (!m.title.empty()) {
            movies.push_back(m);
        }
    }
    return movies;
}

void saveMoviesToFile(const vector<Movie>& movies) {
    ofstream outFile("movies.txt");
    for (const auto& m : movies) {
        outFile << m.title << '\n' << m.language << '\n' << m.genre << '\n' << m.releaseDate << '\n';
    }
}

void showMovies(const vector<Movie>& movies) {
    cout << "======================== AVAILABLE MOVIES ========================" << endl;
    cout << left << setw(5) << "#" << setw(25) << "Title" << setw(15) << "Language" << setw(15) << "Genre" << "Release Date" << endl;
    cout << "------------------------------------------------------------------" << endl;

    if (movies.empty()) {
        cout << "No movies available." << endl;
    }
    else {
        for (size_t i = 0; i < movies.size(); ++i) {
            cout << left
                << setw(5) << to_string(i + 1) + "."
                << setw(25) << movies[i].title
                << setw(15) << movies[i].language
                << setw(15) << movies[i].genre
                << movies[i].releaseDate << endl;
        }
    }
    cout << "==================================================================" << endl << endl;
}



vector<Show> loadShowsFromFile() {
    vector<Show> shows;
    ifstream inFile("shows.txt");
    if (!inFile.is_open()) return shows;

    Show s;
    string priceStr, idStr;
    while (getline(inFile, idStr) && 
        getline(inFile, s.movieTitle) &&
        getline(inFile, s.dateTime) &&
        getline(inFile, priceStr) &&
        getline(inFile, s.cinemaName))
    {
        if (!s.movieTitle.empty()) {
            try {
                s.id = stoi(idStr);
                s.price = stod(priceStr);
                shows.push_back(s);
            }
            catch (...) {
                
            }
        }
    }
    return shows;
}

void saveShowsToFile(const vector<Show>& shows) {
    ofstream outFile("shows.txt");
    for (const auto& s : shows) {
        outFile << s.id << '\n' 
            << s.movieTitle << '\n'
            << s.dateTime << '\n'
            << s.price << '\n'
            << s.cinemaName << '\n';
    }
}


void showShowsForMovie(const string& movieTitle, const vector<Show>& allShows) {
    cout << "--- SHOWS FOR '" << movieTitle << "' ---" << endl;
    cout << left << setw(5) << "ID" << setw(25) << "Date & Time" << setw(15) << "Cinema" << "Price (BGN)" << endl;
    cout << "--------------------------------------------------------" << endl;

    bool found = false;
    for (const auto& show : allShows) {
        if (show.movieTitle == movieTitle) {
            cout << left << setw(5) << show.id
                << setw(25) << show.dateTime
                << setw(15) << show.cinemaName
                << fixed << setprecision(2) << show.price << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No shows available for this movie." << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}

vector<Booking> loadBookingsFromFile() {
    vector<Booking> bookings;
    ifstream file("bookings.txt");
    if (!file.is_open()) return bookings;

    Booking b;
    while (file >> b.bookingId >> b.showId >> b.finalPrice >> b.hallNum >> b.seatRow >> b.seatCol) {
        file.ignore(); 
        getline(file, b.seatType);
        bookings.push_back(b);
    }
    return bookings;
}

void saveBookingsToFile(const vector<Booking>& bookings) {
    ofstream file("bookings.txt");
    for (const auto& b : bookings) {
        file << b.bookingId << " " << b.showId << " " << b.finalPrice << " "
            << b.hallNum << " " << b.seatRow << " " << b.seatCol << " " << b.seatType << endl;
    }
}
string chooseCinema() {
    int cinema;
    while (true) {
        cout << "\nChoose a cinema:\n";
        cout << "1 - Cinema City\n";
        cout << "2 - Cinema Max\n";
        cout << "Enter your choice: ";
        cin >> cinema;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (cinema) {
        case 1:
            return "Cinema City";
        case 2:
            return "Cinema Max";
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    }
}

