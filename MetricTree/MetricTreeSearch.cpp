// MetricTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Point.h"
#include "string.h"
#include "EuclidianSpace.h"
#include <iostream>
#include <ostream>
#include <random>
#include <time.h>
#include <stdio.h>   
#include "MetricTree.h"

using namespace std;

//
//#include <opencv2\opencv.hpp>
//using namespace cv;
//
//#ifdef _DEBUG           
//#pragma comment(lib, "opencv_core249d.lib")   
//#pragma comment(lib, "opencv_imgproc249d.lib")   //MAT processing   
//#pragma comment(lib, "opencv_highgui249d.lib")   
//#else   
//#pragma comment(lib, "opencv_core249.lib")   
//#pragma comment(lib, "opencv_imgproc249.lib")      
//#pragma comment(lib, "opencv_highgui249.lib")   
//#endif   





int main()
{
	srand(time(NULL));
	EuclidianSpace e(40, 10, 10, 10, 100, 500);
	cout <<"Euclidian space"<<endl<< e<<endl;
	MetricTree mt(&e);
	mt.buildMetricTreeBasic(e.getAllPoints(),mt.root);
	//cout << mt <<endl;
	int searchPointId = 2;



	mt.searchMetricTreeDefeatist(&mt.getRoot(), &e.getPointAt(searchPointId));
	//mt.searchMetricTreePrunning(&mt.getRoot(), &e.getPointAt(searchPointId));
	//cout << "NN found : " << mt.nearestNeighbour << endl;
	//cout << mt << endl;

	//cout << "Root" << mt.getRoot();


	cout << "we searched :" << e.getPointAt(searchPointId) << endl;
	cout << "Number of node explored : " << mt.numberOfNodeExplored << endl;

	system("pause");
    return 0;
}


 


//
//int main()
//{
//
//	//read 2 images for histogram comparing   
//	///////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//	Mat imgA, imgB;
//	imgA = imread(".\\image1.jpg");
//	imgB = imread(".\\image2.jpg");
//
//
//	imshow("img1", imgA);
//	imshow("img2", imgB);
//
//
//	//variables preparing   
//	///////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//	int hbins = 30, sbins = 32;
//	int channels[] = { 0,  1 };
//	int histSize[] = { hbins, sbins };
//	float hranges[] = { 0, 180 };
//	float sranges[] = { 0, 255 };
//	const float* ranges[] = { hranges, sranges };
//
//	Mat patch_HSV;
//	MatND HistA, HistB;
//
//	//cal histogram & normalization   
//	///////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//	cvtColor(imgA, patch_HSV, CV_BGR2HSV);
//	calcHist(&patch_HSV, 1, channels, Mat(), // do not use mask   
//		HistA, 2, histSize, ranges,
//		true, // the histogram is uniform   
//		false);
//	normalize(HistA, HistA, 0, 1, CV_MINMAX);
//
//
//	cvtColor(imgB, patch_HSV, CV_BGR2HSV);
//	calcHist(&patch_HSV, 1, channels, Mat(),// do not use mask   
//		HistB, 2, histSize, ranges,
//		true, // the histogram is uniform   
//		false);
//	normalize(HistB, HistB, 0, 1, CV_MINMAX);
//
//	//compare histogram   
//	///////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//	int numrows = hbins * sbins;
//
//	//make signature
//	Mat sig1(numrows, 3, CV_32FC1);
//	Mat sig2(numrows, 3, CV_32FC1);
//
//	//fill value into signature
//	for (int h = 0; h< hbins; h++)
//	{
//		for (int s = 0; s< sbins; ++s)
//		{
//			float binval = HistA.at< float>(h, s);
//			sig1.at< float>(h*sbins + s, 0) = binval;
//			sig1.at< float>(h*sbins + s, 1) = h;
//			sig1.at< float>(h*sbins + s, 2) = s;
//
//			binval = HistB.at< float>(h, s);
//			sig2.at< float>(h*sbins + s, 0) = binval;
//			sig2.at< float>(h*sbins + s, 1) = h;
//			sig2.at< float>(h*sbins + s, 2) = s;
//		}
//	}
//
//	//compare similarity of 2images using emd.
//	float emd = cv::EMD(sig1, sig2, CV_DIST_L2); //emd 0 is best matching. 
//	printf("similarity %5.5f %%\n", (1 - emd) * 100);
//
//	waitKey(0);
//
//	return 0;
//}
