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
	while (inFile.get(letter)) {
		comment = false;
		if (letter == '\n') {
			if (!p2Check) {
				if (word == "P2") {
					p2Check == true;
					word = "";
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
					}
					else if (word[i] == '\n') {
						yLength = atoi(dimension.c_str());
						dimension = "";
						dimensionCheck = true;
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
				}
			}
			else {
				pixelStr += word;
				word = "";
			}
		}
		else if (letter == '#') {
			while (letter != '\n') {
				inFile.get(letter);
			}
			comment = true;
		}

		if (comment == false) {
			word += letter;
		}
	}
	cout << "The X dimension is: " <<  xLength <<  endl;
	cout << "The Y dimension is: " <<  yLength <<  endl;
	cout << "The max pixel is: " << maxVal << endl;
	return pixelStr;
}

int main() {
	string pixels = uploadData("test.pgm");
	cout << pixels;
	return 0;
}

