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
	int numberOfNodeExplored = 0;
	Node *root;
	Point nearestNeighbour;
	int getNodeCount();
	Node getRoot();
	MetricTree(EuclidianSpace* euclidianSpace);
	void buildMetricTreeBasic(vector<Point> listPoints, Node *currentNode);
	void buildMetricTreeOptimized(vector<Point> listPoints, Node *currentNode);
	Point getBestPivot(vector<Point> listPoints);
	bool searchMetricTreePrunning(Node *T, Point *q);
	bool searchMetricTreeDefeatist(Node *T, Point *q);
	static float median(vector<float> scores);
	friend ostream& operator<<(ostream& os, const MetricTree& mt);
	virtual ~MetricTree();
};

