#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

string uploadData(string FileName) {
	int xLength, yLength, maxVal;
	string word = "", dimension = "", maxSize = "", pixelStr = "";
	char letter;
	bool p2Check = false, dimensionCheck = false, maxCheck = false, comment = false;
	ifstream inFile(FileName);
	while (inFile) {
		cout << "got to main inFileLoop" << endl;
		comment = false;
		inFile >> letter;
		if (letter == '\n') {
			cout << "found a newline" << endl;
			cout << word << endl;
			if (!p2Check) {
				if (word == "P2") {
					p2Check == true;
					word = "";
					cout << "got P2" << endl;
				}
			}
			else if (!dimensionCheck) {
				for (int i = 0; i < word.length(); i++) {
					if (word[i] != ' ' && word[i] != '\n') {
						dimension += word[i];
					}
					else if (word[i] == ' ') {
						xLength = atoi(dimension.c_str());
						dimension = "";
						cout << "got x" << endl;
					}
					else if (word[i] == '\n') {
						yLength = atoi(dimension.c_str());
						dimension = "";
						dimensionCheck = true;
						cout << "got y" << endl;
					}
				}
			}
			else if (!maxCheck) {
				if (letter != ' ' || letter != '\n') {
					maxSize += letter;
				}
				else {
					maxVal = atoi(maxSize.c_str());
					maxCheck = true;
					cout << "got maxSize" << endl;
				}
			}
			else {
				pixelStr += word;
				word = "";
			}
		}
		else if (letter == '#') {
			while (letter != '\n') {
				inFile >> letter;
			}
			comment = true;
		}

		if (comment == false) {
			word += letter;
		}
	}
	return pixelStr;
}

int main() {
	string pixels = uploadData("test.pgm");
	cout << pixels;
	return 0;
}

