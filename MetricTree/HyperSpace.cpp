#include "stdafx.h"
#include "HyperSpace.h"

HyperSpace::HyperSpace(int pointsCount, int pointsDimension ,int dimensionSize,int bound)
{
	this->pointsCount = pointsCount;
	this->dimensionSize = dimensionSize;
	this->bound = bound;
	
	for (int i = 0; i < pointsCount; i++) {
		Point p =  Point(dimensionSize, bound);
		if (pointsDimension < dimensionSize) {
			for (int j = pointsDimension; j < dimensionSize; j++) {
				p.setAt(j, 0.0f);
			}
		}
		this->points.push_back(p);
	}
}

HyperSpace::HyperSpace(int pointsCount, int pointsDimension,int dimensionSize, int bound, float mean, float stdDev)
{
	this->pointsCount = pointsCount;
	this->dimensionSize = dimensionSize;
	this->bound = bound;

	for (int i = 0; i < pointsCount; i++) {
		Point p = Point(dimensionSize, bound, mean, stdDev);
		if (pointsDimension < dimensionSize) {
			for (int j = pointsDimension; j < dimensionSize; j++) {
				p.setAt(j, 0.0f);
			}
		}
		this->points.push_back(p);
	}
}

Point HyperSpace::getPointAt(int pos)
{
	return points.at(pos);
}

vector<Point> HyperSpace::getAllPoints()
{
	return this->points;
}

float HyperSpace::EuclidianDistance(Point & a, Point & b)
{
	
	int dimension = a.getDimension() == b.getDimension() ? a.getDimension() : 0;
	if (dimension == 0)
		return 0.0f;

	//float minDistUntilNow = numeric_limits<float>::max();


	float dist = 0.0f;
	for (int k = 0; k < dimension; k++) {
		dist += (float)pow((float)a.getAt(k) - (float)b.getAt(k), 2.0f);
	}
	//dist = (float)dist / (float)dimension;
	dist = (float)sqrt(dist);


	return dist;
	
}

float HyperSpace::LRMSDDistance(Point & a, Point & b)
{
	vector<float> coords_p;
	vector<float> coords_q;

	for (int i = 0; i < a.getDimension(); i++) {
		coords_p.push_back(a.getAt(i));
	}
	for (int i = 0; i < b.getDimension(); i++) {
		coords_q.push_back(b.getAt(i));
	}

	Conformation p(coords_p.size(), coords_p.begin(), coords_p.end());
	Conformation q(coords_q.size(), coords_q.begin(), coords_q.end());

	//cout << q;

	LRMSD distance;
	return distance(p, q);
}


HyperSpace::~HyperSpace()
{
	
}

ostream& operator<<(ostream& os, const HyperSpace& e)
{
	int size = e.pointsCount;
	for (int i = 0; i < size; i++) {
		os << i << ": " << e.points.at(i) << endl;
	}
	os << endl;
	return os;
}
