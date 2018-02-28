#include "webpage.h"
#include <sstream>
#include <fstream>
#include <cstring>
#include <map>
#include <iostream>
#include <cstdlib>

using namespace std;

void webpage_parser(string word, string name, Webpage* web, map<string, Webpage*> &nameToWeb);
int string_parser(string q, set<string> &words, map<string, Webpage*> &nameToWeb, map<string, set<Webpage*> > &wordToWeb, ofstream &output);
void intersectWebpage(set<string> &words, map<string, Webpage*> &nameToWeb, map<string, set<Webpage*> > &wordToWeb, ofstream &output);
set<Webpage*> intersectString(set<Webpage*> &tempSet, set<Webpage*> &otherSet);
void unionWebpage(set<string> &words, map<string, Webpage*> &nameToWeb, map<string, set<Webpage*> > &wordToWeb, ofstream &output);
void print(string str, ofstream &output);
void incoming(string str, map<string, Webpage*> &nameToWeb, ofstream &output);
void outgoing(string str, map<string, Webpage*> &nameToWeb, ofstream &output);

int main(int argc, char* argv[])
{
	if (argc < 4) {
		cerr << "Please provide an index, query, and output file." << endl;
		return -1;
	}

	ifstream index(argv[1]);
	ifstream query(argv[2]);
	ofstream output(argv[3]);


	if(index.fail()) {
		cerr << "Invalid index file" << endl;
		return -1;
	}

	if(query.fail()) {
		cerr << "Invalid query file" << endl;
		return -1;
	}

	set<string> words;
	map<string, Webpage*> nameToWeb;
	map<string, set<Webpage*> > wordToWeb;

	while (!index.fail() && !index.eof()){
		Webpage* web = new Webpage;
		string str;
		getline(index, str);
		nameToWeb.insert(pair <string, Webpage*> (str, web));
	}

	map<string, Webpage*>::iterator it;
	for (it = nameToWeb.begin(); it != nameToWeb.end(); ++it){
		ifstream webfile(it->first);
		string word;
		while (getline(webfile, word))
			webpage_parser(word, it->first, it->second, nameToWeb);
		
	}
	
	while (!query.fail() && !query.eof()){
		string q;
		getline(query, q);
		int valid = string_parser(q, words, nameToWeb, wordToWeb, output);
		if (valid == -1){
			output << "Invalid query" << endl;
			continue;
		}
		if (words.size() == 1){
			unionWebpage(words, nameToWeb, wordToWeb, output);
		}
		words.clear();
	}

	

	return 0;
}

void webpage_parser(string word, string name, Webpage* web, map<string, Webpage*> &nameToWeb){
	stringstream ss(word);
	char a;
	while (ss >> a){
		if (isalnum(a)){
			a = tolower(a);
			string s(1,a);
			while (ss >> noskipws >> a && isalnum(a)){
		  		a = tolower(a);
		  		s.push_back(a);
		  	}
		  	web->content_push(s);
		}
		if (a == '('){
			ss >> a;
			a = tolower(a);
			string s(1,a);
		  	while (ss >> a && a != ')') {
		    	a = tolower(a);
		    	s.push_back(a);
		  	}
			web->outgoing_insert(s);
			map<string, Webpage*>::iterator it;
			for (it = nameToWeb.begin(); it != nameToWeb.end(); ++it){		  	
				if(it->first == s){
					(it->second)->incoming_insert(name);
				}
			}
				
		}
	}
	return;
}

int string_parser(string q, set<string> &words, map<string, Webpage*> &nameToWeb, map<string, set<Webpage*> > &wordToWeb, ofstream &output){
	stringstream ss(q);
	string s;
	while (ss >> s){
		if (s == "AND"){
			int count = 0;
			while (ss >> s){
				++count;
				for (size_t i = 0; i < s.length(); ++i){
					s[i] = tolower(s[i]);
				}
				words.insert(s);
			} 
			if (count > 0){
				intersectWebpage(words, nameToWeb, wordToWeb, output);
			}
			else
				words.insert(s);
		}
		else if (s == "OR"){
			int count = 0;
			while (ss >> s){
				++count;
				for (size_t i = 0; i < s.length(); ++i){
					s[i] = tolower(s[i]);
				}
				words.insert(s);
			} 
			if (count > 0)
				unionWebpage(words, nameToWeb, wordToWeb, output);
			else
				words.insert(s);
		}
		else if (s == "PRINT"){
			int count = 0;
			while (ss >> s){
				++count;
				words.insert(s);
			} 
			if (count == 1)
				print(s, output);
			else if (count == 0)
				words.insert(s);
			else 
				return -1;
		}
		else if (s == "INCOMING"){
			int count = 0;
			while (ss >> s){
				++count;
			} 
			if (count == 1)
				incoming(s, nameToWeb, output);
			else if (count == 0)
				words.insert(s);
			else 
				return -1;
		}
		else if (s == "OUTGOING"){
			int count = 0;
			while (ss >> s){
				++count;
			} 
			if (count == 1)
				outgoing(s, nameToWeb, output);
			else if (count == 0)
				words.insert(s);
			else 
				return -1;
		}
		else{
			if(ss >> s)
				return -1;
			else
				words.insert(s);
		}			
	}
	return 0;
}

