#include "ListNode.hpp"
#include "LinkedList.hpp"
#include <vector>
#include <iostream>

LinkedList::LinkedList() {
	head = new ListNode;
	tail = new ListNode;

	head->previous = nullptr;
	tail->next = nullptr;
	
	head->next = tail;
	tail->previous = head;

	searcher = Searcher(head);
	count = 0;
}

LinkedList::~LinkedList() {
	makeEmpty();
}

LinkedList::LinkedList(const LinkedList& source) {
	head = new ListNode;
	tail = new ListNode;

	head->next = tail;
	tail->previous = head;
	count = 0;

	Iterator iter(source.head->next);
	while (!iter.isPastEnd()) {
		insertAtTail(iter.retrieve());
	}
}

LinkedList* LinkedList::operator=(const LinkedList& source) {
	if (this == &source) {
		return this;
	}
	else {
		makeEmpty();
		Iterator iter(source.head->next);
		while (!iter.isPastEnd()) {
			insertAtTail(iter.retrieve());
			iter.moveForward();
		}
	}
	return this;
}

void LinkedList::resetSearcher() {
	searcher.reset(head);
}

bool LinkedList::isEmpty() const {
	return (count == 0);
}

void LinkedList::makeEmpty() {
	std::vector<int> values(count);
	Iterator currentPosition = first();
	for (int i = 0; i < count; i++) {
		values[i] = currentPosition.retrieve();
		currentPosition.moveForward();
	}

	for (int i = 0; i < count; i++) {
		remove(values[i]);
	}
}

Iterator LinkedList::first() {
	Iterator iter(head->next);
	return iter;
}

Iterator LinkedList::last() {
	Iterator iter(tail->previous);
	return iter;
}

void LinkedList::insertAfter(int x, Iterator position) {
	ListNode* newNode = new ListNode(x);
	
	newNode->previous = position.current;
	newNode->next = position.current->next;
	
	position.current->next->previous = newNode;
	position.current->next = newNode;

	count++;
	resetSearcher();
}

void LinkedList::insertBefore(int x, Iterator position) {
	ListNode* newNode = new ListNode(x);
	
	newNode->previous = position.current->previous;
	newNode->next = position.current;

	position.current->previous->next = newNode;
	position.current->previous = newNode;

	count++;
	resetSearcher();
}

void LinkedList::insertAtTail(int x) {
	Iterator pos = last();
	insertAfter(x, pos);
}

void LinkedList::insertAtHead(int x) {
	Iterator pos = first();
	insertBefore(x, pos);
	resetSearcher();
}

void LinkedList::remove(int x) {
	Iterator pos = first();
	while (pos.retrieve() != x && !pos.isPastEnd()) {
		pos.moveForward();
	}
	if (pos.retrieve() == x) {
		pos.current->previous->next = pos.current->next;
		pos.current->next->previous = pos.current->previous;

		delete pos.current;
		count--;
		resetSearcher();
	}
}

Iterator LinkedList::find(int x) {
	Iterator pos = first();
	while (pos.retrieve() != x && !pos.isPastEnd()) {
		pos.moveForward();
	}
	return pos;
}

int LinkedList::size() const {
	return count;
}

Iterator LinkedList::operator[](int index) {
	if (index > count) {
		return Iterator(tail);
	}
	else if (searcher.pos() == -1) {
		while ( searcher.pos() != index && !searcher.isPastEnd()) {
			searcher.moveForward();
		}
		return Iterator(searcher.current);
	}
	else { 
		int diff = index - searcher.pos();
		while (diff < 0) {
			searcher.moveBackward();
			diff++;
		}
		while (diff > 0) {
			searcher.moveForward();
			diff--;
		}
		return Iterator(searcher.current);
	}
}

void printList(LinkedList& source, bool direction) {
	if (direction) {
		Iterator pos = source.first();
		for (int i = 0; i < source.size(); i++) {
			std::cout << "[" << pos.retrieve() << "]";
			pos.moveForward();
		}
	}
	else {
		Iterator pos = source.last();
		for (int i = 0; i < source.size(); i++) {
			std::cout << "[" << pos.retrieve() << "]";
			pos.moveBackward();
		}
	}

	std::cout << std::endl;
}

