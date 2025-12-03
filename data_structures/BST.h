#pragma once
#include "../Patient.h"
#include <iostream>

// Binary Search Tree for patients, ordered by (severity,id)

// Node
class BSTNode {
public:
	Patient data;
	BSTNode* left;
	BSTNode* right;

    BSTNode() : data(), left(nullptr), right(nullptr) {}

	BSTNode(const Patient& data) {
		this->data = data;
		left = nullptr;
		right = nullptr;
	}
};



class BST {
private:
    BSTNode* root;

    // Compare priority of two patients
    int compare(const Patient& a, const Patient& b) const;

    // Internal recursive functions
    BSTNode* insert(BSTNode* node, const Patient& key);
    BSTNode* search(BSTNode* node, const Patient& key) const;
    BSTNode* findMin(BSTNode* node) const;
    BSTNode* findMax(BSTNode* node) const;
    BSTNode* remove(BSTNode* node, const Patient& key);
    void inorder(BSTNode* node) const;
    void reverseInorder(BSTNode* node) const;
    void preorder(BSTNode* node) const;
    void postorder(BSTNode* node) const;
    void destroy(BSTNode* node);

public:
    BST();
    ~BST();
    bool isEmpty() const;
    void insert(const Patient& key);
    void remove(const Patient& key);
    bool search(const Patient& key);
    void printInorder() const;
    void printPreorder() const;
    void printPostorder() const;
    void printDescending() const;
    void deletePatientRecord();
    bool getHighestPriority(Patient& out) const;
};



/*
* This is a method to compare to Patient elements
* needed for priority.
* First: severity is compared.
* Second: Arrival time is compared. 
* 
* The method returns positive number if a is 
* in higher priority compared to b.
* And returns a negative number in vice verse.
*/
int BST::compare(const Patient& a, const Patient& b) const {
    if (a.getSeverity() != b.getSeverity()) {
        return a.getSeverity() - b.getSeverity();  // higher severity first
    }
    return b.getID() - a.getID();
}

// Insert
BSTNode* BST::insert(BSTNode* node, const Patient& key) {
    if (!node) return new BSTNode(key);
    int cmp = compare(key, node->data);

    if (cmp < 0) node->left = insert(node->left, key);
    else if (cmp > 0) node->right = insert(node->right, key);
    return node;
}

// Search
BSTNode* BST::search(BSTNode* node, const Patient& key) const {
    if (!node) return nullptr;
    int cmp = compare(key, node->data);

    if (cmp == 0) return node;
    else if (cmp < 0) return search(node->left, key);
    else return search(node->right, key);
}

// Find minimum
BSTNode* BST::findMin(BSTNode* node) const {
    if (!node) return nullptr;
    while (node->left) node = node->left;
    return node;
}

// Find maximum
BSTNode* BST::findMax(BSTNode* node) const {
    if (!node) return nullptr;
    while (node->right) node = node->right;
    return node;
}

// Remove
BSTNode* BST::remove(BSTNode* node, const Patient& key) {
    if (!node) return nullptr;
    int cmp = compare(key, node->data);

    if (cmp < 0) node->left = remove(node->left, key);
    else if (cmp > 0) node->right = remove(node->right, key);
    else {
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }
        else if (!node->left) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }
        else {
            BSTNode* pred = findMax(node->left);
            node->data = pred->data;
            node->left = remove(node->left, pred->data);
        }
    }
    return node;
}

// Traversals
void BST::inorder(BSTNode* node) const {
    if (!node) return;
    inorder(node->left);
    std::cout << node->data.getPatientInfo() << std::endl;
    inorder(node->right);
}

void BST::reverseInorder(BSTNode* node) const {
    if (!node) return;
    reverseInorder(node->right);
    std::cout << node->data.getPatientInfo() << std::endl;
    reverseInorder(node->left);
}

void BST::preorder(BSTNode* node) const {
    if (!node) return;
    std::cout << node->data.getPatientInfo() << std::endl;
    preorder(node->left);
    preorder(node->right);
}

void BST::postorder(BSTNode* node) const {
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    std::cout << node->data.getPatientInfo() << std::endl;
}

// Destroy
void BST::destroy(BSTNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

// Constructor
BST::BST() : root(nullptr) {}

// Destructor
BST::~BST() {
    destroy(root);
    root = nullptr;
}

bool BST::isEmpty() const {
    return root == nullptr;
}

void BST::insert(const Patient& key) {
    root = insert(root, key);
}

void BST::remove(const Patient& key) {
    root = remove(root, key);
}

bool BST::search(const Patient& key) {
    return search(root, key) != nullptr;
}

void BST::printInorder() const {
    inorder(root);
    std::cout << std::endl;
}

void BST::printPreorder() const {
    preorder(root);
    std::cout << std::endl;
}

void BST::printPostorder() const {
    postorder(root);
    std::cout << std::endl;
}

void BST::printDescending() const {
    reverseInorder(root);
    std::cout << std::endl;
}

void BST::deletePatientRecord() {
    if (!root) {
        std::cout << "No patients in BST." << std::endl;
        return;
    }

    BSTNode* maxNode = findMax(root);
    if (!maxNode) return;

    Patient highest = maxNode->data;
    std::cout << "Deleting highest priority patient from BST" << std::endl;
    highest.getInfo();

    root = remove(root, highest);
}

bool BST::getHighestPriority(Patient& out) const {
    if (!root) return false;
    BSTNode* maxNode = findMax(root);
    if (!maxNode) return false;
    out = maxNode->data;
    return true;
}




