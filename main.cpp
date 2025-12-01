#include <iostream>
#include "Hospital.h"

int main() {
    Hospital h;

    h.registerPatient("Asliddin", 5);
    h.registerPatient("Zafar", 9);
    h.registerPatient("Farangiz", 7);
    h.registerPatient("Shahnoza", 10);
    h.registerPatient("Sadriddin", 9);

    h.displayWaitingPatients();

    h.consultNextPatient();  
    h.consultNextPatient();  
    h.consultNextPatient();  
    h.consultNextPatient();  
    h.consultNextPatient();  

    h.displayHistory();
}
