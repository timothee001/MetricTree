#pragma once
#include "Point.h"
class Node
{
	Point pivot;
	float d1, d2, d3, d4;
	bool isLeaf;
public:
	Node();
	Node * left;
	Node * right;
	void setPivot(Point pivot);
	void setLeftNode(Node * left);
	void setRightNode(Node *right);
	void setD(int d, float value);
	Point getPivot();
	float getD(int d);
	void setLeafTrue();
	bool isALeaf();
	friend ostream& operator<<(ostream& os, const Node& mt);
	virtual ~Node();
};

