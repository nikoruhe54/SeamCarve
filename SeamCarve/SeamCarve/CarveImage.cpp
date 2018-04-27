#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;


string uploadData(string FileName, int &x, int &y, int &max) {
	int xLength = 0, yLength = 0, maxVal = 0;
	string word = "", dimension = "", maxSize = "", pixelStr = "";
	string xNum = "", yNum = "";
	char letter;
	bool p2Check = false, dimensionCheck = false, maxCheck = false, comment = false;
	ifstream inFile(FileName);
	getline(inFile, word);
	while (word != "P2") {
		getline(inFile, word);
	}

	getline(inFile, dimension);
	while (dimension[0] == '#') {
		getline(inFile, dimension);
	}

	getline(inFile, maxSize);
	while (maxSize[0] == '#') {
		getline(inFile, maxSize);
	}

	bool splitD = false;
	for (int i = 0; i < dimension.length(); i++) {
		if (dimension[i] != ' ' && splitD == false) {
			xNum += dimension[i];
		}
		else if (dimension[i] != ' ' && dimension[i] != '\n'){
			splitD = true;
			yNum += dimension[i];
		}
	}

	xLength = atoi(xNum.c_str());
	yLength = atoi(yNum.c_str());

	while (inFile) {
		getline(inFile, word);
		if (word[0] != '#') {
			pixelStr += word;
		}
	}
	return pixelStr;
	/*
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
	*/
}

/*
void buildPixelMatrix(int** &pixelMatrix, string pixels, int xLen, int yLen) {
	int xCount = 0, yCount = 0;
	string tempNum = "";
	for (int i = 0; i < pixels.length(); i++) {
		if (xCount < xLen) {
			if (pixels[i] != ' ' && pixels[i] != '\n' && pixels[i] != '\t') {
				tempNum += pixels[i];
			}
			else {
				pixelMatrix[xCount][yCount] = atoi(tempNum.c_str());
				tempNum = "";
				xCount++;
			}
		}
		else {
			if (pixels[i] != ' ' && pixels[i] != '\n' && pixels[i] != '\t') {
				tempNum += pixels[i];
			} 
			else {
				yCount++;
				xCount = 0;
				pixelMatrix[xCount][yCount] = atoi(tempNum.c_str());
				tempNum = "";
				xCount++;
			}
		}
	}
}
*/
int main() {
	int xLen = 0, yLen = 0, maxLen = 0;
	string pixels = uploadData("bug.pgm", xLen, yLen, maxLen);
	int** pixelMatrix = new int*[yLen];
	for (int j = 0; j < yLen; j++) {
		pixelMatrix[j] = new int[xLen];
	}
	//buildPixelMatrix(pixelMatrix, pixels, xLen, yLen);
	/*
	for (int i = 0; i < yLen; i++) {
		for (int a = 0; a < xLen; a++) {
			cout << pixelMatrix[a][i] << " ";
		}
		cout << endl;
	}
	*/
	while (1) {

	}
	return 0;
}


