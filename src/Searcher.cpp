#include "Searcher.hpp"

Searcher::Searcher() : Iterator() {
	index = -1;
}

Searcher::Searcher(ListNode* theNode) : Iterator(theNode) {
	index = -1;
}

int Searcher::pos() const {
	return index;
}

void Searcher::moveForward() {
	if (!isPastEnd()) {
		current = current->next;
		index++;
	}
}

void Searcher::moveBackward() {
	if (!isPastBeginning()) {
		current = current->previous;
		index--;
	}
}