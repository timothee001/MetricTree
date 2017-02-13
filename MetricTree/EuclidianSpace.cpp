#include "stdafx.h"
#include "EuclidianSpace.h"
#include <limits>

EuclidianSpace::EuclidianSpace(int pointsCount, int pointsDimension ,int dimensionSize,int bound)
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

EuclidianSpace::EuclidianSpace(int pointsCount, int pointsDimension,int dimensionSize, int bound, float mean, float stdDev)
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

Point EuclidianSpace::getPointAt(int pos)
{
	return points.at(pos);
}

vector<Point> EuclidianSpace::getAllPoints()
{
	return this->points;
}

float EuclidianSpace::EuclidianDistance(Point & a, Point & b)
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


EuclidianSpace::~EuclidianSpace()
{
	
}

ostream& operator<<(ostream& os, const EuclidianSpace& e)
{
	int size = e.pointsCount;
	for (int i = 0; i < size; i++) {
		os << i << ": " << e.points.at(i) << endl;
	}
	os << endl;
	return os;
}
