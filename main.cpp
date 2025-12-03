#include "Menu_methods.h"
using namespace std;

int main() {
    if (!login()) {
        return 0;
    }

    Hospital hospital;
    int choice;

    while (true) {
        showMenu();

        choice = getIntInput(0, 6);

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

        case 5:
            handleSearchPatient(hospital);
            break;

        case 6:
            system("cls");
            break;

        default:
            cout << "Unknown option. Please choose 0–4.\n";
            break;
        }
        cout << "\n\n\n\n\n";
    }

    return 0;
}
