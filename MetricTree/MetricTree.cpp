#include "stdafx.h"
#include "MetricTree.h"
#include <algorithm>
#include <map>
#include <iostream>
#include <cassert>


int MetricTree::getNodeCount()
{
	return this->nodeCount;
}

Node MetricTree::getRoot()
{
	return *this->root;;
}

MetricTree::MetricTree(EuclidianSpace* euclidianSpace)
{
	this->euclidianSpace = euclidianSpace;
}


Node* MetricTree::buildMetricTree(vector<Point> listPoints)
{

	Node * newNode = new Node();
	this->allNodes.push_back(newNode);
	if (listPoints.size() <= 1) {
		newNode->setLeafTrue();
		cout << *newNode << endl;
		return newNode;
	}

	int listPointsSize = listPoints.size();
	int randNumberOfPoints = 1 + (rand() % (int)(listPointsSize));
	vector<int> pointsSelected;
	do {
		int randNum = (rand() % (int)(listPointsSize));
		if (!(find(pointsSelected.begin(), pointsSelected.end(), randNum) != pointsSelected.end())) {
			pointsSelected.push_back(randNum);
		}

	} while (pointsSelected.size() < randNumberOfPoints);

	cout << "Select Q space " << endl;
	cout << "max number of point : " << listPointsSize << endl;
	cout << "number of random point :" << randNumberOfPoints << endl;

	for (int i = 0; i < randNumberOfPoints; i++) {
		cout << "selected point for Q " << i << " :" << pointsSelected.at(i) << endl;
	}
	Point randPivot = listPoints.at(pointsSelected.at(0));
	newNode->setPivot(randPivot);
	cout << "selected pivot (point at 0) (v) : " << randPivot;
	map<Point*, float> m;
	vector<float> allDistances;
	for (int i = 0; i < randNumberOfPoints; i++) {
		
		float dist = this->euclidianSpace->EuclidianDistance(randPivot, listPoints.at(pointsSelected.at(i)));
		m[&listPoints.at(pointsSelected.at(i))] = dist;
		allDistances.push_back(dist);

		cout << "Dist point for Q " << i << " to pivot " << dist << endl;
	}

	float median = this->median(allDistances);
	cout << "median : " << median << endl;

	vector<Point> leftTree;
	vector<Point> rightTree;


	map<Point*, float> m2;

	for (int i = 0; i < listPointsSize; i++) {

		float dist = this->euclidianSpace->EuclidianDistance(randPivot, listPoints.at(i));
		m2[&listPoints.at(i)] = dist;
		cout << "Dist point for S " << i << " to pivot " << dist << endl;
	}

	map<Point*, float>::iterator it;
	for (it = m2.begin(); it != m2.end(); it++)
	{	
		if (it->second<median) {
			cout << "to left " << *it->first<<endl;
			leftTree.push_back(*it->first);
		}
		else {
			cout << "to right " << *it->first << endl;
			rightTree.push_back(*it->first);
		}	
	}

	float d1 = numeric_limits<float>::max();
	float d3 = numeric_limits<float>::max();
	float d2 = numeric_limits<float>::min();
	float d4 = numeric_limits<float>::min();

	for (int i = 0; i < leftTree.size(); i++) {
		float distPivotPoint = this->euclidianSpace->EuclidianDistance(randPivot, leftTree.at(i));
		if (distPivotPoint <= d1) {
			d1 = distPivotPoint;
		}

		if (distPivotPoint >= d2) {
			d2 = distPivotPoint;
		}
	}

	for (int i = 0; i < rightTree.size(); i++) {
		float distPivotPoint = this->euclidianSpace->EuclidianDistance(randPivot, rightTree.at(i));
		if (distPivotPoint <= d3) {
			d3 = distPivotPoint;
		}

		if (distPivotPoint >= d4) {
			d4 = distPivotPoint;
		}
	}

	newNode->setD(1, d1);
	newNode->setD(2, d2);
	newNode->setD(3, d3);
	newNode->setD(4, d4);

	cout << *newNode << endl;

	if (this->nodeCount == 0) {
		this->root = newNode;
	}


	

	Node* leftn = this->buildMetricTree(leftTree);
	newNode->left = leftn;

	Node* rightn = rightn = this->buildMetricTree(rightTree);
	newNode->right = rightn;

	this->nodeCount++;
	return newNode;
}

bool MetricTree::search_MetricTree(Node *T, Point *q)
{
	float tau = std::numeric_limits<float>::max();


	Point pivot = T->getPivot();
	float I = this->euclidianSpace->EuclidianDistance(pivot, *q);
	cout << "I : " << I << endl;

	if (I < tau) {
		tau = I;
	}


	float Ilmin = T->getD(1) - tau;
	float Ilmax = T->getD(2) + tau;
	float Irmin = T->getD(3) - tau;
	float Irmax = T->getD(4) + tau;

	cout << "Current Node explored : " << *T << endl;
	cout << "Ilmin : " << Ilmin << endl;
	cout << "Ilmax : " << Ilmax << endl;
	cout << "Irmin : " << Irmin << endl;
	cout << "Irmax : " << Irmax << endl <<endl;

	if ((I >= Ilmin) & (I <= Ilmax)) {
		cout << "We search left node " << endl;
		this->search_MetricTree(T->left, q);
	}

	if ((I >= Irmin) & (I <= Irmax)) {
		cout << "We search right node " << endl;
		this->search_MetricTree(T->right, q);
	}

	return false;
}

float MetricTree::median(vector<float> scores)
{
	double median;
	size_t size = scores.size();

	sort(scores.begin(), scores.end());

	if (size % 2 == 0)
	{
		median = (scores[size / 2 - 1] + scores[size / 2]) / 2;
	}
	else
	{
		median = scores[size / 2];
	}

	return median;
}

MetricTree::~MetricTree()
{
}

ostream & operator<<(ostream & os, const MetricTree & mt)
{
	os << "Begin METRIC TREE --------------------- " << endl;
	os << "Racine : " << *mt.root << endl;

	int nodeCount = 0;
	int leafCount = 0;
	for (int i = 0; i < mt.allNodes.size(); i++) {

		if (mt.allNodes.at(i)->isALeaf()) {
			leafCount++;
		}
		else {
			nodeCount++;
		}

		os << "Node or leaf count number : " << i <<endl;
		os << *mt.allNodes.at(i)<<endl;
		
		if (!mt.allNodes.at(i)->isALeaf()) {
			os << "LEFT NODE : " << *(*mt.allNodes.at(i)).left << endl;
			os << "RIGHT NODE : " << *(*mt.allNodes.at(i)).right << endl;
		}
	}
	os << "nombre de node " << nodeCount << endl;
	os << "nombre de feuille " << leafCount << endl;
	os << "End METRIC TREE --------------------- " << endl;
	return os;
}
