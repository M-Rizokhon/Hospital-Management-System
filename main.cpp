#include <iostream>
#include <limits>
#include "Hospital.h"

using namespace std;

void showMenu() {
    cout << "\n=====================================\n";
    cout << "      HOSPITAL MANAGEMENT SYSTEM     \n";
    cout << "=====================================\n";
    cout << "1. Register new patient\n";
    cout << "2. Consult next patient\n";
    cout << "3. Show waiting patients\n";
    cout << "4. Show visit history\n";
    cout << "0. Exit\n";
    cout << "-------------------------------------\n";
    cout << "Enter choice: ";
}


int main() {
    Hospital hospital;
    int choice;

    while (true) {
        showMenu();

        if (!(cin >> choice)) {
            // handle non-numeric input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover '\n'

        if (choice == 0) {
            cout << "Exiting... Bye!\n";
            break;
        }

        switch (choice) {
        case 1: {
            string name;
            int severity;

            cout << "Enter patient name: ";
            getline(cin, name);

            cout << "Enter severity (0 - 10): ";
            while (!(cin >> severity) || severity < 0 || severity > 10) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid severity. Enter a number from 0 to 10: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            hospital.registerPatient(name, severity);
            break;
        }

        case 2:
            hospital.consultNextPatient();
            break;

        case 3:
            hospital.displayWaitingPatients();
            break;

        case 4:
            hospital.displayHistory();
            break;

        default:
            cout << "Unknown option. Please choose 0–4.\n";
            break;
        }
    }

    return 0;
}
