#pragma once
#include "Point.h"
#include "HyperSpace.h"
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>


#include <SBL/CSB/Least_RMSD_cartesian.hpp>
#include <CGAL/Cartesian_d.h>
#include <CGAL/Cartesian.h>
//Works with primitive types

typedef CGAL::Cartesian_d<double>                      K;
typedef K::Point_d                                     Conformation;
typedef SBL::CSB::T_Least_RMSD_cartesian<Conformation> LRMSD;

using namespace std;
class HyperSpace
{
	vector<Point> points;
	int pointsCount;
	int dimensionSize;
	
public:
	int bound;
	HyperSpace();
	HyperSpace(int pointsCount, int pointsDimension,int dimensionSize, int bound);
	HyperSpace(int pointsCount, int pointsDimension, int dimensionSize, int bound, float mean, float stdDev);
	Point getPointAt(int pos);
	vector<Point> getAllPoints();
	static float EuclidianDistance(Point &a, Point &b);
	static float LRMSDDistance(Point &a, Point &b);
	int getPointsCount();
	friend ostream& operator<<(ostream& os, const HyperSpace& p);
	virtual ~HyperSpace();
};

