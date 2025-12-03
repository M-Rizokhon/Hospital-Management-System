#pragma once
#include <iostream>
#include <vector>
#include "BST.h"

// A very simple implementation of a hash map data structure
class HashMap {
private:
	std::vector<BSTNode> map;

public:
	HashMap() : map(1000) {}     


	void insert(int key, BSTNode node) {
		map[key] = node;
	}


	BSTNode get(int key) {
		return map[key];
	}

	void remove(int key) {
		map[key] = BSTNode();
	}

};