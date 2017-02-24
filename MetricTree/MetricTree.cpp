#include "stdafx.h"
#include "MetricTree.h"


int MetricTree::getNodeCount()
{
	return this->nodeCount;
}

Node MetricTree::getRoot()
{
	return *this->root;;
}

MetricTree::MetricTree(HyperSpace* euclidianSpace)
{
	this->root = new Node();
	this->hyperSpace = euclidianSpace;
}




void MetricTree::buildMetricTreeBasic(vector<Point> listPoints, Node * currentNode)
{
	this->allNodes.push_back(currentNode);
	if (listPoints.size() <= 1) {
		currentNode->setLeafTrue();
		if (listPoints.size() == 1) {
			currentNode->setPivot(listPoints.at(0));
		}
	}
	else {

		int listPointsSize = listPoints.size();
		int randNumberOfPoints = 1 + (rand() % (int)(listPointsSize));
		vector<int> pointsSelected;
		do {
			int randNum = (rand() % (int)(listPointsSize));
			if (!(find(pointsSelected.begin(), pointsSelected.end(), randNum) != pointsSelected.end())) {
				pointsSelected.push_back(randNum);
			}
		} while (pointsSelected.size() < randNumberOfPoints);
		Point randPivot = listPoints.at(pointsSelected.at(0));
		currentNode->setPivot(randPivot);
		map<Point*, float> m;
		vector<float> allDistances;
		for (int i = 0; i < randNumberOfPoints; i++) {
			float dist = this->hyperSpace->EuclidianDistance(randPivot, listPoints.at(pointsSelected.at(i)));
			m[&listPoints.at(pointsSelected.at(i))] = dist;
			allDistances.push_back(dist);
		}
		float median = this->median(allDistances);
		vector<Point> leftTree;
		vector<Point> rightTree;
		map<Point*, float> m2;
		for (int i = 0; i < listPointsSize; i++) {
			float dist = this->hyperSpace->EuclidianDistance(randPivot, listPoints.at(i));
			m2[&listPoints.at(i)] = dist;
		}
		map<Point*, float>::iterator it;
		for (it = m2.begin(); it != m2.end(); it++)
		{
			if (it->second<median) {
				leftTree.push_back(*it->first);
			}
			else {
				rightTree.push_back(*it->first);
			}
		}
		float d1 = numeric_limits<float>::max();
		float d3 = numeric_limits<float>::max();
		float d2 = numeric_limits<float>::min();
		float d4 = numeric_limits<float>::min();
		for (int i = 0; i < leftTree.size(); i++) {
			float distPivotPoint = this->hyperSpace->EuclidianDistance(randPivot, leftTree.at(i));
			if (distPivotPoint <= d1) {
				d1 = distPivotPoint;
			}
			if (distPivotPoint >= d2) {
				d2 = distPivotPoint;
			}
		}

		for (int i = 0; i < rightTree.size(); i++) {
			float distPivotPoint = this->hyperSpace->EuclidianDistance(randPivot, rightTree.at(i));
			if (distPivotPoint <= d3) {
				d3 = distPivotPoint;
			}
			if (distPivotPoint >= d4) {
				d4 = distPivotPoint;
			}
		}
		currentNode->setD(1, d1);
		currentNode->setD(2, d2);
		currentNode->setD(3, d3);
		currentNode->setD(4, d4);

		currentNode->left = new Node();
		buildMetricTreeBasic(leftTree, currentNode->left);
		currentNode->right = new Node();
		buildMetricTreeBasic(rightTree, currentNode->right);
		
	}



}

