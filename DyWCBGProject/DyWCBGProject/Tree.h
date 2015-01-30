#pragma once
#include"Basic.h"

class TreeNode
{
public:
	//======================for Query========================
	vector<Y> _YG;
	vector<X> _XG;
	vector<Y> _IYG;
	//vector<Y> _IYLG;
	//vector<Y> _IYRG;
	vector<Y> _MYG;
	vector<Y> _MYLG;
	vector<Y> _MYRG;
	vector<X> _MXG;
	vector<X> _MXLG;
	vector<X> _MXRG;
	vector<X> _TXG;
	//====================================================


	//====================for Query Test=========================
	vector<Y> _YGTest;
	vector<X> _XGTest;
	vector<Y> _IYGTest;
	//vector<Y> _IYLG;
	//vector<Y> _IYRG;
	vector<Y> _MYGTest;
	vector<Y> _MYLGTest;
	vector<Y> _MYRGTest;
	vector<X> _MXGTest;
	vector<X> _MXLGTest;
	vector<X> _MXRGTest;
	vector<X> _TXGTest;
	vector<Edge> _MatchingG;
	//============================================================

	//==================for update==========================
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

	vector<Y> _newMY;
	vector<X> _newIX;
	//==========================================================
	




	TreeNode * _leftChild;
	TreeNode * _rightChild;
	TreeNode * _parent;


	TreeNode(vector<Y>);	//init
	TreeNode(vector<Y>, vector<Y>);

	Y maxY();
	Y minY();

	//Y alphaPostforZL(Y y);
	Y alphaPostforZR(Y y);
	Y alphaPreforZR(Y y);
	Y betaPreforZL(Y y);
	Y betaPostforZL(Y y);

	Y betaPreforZ(Y y);

	Y betaPostforZRG(Y y);

	//===================for insertX==========================
	void performXEEESEE(Msg & rMsg);//for msg from L
	void performXESEE(Msg & rMsg);//for msg from R
	void getXReachableSetinR(Y apost, vector<X> & RMXR, vector<Y> & CIYR);
	void getXReachableSetinL(Y bpre, vector<X> & RMXL, vector<Y> & CIYL);
	void getXReachableSet2inL(Y bpre1, Y bpre, vector<X> & RMXL2, vector<Y> & CIYL2);//for msg from L
	void updateStableCount(Msg & msg);
	//void updatet1t2(Msg & msg);
	//void getCompensableYL(X x, Y t1, Y t2, int stableCountinChild, vector<Y> & CIYL, vector<Y> & CIYR, vector<Y> & CIYL2);
	Y getMaxWeightCY(vector<Y> CIYL, vector<Y> CIYR, vector<Y> CIYL2);
	X getMinWeightRX(vector<X> RMXL, vector<X> RMXR, vector<X> RMXL2);
	Y getMaxWeightCY(vector<Y> CIYL, vector<Y> CIYR);
	X getMinWeightRX(vector<X> RMXL, vector<X> RMXR);
	//=======================================================

	X getMineBackXfromMXR(Y bpost, Y apost);
	void updateNewIXMY(Msg oldMsg, Msg curMsg);

	//===================for insertY=========================
	void getThreeTightPoints(Y iy, Y & bPost, Y & bPost1, Y & aPre);
	void getYReachableSetinInternalNode(Msg msg, vector<X> & CIX, vector<Y> & RMY);
	void getYReachableSetinLeaf(Y aPre, vector<X> & CIX, vector<Y> & RMY);
	X getMaxsForwardXFromMXL(Y bpost, Y apre);
	X getMaxWeightCX(vector<X> CIX);
	Y getMinWeightRY(vector<Y> RMY);
	/*void getYReachableSetinR(Y apre, vector<X> & CIXR, vector<Y> & RMYR);
	void getYReachableSetinL(Y bPost, vector<X> & CIXL, vector<Y> & RMYL);
	void getYReachableSetinL2(Y bPost, Y bPost1, vector<X> & CIXL2, vector<Y> RMYL2);*/
	/*X getMaxWeightCX(vector<X> CIXL, vector<X> CIXR, vector<X> CIXL2);
	Y getMinWeightRY(vector<Y> RMYL, vector<Y> RMYR, vector<Y> RMYL2);*/
	//==============================================================




	//========================for query X=========================
	Y searchXMateRecur(X x, int delta = 0);
	//==========================================================



	//========================for query info=========================

	Msg insertXintoLeafG(X x);
	Msg insertXintoNodeLG(Msg msg);
	Msg insertXintoNodeRG(Msg msg);

	Msg deleteXfromLeafG(X x);
	Msg deleteXfromNodeLG(Msg msg);
	Msg deleteXfromNodeRG(Msg msg);

	Msg insertYintoLeafG(Y y);
	Msg insertYintoNodeLG(Msg msg);
	Msg insertYintoNodeRG(Msg msg);

	Msg deleteYfromLeafG(Y y);
	Msg deleteYfromNodeLG(Msg msg);
	Msg deleteYfromNodeRG(Msg msg);

	//auxilary
	X getMaxEndXinMXRG(X x);
	Y getMaxYinMYRG(Y y = *(new Y()));
	vector<Y> getNewMYRG();
	//==============================================================

	int verifyNodeInvariants();
	void splitNode(X insertedX);
	int verifyGSets();

	//=========================for update=================================
	Msg insertYintoLeaf(Y y);
	Msg insertXintoLeaf(X x);

	Msg insertXintoNodeL(Msg msg);
	Msg insertXintoNodeR(Msg msg);

	Msg insertYintoNodeL(Msg msg);
	Msg insertYintoNodeR(Msg msg);
	//=======================================================================
		
	//lazy
	vector<Y> getYL();
	vector<Y> getYR();
	vector<Y> getIYL();
	vector<Y> getIYR();

	vector<Y> getYLG();
	vector<Y> getYRG();
	vector<Y> getIYLG();
	vector<Y> getIYRG();

};

class Tree
{
public:
	TreeNode* _root;

	Tree(vector<Y>);	// init

	//=============================for update===============================
	void insertXinTree(X x);
	void insertYinTree(Y y);
	//======================================================================


	//=============================for query=================================
	void updateQueryInfo(Msg msg);
	void insertXinTreeG(X x);
	void deleteXfromTreeG(X x);
	void insertYinTreeG(Y y);
	void deleteYfromTreeG(Y y);
	//=====================================================================

	Y queryXMate(int id);
	X queryYMate(int value);

	Y getYMateEnd(Y y);
	Y getTestXMate(X x);

	

	TreeNode* locateLeaf(X x);
	TreeNode* locateLeaf(Y y);


	void verifyInvariantsRecur(int& flag, TreeNode*& errorNode);
	void verifyInvariantsRecur(int& flag, TreeNode*& errorNode, TreeNode* curRoot);

	void verifyGloverInfo(int& flag, TreeNode*& errorNode);
	void verifyGloverInfo(int& flag, TreeNode*& errorNode, TreeNode* curRoot);

	void constructGloverInfo();
	void constructGloverInfo(TreeNode* curRoot, vector<X> MX, vector<Y> MY);

	void printMY();
	void printMY(TreeNode* curRoot, ofstream & my);
	void printRMY();
};