// MetricTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Point.h"
#include "string.h"
#include "HyperSpace.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <random>
#include <time.h>
#include <stdio.h>   
#include "MetricTree.h"

using namespace std;

int main()
{
	srand(time(NULL));
	HyperSpace e(50, 30, 30, 1000);
	cout <<"Hyper space"<<endl<< e<<endl;
	/*MetricTree mt(&e);
	mt.buildMetricTreeBasicOnConformations(e.getAllPoints(), mt.root);*/
	int searchPointId = 2;
	/*mt.searchMetricTreePrunningConformation(&mt.getRoot(), &e.getPointAt(searchPointId));
	cout << "we searched :" << e.getPointAt(searchPointId) << endl;
	cout << "Number of node explored  (without optimizaion): " << mt.numberOfNodeExplored << endl;
*/
	MetricTree mt2(&e);
	mt2.buildMetricTreeBasic(e.getAllPoints(), mt2.root);
	mt2.searchMetricTreeDefeatist(&mt2.getRoot(), &e.getPointAt(searchPointId));
	cout << "we searched :" << e.getPointAt(searchPointId) << endl;
	cout << "Number of node explored (without optimizaion): " << mt2.numberOfNodeExplored << endl;

	MetricTree mt3(&e);
	mt3.buildMetricTreeOptimized(e.getAllPoints(), mt3.root);
	mt3.searchMetricTreeDefeatist(&mt3.getRoot(), &e.getPointAt(searchPointId));
	cout << "we searched :" << e.getPointAt(searchPointId) << endl;
	cout << "Number of node explored (with optimizaion): " << mt3.numberOfNodeExplored << endl;



	//mt.buildMetricTreeBasic(e.getAllPoints(),mt.root);
	//cout << mt <<endl;
	//

	//mt.searchMetricTreeDefeatist(&mt.getRoot(), &e.getPointAt(searchPointId));

	//cout << "NN found : " << mt.nearestNeighbour << endl;
	//cout << mt << endl;

	//cout << "Root" << mt.getRoot();

	system("pause");

    return 0;
}


 