void MetricTree::buildMetricTreeBasicOnConformations(vector<Point> listPoints, Node * currentNode)
{

	this->allNodes.push_back(currentNode);
	if (listPoints.size() <= 1) {
		//If we are at a leaf we set it as true and if the size is one we choose the point as the pivot
		currentNode->setLeafTrue();
		if (listPoints.size() == 1) {
			currentNode->setPivot(listPoints.at(0));
		}
	}
	else {

		int listPointsSize = listPoints.size();
		// we choose a random number of point among the existing one
		int randNumberOfPoints = 1 + (rand() % (int)(listPointsSize));

		//This part select randNumberOfPoints point that are different and put them in a vector
		vector<int> pointsSelected;
		do {
			int randNum = (rand() % (int)(listPointsSize));
			if (!(find(pointsSelected.begin(), pointsSelected.end(), randNum) != pointsSelected.end())) {
				pointsSelected.push_back(randNum);
			}
		} while (pointsSelected.size() < randNumberOfPoints);


		//We choose arbitrary the first point of the list as pivot (it will be optimize with the pivot selection)
		Point randPivot = listPoints.at(pointsSelected.at(0));
		currentNode->setPivot(randPivot);

		//we compute all the distances between the rand previous pivot and the randNumberOfPoints points selected previously
		map<Point*, float> m;
		vector<float> allDistances;
		for (int i = 0; i < randNumberOfPoints; i++) {
			float dist = this->hyperSpace->LRMSDDistance(randPivot, listPoints.at(pointsSelected.at(i)));
			m[&listPoints.at(pointsSelected.at(i))] = dist;
			allDistances.push_back(dist);
		}

		//We take the median of all our values
		float median = this->median(allDistances);

		vector<Point> leftTree;
		vector<Point> rightTree;

		//we get of the distance overall between the pivot and the current remaining list of point to split it into two
		map<Point*, float> m2;
		for (int i = 0; i < listPointsSize; i++) {
			float dist = this->hyperSpace->LRMSDDistance(randPivot, listPoints.at(i));
			m2[&listPoints.at(i)] = dist;
		}
		map<Point*, float>::iterator it;
		for (it = m2.begin(); it != m2.end(); it++)
		{
			//If it is inferior to the median it goes on left subtree
			if (it->second<median) {
				leftTree.push_back(*it->first);
			}
			//If it is superior to the median it goes on right subtree
			else {
				rightTree.push_back(*it->first);
			}
		}
		float d1 = numeric_limits<float>::max();
		float d3 = numeric_limits<float>::max();
		float d2 = numeric_limits<float>::min();
		float d4 = numeric_limits<float>::min();
		// We compute all the d distances as shown in the algorithm
		for (int i = 0; i < leftTree.size(); i++) {
			float distPivotPoint = this->hyperSpace->LRMSDDistance(randPivot, leftTree.at(i));
			if (distPivotPoint <= d1) {
				d1 = distPivotPoint;
			}
			if (distPivotPoint >= d2) {
				d2 = distPivotPoint;
			}
		}

		for (int i = 0; i < rightTree.size(); i++) {
			float distPivotPoint = this->hyperSpace->LRMSDDistance(randPivot, rightTree.at(i));
			if (distPivotPoint <= d3) {
				d3 = distPivotPoint;
			}
			if (distPivotPoint >= d4) {
				d4 = distPivotPoint;
			}
		}
		currentNode->setD(1, d1);
		currentNode->setD(2, d2);
		currentNode->setD(3, d3);
		currentNode->setD(4, d4);

		//We recurse on subtree we have created
		currentNode->left = new Node();
		buildMetricTreeBasicOnConformations(leftTree, currentNode->left);
		currentNode->right = new Node();
		buildMetricTreeBasicOnConformations(rightTree, currentNode->right);

	}


}

