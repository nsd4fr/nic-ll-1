#pragma once

#include "ListNode.hpp"
#include "Searcher.hpp"

class Iterator;
class Searcher;

class LinkedList {
	ListNode* head;
	ListNode* tail;
	int count;
	friend class Iterator;
	friend class Searcher;

	Searcher searcher;

public:
	LinkedList();
	LinkedList(const LinkedList& source);
	~LinkedList();
	LinkedList* operator=(const LinkedList& source);
	bool isEmpty() const;
	void makeEmpty();
	Iterator first();
	Iterator last();
	void insertAfter(int x, Iterator position);
	void insertBefore(int x, Iterator position);
	void insertAtTail(int x);
	void insertAtHead(int x);
	void remove(int x);
	Iterator find(int x);

	Iterator operator[](int index);
	Iterator at(int index);

	int size() const;
};

void printList(LinkedList& source, bool direction);