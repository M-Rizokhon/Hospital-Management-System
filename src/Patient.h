#pragma once
#include <string>
// implementation of a patient class



class Patient {
private:
	std::string name;
	int severity;
	int id;


public:
	// constructor
	Patient(std::string name, int severity, int id) : name(name), severity(severity), id(id) {}

	std::string getName() const { return name; }
	void setName(std::string new_name) { name = new_name; }

	int getID() const { return id; }
	void setID(int new_id) { id = new_id; }

    int getSeverity() const { return severity; }
    void setSeverity(int sev) { severity = sev; }


	void getInfo() const;

    std::string getPatientInfo() const {
        std::string info = "";
        info += "Name: " + name;
        info += "Severity: " + std::to_string(severity);
        info += "ID: " + std::to_string(id);

        return info;
    }

};



