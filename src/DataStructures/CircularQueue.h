#pragma once
#include <iostream>
using namespace std;
# include <..Patient.h>
// Node
class Node {
public:
	Patient data;
	Node* next;
};

// CircularQueue 
class CircularQueue {
private:
	Node* Rear;
public:
	// constructor
	CircularQueue() {
		Rear = nullptr;
	}
	// destructor 
	~CircularQueue() {
		if (Rear == nullptr) { return; }

		Node* current = Rear->next;
		Node* nextNode = nullptr;

		while (current != Rear) {
			nextNode = current->next;
			delete current;
			current = nextNode;
		}
		delete Rear;
		Rear = nullptr;
	}
	// isEmpty
	bool isEmpty() {
		return Rear == nullptr;
	}
	// enqueue
	void enqueue(Patient p) {
		Node* newNode = new Node();
		newNode->data = p;

		if (isEmpty()) {
			Rear = newNode;
			Rear->next = Rear;
		}
		else {
			newNode->next = Rear->next;
			Rear->next = newNode;
			Rear = newNode;
		}

	}

	// dequeue
	Patient dequeue() {
		if (isEmpty()) {
			cout<<"Queue is Empty. Cannot dequeue."<<endl;
			return Patient();
		}
		
		Node* Front = Rear->next;
		Patient dequeuedData = Front->data;

		if (Front == Rear) {
			delete Front;
			Rear = nullptr;
		}
		else {
			Rear->next = Front->next;
		}

		return dequeuedData;
	}

	// Display
	void display() {
		if (isEmpty()) {
			cout << "Queue is Empty." << endl;
			return;
		}
		Node* current = Rear->next;
		do {
			current->data.getInfo();
			current = current->next;
		} while (current != Rear->next);
	}

	// getFront
	Patient getFront() {
		if (isEmpty()) {
			cout << "Queue is Empty" << endl;
			return Patient();
		}

		return Rear->next->data;
	}
	// getRear
	Patient getRear() {
		if (isEmpty()) {
			cout << "Queue is Empty" << endl;
			return Patient();
		}
		
		return Rear->data;
	}
};


