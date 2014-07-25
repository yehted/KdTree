/*****************************************************
* Immutable point data type for points in the plane
*
*
******************************************************/

#include <iostream>

class Point2D {
public:
	Point2D();
	Point2D(double x, double y);
	double x() const;
	double y() const;
	double distanceTo(const Point2D& that) const;
	double distanceSquaredTo(const Point2D& that) const;
	bool operator<(const Point2D& that) const;
	bool operator==(const Point2D& that);
	friend std::ostream& operator<<(std::ostream& output, const Point2D& that);
	void draw();

private:
	double x_;
	double y_;
};