#include <iostream>
#include "Menu.h"
using namespace std;
int main()
{
    vector<string> options =
    {
        "Search Movie",
        "Book Ticket",
        "View Bookings",
        "Admin Panel",
        "Exit"
    };
    Menu mainMenu(options);
    while (true)
    {
        int choice = mainMenu.display();
        system("cls");
        switch (choice)
        {
        case 0:
            cout << "Search Movie Selected\n";
            break;
        case 1:
            cout << "Book Ticket Selected\n";
            break;
        case 2:
            cout << "View Bookings Selected\n";
            break;
        case 3:
            cout << "Admin Panel Selected\n";
            break;
        case 4:
            return 0;
        }
        system("pause");
    }
}