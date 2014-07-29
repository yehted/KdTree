#include "RectHV.h"
#include "Deque.h"
#include <set>

class KdTree {
public:
	class Node {
	public:
		Node();
		Node(const Point2D& p, double xmin, double ymin, double xmax, double ymax);
		int comparebyX(const Point2D& p);
		int comparebyY(const Point2D& p);

		Point2D p_;
		RectHV rect_;
		Node* lb;
		Node* rt;
	};
	KdTree();
	bool isEmpty();
	int size();
	void insert(const Point2D& p);
	bool contains(const Point2D& p);
	void draw();
	Deque<Point2D> range(const RectHV& rect);
	Point2D nearest(const Point2D& p);

private:
	int N_;
	Node* root_;

	Node* insert(Node* x, const Point2D& p, bool HNode,
		double xmin, double ymin, double xmax, double ymax);
	Node* get(Node* x, const Point2D& p, bool HNode);
	void range(Node* x, Deque<Point2D>& deque, const RectHV& rect, bool HNode);
	Point2D nearest(Node* x, const Point2D& p, Point2D& champ, double d, bool HNode);
};