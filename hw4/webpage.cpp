#include "webpage.h"

using namespace std;

Webpage::Webpage(){

}

void Webpage::content_push(string str){
	content.push_back(str); 
}

int Webpage::content_size(){
	return content.size(); 
}

vector<string> Webpage::get_content(){
	return content; 
}

void Webpage::incoming_insert(string str){
	incomingLinks.insert(str);
}

int Webpage::incoming_size(){
	return incomingLinks.size(); 
}

set<string> Webpage::get_incoming(){
	return incomingLinks; 
}

void Webpage::outgoing_insert(string str){
	outgoingLinks.insert(str);
}

int Webpage::outgoing_size(){
	return outgoingLinks.size(); 
}

set<string> Webpage::get_outgoing(){
	return outgoingLinks; 
}