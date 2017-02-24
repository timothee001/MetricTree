#include "Node.h"
#include "HyperSpace.h"
#include <vector>
#include "Point.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <iostream>
#include <cassert>

using namespace std;
#pragma once
class MetricTree
{
	
	HyperSpace* hyperSpace;
	int nodeCount = 0;
	vector<Node*> allNodes;
public:
	int numberOfNodeExplored = 0;
	bool found = 0;
	Node *root;
	Point nearestNeighbour;
	int getNodeCount();
	Node getRoot();
	MetricTree(HyperSpace* hyperspace);
	void buildMetricTreeBasic(vector<Point> listPoints, Node *currentNode);
	void buildMetricTreeBasicOnConformations(vector<Point> listPoints, Node *currentNode);
	void buildMetricTreeOptimized(vector<Point> listPoints, Node *currentNode);
	void buildMetricTreeOptimizedOnConformations(vector<Point> listPoints, Node *currentNode);
	Point getBestPivot(vector<Point> listPoints);
	Point getBestPivotConformation(vector<Point> listPoints);
	Point getBestPivot2(vector<Point> listPoints);
	bool searchMetricTreePrunning(Node *T, Point *q);
	bool searchMetricTreePrunningConformation(Node *T, Point *q);
	bool searchMetricTreeDefeatist(Node *T, Point *q);
	bool searchMetricTreeDefeatistConformation(Node *T, Point *q);
	static float median(vector<float> scores);
	friend ostream& operator<<(ostream& os, const MetricTree& mt);
	virtual ~MetricTree();
};

