#include "Node.h"
#include "EuclidianSpace.h"
#include <vector>
#include "Point.h"
#include <iostream>
using namespace std;
#pragma once
class MetricTree
{
	
	EuclidianSpace* euclidianSpace;
	int nodeCount = 0;
	vector<Node*> allNodes;
public:
	Node *root;
	Point nearestNeighbour;
	int getNodeCount();
	Node getRoot();
	MetricTree(EuclidianSpace* euclidianSpace);
	void buildMetricTree(vector<Point> listPoints, Node *currentNode);
	void buildMetricTree2(vector<Point> listPoints, Node *currentNode);
	bool search_MetricTree(Node *T, Point *q);
	static float median(vector<float> scores);
	friend ostream& operator<<(ostream& os, const MetricTree& mt);
	virtual ~MetricTree();
};

