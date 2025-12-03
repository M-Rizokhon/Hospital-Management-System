#pragma once
#include <iostream>
#include "../Patient.h"

// QueueNode for circular linked queue
class QueueNode {
public:
	Patient data;
	QueueNode* next;

	QueueNode(const Patient& p) {
		data = p;
		next = nullptr;
	}
};


// CircularQueue
class CircularQueue {
private:
	QueueNode* Rear;
public:
	CircularQueue();
	~CircularQueue();

	bool isEmpty() const;
	void enqueue(const Patient& p);
	Patient dequeue();
	void display() const;
	Patient getFront() const;
	Patient getRear() const;
};


// constructor
CircularQueue::CircularQueue() {
    Rear = nullptr;
}

// destructor
CircularQueue::~CircularQueue() {
    if (Rear == nullptr) {
        return;
    }

    QueueNode* current = Rear->next;
    QueueNode* nextNode = nullptr;

    while (current != Rear) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    delete Rear;
    Rear = nullptr;
}

// isEmpty
bool CircularQueue::isEmpty() const {
    return Rear == nullptr;
}

// enqueue
void CircularQueue::enqueue(const Patient& p) {
    QueueNode* newNode = new QueueNode(p);

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
Patient CircularQueue::dequeue() {
    if (isEmpty()) {
        std::cout << "Queue is Empty" << std::endl;
        return Patient();
    }

    QueueNode* Front = Rear->next;
    Patient dequeuedData = Front->data;

    if (Front == Rear) {
        delete Front;
        Rear = nullptr;
    }
    else {
        Rear->next = Front->next;
        delete Front;
    }

    return dequeuedData;
}

// display
void CircularQueue::display() const {
    if (isEmpty()) {
        std::cout << "Queue is Empty." << std::endl;
        return;
    }

    QueueNode* current = Rear->next;
    do {
        current->data.getInfo();
        current = current->next;
    } while (current != Rear->next);
}

// getFront
Patient CircularQueue::getFront() const {
    if (isEmpty()) {
        std::cout << "Queue is Empty" << std::endl;
        return Patient();
    }
    return Rear->next->data;
}

// getRear
Patient CircularQueue::getRear() const {
    if (isEmpty()) {
        std::cout << "Queue is Empty" << std::endl;
        return Patient();
    }
    return Rear->data;
}





