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


	//for stable
	vector<X> _MXS;
	vector<X> _MXLS;
	vector<X> _MXRS;
	vector<Y> _MYS;
	vector<Y> _MYLS;
	vector<Y> _MYRS;
	vector<Y> _IYS;

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


	Y alphaPostforZLS(Y y);
	Y alphaPostforZRS(Y y);
	Y alphaPreforZRS(Y y);
	Y betaPreforZLS(Y y);
	Y betaPostforZLS(Y y);

	void updatet1t2inLeafX(Msg & msg);
	void updatet1t2inInternalNodeX(Msg & msg);
	
	void updateStableSetinLeaf(Msg msg);
	void updateStableSetinInternalNode(Msg msg, Y t1inChild, Y t2inChild, bool forceSwap = false);

	int verifyNodeInvariants();
	void splitNode(X insertedX);
	int verifyCIY(vector<Y> CIYLCorrect, vector<Y> CIYRCorrect, vector<Y> CIYL2Correct, vector<Y> CIYL, vector<Y> CIYR, vector<Y> CIYL2);

	Msg insertYintoLeaf(Y y);
	Msg insertXintoLeaf(X x);

	Msg insertXintoNodeL(Msg msg);
	Msg insertXintoNodeR(Msg msg);

	void getCompensableYL(X x, Y t1, Y t2, int stableCountinChild, vector<Y> & CIYL, vector<Y> & CIYR, vector<Y> & CIYL2);
	
	//lazy
	vector<Y> getYL();
	vector<Y> getYR();
	vector<Y> getIYL();
	vector<Y> getIYR();
	//vector<Y> getIYS();
	
	void getStableSet(vector<X> & MXS, vector<Y> & MYS);

	vector<X> getReachableSetinLeftPart(X x);

	//vector<X> getStableReachableSet(X x);

	void getCompensableYLForce(X x, vector<Y> & CIYL, vector<Y> & CIYR, vector<Y> & CIYL2);

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