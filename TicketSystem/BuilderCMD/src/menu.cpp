
#include "Menu.h"
#include "Models.h"
#include <string>
#include <fstream>
//#include <windows.h>
//#pragma comment(lib,"kernel32.lib")
#include <iostream>
void clearscreen()
{
	system("cls");
}

void Admin::adminLogIn()
{
	string userName;
	string passWord;
	cout << "                               You have chosen admin menu!" << endl;
	cout << "You have to log in to use admin menu!" << endl << "Username: ";
	cin >> userName;
	if (userName == "admin")
	{
		cout << "Password: ";
		cin >> passWord;
		if (passWord == "admin")
		{
			clearscreen();
			cout << "                       You have loged in successfully!" << endl;
		}
		else
		{
			cout << "Incorrect password!";
			exit(0);
		}
	}
	else
	{
		cout << "Incorrect username!";
		exit(0);
	}
}
void Customer::customerLogIn()
{
	string userNameUser;
	string passWordUser;
	cout << "                               You have chosen customer menu!" << endl;
	cout << "You have to log in to use customer menu!" << endl << "Username: ";
	cin >> userNameUser;
	if (userNameUser == "user")
	{
		cout << "Password: ";
		cin >> passWordUser;
		if (passWordUser == "user")
		{
			clearscreen();
			cout << "                       You have loged in successfully!" << endl;
		}
		else
		{
			cout << "Incorrect password!";
			exit(0);
		}
	}
	else
	{
		cout << "Incorrect username!";
		exit(0);
	}
}
static vector<Movie> loadMoviesFromFile();
static void saveMoviesToFile(const vector<Movie>& movies);
static void showMovies(const vector<Movie>& movies);


//void Admin::viewHallsAndShows(const string& cinemaName) {
//	ifstream inFile(cinemaName + "_halls.txt");
//	if (!inFile.is_open()) {
//		cout << "No halls found for cinema: " << cinemaName << endl;
//		return;
//	}
//
//	int hallCount = 0;
//	while (!inFile.eof()) {
//		Hall h;
//		if (!(inFile >> h.number)) break;
//		++hallCount;
//		cout << "\n--- Hall " << h.number << " ---\n";
//
//		int seatCount;
//		inFile >> seatCount;
//		inFile.ignore();
//		for (int i = 0; i < seatCount; ++i) {
//			Seat s;
//			inFile >> s.row >> s.number >> s.type >> s.isBooked;
//			h.seats.push_back(s);
//		}
//
//		int showCount;
//		inFile >> showCount;
//		inFile.ignore();
//		for (int i = 0; i < showCount; ++i) {
//			Show show;
//			getline(inFile, show.movie.title);
//			getline(inFile, show.movie.language);
//			getline(inFile, show.movie.genre);
//			getline(inFile, show.movie.releaseDate);
//			getline(inFile, show.time);
//			h.shows.push_back(show);
//		}
//
//		// Показване на шоута
//		for (size_t i = 0; i < h.shows.size(); ++i) {
//			cout << "\nShow " << i + 1 << ":\n";
//			cout << "  Title: " << h.shows[i].movie.title << '\n';
//			cout << "  Language: " << h.shows[i].movie.language << '\n';
//			cout << "  Genre: " << h.shows[i].movie.genre << '\n';
//			cout << "  Release Date: " << h.shows[i].movie.releaseDate << '\n';
//			cout << "  Time: " << h.shows[i].time << '\n';
//		}
//	}
//
//	if (hallCount == 0)
//		cout << "No halls available for this cinema.\n";
//}
//


