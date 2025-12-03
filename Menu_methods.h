#pragma once
#include <iostream>
#include <limits>
#include <conio.h>
#include "Hospital.h"

//using namespace std;


// Method to get the user input for a choice from the menu
int getIntInput(int min, int max) {
    int value;
    while (true) {
        if (std::cin >> value && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear leftover '\n'
            return value;
        }
        else {
            std::cin.clear(); // clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input. Enter a number between " << min << " and " << max << ": ";
        }
    }
}


// Method to register a new patient
void handleRegister(Hospital& hospital) {
    std::string name;
    std::string department;
    int severity;

    std::cout << "Enter patient name: ";
    std::getline(std::cin, name);

    if (name.empty()) {
        std::cout << "Patient name cannot be empty.\n";
        return;
    }

    std::cout << "Enter severity (1 - 10): ";
    severity = getIntInput(1, 10);
    std::cin.sync();
    
    if (severity >= hospital.getCriticalThreshold()) {
        std::cout << "Enter the department: ";
        std::getline(std::cin, department);

        if (department.empty()){
            std::cout << "Department cannot be left blank\n";
            return;
        }

        bool validDep = false;
        if (department == "emergency" ||
            department == "pediatrics" ||
            department == "cardiology" ||
            department == "general OPD") validDep = true;

        if (!validDep) {
            std::cout << "Invalid department\n";
            return;
        }

        hospital.registerPatient(name, severity, department);
        
    }
    else {
        hospital.registerPatient(name, severity);
    }

}


// Method to search for a patient 
void handleSearchPatient(Hospital& hospital) {
    int patientID;

    std::cout << "Enter the patient ID: ";
    std::cin >> patientID;

    int flag = hospital.searchPatient(patientID);

    if (flag == -1) {
        std::cout << "The patient has never been to our hospital\n";
    }
    else if (flag == 1) {
        std::cout << "The patient has already been treated\n";
    }
    else {
        std::cout << "The patient is waiting to be treated\n";
    }
}


// Method to display the menu
void showMenu() {
    std::cout << "\n=====================================\n";
    std::cout << "      HOSPITAL MANAGEMENT SYSTEM     \n";
    std::cout << "=====================================\n";
    std::cout << "1. Register new patient\n";
    std::cout << "2. Consult next patient\n";
    std::cout << "3. Show waiting patients\n";
    std::cout << "4. Show visit history\n";
    std::cout << "5. Search for a patient\n";
    std::cout << "6. Clear the console\n";
    std::cout << "0. Exit\n";
    std::cout << "-------------------------------------\n";
    std::cout << "Enter choice: ";
}






// ------------------------------------------------------------------------------------------------------------------------
// Methods related to login
std::string getPassword() {
    std::string password;
    char ch;
    std::cout << "Enter admin password: ";
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        }
        else {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}

bool login() {
    const std::string adminPassword = "12345";
    std::string input;

    std::cout << "====== Hospital System Login ======\n";

    for (int attempts = 1; attempts <= 5; attempts++) {
        input = getPassword();

        if (input == adminPassword) {
            std::cout << "\nAccess granted. Welcome, admin!\n\n";
            return true;
        }
        else {
            std::cout << "Incorrect password. (" << attempts << "/5 attempts)\n";
        }
    }

    std::cout << "\nToo many failed attempts. Program locked.\n";
    return false;
}