void MetricTree::buildMetricTreeOptimized(vector<Point> listPoints, Node * currentNode)
{
	this->allNodes.push_back(currentNode);
	if (listPoints.size() <= 1) {
		currentNode->setLeafTrue();
		if (listPoints.size() == 1) {
			currentNode->setPivot(listPoints.at(0));
		}
	}
	else {

		int listPointsSize = listPoints.size();
		int randNumberOfPoints = 1 + (rand() % (int)(listPointsSize));
		vector<int> pointsSelected;
		do {
			int randNum = (rand() % (int)(listPointsSize));
			if (!(find(pointsSelected.begin(), pointsSelected.end(), randNum) != pointsSelected.end())) {
				pointsSelected.push_back(randNum);
			}
		} while (pointsSelected.size() < randNumberOfPoints);

		vector<Point> pointsSelectedValues;
		for (int i = 0; i < pointsSelected.size(); i++) {
			pointsSelectedValues.push_back(listPoints.at(pointsSelected.at(i)));
		}

		Point optimizedPivot = this->getBestPivot(pointsSelectedValues);


		currentNode->setPivot(optimizedPivot);
		map<Point*, float> m;
		vector<float> allDistances;
		for (int i = 0; i < randNumberOfPoints; i++) {
			float dist = this->hyperSpace->EuclidianDistance(optimizedPivot, listPoints.at(pointsSelected.at(i)));
			m[&listPoints.at(pointsSelected.at(i))] = dist;
			allDistances.push_back(dist);
		}
		float median = this->median(allDistances);
		vector<Point> leftTree;
		vector<Point> rightTree;
		map<Point*, float> m2;
		for (int i = 0; i < listPointsSize; i++) {
			float dist = this->hyperSpace->EuclidianDistance(optimizedPivot, listPoints.at(i));
			m2[&listPoints.at(i)] = dist;
		}
		map<Point*, float>::iterator it;
		for (it = m2.begin(); it != m2.end(); it++)
		{
			if (it->second<median) {
				leftTree.push_back(*it->first);
			}
			else {
				rightTree.push_back(*it->first);
			}
		}
		float d1 = numeric_limits<float>::max();
		float d3 = numeric_limits<float>::max();
		float d2 = numeric_limits<float>::min();
		float d4 = numeric_limits<float>::min();
		for (int i = 0; i < leftTree.size(); i++) {
			float distPivotPoint = this->hyperSpace->EuclidianDistance(optimizedPivot, leftTree.at(i));
			if (distPivotPoint <= d1) {
				d1 = distPivotPoint;
			}
			if (distPivotPoint >= d2) {
				d2 = distPivotPoint;
			}
		}

		for (int i = 0; i < rightTree.size(); i++) {
			float distPivotPoint = this->hyperSpace->EuclidianDistance(optimizedPivot, rightTree.at(i));
			if (distPivotPoint <= d3) {
				d3 = distPivotPoint;
			}
			if (distPivotPoint >= d4) {
				d4 = distPivotPoint;
			}
		}
		currentNode->setD(1, d1);
		currentNode->setD(2, d2);
		currentNode->setD(3, d3);
		currentNode->setD(4, d4);

		currentNode->left = new Node();
		buildMetricTreeOptimized(leftTree, currentNode->left);
		currentNode->right = new Node();
		buildMetricTreeOptimized(rightTree, currentNode->right);

	}



}

void MetricTree::buildMetricTreeOptimizedOnConformations(vector<Point> listPoints, Node * currentNode)
{
	this->allNodes.push_back(currentNode);
	if (listPoints.size() <= 1) {
		currentNode->setLeafTrue();
		if (listPoints.size() == 1) {
			currentNode->setPivot(listPoints.at(0));
		}
	}
	else {

		int listPointsSize = listPoints.size();
		int randNumberOfPoints = 1 + (rand() % (int)(listPointsSize));
		vector<int> pointsSelected;
		do {
			int randNum = (rand() % (int)(listPointsSize));
			if (!(find(pointsSelected.begin(), pointsSelected.end(), randNum) != pointsSelected.end())) {
				pointsSelected.push_back(randNum);
			}
		} while (pointsSelected.size() < randNumberOfPoints);

		vector<Point> pointsSelectedValues;
		for (int i = 0; i < pointsSelected.size(); i++) {
			pointsSelectedValues.push_back(listPoints.at(pointsSelected.at(i)));
		}

		Point optimizedPivot = this->getBestPivotConformation(pointsSelectedValues);


		currentNode->setPivot(optimizedPivot);
		map<Point*, float> m;
		vector<float> allDistances;
		for (int i = 0; i < randNumberOfPoints; i++) {
			float dist = this->hyperSpace->LRMSDDistance(optimizedPivot, listPoints.at(pointsSelected.at(i)));
			m[&listPoints.at(pointsSelected.at(i))] = dist;
			allDistances.push_back(dist);
		}
		float median = this->median(allDistances);
		vector<Point> leftTree;
		vector<Point> rightTree;
		map<Point*, float> m2;
		for (int i = 0; i < listPointsSize; i++) {
			float dist = this->hyperSpace->LRMSDDistance(optimizedPivot, listPoints.at(i));
			m2[&listPoints.at(i)] = dist;
		}
		map<Point*, float>::iterator it;
		for (it = m2.begin(); it != m2.end(); it++)
		{
			if (it->second<median) {
				leftTree.push_back(*it->first);
			}
			else {
				rightTree.push_back(*it->first);
			}
		}
		float d1 = numeric_limits<float>::max();
		float d3 = numeric_limits<float>::max();
		float d2 = numeric_limits<float>::min();
		float d4 = numeric_limits<float>::min();
		for (int i = 0; i < leftTree.size(); i++) {
			float distPivotPoint = this->hyperSpace->LRMSDDistance(optimizedPivot, leftTree.at(i));
			if (distPivotPoint <= d1) {
				d1 = distPivotPoint;
			}
			if (distPivotPoint >= d2) {
				d2 = distPivotPoint;
			}
		}

		for (int i = 0; i < rightTree.size(); i++) {
			float distPivotPoint = this->hyperSpace->LRMSDDistance(optimizedPivot, rightTree.at(i));
			if (distPivotPoint <= d3) {
				d3 = distPivotPoint;
			}
			if (distPivotPoint >= d4) {
				d4 = distPivotPoint;
			}
		}
		currentNode->setD(1, d1);
		currentNode->setD(2, d2);
		currentNode->setD(3, d3);
		currentNode->setD(4, d4);

		currentNode->left = new Node();
		buildMetricTreeOptimizedOnConformations(leftTree, currentNode->left);
		currentNode->right = new Node();
		buildMetricTreeOptimizedOnConformations(rightTree, currentNode->right);

	}

}