void Admin::createOrDeleteMovie()
{
	vector<Movie> movies = loadMoviesFromFile();

	cout << "Choose what you wnat to do" << endl << "1 for adding a new movie" << endl << "2 for deleting an existing movie" << endl;

	int inAdminMenuChoice;
	cin >> inAdminMenuChoice;
	switch (inAdminMenuChoice)
	{
	case 1:
		clearscreen();
		cout << "Add new movie" << endl;

		{
			string title, language, genre, releaseDate;

			cin.ignore();
			cout << "Title: ";
			getline(cin, title);

			cout << "Language: ";
			getline(cin, language);

			cout << "Genre: ";
			getline(cin, genre);

			cout << "Date of release: ";
			getline(cin, releaseDate);

			Movie newMovie{ title, language, genre, releaseDate };
			movies.push_back(newMovie);

			saveMoviesToFile(movies);

			cout << "\nMovie added successfully" << endl;
			cout << "Title: " << newMovie.title << endl;
			cout << "Language: " << newMovie.language << endl;
			cout << "Genre: " << newMovie.genre << endl;
			cout << "Date: " << newMovie.releaseDate << endl;
		}
		break;

	case 2:
		clearscreen();
		cout << "Delete an existing movie" << endl;

		if (movies.empty()) {
			cout << "No movies available to delete." << endl;
			break;
		}

		showMovies(movies);

		cout << "Enter the number of the movie to delete: ";
		int delIndex;
		cin >> delIndex;

		if (delIndex < 1 || delIndex >(int)movies.size()) {
			cout << "Invalid movie number." << endl;
			break;
		}

		// Изтриване на избрания филм
		movies.erase(movies.begin() + (delIndex - 1));

		saveMoviesToFile(movies);

		cout << "Movie deleted successfully." << endl;
		break;

	default:
		cout << "Invalid choice" << endl;
	}
}

void Admin::createHallAndShow(string cinemaName) {
	vector<Hall> halls;

	// Зареждане на съществуващи зали (ако има)
	ifstream inFile(cinemaName + "_halls.txt");
	if (inFile.is_open()) {
		
		while (!inFile.eof()) {
			Hall h;
			inFile >> h.number;
			int seatCount;
			inFile >> seatCount;
			inFile.ignore(); // прескача newline
			for (int i = 0; i < seatCount; ++i) {
				Seat s;
				inFile >> s.row >> s.number >> s.type >> s.isBooked;
				h.seats.push_back(s);
			}

			int showCount;
			inFile >> showCount;
			inFile.ignore(); // прескача newline
			for (int i = 0; i < showCount; ++i) {
				Show show;
				getline(inFile, show.movie.title);
				getline(inFile, show.movie.language);
				getline(inFile, show.movie.genre);
				getline(inFile, show.movie.releaseDate);
				getline(inFile, show.time);
				h.shows.push_back(show);
			}

			halls.push_back(h);
		}
	}

	clearscreen();
	Hall newHall;
	cout << "Enter hall number: ";
	cin >> newHall.number;

	// Създаване на 5x10 места
	for (int r = 1; r <= 5; ++r) {
		for (int n = 1; n <= 10; ++n) {
			Seat s;
			s.row = r;
			s.number = n;
			s.type = "standard";
			s.isBooked = false;
			newHall.seats.push_back(s);
		}
	}

	// Зареждане на филмите
	vector<Movie> movies = loadMoviesFromFile();
	if (movies.empty()) {
		cout << "No movies available. Add movies first.\n";
		return;
	}

	int howMany;
	cout << "How many shows do you want to add to this hall? ";
	cin >> howMany;
	cin.ignore();

	for (int i = 0; i < howMany; ++i) {
		cout << "\nChoose movie for show " << i + 1 << ":\n";
		for (size_t j = 0; j < movies.size(); ++j) {
			cout << j + 1 << ". " << movies[j].title << endl;
		}
		
		int movieIndex;
		cin >> movieIndex;
		cin.ignore();

		if (movieIndex < 1 || movieIndex >(int)movies.size()) {
			cout << "Invalid index. Skipping show.\n";
			continue;
		}

		Show show;
		show.movie = movies[movieIndex - 1];
		cout << "Enter time for show (e.g., 18:00): ";
		getline(cin, show.time);

		newHall.shows.push_back(show);
	}

	halls.push_back(newHall);

	// Записване във файл
	 string tempFilename = cinemaName + "_halls_temp.txt";
	 ofstream outFile(tempFilename);

	for (const auto& h : halls) {
		outFile << h.number << '\n';
		outFile << h.seats.size() << '\n';
		for (const auto& s : h.seats) {
			outFile << s.row << ' ' << s.number << ' ' << s.type << ' ' << s.isBooked << '\n';
		}
		outFile << h.shows.size() << '\n';
		for (const auto& sh : h.shows) {
			outFile << sh.movie.title << '\n'
				<< sh.movie.language << '\n'
				<< sh.movie.genre << '\n'
				<< sh.movie.releaseDate << '\n'
				<< sh.time << '\n';
		}
	}
	 outFile.close();
	 remove((cinemaName + "_halls.txt").c_str());
	 rename(tempFilename.c_str(), (cinemaName + "_halls.txt").c_str());

	cout << "Hall and shows added successfully to " << cinemaName << ".\n";
}







