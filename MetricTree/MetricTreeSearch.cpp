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
#include <sstream>

using namespace std;


int main()
{
	srand(time(NULL));

	vector<int> allParams;
	while (allParams.size()== 0) {
	cout << "Type the dimension of the hyperspace : Number of points - Points Dimension - Dimension of the space - Max absolute value - Optional Mean - Optional Standard Deviation" << endl;
	

	while (allParams.size() == 0) {
	char params[256];
	cin.getline(params, 256);
	std::string s = string(params);
	std::istringstream is(s);
	int n;
	while (is >> n) {
		allParams.push_back(n);
	}
	if (!(allParams.size() == 4 || allParams.size() == 6)) {
		allParams.clear();
	}
	}


	HyperSpace e;
	if (allParams.size() == 4) {
		e = HyperSpace(allParams.at(0), allParams.at(1), allParams.at(2), allParams.at(3));
		cout <<"Hyper space"<<endl<< e<<endl;
	}else if (allParams.size() == 6) {
		e = HyperSpace(allParams.at(0), allParams.at(1), allParams.at(2), allParams.at(3), allParams.at(4), allParams.at(5));
		cout << "Hyper space" << endl << e << endl;
	}


	if (allParams.size() != 0) {

		int choice=0;
		while (choice == 0) {
		cout << "What metric tree do you want to build ?" << endl;
		cout << "1: Basic" << endl;
		cout << "2: Basic on conformations" << endl;
		cout << "3: Optimized" << endl;
		cout << "4: Optimized on conformations" << endl;
		cin >> choice;
		if (!(choice >= 1 && choice <= 4)) {
			choice = 0;
		}
		}

		MetricTree mt;
		if (choice == 1) {
			mt = MetricTree(&e);
			mt.buildMetricTreeBasic(e.getAllPoints(), mt.root);
		}else if (choice == 2) {
			mt = MetricTree(&e);
			mt.buildMetricTreeBasicOnConformations(e.getAllPoints(), mt.root);
		}
		else if (choice == 3) {
			mt = MetricTree(&e);
			mt.buildMetricTreeOptimized(e.getAllPoints(), mt.root);
		}
		else if(choice == 4) {
			mt = MetricTree(&e);
			mt.buildMetricTreeBasicOnConformations(e.getAllPoints(), mt.root);
		}

		cout << "Type 1 if you want to print the metric tree " << endl;
		int seeTree = 0;
		cin >> seeTree;
		if (seeTree == 1) {
			cout << mt << endl;;
		}

		int searchAgain = true;
		
		while (searchAgain) {
		cout << "Lets search point, the number of point in the hyperspace is : " << e.getPointsCount()<<endl;
		cout << "Type a number between 0 and " << (e.getPointsCount() - 1) << " included to search the point at this position " << endl;
		cout << "Otherwise type 99999 if you want to search a point that doesn't exist to test it !" << endl;
		int Pointchoice = -1;
		while (Pointchoice == -1) {
			cin >> Pointchoice;
			if (!((Pointchoice >= 0 && Pointchoice < e.getPointsCount()) || (Pointchoice == 99999))) {
				Pointchoice = -1;
			}
		}

		int typeOfSearch = 0;
		while (typeOfSearch < 1 || typeOfSearch>2)
		{
			cout << "What type of search do you want to do ?" << endl;
			cout << "1: Prunning condition" << endl;
			cout << "2: Defeastist" << endl;
			cin >> typeOfSearch;
		}

		Point *pointToSearch;
		if (Pointchoice != 99999) {
			pointToSearch = &e.getPointAt(Pointchoice);
		}
		else {
			pointToSearch = new Point(allParams.at(1), (float)allParams.at(3));
		}

		if (typeOfSearch == 1 && (choice == 1 || choice ==3)) {
			mt.searchMetricTreePrunning(&mt.getRoot(), pointToSearch);
			cout << "we searched :" << *pointToSearch << endl;
			cout << "Number of node explored : " << mt.numberOfNodeExplored << endl;
		}else if (typeOfSearch == 1 && (choice == 2 || choice == 4)) {
			mt.searchMetricTreePrunningConformation(&mt.getRoot(), pointToSearch);
			cout << "we searched :" << *pointToSearch << endl;
			cout << "Number of node explored : " << mt.numberOfNodeExplored << endl;
		}
		else if (typeOfSearch == 2 && (choice == 1 || choice == 3)) {
			mt.searchMetricTreeDefeatist(&mt.getRoot(), pointToSearch);
			cout << "we searched :" << *pointToSearch << endl;
			cout << "Number of node explored : " << mt.numberOfNodeExplored << endl;
		}
		else if (typeOfSearch == 2 && (choice == 2 || choice == 4)) {
			mt.searchMetricTreeDefeatistConformation(&mt.getRoot(), pointToSearch);
			cout << "we searched :" << *pointToSearch << endl;
			cout << "Number of node explored : " << mt.numberOfNodeExplored << endl;
		}
		mt.reinitializeSearchParams();

		int newSearch = 0;
		cout << "Do you want to stop making research  ? Type 1 if yes otherwise type an other number" << endl;
		cin >> newSearch;
		if (newSearch == 1) {
			searchAgain = false;
		}
		}



	}

	int startFrom0 = 0;
	cout << " Do you wan to repeat the experiment from scratch ? (type 1 is yes)" << endl;
	cin >> startFrom0;
	if (startFrom0 == 1) {
		allParams.clear();
	}

	}

//	HyperSpace e(50, 30, 30, 1000);
//	cout <<"Hyper space"<<endl<< e<<endl;
//	/*MetricTree mt(&e);
//	mt.buildMetricTreeBasicOnConformations(e.getAllPoints(), mt.root);*/
//	int searchPointId = 2;
//	/*mt.searchMetricTreePrunningConformation(&mt.getRoot(), &e.getPointAt(searchPointId));
//	cout << "we searched :" << e.getPointAt(searchPointId) << endl;
//	cout << "Number of node explored  (without optimizaion): " << mt.numberOfNodeExplored << endl;
//*/
//	MetricTree mt2(&e);
//	mt2.buildMetricTreeBasic(e.getAllPoints(), mt2.root);
//	mt2.searchMetricTreePrunning(&mt2.getRoot(), &e.getPointAt(searchPointId));
//	cout << "we searched :" << e.getPointAt(searchPointId) << endl;
//	cout << "Number of node explored (without optimizaion): " << mt2.numberOfNodeExplored << endl;
//
//	MetricTree mt3(&e);
//	mt3.buildMetricTreeOptimized(e.getAllPoints(), mt3.root);
//	mt3.searchMetricTreePrunning(&mt3.getRoot(), &e.getPointAt(searchPointId));
//	cout << "we searched :" << e.getPointAt(searchPointId) << endl;
//	cout << "Number of node explored (with optimizaion): " << mt3.numberOfNodeExplored << endl;
//
//
//
//	//mt.buildMetricTreeBasic(e.getAllPoints(),mt.root);
//	//cout << mt <<endl;
//	//
//
//	//mt.searchMetricTreeDefeatist(&mt.getRoot(), &e.getPointAt(searchPointId));
//
//	//cout << "NN found : " << mt.nearestNeighbour << endl;
//	//cout << mt << endl;
//
//	//cout << "Root" << mt.getRoot();

	system("pause");

    return 0;
}


 