void intersectWebpage(set<string> &words, map<string, Webpage*> &nameToWeb, map<string, set<Webpage*> > &wordToWeb, ofstream &output){
	map<string, Webpage*>::iterator it;
	set<string>::iterator a;
	for (a = words.begin(); a != words.end(); ++a){
		set<Webpage*> webSet;
		for (it = nameToWeb.begin(); it != nameToWeb.end(); ++it){
			if ((it->second)->get_content().find(*a) != (it->second)->get_content().end()){
					webSet.insert(it->second);
					break;
			}
		}
		wordToWeb.insert(pair <string, set<Webpage*> >(*a, webSet));
	}
	
	map<string, set<Webpage*> >::iterator b;
	set< Webpage*>::iterator c;
	set<Webpage*> tempSet;
	tempSet.clear();

	for (it = nameToWeb.begin(); it != nameToWeb.end(); ++it){
		tempSet.insert(it->second);
	}

	for (b = wordToWeb.begin(); b != wordToWeb.end(); ++b){
		set<Webpage*> otherSet;
		for (c = (b->second).begin(); c != (b->second).end(); ++c){
			otherSet.insert(*c);
		}
		tempSet = intersectString(tempSet, otherSet);
	} 

	output << tempSet.size() << endl;
	for (c = tempSet.begin(); c != tempSet.end(); ++c){
		for (it = nameToWeb.begin(); it != nameToWeb.end(); ++it){
			if(it->second == *c)
				output << it->first << endl;
		}
	}
	
	return;
}

set<Webpage*> intersectString(set<Webpage*> &tempSet, set<Webpage*> &otherSet){
	set<Webpage*>::iterator it;
	set<Webpage*> finalSet;
	for (it = tempSet.begin(); it != tempSet.end(); ++it){
		if (otherSet.find(*it) != otherSet.end())
			finalSet.insert(*it);
	}
	return finalSet;
}


void unionWebpage(set<string> &words, map<string, Webpage*> &nameToWeb, map<string, set<Webpage*> > &wordToWeb, ofstream &output){
	map<string, Webpage*>::iterator it;
	set<string>::iterator a;
	for (a = words.begin(); a != words.end(); ++a){
		set<Webpage*> webSet;
		for (it = nameToWeb.begin(); it != nameToWeb.end(); ++it){
			if ((it->second)->get_content().find(*a) != (it->second)->get_content().end()){ 
				webSet.insert(it->second);
					break;
			}
		}
		wordToWeb.insert(pair <string, set<Webpage*> >(*a, webSet));
	}
	map<string, set<Webpage*> >::iterator b;
	set<Webpage*>::iterator c;
	set<Webpage*> finalSet;
	finalSet.clear();

	for (b = wordToWeb.begin(); b != wordToWeb.end(); ++b){
		for (c = (b->second).begin(); c != (b->second).end(); ++c){
			finalSet.insert(*c);
		}
	}

	output << finalSet.size() << endl;
	for (c = finalSet.begin(); c != finalSet.end(); ++c){
		for (it = nameToWeb.begin(); it != nameToWeb.end(); ++it){
			if(it->second == *c)
				output << it->first << endl;
		}
	}
	return;
}

void print(string str, ofstream &output){
	ifstream input(str);
	string word;
	while (getline(input, word)){
		stringstream ss(word);
		char a;
		while (ss >> noskipws >> a){
			if (a == '('){
				ss >> a;
		  		while (a != ')') {
		    		ss >> a;
		  		}
			}

			else
				output << a;

		}
		output << endl;
	}
	return;
}

void incoming(string str, map<string, Webpage*> &nameToWeb, ofstream &output){
	bool valid = false;
	map<string, Webpage*>::iterator it;
	set<string>::iterator a;
	for (it = nameToWeb.begin(); it != nameToWeb.end(); ++it){
		if (it->first == str){
			valid = true;
			output << (it->second)->incoming_size() << endl;
			for (a = (it->second)->get_incoming().begin(); a != (it->second)->get_incoming().end(); ++a){
				output << *a << endl;
			}
		}
	}
	if (!valid)
		output << "0" << endl;
	return;
}

void outgoing(string str, map<string, Webpage*> &nameToWeb, ofstream &output){
	bool valid = false;
	map<string, Webpage*>::iterator it;
	set<string>::iterator a;
	for (it = nameToWeb.begin(); it != nameToWeb.end(); ++it){
		if (it->first == str){
			valid = true;
			output << (it->second)->outgoing_size() << endl;
			for (a = (it->second)->get_outgoing().begin(); a != (it->second)->get_outgoing().end(); ++a){
				output << *a << endl;
			}
		}
	}
	if (!valid)
		output << "0" << endl;
	return;
}