#include "KdTree.h"

KdTree::Node* KdTree::Node::insert(Node* x, Point2D p, bool HNode,
	double xmin, double ymin, double xmax, double ymax) {

}

KdTree::KdTree() : root_(NULL), N_(0) {}

bool KdTree::isEmpty() { return N_ == 0; }

int KdTree::size() { return N_; }

void KdTree::insert(const Point2D& p) {
	root_ = insert(root_, p, false, 0, 0, 1, 1);
	N_++;
}
