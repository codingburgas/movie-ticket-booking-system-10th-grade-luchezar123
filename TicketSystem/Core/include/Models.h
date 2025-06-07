// Core/Header Files/classes.h
#pragma once
#include <iostream>
#include <vector>
using namespace std;

// Movie class
struct Movie {

    string title;
    string language;
    string genre;
    string releaseDate;
};

struct Seat {

    int row;
    int number;
    string type; 
    bool isBooked;
};

// Клас за прожекция
struct  Show {

    Movie movie;
    string time;

};

// Клас за зала
struct Hall {

    int number;
    vector<Seat> seats;
    vector<Show> shows;

};

// Клас за кино
struct Cinema {

    string name;
    string location;
    vector<Hall> halls;
};

// Базов клас за потребител
class User {
protected:
    string name;

public:
    User(string n) : name(n) {}
    virtual string getType() = 0;
};


// Клас за резервация
class Booking {
private:
    User* user;
    vector<Seat*> bookedSeats;
    string paymentMethod;

public:
    Booking(User* u, vector<Seat*> s, string p) : user(u), bookedSeats(s), paymentMethod(p) {
        for (auto seat : bookedSeats) {
           // seat->book();
        }
    }
};


// Seat class
//class Seat {
//private:
//    int row;
//    int number;
//    string type;
//    bool isBooked;
//
//public:
//    Seat(int r, int n, string t) : row(r), number(n), type(t), isBooked(false) {}
//    bool getStatus() { return isBooked; }
//    void book() { isBooked = true; }
//    string getType() { return type; }
//};

// ... Добавяме Show, Hall, Cinema, User, Booking, Admin, Customer по същия начин
