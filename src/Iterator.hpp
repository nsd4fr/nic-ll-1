#pragma once

#include "ListNode.hpp"

class LinkedList;

class Iterator {
protected: 
	ListNode* current;
	friend class LinkedList;
	friend class Searcher; 

public:
	Iterator();
	Iterator(ListNode* theNode);
	bool isPastEnd() const;
	bool isPastBeginning() const;
	void moveForward();
	void moveBackward();
	int retrieve() const;
};