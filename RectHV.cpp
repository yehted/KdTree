#include "RectHV.h"

RectHV::RectHV() : xmin_(0), ymin_(0), xmax_(0), ymax_(0) {}

RectHV::RectHV(double xmin, double ymin, double xmax, double ymax) :
xmin_(xmin), ymin_(ymin), xmax_(xmax), ymax_(ymax) {
	if (xmax < xmin || ymax < ymin)
		throw std::invalid_argument("Invalid rectangle");
}

double RectHV::xmin() const { return xmin_; }
double RectHV::ymin() const { return ymin_; }
double RectHV::xmax() const { return xmax_; }
double RectHV::ymax() const { return ymax_; }

bool RectHV::contains(const Point2D& p) const {
	return (p.x() >= xmin_) && (p.x() <= xmax_)
		&& (p.y() >= ymin_) && (p.y() <= ymax_);
}

bool RectHV::intersects(const RectHV& that) {
	return (xmax_ >= that.xmin_) && (ymax_ >= that.ymin_)
		&& (that.xmax_ >= xmin_) && (that.ymax_ >= ymin_);
}

double RectHV::distanceSquaredTo(const Point2D& p) {
	double dx = 0.0, dy = 0.0;
	if		(p.x() < xmin_) dx = p.x() - xmin_;
	else if (p.x() > xmax_) dx = p.x() - xmax_;
	if		(p.y() < ymin_) dx = p.y() - ymin_;
	else if (p.y() > ymax_) dx = p.y() - ymax_;
	return dx*dx + dy*dy;
}

double RectHV::distanceTo(const Point2D& p) {
	return sqrt(distanceSquaredTo(p));
}

bool RectHV::operator==(const RectHV& that) {
	if (&that == this) return true;
	if (&that == NULL) return false;
	if (xmin_ != that.xmin_) return false;
	if (ymin_ != that.ymin_) return false;
	if (xmax_ != that.xmax_) return false;
	if (ymax_ != that.ymax_) return false;
	return true;
}

std::ostream& operator<<(std::ostream& output, const RectHV& that) {
	output << "[" << that.xmin_ << ", " << that.xmax_ << "] x [" << that.ymin_ << ", " << that.ymax_ << "]";
	return output;
}