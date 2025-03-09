#include <iostream>
#include <string>
using namespace std;

void menu()
{
    int menu;
    cout << "Choose in which menu you want to enter" << endl << "1 for admin" << endl << "2 for customer" << endl;
    cin >> menu;
    switch (menu)
    {
    case 1:
        cout << "You have entered admin menu";
        break;
    case 2:
        cout << "You have entered customer menu";;
        break;
    default:
        cout << "Incorrect input";
    }
}
void cinema()
{
    int cinema;
    cout << "Choose in which cinema you want to go" << endl << "1 for cinemaCity" << endl << "2 for cinemaMax" << endl;
    cin >> cinema;
    switch (cinema)
    {
    case 1:
        cout << "You have entered cinemaCity";
        break;
    case 2:
        cout << "You have entered cinemaMax";;
        break;
    default:
        cout << "Incorrect input";
    }
}
int main()
{

    menu();
    cinema();
}