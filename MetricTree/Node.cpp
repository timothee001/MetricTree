#include "stdafx.h"
#include "Node.h"
#include <iostream>
#include <ostream>

Node::Node()
{
	this->id= reinterpret_cast<uint32_t>(this);
}

void Node::setPivot(Point pivot)
{
	this->pivot = pivot;
}

void Node::setLeftNode(Node * left)
{
	this->left = left;
}

void Node::setRightNode(Node * right)
{
	this->right = right;
}

void Node::setD(int d, float value)
{
	if (d == 1) {
		this->d1 = value;
	}else if (d == 2) {
		this->d2 = value;
	}
	else if (d == 3) {
		this->d3 = value;
	}
	else if (d == 4) {
		this->d4 = value;
	}
}

Point Node::getPivot()
{
	return this->pivot;
}



float Node::getD(int d)
{
	if (d == 1) {
		return this->d1;
	}
	else if (d == 2) {
		return this->d2;
	}
	else if (d == 3) {
		return this->d3;
	}
	else if (d == 4) {
		return this->d4;
	}
}

void Node::setLeafTrue()
{
	this->isLeaf = true;
}

bool Node::isALeaf()
{
	return this->isLeaf;
}


Node::~Node()
{
}

ostream & operator<<(ostream & os, const Node & mt)
{
	if(&mt!=NULL){
	os << "Begin Node "<< mt.id <<"--------------------- " << endl;
	os << "isLeaf " << mt.isLeaf << endl;
	os << "Pivot : " << mt.pivot << endl;
	os << "d1 : " << mt.d1 << " d2 : " << mt.d2<< " d3 : " << mt.d3 << " d4 : " << mt.d4 << endl;
	os << "End Node --------------------- " << endl;
	}
	return os;
}