Point MetricTree::getBestPivot2(vector<Point> listPoints) {

	Point bestPivotSoFar = Point();
	float maxDistSoFar = 0.0;
	for (int i = 0; i < listPoints.size(); i++) {
		float currentDist = 0.0;
		for (int j = 0; j < listPoints.size(); j++) {
			currentDist += this->hyperSpace->EuclidianDistance(listPoints.at(i), listPoints.at(j));
		}
		if (currentDist >= maxDistSoFar) {
			maxDistSoFar = currentDist;
			bestPivotSoFar=listPoints.at(i);
		}
	}
	return bestPivotSoFar;
}

Point MetricTree::getBestPivot(vector<Point> listPoints)
{
	if(listPoints.size()==1){
		return listPoints.at(0);
	}else if (listPoints.size() > 0) {
		int dim = listPoints.at(0).getDimension();
		float * values = new float[dim];

		for (int i = 0; i < dim; i++) {
			float sumDim = 0.0;
			for (int j = 0; j < listPoints.size(); j++) {
				sumDim += listPoints.at(j).getAt(i);
			}
			float meanDim = sumDim / listPoints.size();
			values[i] = meanDim;
		}


		Point center = Point(dim, values);
		float maxDistSoFar = 0.0;
		Point bestPivotSoFar = listPoints.at(0);

		for (int j = 0; j < listPoints.size(); j++) {
			float currentDist = this->hyperSpace->EuclidianDistance(center, listPoints.at(j));
			if (currentDist > maxDistSoFar) {
				maxDistSoFar = currentDist;
				bestPivotSoFar = listPoints.at(j);
			}
		}

		return bestPivotSoFar;
	}
	return Point();
}

Point MetricTree::getBestPivotConformation(vector<Point> listPoints)
{
	if (listPoints.size() == 1) {
		return listPoints.at(0);
	}
	else if (listPoints.size() > 0) {
		int dim = listPoints.at(0).getDimension();
		float * values = new float[dim];

		for (int i = 0; i < dim; i++) {
			float sumDim = 0.0;
			for (int j = 0; j < listPoints.size(); j++) {
				sumDim += listPoints.at(j).getAt(i);
			}
			float meanDim = sumDim / listPoints.size();
			values[i] = meanDim;
		}


		Point center = Point(dim, values);
		float maxDistSoFar = 0.0;
		Point bestPivotSoFar = listPoints.at(0);

		for (int j = 0; j < listPoints.size(); j++) {
			float currentDist = this->hyperSpace->LRMSDDistance(center, listPoints.at(j));
			if (currentDist > maxDistSoFar) {
				maxDistSoFar = currentDist;
				bestPivotSoFar = listPoints.at(j);
			}
		}

		return bestPivotSoFar;
	}
	return Point();
}



