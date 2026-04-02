#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

void printLogo() {
    cout << "______     __     __   __     ______     __    __     ______\n";
    cout << "/\\  ___\\   /\\ \\   /\\ \"-.\\ \\   /\\  ___\\   /\\ \"-./  \\   /\\  __ \\\n";
    cout << "\\ \\ \\____  \\ \\ \\  \\ \\ \\-.  \\  \\ \\  __\\   \\ \\ \\-./\\ \\  \\ \\  __ \\\n";
    cout << " \\ \\_____\\  \\ \\_\\  \\ \\_\\\\\"\\_\\  \\ \\_____\\  \\ \\_\\ \\ \\_\\  \\ \\_\\ \\_\\\n";
    cout << "  \\/_____/   \\/_/   \\/_/ \\/_/   \\/_____/   \\/_/  \\/_/   \\/_/\\/_/\n";
    cout << "----------------------------------------------------------------\n\n";
}

int main() {
    vector<string> options = {
        "Search Movie",
        "Book Ticket",
        "View Bookings",
        "Admin Panel",
        "Exit"
    };

    int selected = 0;
    bool running = true;

    while (running) {
        system("cls");
        printLogo();

        for (int i = 0; i < options.size(); i++) {
            if (i == selected) {
                cout << " > " << options[i] << " < " << endl; 
            }
            else {
                cout << "   " << options[i] << endl;
            }
        }

        int key = _getch();

        if (key == 0 || key == 224) {
            switch (_getch()) { 
            case 72:
                if (selected > 0) selected--;
                break;
            case 80: 
                if (selected < options.size() - 1) selected++;
                break;
            }
        }
        else if (key == 13) { 
            system("cls");
            if (options[selected] == "Exit") {
                cout << "Exiting... Goodbye!" << endl;
                running = false;
            }
            else {
                cout << "You selected: " << options[selected] << endl;
                cout << "\nPress any key to return to menu...";
                _getch();
            }
        }
    }

    return 0;
}