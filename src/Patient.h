#pragma once
#include <string>
#include <iostream>
using namespace std;
// implementation of a patient class

class Patient {
private:
	string name;
	int severity;
	int id;

public:

	// constructor
	Patient(string name, int severity, int id) : name(name), severity(severity), id(id) {}

	// getter and setter
	string getName() { return name; }
	void setName(string new_name) { name = new_name; }

	int getID() { return id; }
	void setID(int new_id) { id = new_id; }

	int getSeverity() const { return severity; }
	void setSeverity(int sev) { severity = sev; }

	// getInfo
	void getInfo() {
		cout << "--- Patient Information ---" << endl;
		cout << "ID:        " << id << endl;
		cout << "Name:      " << name << endl;
		cout << "Severity:  " << severity << endl;
		cout << "---------------------------" << endl;
	}

    

	std::string getPatientInfo() const {
        std::string info = "";
        info += "Name: " + name;
        info += "Severity: " + std::to_string(severity);
        info += "ID: " + std::to_string(id);
        return info;
    }
};