bool MetricTree::searchMetricTreePrunning(Node *T, Point *q)
{
	
	cout << "Node explored n° : " << this->numberOfNodeExplored << endl;
	cout << "search Metric function called " << endl;
	cout << "Current Node explored : " << *T << endl;

	if (T->getPivot() == *q) {
		cout << "Point has been found at this Node" << endl;
		this->found = true;
		return true;
	}

	float tau = 0.0;
	if (this->numberOfNodeExplored==0.0) {
		tau = std::numeric_limits<float>::max();
	}
	Point pivot = T->getPivot();

	if (T->isALeaf()) {
		return false;
	}
	else {
		/*cout << "On the left " << *(T->left) << endl;
		cout << "On the right " << *(T->right) << endl;*/
	}

	float I = this->hyperSpace->EuclidianDistance(pivot, *q);
	

	if (I < tau) {
		tau = I;
		this->nearestNeighbour = pivot;
	}

	

	float Ilmin = T->getD(1) - tau;
	float Ilmax = T->getD(2) + tau;
	float Irmin = T->getD(3) - tau;
	float Irmax = T->getD(4) + tau;

	cout << "I : " << I << endl;
	cout << "tau : " << tau << endl;
	cout << "Ilmin : " << Ilmin << endl;
	cout << "Ilmax : " << Ilmax << endl;
	cout << "Irmin : " << Irmin << endl;
	cout << "Irmax : " << Irmax << endl <<endl;

	if ((I >= Ilmin) & (I <= Ilmax) & !this->found) {
		//cout << "I : " << I << " Ilmin : " << Ilmin << " Ilmax : " << Ilmax << endl;
		this->numberOfNodeExplored++;
		//cout << "We search left node " << endl;
		if (T->isALeaf()) {
			//cout << "We reach the leaf " << endl;
		//return false;
		}
		this->searchMetricTreePrunning(T->left, q);
	}

	if ((I >= Irmin) & (I <= Irmax) & !this->found) {
		//cout << "I : " << I << " Irmin : " << Irmin << " Irmax : " << Irmax << endl;
		this->numberOfNodeExplored++;
		/*cout << "We search right node " << endl;*/
		if (T->isALeaf()) {
		/*	cout << "We reach the leaf " << endl;*/
			//return false;
		}
		this->searchMetricTreePrunning(T->right, q);
	}

	return true;	
}

bool MetricTree::searchMetricTreePrunningConformation(Node * T, Point * q)
{
	cout << "Node explored n° : " << this->numberOfNodeExplored << endl;
	cout << "search Metric function called " << endl;
	cout << "Current Node explored : " << *T << endl;

	if (T->getPivot() == *q) {
		cout << "Point has been found at this Node" << endl;
		this->found = true;
		return true;
	}

	float tau = 0.0;
	if (this->numberOfNodeExplored == 0.0) {
		tau = std::numeric_limits<float>::max();
	}
	Point pivot = T->getPivot();

	if (T->isALeaf()) {
		return false;
	}
	else {
		/*cout << "On the left " << *(T->left) << endl;
		cout << "On the right " << *(T->right) << endl;*/
	}

	float I = this->hyperSpace->LRMSDDistance(pivot, *q);


	if (I < tau) {
		tau = I;
		this->nearestNeighbour = pivot;
	}



	float Ilmin = T->getD(1) - tau;
	float Ilmax = T->getD(2) + tau;
	float Irmin = T->getD(3) - tau;
	float Irmax = T->getD(4) + tau;

	cout << "I : " << I << endl;
	cout << "tau : " << tau << endl;
	cout << "Ilmin : " << Ilmin << endl;
	cout << "Ilmax : " << Ilmax << endl;
	cout << "Irmin : " << Irmin << endl;
	cout << "Irmax : " << Irmax << endl <<endl;

	if ((I >= Ilmin) & (I <= Ilmax) & !this->found) {
		//cout << "I : " << I << " Ilmin : " << Ilmin << " Ilmax : " << Ilmax << endl;
		this->numberOfNodeExplored++;
		//cout << "We search left node " << endl;
		if (T->isALeaf()) {
			//cout << "We reach the leaf " << endl;
			//return false;
		}
		this->searchMetricTreePrunningConformation(T->left, q);
	}

	if ((I >= Irmin) & (I <= Irmax) & !this->found) {
		//cout << "I : " << I << " Irmin : " << Irmin << " Irmax : " << Irmax << endl;
		this->numberOfNodeExplored++;
		/*cout << "We search right node " << endl;*/
		if (T->isALeaf()) {
			/*	cout << "We reach the leaf " << endl;*/
			//return false;
		}
		this->searchMetricTreePrunningConformation(T->right, q);
	}

	return true;
}

