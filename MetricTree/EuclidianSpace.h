#pragma once
#include <vector>
#include "Point.h"
#include <iostream>
using namespace std;
class EuclidianSpace
{
	vector<Point> points;
	int pointsCount;
	int dimensionSize;
	
public:
	int bound;
	EuclidianSpace(int pointsCount, int pointsDimension,int dimensionSize, int bound);
	EuclidianSpace(int pointsCount, int pointsDimension, int dimensionSize, int bound, float mean, float stdDev);
	Point getPointAt(int pos);
	vector<Point> getAllPoints();
	static float EuclidianDistance(Point &a, Point &b);
	friend ostream& operator<<(ostream& os, const EuclidianSpace& p);
	virtual ~EuclidianSpace();
};

