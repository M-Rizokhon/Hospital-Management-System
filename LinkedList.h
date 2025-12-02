#pragma once
#include <iostream>
#include "Patient.h"


class HistoryNode {
public:
    Patient patient;
    HistoryNode* next;

    HistoryNode(const Patient& p) : patient(p), next(nullptr) {}
};

class LinkedList {
public:
    HistoryNode* head;
    HistoryNode* tail;

    LinkedList() : head(nullptr), tail(nullptr) {}

    // insert to List (copy patient into history)
    void addHistory(const Patient& p) {
        HistoryNode* temp = new HistoryNode(p);
        if (head == nullptr) {
            head = tail = temp;
        }
        else {
            tail->next = temp;
            tail = temp;
        }
    }

    // print history (all node infos)
    void print() const {
        if (head == nullptr) {
            std::cout << "No history to print!" << std::endl;
            return;
        }
        HistoryNode* temp = head;
        while (temp != nullptr) {
            temp->patient.getInfo();
            temp = temp->next;
        }
    }

    // destructor 
    ~LinkedList() {
        HistoryNode* temp = head;
        while (temp != nullptr) {
            HistoryNode* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};