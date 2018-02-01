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
	if(!in->next)
	{
		return in;
	}
	else
	{
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

	return in;
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

	return in;

}


Node* fullsort (Node* in){
	Node* start = in;
	Node* problem = sortHelper(in);
	Node* sort = new Node;
	sort = insertHelper(start, problem);
	start = NULL;
	return sort;
	
}


	