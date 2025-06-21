#include "pch.h"
#include "Admin.h"
#include "misc.h"
#include <limits>
void Admin::adminLogIn() {
    string userName;
    string passWord;
    cout << "                      You have chosen admin menu!" << endl;
    cout << "You have to log in to use admin menu!" << endl << "Username: ";
    cin >> userName;
    if (userName == "admin") {
        cout << "Password: ";
        cin >> passWord;
        if (passWord == "admin") {
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
void Admin::manageMovies() {
    clearscreen();
    vector<Movie> movies = loadMoviesFromFile();
    showMovies(movies);

    cout << "Choose what you want to do:" << endl
        << "1. Add a new movie" << endl
        << "2. Delete an existing movie" << endl
        << "3. Go back" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        string title, language, genre, releaseDate;
        cout << "\n--- Add New Movie ---" << endl;
        cout << "Title: "; getline(cin, title);
        cout << "Language: "; getline(cin, language);
        cout << "Genre: "; getline(cin, genre);
        cout << "Release date: "; getline(cin, releaseDate);

        Movie newMovie{ title, language, genre, releaseDate };
        movies.push_back(newMovie);
        saveMoviesToFile(movies);
        cout << "\nMovie added successfully!" << endl;
        break;
    }
    case 2: {
        if (movies.empty()) {
            cout << "No movies available to delete." << endl;
            break;
        }
        cout << "\nEnter the number of the movie to delete: ";
        int delIndex;
        cin >> delIndex;

        if (delIndex >= 1 && delIndex <= (int)movies.size()) {
            movies.erase(movies.begin() + (delIndex - 1));
            saveMoviesToFile(movies);
            cout << "Movie deleted successfully." << endl;
        }
        else {
            cout << "Invalid movie number." << endl;
        }
        break;
    }
    case 3:
        return;
    default:
        cout << "Invalid choice." << endl;
    }
}
void Admin::addShow() {
    clearscreen();
    vector<Movie> movies = loadMoviesFromFile();
    vector<Show> shows = loadShowsFromFile();
    if (movies.empty()) {
        cout << "No movies exist. Please add a movie first." << endl;
        return;
    }
    showMovies(movies);

    cout << "--- Add New Show ---" << endl;
    cout << "Enter the number of the movie for the show: ";
    int movieIndex;
    cin >> movieIndex;

    if (movieIndex < 1 || movieIndex >(int)movies.size()) {
        cout << "Invalid movie number." << endl;
        return;
    }


    int nextId = 1;
    if (!shows.empty()) {
        nextId = shows.back().id + 1;
    }

    Show newShow;
    newShow.id = nextId;
    newShow.movieTitle = movies[movieIndex - 1].title;

    cout << "Enter show date and time (e.g., 25.12.2024 20:30): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newShow.dateTime);

    cout << "Enter price: ";
    cin >> newShow.price;


    newShow.cinemaName = chooseCinema();

    shows.push_back(newShow);
    saveShowsToFile(shows);

    cout << "\nShow for '" << newShow.movieTitle << "' with ID " << newShow.id << " added successfully!" << endl;

}
void Admin::deleteShow() {
    clearscreen();
    vector<Show> shows = loadShowsFromFile();
    if (shows.empty()) {
        cout << "No shows available to delete." << endl;
        return;
    }


    cout << "--- ALL SHOWS ---" << endl;
    for (const auto& s : shows) {
        cout << "ID: " << s.id << " - " << s.movieTitle << endl;
    }

    cout << "\nEnter the ID of the show to delete: ";
    int idToDelete;
    cin >> idToDelete;

    bool found = false;
    for (auto it = shows.begin(); it != shows.end(); ++it) {
        if (it->id == idToDelete) {
            shows.erase(it);
            found = true;
            break;
        }
    }

    if (found) {
        saveShowsToFile(shows);
        cout << "Show deleted successfully." << endl;
    }
    else {
        cout << "Show with that ID not found." << endl;
    }
}
void Admin::editShow() {
    clearscreen();
    vector<Show> shows = loadShowsFromFile();
    if (shows.empty()) {
        cout << "No shows available to edit." << endl;
        return;
    }

    cout << "--- ALL SHOWS ---" << endl;
    for (const auto& s : shows) {
        cout << "ID: " << s.id << " - " << s.movieTitle << endl;
    }

    cout << "\nEnter the ID of the show to edit: ";
    int idToEdit;
    cin >> idToEdit;

    bool found = false;
    for (auto& show : shows) {
        if (show.id == idToEdit) {
            cout << "\n--- Editing Show ID: " << show.id << " (" << show.movieTitle << ") ---" << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter new date and time(current: " << show.dateTime << "): " << endl;
            getline(cin, show.dateTime);
            cout << "Enter new price (current: " << show.price << "): ";
            cin >> show.price;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter new cinema name (current: " << show.cinemaName << "): ";
            getline(cin, show.cinemaName);
            found = true;
            break;
        }
    }
    if (found) {
        saveShowsToFile(shows);
        cout << "Show updated." << endl;
    }
    else {
        cout << "Show not found." << endl;
    }
}
void Admin::adminMenu() {
    adminLogIn();
    while (true) {
        vector<Movie> movies = loadMoviesFromFile();
        showMovies(movies);

        cout << "ADMIN MENU - What would you like to do?\n";
        cout << "1 - Manage Movies (Add/Delete)\n";
        cout << "2 - Add Show\n";
        cout << "3 - Delete Show\n";
        cout << "4 - Edit Show\n";
        cout << "5 - Return to main menu\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: manageMovies(); break;
        case 2: addShow(); break;
        case 3: deleteShow(); break;
        case 4: editShow(); break;
        case 5: return;
        default: cout << "Invalid choice!\n";
        }
        cout << "\nPress Enter to continue...";
        cin.get();
        clearscreen();
    }
}