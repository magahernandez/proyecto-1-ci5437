#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int size, qSize;

void printLine(int t1, int t2, fstream &file) {

	for (int i=0; i<qSize; i++) {
		if (i == t1) {
			file << "0 ";
		} else if (i == t2) {
			file << "X ";
		} else {
			file << "- ";
		}
	}

	file << "=> ";

	for (int i=0; i<qSize; i++) {
		if (i == t2) {
			file << "0 ";
		} else if (i == t1) {
			file << "X ";
		} else {
			file << "- ";
		}
	}

    file << "MOVE_BLANK_FROM_" << t1 << "_TO_" << t2 << "\n";
}

int main (int argc, char *argv[]) {

	size = atoi(argv[1]);
	qSize = size*size;

    fstream file;

    ostringstream os;
    os << qSize-1 << "-puzzle.psvn";
    string s = os.str();

    file.open(s,ios::out);

    if(!file){
        cout<<"Error in creating file!!!";
        return 0;
    }

    file << "# " << qSize-1 << "-puzzle\n\n";

    file << "DOMAIN tile " << qSize << " # define a domain called 'tile' consisting of " << qSize << " constants\n\t";

	for (int i=0; i<qSize; i++) {
        file << i << " ";
	}

    file << " # these are the constants (0 is Blank)";

    file << "\n\n" << qSize << " # a state is a vector of length " << qSize << "\n\n";

	for (int i=0; i<qSize; i++) {
		file <<"tile ";
	}

	file << "\n\n";

	for (int i=0; i<qSize; i++) {
		
        // MOVE BLANK UP
		if (i >= size) {
			printLine(i, i-size, file);
		}

		// MOVE BLANK DOWN
		if (i < (size-1)*size) {
			printLine(i, i+size, file);
		} 

		// MOVE BLANK LEFT
		if (i%size != 0) {
		    printLine(i, i-1, file);
		}

		// MOVE BLANK RIGHT
		if (i%size != (size-1)) {
			printLine(i, i+1, file);
		}

	}

	file << "\nGOAL ";

	for (int i=0; i<qSize; i++) {
		file << i << " ";
	}

	file << "\n";


    file.close();

	return 1;
}