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
         CircularQueue ordinary_patients;
         void register_queue(Patient p);
         void delete_queue();
         void register_BST(Patient p);
         void delete_BST();
    
    public:
        void add_to_history(Patient p);
        void display_history();
        void register_patient(Patient p);
        void delete_patient();
    
        // consult patient
    };

	void Hospital::add_to_history(Patient p){
		History.addHistory(&p);
	}

	void Hospital::display_history(){
		History.print();
	}