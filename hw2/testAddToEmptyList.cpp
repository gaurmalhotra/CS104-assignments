#include "lliststr.h"
#include <iostream>
#include <string>

using namespace std;

void checkEmpty(LListStr *list, bool expEmpty) {
	if (list->empty() == expEmpty) {
		cout << "SUCCESS: List is ";
		if (!expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
	else {
		cout << "FAIL: List is ";
		if (expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
}

void checkSize(LListStr *list, int expSize) {
	int size = list->size();
	if (size == expSize) {
		cout << "SUCCESS: List has size " << size << endl;
	}
	else {
		cout << "FAIL: List has size " << size;
		cout << " but expected " << expSize << endl;
	}
}

void checkGet(LListStr *list, int pos, const string &expStr) {
	string str = list->get(pos);
	if (str == expStr) {
		cout << "SUCCESS: String at index " << pos << " is \'" << expStr << "\'" << endl;
	} 
	else {
		cout << "FAIL: String at index " << pos << " is \'" << str << "\'";
		cout << " but expected \'" << expStr << "\'" << endl;
	}
}

int main() {
	LListStr* list = new LListStr();

	// Check if the list is initially empty.
	checkEmpty(list, true);
	checkSize(list, 0);

	// Insert an item at the head.
	list->insert(0, "CSCI104");

	// Verify the list is not empty
	checkEmpty(list, false);
	checkSize(list, 1);

	// Check if the value is correct.
	checkGet(list, 0, "CSCI104");

	// TODO: Continue adding tests for your program, or start your own file with your
	// own tests. Remember to submit a file that is named correctly!
	list->insert(1, "CSCI201");
	cout << "CSCI201 should be inserted at position 1." << endl;

	cout << "The list so far is: " << endl;
	cout << list->get(0) << " ";
	cout << list->get(1) << endl;
	checkSize(list, 2);


	list->insert(2, "CSCI270");
	cout << "CSCI270 should be inserted at position 2." << endl;

	cout << "The list so far is: " << endl;
	cout << list->get(0) << " ";
	cout << list->get(1) << " ";
	cout << list->get(2) << endl;

	checkSize(list, 3);
	checkGet(list, 2, "CSCI270");

	// Insert an item at the head.
	list->remove(1);
	cout << "Position 1 should be removed." << endl;
	cout << "The list so far is: " << endl;
	cout << list->get(0) << " ";
	cout << list->get(1) << " ";
	cout << list->get(2) << endl;

	checkEmpty(list, false);
	checkSize(list, 2);

	checkGet(list, 1, "CSCI270");

	list->set(0, "ACCT410");

	cout << "Position 0 is now " << list->get(0) << endl;
	cout << "The final list is: " << endl;
	cout << list->get(0) << " ";
	cout << list->get(1) << " ";
	cout << list->get(2) << endl;

	// Clean up memory.
	delete list;
}
