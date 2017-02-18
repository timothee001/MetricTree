#pragma once
#include <vector>
using namespace std;

class Point
{
	float * point;
	int dimension;
public:
	
	Point(int dimension, float maxValue);
	Point(int dimension, float maxValue, float mean, float stdDev);
	Point(int dimension, float* values);
	Point();
	float * getPoint();
	float getAt(int dim);
	void setAt(int dim, float value);
	int getDimension();
	friend ostream& operator<<(ostream& os, const Point& p);
	bool operator==(Point& point)const;
	virtual ~Point();
};

