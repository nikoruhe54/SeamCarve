#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

string uploadData(string FileName, int &x, int &y, int &max) {
	int xLength = 0, yLength = 0, maxVal = 0;
	string word = "", dimension = "", maxSize = "", pixelStr = "";
	char letter;
	bool p2Check = false, dimensionCheck = false, maxCheck = false, comment = false;
	ifstream inFile(FileName);
	while (inFile.get(letter)) {
		comment = false;
		if (letter == '\n') {
			if (!p2Check) {
				if (word == "P2") {
					p2Check = true;
					word = "";
				}
			}
			else if (!dimensionCheck) {
				for (int i = 0; i < word.length(); i++) {
					if (word[i] != ' ' && word[i] != '\n') {
						dimension += word[i];
					}
					else if (word[i] == ' ') {
						if (xLength == 0) {
							xLength = atoi(dimension.c_str());
							dimension = "";
						}
					}
					 if (i == word.length()-1) {
						yLength = atoi(dimension.c_str());
						dimension = "";
						dimensionCheck = true;
						word = "";
					}
				}
			}
			else if (!maxCheck) {
				maxVal = atoi(word.c_str());
				maxCheck = true;
				word = "";
			}
			else {
				pixelStr += word;
				pixelStr += "\n";
				word = "";
			}
		}
		else if (letter == '#') {
			while (letter != '\n') {
				inFile.get(letter);
			}
			comment = true;
		}

		if (comment == false && letter != '\n') {
			word += letter;
		}
	}
	x = xLength;
	y = yLength;
	max = maxVal;
	return pixelStr;
}

int main() {
	int xLen = 0, yLen = 0, maxLen = 0;
	cout << xLen << endl;
	cout << yLen << endl;
	cout << maxLen << endl;
	string pixels = uploadData("test.pgm", xLen, yLen, maxLen);
	cout << pixels;
	return 0;
}

