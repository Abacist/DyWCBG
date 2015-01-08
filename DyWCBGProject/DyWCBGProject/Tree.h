#pragma once
#include"Basic.h"

class TreeNode
{
public:
	vector<X> _X;
	vector<Y> _Y;

	vector<X> _MX;
	vector<X> _MXR;
	vector<X> _MXL;
	//in leaf: MX = MXR

	vector<X> _IX;
	vector<X> _TX;

	vector<Y> _MY;
	vector<Y> _MYL;
	vector<Y> _MYR;
	//in leaf: MY = MYR
	
	vector<Y> _IY;

	TreeNode * _leftChild;
	TreeNode * _rightChild;
	TreeNode * _parent;


	TreeNode(vector<Y>);	//init

	Y maxY();
	Y minY();

	Y alphaPostforZL(Y y);
	Y alphaPostforZR(Y y);
	Y alphaPreforZR(Y y);
	Y betaPreforZL(Y y);
	Y betaPostforZL(Y y);

	int verifyNodeInvariants();
	void splitNode(X insertedX);

	Msg insertYintoLeaf(Y y);
	Msg insertXintoLeaf(X x);

	Msg insertXintoNodeL(Msg msg, vector<X> RMXSinChild);
	Msg insertXintoNodeR(Msg msg, vector<X> RMXSinChild);

	vector<Y> getYL();
	vector<Y> getYR();
	vector<Y> getIYL();
	vector<Y> getIYR();
	
	void getStableSet(vector<X> & MXS, vector<Y> & MYS);

	vector<X> getReachableSetinLeftPart(X x);
	vector<X> getStableReachableSet(X x);
	void getCompensableYL(X x, vector<Y> & CIYL, vector<Y> & CIYR, vector<Y> & CIYL2);

};

class Tree
{
public:
	TreeNode* _root;

	Tree(vector<Y>);	// init

	void insertXinTree(X x);
	void insertYinTree(Y y);

	TreeNode* locateLeaf(X x);
	TreeNode* locateLeaf(Y y);


	void verifyInvariantsRecur(int& flag, TreeNode*& errorNode);
	void verifyInvariantsRecur(int& flag, TreeNode*& errorNode, TreeNode* curRoot);
};