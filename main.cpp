#include <fstream>
#include "PointSET.h"

using namespace std;

int main(int argc, char* argv[]) {
	ifstream inFile;
	//inFile.open(argv[1]);
	inFile.open("kdtree\\circle100.txt");
	if (!inFile.is_open()) {
		cerr << "File not opened" << endl;
		exit(1);
	}

	PointSET brute;
	double x, y;
	while (true) {
		inFile >> x;
		inFile >> y;
		if (inFile.eof()) break;
		Point2D p(x, y);
		brute.insert(p);
	}
	cout << "Size of brute: " << brute.size() << endl;

	RectHV r(1.0, 1.0, 2.0, 2.0);
	cout << r << endl;
	return 0;
}