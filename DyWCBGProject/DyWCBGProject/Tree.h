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

	//Y alphaPostforZL(Y y);
	Y alphaPostforZR(Y y);
	Y alphaPreforZR(Y y);
	Y betaPreforZL(Y y);
	Y betaPostforZL(Y y);

	Y betaPreforZ(Y y);


	//===================for insertX==========================
	void performEEESEE(Msg msgInChild, Msg & rMsg);//for msg from L
	void performESEE(Msg msgInChild, Msg & rMsg);//for msg from R
	void getReachableSetinR(Y apost, vector<X> & RMXR, vector<Y> & CIYR);
	void getReachableSetinL(Y bpre, vector<X> & RMXL, vector<Y> & CIYL);
	void getReachableSet2inL(Y bpre1, Y bpre, vector<X> & RMXL2, vector<Y> & CIYL2);//for msg from L
	void updateStableCount(Msg & msg);
	//void updatet1t2(Msg & msg);
	//void getCompensableYL(X x, Y t1, Y t2, int stableCountinChild, vector<Y> & CIYL, vector<Y> & CIYR, vector<Y> & CIYL2);
	Y getMaxWeightCY(vector<Y> CIYL, vector<Y> CIYR, vector<Y> CIYL2);
	X getMinWeightRX(vector<X> RMXL, vector<X> RMXR, vector<X> RMXL2);
	Y getMaxWeightCY(vector<Y> CIYL, vector<Y> CIYR);
	X getMinWeightRX(vector<X> RMXL, vector<X> RMXR);
	X getBackXfromMXR(Y bpost, Y apost);
	//=======================================================
	

	int verifyNodeInvariants();
	void splitNode(X insertedX);

	Msg insertYintoLeaf(Y y);
	Msg insertXintoLeaf(X x);

	Msg insertXintoNodeL(Msg msg);
	Msg insertXintoNodeR(Msg msg);

	
	//lazy
	vector<Y> getYL();
	vector<Y> getYR();
	vector<Y> getIYL();
	vector<Y> getIYR();

	

	//no need
	int verifyCIY(X ix, vector<Y> CIYL, vector<Y> CIYR, vector<Y> CIYL2);

	void getMXMY(vector<X> & MXS, vector<Y> & MYS);

	void getCompensableYLForce(X x, vector<Y> & CIYL, vector<Y> & CIYR, vector<Y> & CIYL2);

	//vector<X> getReachableSetinLeftPart(X x);

	//vector<X> getStableReachableSet(X x);

	

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

	void printMY();
	void printMY(TreeNode* curRoot, ofstream & my);
	void printRMY();
};