bool MetricTree::searchMetricTreeDefeatist(Node * T, Point * q)
{

	
	cout << "Node explored n° : " << this->numberOfNodeExplored << endl;
	cout << "search Metric function called " << endl;
	cout << "Current Node explored : " << *T << endl;

	if (T->getPivot() == *q) {
		cout << "Point has been found at this Node" << endl;
		this->found = true;
		return true;
	}

	float tau = 0.0;
	if (this->numberOfNodeExplored == 0.0) {
		tau = std::numeric_limits<float>::max();
	}
	Point pivot = T->getPivot();

	if (pivot == *q) {
	/*	cout << "Point founded" << endl;*/

		return true;
	}


	if (T->isALeaf()) {
		return false;
	}
	else {
		/*cout << "On the left " << *(T->left) << endl;
		cout << "On the right " << *(T->right) << endl;*/
	}

	float I = this->hyperSpace->EuclidianDistance(pivot, *q);


	if (I < tau) {
		tau = I;
		this->nearestNeighbour = pivot;
	}



	float Ilmin = T->getD(1) - tau;
	float Ilmax = T->getD(2) + tau;
	float Irmin = T->getD(3) - tau;
	float Irmax = T->getD(4) + tau;

	cout << "I : " << I << endl;
	cout << "tau : " << tau << endl;
	cout << "Ilmin : " << Ilmin << endl;
	cout << "Ilmax : " << Ilmax << endl;
	cout << "Irmin : " << Irmin << endl;
	cout << "Irmax : " << Irmax << endl << endl;
	if ((I >= Ilmin) & (I <= Ilmax) & !this->found) {
		//cout << "I : " << I << " Ilmin : " << Ilmin << " Ilmax : " << Ilmax << endl;
		this->numberOfNodeExplored++;
		//cout << "We search left node " << endl;
		if (T->isALeaf()) {
			//cout << "We reach the leaf " << endl;
			//return false;
		}
		this->searchMetricTreeDefeatist(T->left, q);
	}

	else{
		//cout << "I : " << I << " Irmin : " << Irmin << " Irmax : " << Irmax << endl;
		this->numberOfNodeExplored++;
		/*cout << "We search right node " << endl;*/
		if (T->isALeaf()) {
			/*	cout << "We reach the leaf " << endl;*/
			//return false;
		}
		this->searchMetricTreeDefeatist(T->right, q);
	}
	

	return true;
}

bool MetricTree::searchMetricTreeDefeatistConformation(Node * T, Point * q)
{

	cout << "Node explored n° : " << this->numberOfNodeExplored << endl;
	cout << "search Metric function called " << endl;
	cout << "Current Node explored : " << *T << endl;

	if (T->getPivot() == *q) {
		cout << "Point has been found at this Node" << endl;
		this->found = true;
		return true;
	}

	float tau = 0.0;
	if (this->numberOfNodeExplored == 0.0) {
		tau = std::numeric_limits<float>::max();
	}
	Point pivot = T->getPivot();

	if (pivot == *q) {
		/*	cout << "Point founded" << endl;*/

		return true;
	}


	if (T->isALeaf()) {
		return false;
	}
	else {
		/*cout << "On the left " << *(T->left) << endl;
		cout << "On the right " << *(T->right) << endl;*/
	}

	float I = this->hyperSpace->LRMSDDistance(pivot, *q);


	if (I < tau) {
		tau = I;
		this->nearestNeighbour = pivot;
	}



	float Ilmin = T->getD(1) - tau;
	float Ilmax = T->getD(2) + tau;
	float Irmin = T->getD(3) - tau;
	float Irmax = T->getD(4) + tau;

	cout << "I : " << I << endl;
	cout << "tau : " << tau << endl;
	cout << "Ilmin : " << Ilmin << endl;
	cout << "Ilmax : " << Ilmax << endl;
	cout << "Irmin : " << Irmin << endl;
	cout << "Irmax : " << Irmax << endl << endl;

	if ((I >= Ilmin) & (I <= Ilmax) & !this->found) {
		//cout << "I : " << I << " Ilmin : " << Ilmin << " Ilmax : " << Ilmax << endl;
		this->numberOfNodeExplored++;
		//cout << "We search left node " << endl;
		if (T->isALeaf()) {
			//cout << "We reach the leaf " << endl;
			//return false;
		}
		this->searchMetricTreeDefeatistConformation(T->left, q);
	}

	else{
		//cout << "I : " << I << " Irmin : " << Irmin << " Irmax : " << Irmax << endl;
		this->numberOfNodeExplored++;
		/*cout << "We search right node " << endl;*/
		if (T->isALeaf()) {
			/*	cout << "We reach the leaf " << endl;*/
			//return false;
		}
		this->searchMetricTreeDefeatistConformation(T->right, q);
	}
	return true;
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
