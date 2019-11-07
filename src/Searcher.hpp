#pragma once

#include "ListNode.hpp"
#include "Iterator.hpp"

class Searcher : public Iterator{
	int index;

public:
	Searcher();
	Searcher(ListNode* theNode);
	int pos() const;
	void moveForward();
	void moveBackward();
};