#pragma once
#include <iostream>
#include "Patient.h"
#include "BST.h"
#include "CircularQueue.h"
#include "LinkedList.h"


class Hospital {
private:
	LinkedList history;
	BST criticalPatients;
	CircularQueue ordinaryPatients;

	static const int CRITICAL_THRESHOLD = 9;

	// helper : register into queue
	void register_queue(const Patient& p) {
		ordinaryPatients.enqueue(p);
		cout << "[Reception] Ordinary patient registered in QUEUE." << endl;
	}

	// helper : register into BST
	void register_BST(const Patient& p) {
		criticalPatients.insert(p);
		cout << "[Reception] CRITICAL patient registered in BST." << endl;
	}

	// helper : add to history
	void add_to_history(const Patient& p) {
		history.addHistory(p);
	}

	// helper : consult from BST 
	bool consult_from_BST() {
		if (criticalPatients.isEmpty()) {
			return false;
		}

		Patient p;

		if (!criticalPatients.getHighestPriority(p)) {
			return false;
		}

		// remove from BST
		criticalPatients.remove(p);

		// Add to history
		add_to_history(p);

		cout << "\n[Doctor] Consulting CRITICAL patient:" << endl;
		p.getInfo();

		return true;
	}
	// helper : consult from queue
	bool consult_from_queue() {
		if (ordinaryPatients.isEmpty()) {
			return false;
		}
		Patient p = ordinaryPatients.dequeue();
		add_to_history(p);

		cout<<"\n[Doctor] Consulting ordinary patient:"<<endl;
		p.getInfo();
		return true;
	}

public:
	// default destructor
	Hospital() = default;

	// Registration 

	// create Patient
	void registerPatient(const string& name, int severity) {
		Patient p(name, severity);
		registerPatient(p); // overloading
	}

	void registerPatient(const Patient& p) {
		if (p.getSeverity() >= CRITICAL_THRESHOLD) {
			register_BST(p);
		}
		else {
			register_queue(p);
		}
	}

	// Consulatation

	void consultNextPatient() {
		// critical first
		if (consult_from_BST()) {
			return;
		}

		// then normal queue
		if (consult_from_queue()) {
			return;
		}

		cout << "\n[Doctor] No patients waiting." << endl;
	}

	// Display patients
	void displayWaitingPatients() const {
		std::cout << "\n===== Ordinary Patients (Queue, FIFO) =====\n";
		ordinaryPatients.display();

		std::cout << "\n===== Critical Patients (BST, Inorder) =====\n";
		criticalPatients.printDescending();
	}

	// display visit history
	void displayHistory() const {
		std::cout << "\n===== Patient Visit History =====\n";
		history.print();
		std::cout << "=================================\n";
	}

	// check anything is waiting
	bool hasWaitingPatients() const {
		return !criticalPatients.isEmpty() || !ordinaryPatients.isEmpty();
	}


};