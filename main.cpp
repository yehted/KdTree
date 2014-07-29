#include <fstream>
#include "PointSET.h"
#include "KdTree.h"

using namespace std;

int main(int argc, char* argv[]) {
	ifstream inFile;
	//inFile.open(argv[1]);
	inFile.open("kdtree\\circle10.txt");
	if (!inFile.is_open()) {
		cerr << "File not opened" << endl;
		exit(1);
	}

	PointSET brute;
	KdTree kdtree;

	double x, y;
	while (true) {
		inFile >> x;
		inFile >> y;
		if (inFile.eof()) break;
		Point2D p(x, y);
		brute.insert(p);
		kdtree.insert(p);
	}
	cout << "Size of brute: " << brute.size() << endl;
	cout << "Size of KdTree: " << kdtree.size() << endl;

	RectHV rect(0.2, 0.2, 0.8, 0.5);
	Point2D p(0.1, 0.1);

	cout << "Rectangle: " << rect << endl;
	cout << "Point: " << p << endl;

	cout << "Brute nearest: " << brute.nearest(p) << endl;
	cout << "KdTree nearest: " << kdtree.nearest(p) << endl;

	cout << "Brute contains: " << endl;
	for (Point2D s : brute.range(rect))
		cout << s << endl;
	cout << endl;
	cout << "KdTree contains: " << endl;
	for (Point2D t : kdtree.range(rect))
		cout << t << endl;
	
	return 0;
}