#include "Iterator.hpp"

Iterator::Iterator() {
	current = nullptr;
}

Iterator::Iterator(ListNode* theNode) {
	current = theNode;
}

bool Iterator::isPastEnd() const {
	return (current->next == nullptr);
}

bool Iterator::isPastBeginning() const {
	return (current->previous == nullptr);
}

void Iterator::moveForward() {
	if (!isPastEnd()) {
		current = current->next;
	}
}

void Iterator::moveBackward() {
	if (!isPastBeginning()) {
		current = current->previous;
	}
}

int Iterator::retrieve() const {
	return current->value;
}