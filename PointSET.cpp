#include "PointSET.h"

PointSET::PointSET() {}

bool PointSET::isEmpty() { return set_.size() == 0; }

int PointSET::size() { return set_.size(); }

void PointSET::insert(const Point2D& p) {
	if (!contains(p))
		set_.insert(p);
}

bool PointSET::contains(const Point2D& p) {
	return set_.find(p) != set_.end();
}

Point2D PointSET::nearest(const Point2D& p) {
	if (isEmpty()) return Point2D();
	double minDist(INFINITY);
	double distance(INFINITY);
	Point2D nearest = p;
	for (Point2D s : set_) {
		distance = s.distanceSquaredTo(p);
		if (distance < minDist) {
			minDist = distance;
			nearest = s;
		}
	}
	return nearest;
}

Deque<Point2D> PointSET::range(const RectHV& rect) {
	Deque<Point2D> points;
	for (Point2D p : set_)
		if (rect.contains(p)) points.addLast(p);
	return points;
}