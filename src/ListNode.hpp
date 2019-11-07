#pragma once

class ListNode {
	int value;
	ListNode* next, * previous;

	friend class LinkedList;
	friend class Iterator;
	friend class Searcher;

public:
	ListNode();
	ListNode(int x);
};