# include "ListNode.hpp"

ListNode::ListNode() {
	value = 0;
	next = nullptr;
	previous = nullptr;
}

ListNode::ListNode(int x) {
	value = x;
	next = nullptr;
	previous = nullptr;
}