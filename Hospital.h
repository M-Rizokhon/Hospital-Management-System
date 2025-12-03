#pragma once
#include <iostream>
#include "Patient.h"
#include "../BST.h"
#include "../CircularQueue.h"
#include "../LinkedList.h"
#include "../Hash_map.h"

class Hospital {
private:
    LinkedList history;
    HashMap patientList;    

    //BST criticalPatients;
    CircularQueue ordinaryPatients;

    BST Emergency, Pediatrics, Cardiology, Gen_OPD;

    static const int CRITICAL_THRESHOLD = 9;

    // helper : register into queue
    void register_queue(const Patient& p);

    // helper : register into BST
    void register_BST(const Patient& p, std::string dep);

    // helper : add to history
    void add_to_history(const Patient& p);

    // helper : consult from BST 
    bool consult_from_BST();

    // helper : consult from queue
    bool consult_from_queue();

public:
    // default constructor
    Hospital() = default;

    // Registration 
    void registerPatient(const std::string& name, int severity, std::string dep="none");

    // Consultation
    void consultNextPatient();

    // Display patients
    void displayWaitingPatients() const;

    // Display visit history
    void displayHistory() const;

    // Check if any patients are waiting
    bool hasWaitingPatients() const;

    // Get the Critical Threshold
    int getCriticalThreshold() const;

    // Search for a patient
    int searchPatient(int patientID);
};

// ===== Method Definitions =====

void Hospital::register_queue(const Patient& p) {
    ordinaryPatients.enqueue(p);
    std::cout << "[Reception] Ordinary patient registered in QUEUE." << std::endl;
}

void Hospital::register_BST(const Patient& p, std::string dep) {
    if (dep == "emergency") Emergency.insert(p);
    else if (dep == "pediatrics") Pediatrics.insert(p);
    else if (dep == "cardiology") Cardiology.insert(p);
    else Gen_OPD.insert(p);

    std::cout << "[Reception] CRITICAL patient registered in BST (" << dep << ")." << std::endl;
}

void Hospital::add_to_history(const Patient& p) {
    history.addHistory(p);
}



/*
* Method to consult high-priority patients 
* from 4 different departments.
* 
* There is department-wise priority (top having the highest priority):
* 1. Emergency
* 2. Pediatrics
* 3. Cardiology
* 4. General OPD
* 
* Department wise priority is higher
* than severity based priority
*/
bool Hospital::consult_from_BST() {
    if (Emergency.isEmpty() &&
        Pediatrics.isEmpty() &&
        Cardiology.isEmpty() &&
        Gen_OPD.isEmpty()) return false;

    Patient p;
    if (!Emergency.isEmpty()) { Emergency.getHighestPriority(p); Emergency.remove(p); }
    else if (!Pediatrics.isEmpty()) { Pediatrics.getHighestPriority(p); Pediatrics.remove(p); }
    else if (!Cardiology.isEmpty()) { Cardiology.getHighestPriority(p); Cardiology.remove(p); }
    else if (!Gen_OPD.isEmpty()) { Gen_OPD.getHighestPriority(p); Gen_OPD.remove(p); }
    else return false;

    // remove from the corresponding department
    add_to_history(p);

    std::cout << "\n[Doctor] Consulting CRITICAL patient:" << std::endl;
    p.getInfo();

    p.setTreated();

    return true;
}

bool Hospital::consult_from_queue() {
    if (ordinaryPatients.isEmpty()) return false;

    Patient p = ordinaryPatients.dequeue();
    add_to_history(p);

    std::cout << "\n[Doctor] Consulting ordinary patient:" << std::endl;
    p.getInfo();

    p.setTreated();

    return true;
}

void Hospital::registerPatient(const std::string& name, int severity, std::string dep) {
    Patient p(name, severity);
    
    if (p.getSeverity() >= CRITICAL_THRESHOLD) {
        register_BST(p, dep);
    }
    else {
        register_queue(p);
    }
    patientList.insert(p.getID(), p);
}



void Hospital::consultNextPatient() {
    if (consult_from_BST()) return;
    if (consult_from_queue()) return;

    std::cout << "\n[Doctor] No patients waiting." << std::endl;
}

void Hospital::displayWaitingPatients() const {
    std::cout << "\n===== Ordinary Patients (Queue, FIFO) =====\n";
    ordinaryPatients.display();

    std::cout << "\n===== Critical Patients (BST, Inorder) =====\n";
    std::cout << "\n--- Emergency department ---\n";
    Emergency.printDescending();
    std::cout << "\n--- Pediatrics department ---\n";
    Pediatrics.printDescending();
    std::cout << "\n--- Cardiology department ---\n";
    Cardiology.printDescending();
    std::cout << "\n--- General OPD department ---\n";
    Gen_OPD.printDescending();

}

void Hospital::displayHistory() const {
    std::cout << "\n===== Patient Visit History =====\n";
    history.print();
    std::cout << "=================================\n";
}

bool Hospital::hasWaitingPatients() const {
    return (!Emergency.isEmpty() ||
        !Pediatrics.isEmpty() ||
        !Cardiology.isEmpty() ||
        !Gen_OPD.isEmpty() ||
        !ordinaryPatients.isEmpty());
}


int Hospital::getCriticalThreshold() const {
    return CRITICAL_THRESHOLD;
}


/*
* The method searchs for a patient (using hash map)
* It returns three different ouputs:
* 1  -> patient has already been treated
* 0  -> patient is waiting to be treated
* -1 -> patient has never been to the hospital (does not exist)
*/
int Hospital::searchPatient(int patientID) {
    BSTNode node = patientList.get(patientID);

    // Check if patient exists (id == -1 means default constructed, not found)
    if (node.data.getID() == -1) {
        return -1;
    }

    // Check if the patient has been treated
    if (node.data.isTreated()) {
        return 1;
    }

    // Patient is waiting to be treated
    return 0;
}
