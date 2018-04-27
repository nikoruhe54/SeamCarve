#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;


int** uploadData(string FileName, int &xLength, int &yLength) {
	int maxVal = 0;
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
		if (dimension[i] != ' ') {
			if (splitD == false) {
				xNum += dimension[i];
			}
			if (splitD == true) {
				yNum += dimension[i];
			}
		}
		else {
			splitD = true;
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
	return pixelMatrix;
}

int** makeEMatrix(int** pixelMatrix, int x, int y) {
	int** energy = new int*[y];
	for (int j = 0; j < y; j++) {
		energy[j] = new int[x];
	}

	for (int Yval = 0; Yval < y; Yval++) {
		for (int Xval = 0; Xval < x; Xval++) {
			if (Yval == 0 && Xval == 0) {
				energy[Yval][Xval] = abs(pixelMatrix[Yval + 1][Xval] - pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval][Xval + 1]- pixelMatrix[Yval][Xval]);
			}
			else if (Yval == 0 && Xval == x - 1) {
				energy[Yval][Xval] = abs(pixelMatrix[Yval + 1][Xval]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval][Xval - 1]- pixelMatrix[Yval][Xval]);
			}
			else if (Yval == y - 1 && Xval == 0) {
				energy[Yval][Xval] = abs(pixelMatrix[Yval - 1][Xval]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval][Xval + 1]- pixelMatrix[Yval][Xval]);
			}
			else if (Yval == y - 1 && Xval == x - 1) {
				energy[Yval][Xval] = abs(pixelMatrix[Yval - 1][Xval]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval][Xval - 1]- pixelMatrix[Yval][Xval]);
			}
			else if (Yval == 0){
				energy[Yval][Xval] = abs(pixelMatrix[Yval][Xval - 1]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval][Xval + 1]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval + 1][Xval]- pixelMatrix[Yval][Xval]);
			}
			else if (Yval == y - 1) {
				energy[Yval][Xval] = abs(pixelMatrix[Yval][Xval - 1]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval][Xval + 1]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval - 1][Xval]- pixelMatrix[Yval][Xval]);
			}
			else if (Xval == 0) {
				energy[Yval][Xval] = abs(pixelMatrix[Yval - 1][Xval]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval + 1][Xval]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval][Xval + 1]- pixelMatrix[Yval][Xval]);
			}
			else if (Xval == x - 1) {
				energy[Yval][Xval] = abs(pixelMatrix[Yval - 1][Xval]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval + 1][Xval]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval][Xval - 1]- pixelMatrix[Yval][Xval]);
			}
			else {
				energy[Yval][Xval] = abs(pixelMatrix[Yval][Xval - 1] - pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval][Xval + 1]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval - 1][Xval]- pixelMatrix[Yval][Xval]) + abs(pixelMatrix[Yval + 1][Xval]- pixelMatrix[Yval][Xval]);
			}
		}
	}
	cout << "here is the energy matrix" << endl;
	for (int j = 0; j < y; j++) {
		for (int k = 0; k < x; k++) {
			cout << energy[j][k] << " ";
		}
		cout << endl;
	}
	return energy;
}

int main() {
	int x = 0, y = 0;
	int** pixelMatrix = uploadData("test.pgm", x, y);
	int** eMatrix = makeEMatrix(pixelMatrix, x, y);
	while (1) {

	}
	return 0;
}


