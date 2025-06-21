#include <iostream>
#include "Menu.h"
#include "misc.h"
#include "Customer.h"
#include "Admin.h"

void menuChoice() {
 
    while (true) {
        clearscreen();
        cout << "========================================" << endl;
        cout << "   MOVIE TICKET BOOKING SYSTEM" << endl;
        cout << "========================================" << endl;
        cout << "\nSelect menu:" << endl
            << "1. For Customers" << endl
            << "2. For Admin" << endl
            << "3. Exit" << endl;
        cout << "Enter your choice: ";

        int menuChoose;
        cin >> menuChoose;

        clearscreen();

        switch (menuChoose) {
        case 1: {
            Customer customer;
            customer.customerMenu();
            break;
        }
        case 2: {
            Admin admin;
            admin.adminMenu();
            break;
        }
        case 3:
            cout << "Exiting application. Goodbye!" << endl;
            return;
        default:
            cout << "Incorrect input!" << endl;
        }

        cout << "\nPress Enter to return to the main menu...";
       // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}
