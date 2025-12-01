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
	long long arrivalTime; 
	static int SerializeID;

public:

	// constructor
	Patient(string name, int severity) {
		this->name = name;
		this->severity = severity;
		SerializeID++;
		this->id = SerializeID;

		arrivalTime = time(nullptr);
	}

	// default constructor
	Patient() : name(""), severity(0), id(-1), arrivalTime(0) {}


	// getter and setter
	string getName() const { return name; }
	int getID() const { return id; }
	int getSeverity() const { return severity; }
	long long getArrivalTime() const { return arrivalTime; }

	// setter
	void setName(string new_name) { name = new_name; }
	void setSeverity(int sev) { severity = sev; }

	// comparison for BST (priority)
	// return true if THIS patient has higher priority

	//bool higherPriorityThan(Patient other) {
	//	if (severity != other.severity) {
	//		return severity > other.severity;
	//	}
	//	return arrivalTime < other.arrivalTime;
	//}

	// getInfo
	void getInfo() {
		cout << "--- Patient Information ---" << endl;
		cout << "ID:        " << id << endl;
		cout << "Name:      " << name << endl;
		cout << "Severity:  " << severity << endl;
		cout << "Arrived:   " << arrivalTime << endl;
		cout << "---------------------------" << endl;
	}

	string getPatientInfo() {
		return "ID: " + to_string(id) +
			", Name: " + name +
			", Severity: " + to_string(severity) +
			", Arrival: " + to_string(arrivalTime);
	}
};
int Patient::SerializeID = 0;