#include <iostream>
#include "LinkedList.hpp"
#include "ListNode.hpp"
#include "Iterator.hpp"
#include "Searcher.hpp"

int main() {
	ListNode* node1P = new ListNode(1);
	ListNode* node2P = new ListNode(2);
	ListNode* node3P = new ListNode(3);

	LinkedList list1, list2;

	Iterator node1Iter(node1P);
	Iterator node2Iter(node2P);
	Iterator node3Iter(node3P);

	Iterator list1Iter = list1.first();

	list1.insertBefore(1, list1Iter);
	list1Iter = list1.first();

	list1.insertAfter(2, list1Iter);

	list1Iter.moveForward();
	list1.insertAfter(3, list1Iter);

	std::cout << "The size of list1 = " << list1.size() << std::endl;
	printList(list1, true);

	list2.insertAtTail(3);
	list2.insertAtTail(2);
	list2.insertAtTail(1);
	list2.insertAtHead(-1);
	list2.insertAtHead(-2);
	list2.insertAtHead(-3);

	printList(list2, true);

	std::cout << "List2[5] = " << list2[3].retrieve() << std::endl;
}