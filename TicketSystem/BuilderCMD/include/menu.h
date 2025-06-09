#include <iostream>

using namespace std;

class Admin
{
    public:
    void adminMenu();
    void adminLogIn();
    void createOrDeleteMovie();
    void createHallAndShow(string cinemaName);
   // void viewHallsAndShows(const string& cinemaName);



};
class Customer
{
    public:
    void customerMenu();
    void customerLogIn();
};

void menuChoice();
void chooseCinema();

