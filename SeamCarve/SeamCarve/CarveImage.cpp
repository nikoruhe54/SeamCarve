#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int** uploadData(string FileName) {
	int xLength, yLength, maxVal;
	string word = "";
	char letter;
	bool p2Check = false, dimensionCheck = false, maxCheck = false;
	ifstream inFile(FileName);
	while (inFile) {
		inFile >> letter;
		if (letter == '\n') {
			if (!p2Check) {
				if (word == "P2") {
					p2Check == true;
				}
			}
			else if (!dimensionCheck) {

			}
		}
		else if (letter == '#') {

		}
		else if (letter == ' ') {

		}
		word += letter;
	}

}