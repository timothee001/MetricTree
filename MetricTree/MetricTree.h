#include "Node.h"
#include "EuclidianSpace.h"
#include <vector>
#include "Point.h"
#include <iostream>
using namespace std;
#pragma once
class MetricTree
{
	Node *root;
	EuclidianSpace* euclidianSpace;
	int nodeCount = 0;
	vector<Node*> allNodes;
public:
	int getNodeCount();
	Node getRoot();
	MetricTree(EuclidianSpace* euclidianSpace);
	Node* buildMetricTree(vector<Point> listPoints);
	bool search_MetricTree(Node *T, Point *q);
	static float median(vector<float> scores);
	friend ostream& operator<<(ostream& os, const MetricTree& mt);
	virtual ~MetricTree();
};

