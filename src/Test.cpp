#include <iostream>
#include <memory>
#include <chrono>
#include <algorithm>
#include <vector>

#include "LinkedList.hpp"
#include "ListNode.hpp"
#include "Iterator.hpp"
#include "Searcher.hpp"

#define SIZE 100000 
#define TEST(X, Y) X() ? std::cout << "test " << Y << " succeeded" << std::endl : std::cout << "test " << Y << " failed" << std::endl

class Timer { //from theChernoProject on YouTube
public:
	Timer() {
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		Stop();
	}
	void Stop() {
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
		auto end =   std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint)    .time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;

		std::cout << duration << "us (" << ms << "ms)" << std::endl;
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
};

bool test1();
bool test2();
bool test3();
bool test4();

int main() {
	TEST(test1, 1);
	TEST(test2, 2);
	TEST(test3, 3);
	TEST(test4, 4);
}

bool test1() {
	// Test creation of a linked list and searching.
	LinkedList list = LinkedList();

	list.insertAtHead(1);
	list.insertAtTail(2);
	list.insertAtTail(3);
	list.insertAtHead(-1);

	Iterator i1 = list.find(0);
	if (!i1.isPastEnd()) {
		return false;
	}

	if (i1.isPastBeginning()) {
		return false;
	}

	i1 = list.find(2);
	if (i1.isPastBeginning()) {
		return false;
	}

	if (i1.isPastEnd()) {
		return false;
	}

	if (i1.retrieve() != 2) {
		return false;
	}

	return true;
}

bool test2() {
	//Test placement, access
	LinkedList list = LinkedList();

	list.insertAtHead(1);
	list.insertAtTail(2);
	list.insertAtTail(3);
	list.insertAtHead(-1);
	list.insertAtHead(-2);
	list.insertAtTail(-3);

	//List should be: -2, -1, 1, 2, 3, -3
	int should[6] = { -2, -1, 1, 2, 3, -3 };

	for (int i = 0; i < 6; i++) {
		if (should[i] != list[i].retrieve()) {
			return false;
		}
	}

	if (!list[SIZE].isPastEnd()) {
		return false;
	}

return true;
}

bool test3() {
	//Test deletion of elements

	LinkedList list = LinkedList();

	list.insertAtHead(1);
	list.insertAtTail(2);
	list.insertAtTail(3);
	list.insertAtHead(-1);
	list.insertAtHead(-2);
	list.insertAtTail(-3);

	list.remove(-2); //Remove head
	list.remove(-3); //Remove Tail
	list.remove(1); //Remove middles
	list.remove(2);

	//List should be { -1, 3 }
	int should2[2] = { -1, 3 };
	for (int i = 0; i < 2; i++) {
		if (should2[i] != list[i].retrieve()) {
			return false;
		}
	}

	return true;
}

bool test4() {
	//Test negative access
	
	LinkedList list = LinkedList();
	list.insertAtHead(1);
	list.insertAtTail(2);
	list.insertAtTail(3);
	list.insertAtHead(-1);
	list.insertAtHead(-2);
	list.insertAtTail(-3);

	// List in reverse should be {-3, 3, 2, 1, -1, -2}
	int reverse[7] = { 0, -3, 3, 2, 1, -1, -2 };
	for (int i = 1; i < (list.size()+ 1); i++) {
		if (reverse[i] != list[-i].retrieve()) {
			return false;
		}
	}

	if (!list[-SIZE].isPastEnd()) {
		return false;
	}
	return true;
}

bool test_perf() {
	//Performance of Searcher;
	std::vector<int>* elements = new std::vector<int>();
	elements->reserve(SIZE);

	for (int i = 0; i < SIZE; i++) {
		elements->push_back(i);
	}

	//To simulate sequential indexed access to the a normal
	//Linked List vs my linked list, I will sequentially
	//search for each element in one list, and access each 
	//same element via operator[]

	LinkedList* list_sorted = new LinkedList();
	for (auto i = elements->begin(); i != elements->end(); i++) {
		list_sorted->insertAtTail(*i);
	}

	{
		std::cout << "Beginning normal sequential access" << std::endl;
		Timer A;
		for (int i = 0; i < SIZE; i++) {
			Iterator iter = list_sorted->find(i);
		}
	}

	{
		std::cout << "Beginning optimized sequential access" << std::endl;
		Timer B;
		for (int i = 0; i < SIZE; i++) {
			Iterator iter = (*list_sorted)[i];
		}
	}

	//Now to simulate random access to see if there is any improvement
	//of my optimizations over a normal linked list on average;

	std::vector<int>* elements_sorted = new std::vector<int>(elements->begin(), elements->end());

	std::random_shuffle(elements->begin(), elements->end());

	LinkedList* list_rand = new LinkedList();

	for (auto i = elements->begin(); i != elements->end(); i++) {
		list_rand->insertAtTail(*i);
	}

	//At this point, list_sorted is the same as elements_sorted
	//and list_rand is the same as elements

	{
		std::cout << "Beginning normal random access" << std::endl;
		Timer C;
		for (auto i = elements->begin(); i != elements->end(); i++) {
			Iterator iter = list_rand->at(*i);
		}
	}
	{
		std::cout << "Beginning optimized random access" << std::endl;
		Timer D;
		for (auto i = elements->begin(); i != elements->end(); i++) {
			Iterator iter = (*list_rand)[*i];
		}
	}

	delete list_rand;
	delete list_sorted;
	delete elements;
	delete elements_sorted;

	return true;
}