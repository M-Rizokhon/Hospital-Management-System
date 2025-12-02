#include <iostream>
#include <limits>
#include <conio.h>
#include "Hospital.h"

using namespace std;

string getPassword() {
    string password;
    char ch;
    cout << "Enter admin password: ";
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

bool login() {
    const string adminPassword = "12345";
    string input;

    cout << "====== Hospital System Login ======\n";

    for (int attempts = 1; attempts <= 5; attempts++) {
        input=getPassword();

        if (input == adminPassword) {
            cout << "\nAccess granted. Welcome, admin!\n\n";
            return true;
        } else {
            cout << "Incorrect password. (" << attempts << "/5 attempts)\n";
        }
    }

    cout << "\nToo many failed attempts. Program locked.\n";
    return false;
}



int getIntInput(int min, int max) {
    int value;
    while (true) {
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover '\n'
            return value;
        } else {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Enter a number between " << min << " and " << max << ": ";
        }
    }
}

void handleRegister(Hospital &hospital) {
    string name;
    int severity;

    cout << "Enter patient name: ";
    getline(cin, name);

    if (name.empty()) {
        cout << "Patient name cannot be empty.\n";
        return;
    }

    cout << "Enter severity (0 - 10): ";
    severity = getIntInput(0, 10);

    hospital.registerPatient(name, severity);

}


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
    if (!login()) {
        return 0;
    }

    Hospital hospital;
    int choice;

    while (true) {
        showMenu();

        choice = getIntInput(0, 4);

        if (choice == 0) {
            cout << "Exiting... Bye!\n";
            break;
        }

        switch (choice) {
        case 1: {
            handleRegister(hospital);
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
