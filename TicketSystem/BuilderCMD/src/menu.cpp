
#include "../Include/Menu.h"

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

void Admin::createOrDeleteMovie()
{
	cout << "Choose what you wnat to do" << endl << "1 for adding a new movie" << endl << "2 for deleting an existing movie" << endl;
	int inAdminMenuChoice;
	cin >> inAdminMenuChoice;
	switch (inAdminMenuChoice)
	{
	case 1:
		clearscreen();
		cout << "You have chosen to add a film!";
		break;
	case 2:
		clearscreen();
		cout << "You have chosen to delete an existing film!";
		break;
	default:
		clearscreen();
		cout << "Incorrect input";
		break;
	}
}
void Admin::adminMenu()
{
	clearscreen();
	adminLogIn();
	chooseCinema();
	createOrDeleteMovie();
}

void Customer::customerMenu()
{
	clearscreen();
	cout << "You have chosen customer menu!";
}

void chooseCinema()
{
	clearscreen();
	int cinema;
	cout << "Choose in which cinema you want to go" << endl << "1 for cinemaCity" << endl << "2 for cinemaMax" << endl;
	cin >> cinema;
	switch (cinema)
	{
	case 1: clearscreen();
		cout << "You have entered cinemaCity";
		break;
	case 2: clearscreen();
		cout << "You have entered cinemaMax";;
		break;
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


