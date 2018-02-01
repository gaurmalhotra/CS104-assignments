#include "lliststr.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
	   cerr << "Please provide an input file" << endl;
	   return -1;
    }

    ifstream input(argv[1]);

    if(input.fail()) {
       cerr << "Invalid file" << endl;
       return -1;
    }

    LListStr* list = new LListStr();
    string action;
    

    while(!input.fail()) {
	    input >> action;
	    if (action == "ADD" || action == "REPLACE") {
	    	int pos;
	    	string str;
	    	input >> pos >> str;
	    	if (action == "ADD")
	    		list->insert(pos, str);
	    	else
	    		list->set(pos, str);
	    }

	    else if (action == "ACT") {
	    	int pos;
	    	input >> pos;
	    	if (pos < list->size()) {
		    	if (pos == (list->size()-1)) {
		    		cout << "Assassinated: " << list->get(0) << endl;
		    		list->remove(0);
		    	}
		    	else if (list->size() != 1){
		    		cout << "Assassinated: " << list->get(pos+1) << endl;
		    		list->remove(pos+1);
		    	}
		    	if (list->size() == 1) {
		    		cout << "Winner: " << list->get(list->size()-1) << endl;
		    	}
		    }

		}
		    string line;
		    getline(input,line);
	    }
	
	if(list->size() > 1) {
    	cout << "Remaining Players: " << list->size() << endl;
    	for (int i = 0; i < list->size(); i++){
    		cout << list -> get(i) << endl;
    	}
    }
 
 return 0;
 	
}