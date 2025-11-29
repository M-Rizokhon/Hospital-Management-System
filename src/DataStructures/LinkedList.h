#pragma once
#include <iostream>
#include"Patient.h"

class Node{
    public:
    Patient* patient;
    Node* next;
    Node(Patient* patient ){
        this->patient=patient;
        this->next=nullptr;
    }
};

class HistoryList {
    public:
    Node* head , *tail;
    HistoryList(){
        head=tail=nullptr;
    }

    // insert to List
    void addHistory(Patient *patient){
        Node* temp=new Node(patient);
        if(head==nullptr){
            head=tail=temp;
            return;
        }
        tail->next=temp;
        tail=temp;
    }

    // print history (all node infos)
    void print(){
        if(head==nullptr){
            std::cout<<"No history to print!"<<std::endl;
            return;
        }
        Node* temp=head;
        while(temp!=nullptr){
            temp->patient->info();
            temp=temp->next;
        }

    }

    // destructor 
    ~HistoryList(){
        Node* temp=head;
        while(temp!=nullptr){
            Node*next=temp->next;
            delete temp->patient;
            delete temp;
            temp=next;
        }
    }

};