void showMovies(const vector<Movie>& movies) {
    if (movies.empty()) {
        cout << "No movies available." << endl;
        return;
    }
    for (size_t i = 0; i < movies.size(); ++i) {
        cout << i + 1 << ". " << movies[i].title << " (" << movies[i].releaseDate << ")" << endl;
    }
}
void saveMoviesToFile(const vector<Movie>& movies) {
	ofstream outFile("movies.txt");
	for (const auto& m : movies) {
		outFile << m.title << '\n'
			<< m.language << '\n'
			<< m.genre << '\n'
			<< m.releaseDate << '\n';
	}
}
vector<Movie> loadMoviesFromFile() {
	vector<Movie> movies;
	ifstream inFile("movies.txt");
	if (!inFile.is_open()) return movies; // ако няма файл - връщаме празен вектор

	while (inFile.peek() != EOF) {
		Movie m;
		getline(inFile, m.title);
		getline(inFile, m.language);
		getline(inFile, m.genre);
		getline(inFile, m.releaseDate);

		if (!m.title.empty())  // проверка, за да не добавя празен филм ако файлът е свършил
			movies.push_back(m);
	}
	return movies;
}


void Admin::adminMenu()
{
	adminLogIn();
	while (true) {
		clearscreen();
		chooseCinema();
		string cinemaName = "cinemaCity"; // по избор, зависи какво е избрано от chooseCinema()
		// viewHallsAndShows(cinemaName);
		createHallAndShow(cinemaName);

		createOrDeleteMovie();
		

	}
}

void Customer::customerMenu()
{
	clearscreen();
	customerLogIn();
}

void chooseCinema()
{
	clearscreen();
	int cinema;
	cout << "Choose in which cinema you want to go" << endl << "1 for cinemaCity" << endl << "2 for cinemaMax" << endl << "3 for login choice" << endl;
	cin >> cinema;
	switch (cinema)
	{
	case 1: clearscreen();
		cout << "You have entered cinemaCity";
		break;
	case 2: clearscreen();
		cout << "You have entered cinemaMax";;
		break;
	case 3: clearscreen();
		menuChoice();
	default: clearscreen();
		cout << "Incorrect input";
	}
	cout << endl;

}






void menuChoice()
{
	Customer* customerPtr = new Customer;
	Admin* adminPtr = new Admin;

	cout << "Select menu" << endl << "1 For customers" << endl << "2 For Admin" << endl;

	int menuChoose;
	cin >> menuChoose;
	clearscreen();
	switch (menuChoose)
	{
	case 1:
		customerPtr->customerMenu();

		break;
	case 2:
		adminPtr->adminMenu();

		break;
	default:
		clearscreen();
		cout << "Incorrect input!";

	}

	delete customerPtr;
	delete adminPtr;
}


