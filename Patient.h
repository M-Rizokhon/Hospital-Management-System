#pragma once
#include <string>
#include <iostream>
#include <ctime>


// implementation of a patient class
class Patient {

private:

	std::string name;  
	int severity;    // severity of illness (1-10)
	int id;          // specific patient ID
	std::string arrivalTime;  
	time_t arrivalTimeT;
	static int SerializeID;     // static variable to assign ID for patients



	// get the current time
	std::string getCurrentTime() {
		std::time_t now = std::time(nullptr);   // get current time
		char buffer[26];
		ctime_s(buffer, sizeof(buffer), &now);      // convert it to string safely
		std::string timeStr(buffer);

		// remove a newline at the end of string
		if (!timeStr.empty() && timeStr.back() == '\n') {
			timeStr.pop_back();
		}

		return timeStr;
	}


public:

	// parametrized constructor
	Patient(std::string name, int severity) {
		this->name = name;
		this->severity = severity;
		SerializeID++;
		this->id = SerializeID;
		arrivalTimeT = std::time(nullptr);

		arrivalTime = getCurrentTime();
	}


	// default constructor
	Patient() : name(""), severity(0), id(-1), arrivalTime(""), arrivalTimeT(std::time(nullptr)) {}


	// getter methods
	std::string getName() const { return name; }
	int getID() const { return id; }
	int getSeverity() const { return severity; }
	time_t getArrivalTime() const { return arrivalTimeT; }


	// setter methods
	void setName(std::string new_name) { name = new_name; }
	void setSeverity(int sev) { severity = sev; }

	// print patient info to the console
	void getInfo() const {
		std::cout << "--- Patient Information ---" << std::endl;
		std::cout << "ID:        " << id << std::endl;
		std::cout << "Name:      " << name << std::endl;
		std::cout << "Severity:  " << severity << std::endl;
		std::cout << "Arrived:   " << arrivalTime << std::endl;
		std::cout << "---------------------------" << std::endl;
	}

	std::string getPatientInfo() const {
		return "ID: " + std::to_string(id) +
			", Name: " + name +
			", Severity: " + std::to_string(severity) +
			", Arrival: " + arrivalTime;
	}
};

int Patient::SerializeID = 0;