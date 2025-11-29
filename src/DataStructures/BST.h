#pragma once
#include "Patient.h"
#include <iostream>

// implementation of Binary Search Tree 

struct Node {
    Patient data;
    Node* left;
    Node* right;

    Node(Patient data): data(data), left(nullptr), right(nullptr){}
};


class BST {
private:
    Node* root;

    // core functions (private)
    Node* insert(Node* node, Patient key);
    Node* search(Node* node, Patient key);
    Node* findMin(Node* node);
    Node* findMax(Node* node);
    Node* remove(Node* node, Patient key);

    // traversals
    void inorder(Node* node);
    void preorder(Node* node);
    void postorder(Node* node);

public:
    // public interface functions
    BST() {}
    ~BST() {} 
    void insert(Patient key);
    void remove(Patient key);
    bool search(Patient key);

    void printPreorder();
    void printInorder();
    void printPostOrder();
};



/* Core private functions */

// insert a new node (recursive)
Node* BST::insert(Node* node, Patient key) {
    if (node == nullptr) 
        return new Node(key);
    
    if (key.getSeverity() > node->data.getSeverity()) 
        node->right = insert(node->right, key);
    else
        node->left = insert(node->left, key);

    return node;
}


// search for a node
Node* BST::search(Node* node, Patient key) {
    if (node == nullptr) return nullptr;

    if (node->data.getID() == key.getID())
        return node;
    
    if (key.getSeverity() > node->data.getSeverity()) 
        return search(node->right, key);
    else 
        return search(node->left, key);    
}



// find a node with minimum severity
Node* BST::findMin(Node* node) {
    while (node && node->left) { 
        node = node->left;
    }
    return node;
}



// find a node with maximum severity
Node* BST::findMax(Node* node) {
    while (node && node->right) {
        node = node->right;
    }
    return node;
}



// remove a node 
Node* BST::remove(Node* node, Patient key) {
    if (!node) return nullptr;

    if (key.getSeverity() > node->data.getSeverity())  
        node->right = remove(node->right, key);
    else if (key.getSeverity() < node->data.getSeverity()) 
        node->left = remove(node->left, key);

    else if (node->data.getID() != key.getID())
            node->left = remove(node->left, key);

    else {
        // Case 1: No child
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }


        // Case 2: One child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }

        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }


        // Case 3: Two children
        // replace with inorder predecessor
        Node* pred = findMax(node->left);
        node->data = pred->data;
        node->left = remove(node->left, pred->data);
    }
    return node;
}






/* Traversals*/
void BST::inorder(Node* node) {
    if (!node) return;
    inorder(node->left);
    std::cout << node->data.getPatientInfo() << "\n\n";
    inorder(node->right);
}


void BST::preorder(Node* node) {
    if (!node) return;
    std::cout << node->data.getPatientInfo() << "\n\n";
    preorder(node->left);
    preorder(node->right);
}


void BST::postorder(Node* node) {
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    std::cout << node->data.getPatientInfo() << "\n\n";
}





/* Public interface functions */
BST::BST(): root(nullptr) {}   // constructor
BST::~BST() {}     // destructor

void BST::insert(Patient key) {
    root = insert(root, key);
}

void BST::remove(Patient key) {
    root = remove(root, key);
}

bool BST::search(Patient key) {
    return search(root, key) != nullptr;
}


void BST::printInorder() {
    inorder(root);
    std::cout << std::endl;
}

void BST::printPreorder() {
    preorder(root);
    std::cout << std::endl;
}

void BST::printPostOrder() {
    postorder(root);
    std::cout << std::endl;
}



