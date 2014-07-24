#include "RectHV.h"
#include "Deque.h"
#include <set>

class PointSET {
public:
	PointSET();
	bool isEmpty();
	int size();
	void insert(const Point2D& p);
	bool contains(const Point2D& p);
	void draw();
	Deque<Point2D> range(const RectHV& rect);
	Point2D nearest(const Point2D& p);

private:
	std::set<Point2D> set_;
};