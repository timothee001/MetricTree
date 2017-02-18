#include "stdafx.h"
#include "Point.h"
#include <time.h>
#include <iostream>
#include <ostream>
#include <random>
using namespace std;


Point::Point(int dimension,float maxValue)
{
	this->dimension = dimension;
	this->point = new float[dimension];
	for (int i = 0; i < dimension; i++) {
		float randN= static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / maxValue));
		int randomval = rand() % 2;
		if (randomval == 1) {
			randN = -randN;
		}
		this->point[i] = randN;
	}
}

Point::Point(int dimension, float maxValue, float mean, float stdDev)
{
	this->dimension = dimension;
	this->point = new float[dimension];
	default_random_engine generator(rand());
	normal_distribution<float> distribution(mean, stdDev);
	for (int i = 0; i < dimension; i++) {
		
		float randN = distribution(generator);

		while (randN<-maxValue || randN>maxValue) {
			randN = distribution(generator);
		}

		this->point[i] = randN;
	}
}

Point::Point(int dimension, float * values)
{
	this->dimension = dimension;
	this->point = values;
}


Point::Point()
{
}

float * Point::getPoint()
{
	return this->point;
}

float Point::getAt(int dim)
{
	return this->point[dim];
}

void Point::setAt(int dim, float value)
{
	this->point[dim] = value;
}

int Point::getDimension()
{
	return this->dimension;
}

ostream& operator<<(ostream& os, const Point& p)
{
	for (int i = 0; i < p.dimension; i++) {
		os << p.point[i] << ", ";
	}
	os << endl;
	return os;
}


bool Point::operator==(Point & point) const
{
	bool equal = true;

	if (this->dimension != point.dimension) {
		return false;
	}

	for (int i = 0; i < this->dimension; i++) {

		if (this->point[i] != point.getAt(i)) {
			return false;
		}

	}

	

	return equal;
}

Point::~Point()
{

}
