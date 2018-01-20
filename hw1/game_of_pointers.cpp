#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>

using namespace std;

struct Warrior {
    string weapon;
    int power;
    bool res;
};

//Feel free to modify the parameters if you need other values
bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirmish_row,
		      int rows, int columns, int &reserves, ofstream &output){

    if (skirmish_row > columns || skirmish_row < 0)
        return false;

    int j = skirmish_row;

    for (int i = 0; i < rows; i++) {

            bool empty = false, invwin = false, protwin = false;

            if (invaders[j][i] != NULL && protectors[i][j] != NULL) {

                if (((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)) || (protectors[i][j] -> res == true)) {

                    if (protectors[i][j] -> res != true) {
                        protectors[i][j] -> power = i*10+(j+1)*10;
                    }

                    invaders[j][i] -> power = (j*10)+((i+1)*10);  

                    if ((protectors[i][j] -> power) > (invaders[j][i] -> power))
                        protwin = true;

                    else if ((protectors[i][j] -> power) < (invaders[j][i] -> power))
                        invwin = true;

                    else 
                        output << "Duel ends in draw" << endl;
                }
                
                if (((i % 2 == 0 && j % 2 == 0) && (protectors[i][j] -> res != true)) || protwin == true) {
                    protectors[i][j] -> weapon = "axe";
                    output << "Invader killed" << endl;
                    invaders[j][i] = NULL;
                }

                else if (((i % 2 != 0 && j % 2 != 0) && (protectors[i][j] -> res != true))|| invwin == true) {
                    
                    invaders[j][i] -> weapon = "axe";

                    for (int k = 0; k < rows; k++) {
                        for (int l = 0; l < columns; l++) {

                            if (invaders[l][k] == NULL) {
                                output << "Protector defected" << endl;
                                invaders[l][k] = protectors[i][j];
                                empty = true;
                                break;
                            }
                        }
                        if (empty) break;
                    }
                    
                    if (!empty)
                        output << "Protector killed" << endl;

                    if (reserves > 0) {
                        protectors[i][j] -> weapon = "axe";
                        protectors[i][j] -> power = 100;
                        protectors[i][j] -> res = true;
                        reserves--;
                    }

                    else
                        protectors[i][j] = NULL;
                }
            }
            
            else if (invaders[j][i] == NULL){
                output << "No assault" << endl;
            }

            else if (invaders[j][i] != NULL && protectors[i][j] == NULL){
                return true;
            }

        }

    return false;
    //returns true if the invaders breach the walls.
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
	   cerr << "Please provide an input and output file" << endl;
	   return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int rows;
    int cols;
    int reserve;
    int skirmishes;

    //read the input file and initialize the values here.
    bool done = false;

    string rows_string;
    string cols_string;
    string reserve_string;
    string skirmishes_string;

    if(input.fail()) {
       cerr << "Invalid file" << endl;
       return -1;
    }

    input >> rows_string >> cols_string >> reserve_string >> skirmishes_string;

    rows = stoi(rows_string);
    cols = stoi(cols_string);
    reserve = stoi(reserve_string);
    skirmishes = stoi(skirmishes_string);

    Warrior ***protectors = new Warrior**[rows];
	
	for (int i = 0; i < rows; i++) {
		protectors[i] = new Warrior*[cols];
	}

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            protectors[i][j] = new Warrior;
        }
    }

    Warrior ***invaders = new Warrior**[cols];

    for (int i = 0; i < cols; i++) {
		invaders[i] = new Warrior*[rows];
	}

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            invaders[i][j] = new Warrior;
        }
    }

    //initialize the protectors and invaders here.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            protectors[i][j] -> power = 0;
            protectors[i][j] -> weapon = "sword";
            protectors[i][j] -> res = false;
            invaders[j][i] -> power = 0;
            invaders[j][i] -> weapon = "sword";
            invaders[j][i] -> res = false;
        }
    }


    for (int i=1; i <= skirmishes; i++){
        int skirmish_row;
        
        input >> skirmish_row;//read the input file to find the value for skirmish row
        
        //In general, it is bad style to throw everything into your main function
        bool end = skirmish(protectors, invaders, skirmish_row, rows, cols, reserve, output);
        if (end)
        	done = true;
    }

    //output the winner and deallocate your memory.
    if (done)
    	output << "Winner: invaders" << endl;
    else
    	output << "Winner: protectors" << endl;

    /*for (int i = 0; i < rows; i ++) {
        for (int j = 0; j < cols; j++) {
            delete protectors[i][j];
        }
        delete[] protectors[i];
    }
    delete[] protectors;

    for (int i = 0; i < cols; i ++) {
        for (int j = 0; j < rows; j++) {
            delete invaders[i][j];
        }
        delete[] invaders[i];
    }
    delete[] invaders;*/

    return 0;
}