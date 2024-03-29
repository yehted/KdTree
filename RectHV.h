/*************************************************
* Implementation of 2D axis-aligned rectangle
* Dependencies: Point2D.h
*
**************************************************/
#ifndef RECTHV_H
#define RECTHV_H

#include "Point2D.h"

class RectHV {
public:
	RectHV();
	RectHV(double xmin, double ymin, double xmax, double ymax);
	double xmin() const;
	double ymin() const;
	double xmax() const;
	double ymax() const;
	bool contains(const Point2D& p) const;
	bool intersects(const RectHV& p);
	double distanceTo(const Point2D& p);
	double distanceSquaredTo(const Point2D& p);
	bool operator==(const RectHV& that);
	friend std::ostream& operator<<(std::ostream& output, const RectHV& that);

private:
	const double xmin_, ymin_;
	const double xmax_, ymax_;
};
#endif // !RECTHV_H