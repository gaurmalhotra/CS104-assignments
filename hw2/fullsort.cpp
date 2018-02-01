#include <iostream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    int value;
    Node *next;
};

Node* sortHelper(Node* in){
	if (in -> next -> value < in -> value) {
		Node* temp = in;
		temp->value = in->value;
		temp->next = in -> next;
		//in -> next = temp;

		in -> value = -1;
		return temp;
	}
	else 
		sortHelper(in -> next);
}

Node* insertHelper(Node* in, Node* temp){
	if (in-> value == -1){
		temp->value = in->value;
		Node* sort = new Node;
		sort-> value = temp -> value;
		delete in;
		return sort;
	}
	if (in->value != -1) {
		in = in->next;
	}

	else {
		insertHelper(in->next, temp);
	}

}


Node* fullsort (Node* in){
	Node* problem = sortHelper(in);
	Node* sort = new Node;
	sort = insertHelper(in, problem);
	return sort;
	
}

int main(){

	Node* first = new Node;
	Node* second = new Node;
	Node* third = new Node;
	Node* fourth = new Node;
	Node* fifth = new Node; 

	//Nodes in linked list 
	first->next = second;
	second->next = third;
	third->next = fourth;
	fourth->next = fifth;
	fifth->next = NULL;

	//values in Linked List 
	first->value= 1;
	second->value= 2;
	third->value= 5;
	fourth->value= 3;
	fifth->value= 4;

	Node* head = fullsort(first);
	//cout << head->value << endl;
	Node* curr = head;
	while(curr){
	cout << curr->value;
	curr = curr->next;
	}
	cout << endl;

	return 0;
}
	
