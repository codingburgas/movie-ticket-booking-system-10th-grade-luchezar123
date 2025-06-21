#pragma once


void clearscreen();


vector<Movie> loadMoviesFromFile();
void saveMoviesToFile(const vector<Movie>& movies);
void showMovies(const vector<Movie>& movies);

vector<Show> loadShowsFromFile();
void saveShowsToFile(const vector<Show>& shows);
void showShowsForMovie(const string& movieTitle, const vector<Show>& allShows);

vector<Booking> loadBookingsFromFile();
void saveBookingsToFile(const vector<Booking>& bookings);

string chooseCinema();

const std::string fileUsers = "users.txt";