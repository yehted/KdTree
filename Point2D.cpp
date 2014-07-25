#include "Point2D.h"
#include <math.h>
#include <stdexcept>

Point2D::Point2D() : x_(0.0), y_(0.0) {}

Point2D::Point2D(double x, double y) : x_(x), y_(y) {
	if (isinf(x_) || isinf(y_))
		throw std::invalid_argument("Coordinates must be finite");
	if (isnan(x_) || isnan(y_))
		throw std::invalid_argument("Coordinates cannot be NaN");
	if (x_ == 0.0) x_ = +0.0;
	if (y_ == 0.0) y_ = +0.0;
}

double Point2D::x() const { return x_; }

double Point2D::y() const { return y_; }

double Point2D::distanceTo(const Point2D& that) const {
	double dx = x_ - that.x_;
	double dy = y_ - that.y_;
	return sqrt(dx*dx + dy*dy);
}

double Point2D::distanceSquaredTo(const Point2D& that) const {
	double dx = x_ - that.x_;
	double dy = y_ - that.y_;
	return (dx*dx + dy*dy);
}

bool Point2D::operator<(const Point2D& that) const {
	if (y_ < that.y_) return true;
	if (y_ > that.y_) return false;
	if (x_ < that.x_) return true;
	if (x_ > that.x_) return false;
	return false;
}

bool Point2D::operator==(const Point2D& that) {
	if (&that == this) return true;
	if (&that == NULL) return false;
	return (x_ == that.x_ && y_ == that.y_);
}

std::ostream& operator<<(std::ostream& output, const Point2D& that) {
	output << "(" << that.x_ << ", " << that.y_ << ")";
	return output;
}