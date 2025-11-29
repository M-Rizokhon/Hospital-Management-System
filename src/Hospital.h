#include <iostream>
#include "Patient.h"

#include "DataStructures/BST.h"
#include "DataStructures/CircularQueue.h"
#include "DataStructures/LinkedList.h"

using namespace std;
class Hospital {
private:
	 LinkedList History;
	 BST priority_patients;
	 Circularqueue ordinary_patients;
public:
	void add_to_history(Patient p);
	void display_history();
	void register_BST(Patient p);
	void register_queue(Patient p);
	void register_patient(Patient p);
	void delete_BST();
	void delete_queue();
	void delete_patient();


	// consult patient
	

};