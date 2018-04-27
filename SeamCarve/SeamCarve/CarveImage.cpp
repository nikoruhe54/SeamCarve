#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;


void uploadData(string FileName) {
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

	int** pixelMatrix = new int*[yLength];
	for (int j = 0; j < yLength; j++) {
		pixelMatrix[j] = new int[xLength];
	}
	for (int y = 0; y < yLength; y++) {
		for (int x = 0; x < xLength; x++) {
			inFile >> pixelMatrix[y][x];
		}
	}
	for (int j = 0; j < yLength; j++) {
		for (int k = 0; k < xLength; k++) {
			cout << pixelMatrix[j][k] << " ";
		}
		cout << endl;
	}
	//return pixelMatrix;
}

int main() {
	uploadData("test.pgm");
	return 0;
}


