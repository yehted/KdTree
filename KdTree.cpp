#include "KdTree.h"

KdTree::Node::Node(const Point2D& p, double xmin, double ymin, double xmax, double ymax) :
p_(p), rect_(xmin, ymin, xmax, ymax) {}

int KdTree::Node::comparebyX(const Point2D& p) {
	if (p.x() < p_.x()) return -1;
	if (p.x() > p_.x()) return 1;
	return 0;
}

int KdTree::Node::comparebyY(const Point2D& p) {
	if (p.y() < p_.y()) return -1;
	if (p.y() > p_.y()) return 1;
	return 0;
}

KdTree::Node* KdTree::insert(Node* x, const Point2D& p, bool HNode,
	double xmin, double ymin, double xmax, double ymax) {
	if (x == NULL)
		return new Node(p, xmin, ymin, xmax, ymax);

	// Determine if vertical or horizontal split
	int cmp;
	double edge;
	if (!HNode) {
		cmp = x->comparebyX(p);
		edge = x->p_.x();
	}
	else {
		cmp = x->comparebyY(p);
		edge = x->p_.y();
	}

	// Insert node
	if (cmp < 0) {
		if (!HNode) 
			x->lb = insert(x->lb, p, !HNode, xmin, ymin, edge, ymax);
		else
			x->lb = insert(x->lb, p, !HNode, xmin, ymin, xmax, edge);
	}
	else if (cmp > 0) {
		if (!HNode)
			x->rt = insert(x->rt, p, !HNode, edge, ymin, xmax, ymax);
		else
			x->rt = insert(x->rt, p, !HNode, xmin, edge, xmax, ymax);
	}
	else
		if (p == x->p_) N_--;

	return x;
}

KdTree::KdTree() : root_(NULL), N_(0) {}

bool KdTree::isEmpty() { return N_ == 0; }

int KdTree::size() { return N_; }

void KdTree::insert(const Point2D& p) {
	root_ = insert(root_, p, false, 0, 0, 1, 1);
	N_++;
}

bool KdTree::contains(const Point2D& p) {
	return get(root_, p, false) != NULL;
}

KdTree::Node* KdTree::get(Node* x, const Point2D& p, bool HNode) {
	if (x == NULL) return NULL;

	int cmp;
	if (!HNode)			cmp = x->comparebyX(p);
	else				cmp = x->comparebyY(p);

	if		(cmp < 0)	return get(x->lb, p, !HNode);
	else if (cmp > 0)	return get(x->rt, p, !HNode);
	else {
		if (HNode)		cmp = x->comparebyX(p);
		else			cmp = x->comparebyY(p);

		if (cmp == 0)	return x;
		else			return get(x->rt, p, !HNode);
	}
}

Deque<Point2D> KdTree::range(const RectHV& rect) {
	Deque<Point2D> dq;
	range(root_, dq, rect, false);
	return dq;
}

void KdTree::range(Node* x, Deque<Point2D>& deque, const RectHV& rect, bool HNode) {
	if (x == NULL) return;

	if (rect.contains(x->p_)) deque.addFirst(x->p_);

	if (!HNode) {
		if (rect.xmax() >= x->p_.x()) range(x->rt, deque, rect, !HNode);
		if (rect.xmin() <= x->p_.x()) range(x->lb, deque, rect, !HNode);
	}
	else {
		if (rect.ymax() >= x->p_.y()) range(x->rt, deque, rect, !HNode);
		if (rect.ymin() <= x->p_.y()) range(x->lb, deque, rect, !HNode);
	}
}

Point2D KdTree::nearest(const Point2D& p) {
	if (N_ == 0) return Point2D();
	return nearest(root_, p, root_->p_, root_->p_.distanceSquaredTo(p), false);
}

Point2D KdTree::nearest(Node* x, const Point2D& p, Point2D& champ, double d, bool HNode) {
	if (x == NULL) return champ;
	if (d < x->rect_.distanceSquaredTo(p)) return champ;

	double distance = x->p_.distanceSquaredTo(p);
	if (distance < d) {
		d = distance;
		champ = x->p_;
	}

	// Decide if vertical or horizontal node
	int cmp;
	if (!HNode) cmp = x->comparebyX(p);
	else        cmp = x->comparebyY(p);

	Point2D rchamp = champ;
	double rd;
	if (cmp < 0) {
		rchamp = nearest(x->lb, p, champ, d, !HNode);
		rd = rchamp.distanceSquaredTo(p);
		if (rd < d) {
			champ = rchamp;
			d = rd;
		}
		champ = nearest(x->rt, p, champ, d, !HNode);
	}
	else { //if (cmp > 0) {
		rchamp = nearest(x->rt, p, champ, d, !HNode);
		rd = rchamp.distanceSquaredTo(p);
		if (rd < d) {
			champ = rchamp;
			d = rd;
		}
		champ = nearest(x->lb, p, champ, d, !HNode);
	}

	return champ;
}