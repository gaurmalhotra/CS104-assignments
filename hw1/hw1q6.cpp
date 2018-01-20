#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>

using namespace std;

string reverse (ifstream& ifile, int n);


int main(int argc, char* argv[])
{
	ifstream ifile(argv[1]);
	string num, word;
	ifile >> num;
	int n = stoi(num);

	word = reverse(ifile, n);
	cout << word << endl;

	return 0;

}

string reverse (ifstream& ifile, int n) {
	string line,word;
	ifile >> line;

	if (n == 0) {
		return line;
	}

	else {
		return reverse(ifile, n-1) + line + " ";
	}
}