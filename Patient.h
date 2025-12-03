#pragma once
#include <string>
#include <iostream>
#include <ctime>


/*
* Implementation of a petient class
*/
class Patient {

private:

	std::string name;  
	int severity;               // severity of illness (1-10)
	int id;                     // specific patient ID
	std::string arrivalTime;    // arrival time (e.g. Mon 09.08.2024)
	time_t arrivalTimeT;        // arrival time in time_t object
	static int SerializeID;     // static variable to assign ID for patients
	bool treated;

	std::string getCurrentTime();


public:

	// constructors
	Patient(std::string name, int severity);
	Patient();


	// getter methods
	std::string getName() const;
	int getID() const;
	int getSeverity() const;
	time_t getArrivalTime() const;
	bool isTreated() const;


	// setter methods
	void setName(std::string new_name);
	void setSeverity(int sev);
	void setTreated();

	// get patient information
	void getInfo() const;
	std::string getPatientInfo() const;
};

int Patient::SerializeID = 0;

// -------------------------------------------------------------------------------------------------
/*
* Private Methods
*/
std::string Patient::getCurrentTime() {
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

// -------------------------------------------------------------------------------------------------
/*
* Public methods
*/


// parametrized constructor
Patient::Patient(std::string name, int severity) {
	this->name = name;
	this->severity = severity;
	SerializeID++;
	this->id = SerializeID;
	arrivalTimeT = std::time(nullptr);
	treated = false;

	arrivalTime = getCurrentTime();
}


// default constructor
Patient::Patient() : name(""), severity(0), id(-1), arrivalTime(""), arrivalTimeT(std::time(nullptr)), treated(false) {}


// getter methods
std::string Patient::getName() const { return name; }
int Patient::getID() const { return id; }
int Patient::getSeverity() const { return severity; }
time_t Patient::getArrivalTime() const { return arrivalTimeT; }
bool Patient::isTreated() const { return treated; }



// setter methods
void Patient::setName(std::string new_name) { name = new_name; }
void Patient::setSeverity(int sev) { severity = sev; }
void Patient::setTreated() { treated = true; }



// print patient's info to the console
void Patient::getInfo() const {
	std::cout << "--- Patient Information ---" << std::endl;
	std::cout << "ID:        " << id << std::endl;
	std::cout << "Name:      " << name << std::endl;
	std::cout << "Severity:  " << severity << std::endl;
	std::cout << "Arrived:   " << arrivalTime << std::endl;
	std::cout << "---------------------------" << std::endl;
}


// get patient's info in string format
std::string Patient::getPatientInfo() const {
	return "ID: " + std::to_string(id) +
		", Name: " + name +
		", Severity: " + std::to_string(severity) +
		", Arrival: " + arrivalTime;
}

