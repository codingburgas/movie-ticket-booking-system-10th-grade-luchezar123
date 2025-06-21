#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct Movie {
    string title;
    string language;
    string genre;
    string releaseDate;
};


struct Show {
    int id = 0;
    string movieTitle;
    string dateTime;
    double price = 0.0;
    string cinemaName;
};


struct Booking {
    int bookingId = 0;
    int showId = 0;
    double finalPrice = 0.0;
    string seatType; 
    int hallNum = 0;
    int seatRow = 0;
    int seatCol = 0;
};
