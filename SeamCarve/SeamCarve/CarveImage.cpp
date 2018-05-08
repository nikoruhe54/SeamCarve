#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;


int** uploadData(string FileName, int &xLength, int &yLength, int &max) {
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
	max = atoi(maxSize.c_str());

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

int** carveHorizontal(int** eMatrix, int** &pixelMatrix, int x, int y) {
	int Ylen = y - 1;
	int Xlen = x;
	int minIndex = 0, carve = 0;
	long temp = 9999999999;
	bool firstCol = true;
	int** newImg = new int*[Ylen];
	for (int j = 0; j < y; j++) {
		newImg[j] = new int[Xlen];
	}
	int** totalMatrix = new int*[y];
	for (int t = 0; t < y; t++) {
		totalMatrix[t] = new int[x];
	}

	// build the total Matrix
	cout << "here is the cumulative matrix" << endl;
	for (int a = 0; a < x; a++) {
		for (int b = 0; b < y; b++) {
			if (a == 0) {
				totalMatrix[b][a] = eMatrix[b][a];
				cout << totalMatrix[b][a] << " ";
			}
			else if (a == x - 1) {
				if (b == 0) {
					totalMatrix[b][a] = eMatrix[b][a] + min(totalMatrix[b][a - 1], totalMatrix[b + 1][a - 1]);
					cout << totalMatrix[b][a] << " ";
				}
				else if (b == y - 1) {
					totalMatrix[b][a] = eMatrix[b][a] + min(totalMatrix[b][a - 1], totalMatrix[b - 1][a - 1]);
					cout << totalMatrix[b][a] << " ";
				}
				else {
					totalMatrix[b][a] = eMatrix[b][a] + min(min(totalMatrix[b][a - 1], totalMatrix[b - 1][a - 1]), totalMatrix[b + 1][a - 1]);
					cout << totalMatrix[b][a] << " ";
				}
			}
			else {
				if (b == 0) {
					totalMatrix[b][a] = eMatrix[b][a] + min(totalMatrix[b][a - 1], totalMatrix[b + 1][a - 1]);
					cout << totalMatrix[b][a] << " ";
				}
				else if (b == x - 1) {
					totalMatrix[b][a] = eMatrix[b][a] + min(totalMatrix[b][a - 1], totalMatrix[b - 1][a - 1]);
					cout << totalMatrix[b][a] << " ";
				}
				else {
					totalMatrix[b][a] = eMatrix[b][a] + min(min(totalMatrix[b][a - 1], totalMatrix[b - 1][a - 1]), totalMatrix[b + 1][a - 1]);
					cout << totalMatrix[b][a] << " ";
				}
			}
		}
		cout << "\n";
	}
	for (int X = 0; X < x; X++) {
		for (int Y = 0; Y < y; Y++) {
			if (firstCol == true) {
				if (totalMatrix[Y][X] < temp) {
					temp = eMatrix[Y][X];
					minIndex = Y;
					carve = Y;
				}
			}
			else {
				if (Y <= carve + 1 && Y >= carve - 1) {
					if (eMatrix[Y][X] < temp) {
						temp = eMatrix[Y][X];
						minIndex = Y;
					}
				}
			}
		}
		firstCol = false;
		temp = 65000;
		eMatrix[minIndex][X] = -1;
		carve = minIndex;
	}

	//cout << "here is the horizontal Seam" << endl;
	//build the horizontal seam
	int z = 0;
	for (int a = 0; a < x; a++) {
		for (int b = 0; b < y; b++) {
			if (eMatrix[b][a] != -1) {
				newImg[z][a] = pixelMatrix[b][a];
				//cout << newImg[z][a] << " ";
				z++;
			}
		}
		z = 0;
		//cout << endl;
	}
	return newImg;
}

void carveVertical(int** eMatrix, int** &pixelMatrix, int x, int y) {
	int Ylen = y;
	int Xlen = x-1;
	int minIndex = 0, carve = 0;
	long temp = 9999999999;
	bool firstRow = true;
	int** totalMatrix = new int*[Ylen];
	for (int t = 0; t < y; t++) {
		totalMatrix[t] = new int[x];
	}

	// build the total Matrix
	cout << "here is the cumulative matrix" << endl;
	for (int a = 0; a < y; a++) {
		for (int b = 0; b < x; b++) {
			if (a == 0) {
				totalMatrix[a][b] = eMatrix[a][b];
				cout << totalMatrix[a][b] << " ";
			}
			else if (a == y-1){
				if (b == 0) {
					totalMatrix[a][b] = eMatrix[a][b] + min(totalMatrix[a - 1][b], totalMatrix[a - 1][b + 1]);
					cout << totalMatrix[a][b] << " ";
				}
				else if (b == x - 1) {
					totalMatrix[a][b] = eMatrix[a][b] + min(totalMatrix[a - 1][b], totalMatrix[a - 1][b - 1]);
					cout << totalMatrix[a][b] << " ";
				}
				else {
					totalMatrix[a][b] = eMatrix[a][b] + min(min(totalMatrix[a - 1][b], totalMatrix[a - 1][b - 1]), totalMatrix[a - 1][b + 1]);
					cout << totalMatrix[a][b] << " ";
				}
			}
			else {
				if (b == 0) {
					totalMatrix[a][b] = eMatrix[a][b] + min(totalMatrix[a - 1][b], totalMatrix[a - 1][b + 1]);
					cout << totalMatrix[a][b] << " ";
				}
				else if (b == x - 1) {
					totalMatrix[a][b] = eMatrix[a][b] + min(totalMatrix[a - 1][b], totalMatrix[a - 1][b - 1]);
					cout << totalMatrix[a][b] << " ";
				}
				else {
					totalMatrix[a][b] = eMatrix[a][b] + min(min(totalMatrix[a - 1][b], totalMatrix[a - 1][b - 1]), totalMatrix[a - 1][b + 1]);
					cout << totalMatrix[a][b] << " ";
				}
			}
		}
		cout << "\n";
	}

	int**  newImg= new int*[Ylen];
	for (int j = 0; j < y; j++) {
		newImg[j] = new int[Xlen];
	}

	for (int Y = y-1; Y >= 0; Y--) {
		for (int X = 0; X < x; X++) {
			if (firstRow == true) {
				if (totalMatrix[Y][X] < temp) {
					temp = totalMatrix[Y][X];
					minIndex = X;
					carve = X;
				}
			}
			else {
				if (X <= carve + 1 && X >= carve - 1) {
					if (totalMatrix[Y][X] < temp) {
						temp = totalMatrix[Y][X];
						minIndex = X;
					}
				}
			}
		}
		firstRow = false;
		temp = 9999999999;
		totalMatrix[Y][minIndex] = -1;
		carve = minIndex;
	}

	//cout << "here is the vertical Seam" << endl;
	//build the vertical seam
	int z = 0;
	for (int j = 0; j < y; j++) {
		for (int k = 0; k < x; k++) {
			if (totalMatrix[j][k] != -1) {
				pixelMatrix[j][z] = pixelMatrix[j][k];
				//cout << newImg[j][z] << " ";
				z++;
			}
		}
		z = 0;
		//cout << endl;
	}
	//return newImg;
}

int main(int argc, char *argv[]) {

	int x = 0, y = 0, max = 0;
	bool cutLong = false, cutWide = false;
	int** pixelMatrix = uploadData(argv[1], x, y, max);
	int** eMatrix = makeEMatrix(pixelMatrix, x, y);

	int verticalSeams = stoi(argv[2]), horizontalSeams = stoi(argv[3]);

	//int** verticalImgCarve = new int*[y];
	if (verticalSeams > 0) {
		cutLong = true;
		carveVertical(eMatrix, pixelMatrix, x, y);
		verticalSeams--;
		x--;
	}
	while (verticalSeams > 0) {
		int** newEMatrix = makeEMatrix(pixelMatrix, x, y);
		carveVertical(newEMatrix, pixelMatrix, x, y);
		verticalSeams--;
		x--;
	}
/*
	if (horizontalSeams > 0 && cutLong == false) {
		verticalImgCarve = carveHorizontal(eMatrix, pixelMatrix, x, y);
		horizontalSeams--;
		y--;
	}
	else if (horizontalSeams > 0 && cutLong == true) {
		verticalImgCarve = makeEMatrix(verticalImgCarve, x, y);
		verticalImgCarve = carveHorizontal(verticalImgCarve, pixelMatrix, x, y);
		horizontalSeams--;
		y--;
	}

	while (horizontalSeams > 0) {
		verticalImgCarve = makeEMatrix(verticalImgCarve, x, y);
		verticalImgCarve = carveHorizontal(verticalImgCarve, pixelMatrix, x, y);
		horizontalSeams--;
		y--;
	}
	*/
	cout << "Here is the final Pic" << endl;
	string fileType = "_processed.pgm";
	string newFileName = argv[1] + fileType;
	ofstream myfile(newFileName);
	if (myfile.is_open())
	{
		myfile << "P2\n";
		myfile << x;
		myfile << " ";
		myfile << y;
		myfile << "\n";
		myfile << max;
		myfile << "\n";
		for (int a = 0; a < y; a++) {
			for (int b = 0; b < x; b++) {
				cout << pixelMatrix[a][b] << " ";
				myfile << pixelMatrix[a][b] << "\t";
			}
			myfile << "\n";
			cout << endl;
		}
		myfile.close();
	}

	return 0;
}


