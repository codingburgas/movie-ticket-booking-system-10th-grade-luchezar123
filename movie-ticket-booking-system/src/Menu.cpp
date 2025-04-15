#include "../Menu.h"

Admin* adminPtr = new adminPtr;
Customer* CustomerPtr = new CustomerPtr;

void Admin::adminMenu()
{
    cout << "You have selected the admin menu!";
}
void Customer::customerMenu()
{
    cout << "You have selected the customer menu!";
}

void menuChoice()
{
    cout << "Select menu" << endl << "1 for custumers" << endl << "2 for admin" << endl;
    int menuChoose;
    cin >> menuChoose;

    switch(menuChoose)
    {
        case 1:
        customerPtr->customerMenu();
        break;
        case 2:
        adminPtr->adminMenu();
        break;
        default:
        cout << "Incorrect input!";
        break;
    }
}

delete adminPtr;
delete CustomerPtr;