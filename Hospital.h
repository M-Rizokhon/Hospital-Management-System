#pragma once
#include "Patient.h"
#include <iostream>

// Binary Search Tree for patients, ordered by (severity,id)

// Node
class BSTNode {
public:
	Patient data;
	BSTNode* left;
	BSTNode* right;

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
	// > 0 means a has higher priority
	// < 0 means b has higher priority
	int compare(const Patient& a, const Patient& b) const {
		if (a.getSeverity() != b.getSeverity()) {
			return a.getSeverity() - b.getSeverity();  // higher severity first
		}
		if (a.getArrivalTime() != b.getArrivalTime()) {
			return b.getArrivalTime() - a.getArrivalTime();
		}
		return b.getID() - a.getID();
	}

	// insert
	BSTNode* insert(BSTNode* node, const Patient& key) {
		if (!node) {
			return new BSTNode(key);
		}
		int cmp = compare(key, node->data);

		if (cmp < 0) {
			node->left = insert(node->left, key);
		}
		else if (cmp > 0) {
			node->right = insert(node->right, key);
		}
		else {
			// here we ignore
		}
		return node;
	}

	// search
	BSTNode* search(BSTNode* node, const Patient& key) const {
		if (!node) {
			return nullptr;
		}
		int cmp = compare(key, node->data);

		if (cmp == 0) {
			return node;
		}
		else if (cmp < 0) {
			return search(node->left, key);
		}
		else {
			return search(node->right, key);
		}
	}

	// find minimum
	BSTNode* findMin(BSTNode* node) const {
		if (!node) {
			return nullptr;
		}
		while (node->left) {
			node = node->left;
		}
		return node;
	}

	// find maximum
	BSTNode* findMax(BSTNode* node)const {
		if (!node) {
			return nullptr;
		}
		while (node->right) {
			node = node->right;
		}
	}

	// remove
	BSTNode* remove(BSTNode* node, const Patient& key) {
		if (!node) {
			return nullptr;
		}

		int cmp = compare(key, node->data);

		if (cmp < 0) {
			node->left = remove(node->left, key);
		}
		else if (cmp > 0) {
			node->right = remove(node->right, key);
		}
		else {

			// case 1 : no children
			if (!node->left && !node->right) {
				delete node;
				return nullptr;
			}

			// case 2: one child
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

			// case 3: two children
			else {
				BSTNode* pred = findMax(node->left);
				node->data = pred->data; // copy
				node->left = remove(node->left, pred->data); // delete
			}
		}
		return node;
	}

	// Travesals

	void inorder(BSTNode* node) const {
		if (!node) {
			return;
		}
		inorder(node->left);
		cout << node->data.getPatientInfo() << endl;
		inorder(node->right);
	}
	void reverseInorder(BSTNode* node) const {
		if (!node) {
			return;
		}
		reverseInorder(node->right);
		cout << node->data.getPatientInfo() << endl;
		reverseInorder(node->left);
	}

	void preorder(BSTNode* node) const {
		if (!node) {
			return;
		}
		cout << node->data.getPatientInfo() << endl;
		preorder(node->left);
		preorder(node->right);
	}

	void postorder(BSTNode* node) const {
		if (!node) {
			return;
		}
		postorder(node->left);
		postorder(node->right);
		cout << node->data.getPatientInfo() << endl;
	}
	
	// destroy
	void destroy(BSTNode* node) {
		if (!node) {
			return;
		}
		destroy(node->left);
		destroy(node->right);
		delete node;
	}

	public:
		// constructor
		BST() {
			root = nullptr;
		}
		// destructor
		~BST() {
			destroy(root);
			root = nullptr;
		}
		bool isEmpty() const {
			return root == nullptr;
		}
		void insert(const Patient& key) {
			root = insert(root, key);
		}
		void remove(const Patient& key) {
			root = remove(root, key);
		}
		bool search(const Patient& key) {
			return search(root, key) != nullptr; // overloading
		}
		void printInorder() const {
			inorder(root);
			cout << endl;
		}
		void printPreorder() const {
			preorder(root);
			cout << endl;
		}
		void printPostorder() const {
			postorder(root);
			cout << endl;
		}
		void printDescending() const { 
			reverseInorder(root); 
			cout << endl;
		}
		void deletePatientRecord() {
			if (!root) {
				cout << "No patients in BST." << endl;
				return;
			}

			BSTNode* maxNode = findMax(root);
			if (!maxNode) {
				return;
			}

			Patient highest = maxNode->data;
			cout << "Deleting highest priority patient from BST" << endl;
			highest.getInfo();

			root = remove(root, highest);
		}

		bool getHighestPriority(Patient& out) const {
			if (!root) return false;
			BSTNode* maxNode = findMax(root);
			if (!maxNode) return false;
			out = maxNode->data;
			return true;
		}
};





