#include"Tree.h"

extern int verifyEachUpdate;

void Tree::insertYinTree(Y y)
{
	if (find(_root->_Y.begin(), _root->_Y.end(), y) != _root->_Y.end())
	{
		//already inserted
		return;
	}
	TreeNode* curNode = locateLeaf(y);
	Msg msg = _root->insertYintoLeaf(y);
	int flag = 0;
	if (verifyEachUpdate)
	{
		flag = curNode->verifyNodeInvariants();
		if (flag)
		{
			throw new exception();
		}
	}
	TreeNode* child = curNode;
	curNode = curNode->_parent;
	while (curNode != NULL)
	{
		if (child == curNode->_leftChild)
		{
			msg = curNode->insertYintoNodeL(msg);
		}
		else
		{
			msg = curNode->insertYintoNodeR(msg);
		}
		if (verifyEachUpdate)
		{
			flag = curNode->verifyNodeInvariants();
			if (flag)
			{
				throw new exception();
			}
		}
		child = curNode;
		curNode = curNode->_parent;
	}
	if (verifyEachUpdate)
	{
		cout << "Y id:\t" << y._value << " pass" << endl;
	}
}



Msg TreeNode::insertYintoLeaf(Y y)
{
	Msg msg;
	msg._aY = y;
	_Y.push_back(y);

	vector<X> CIXR;
	vector<Y> RMYR;
	Y aPre = alphaPreforZR(y);
	getYReachableSetinLeaf(aPre, CIXR, RMYR);
	RMYR.push_back(y);

	if (CIXR.empty())
	{
		//replace
		sort(RMYR.begin(), RMYR.end(), cmpYWeightInc);
		msg._aMY = y;
		_MY.push_back(y);
		_MYR.push_back(y);

		msg._bMY = RMYR[0];
		_MY.erase(find(_MY.begin(), _MY.end(), RMYR[0]));
		_MYR.erase(find(_MYR.begin(), _MYR.end(), RMYR[0]));

		msg._aIY = RMYR[0];
		_IY.push_back(RMYR[0]);
	}
	else
	{
		//compense
		sort(CIXR.begin(), CIXR.end(), cmpXWeightInc);
		X cX = CIXR[CIXR.size() - 1];

		msg._aMY = y;
		_MY.push_back(y);
		_MYR.push_back(y);

		msg._aMX = cX;
		_MX.push_back(cX);
		_MXR.push_back(cX);

		msg._bIX = cX;
		_IX.erase(find(_IX.begin(), _IX.end(), cX));
	}
	
	return msg;
}



Msg TreeNode::insertYintoNodeL(Msg msg)
{
	Msg rMsg;
	rMsg._aY = msg._aY;
	_Y.push_back(msg._aY);
	Y iy = msg._aY;

	Y bPost, bPost1, aPre;
	getThreeTightPoints(iy, bPost, bPost1, aPre);
	vector<X> CIX;
	vector<Y> RMY;
	getYReachableSetinInternalNode(msg, CIX, RMY);
	RMY.push_back(iy);

	if (CIX.empty())
	{
		//replace

	}
	else
	{
		//compense
		X cX = getMaxWeightCX(CIX);
		X bX = getMineBackXfromMXR(bPost, alphaPostforZR(maxY()));


		if (cX._s <= bPost && cX._e >= aPre)
		{

		}
		else if (cX._s <= bPost && cX._e < aPre)
		{

		}
		else if (cX._s <= bPost1 && cX._e >= aPre)
		{

		}
		else if (cX._s <= bPost1 && cX._e < aPre)
		{

		}
		else
		{
			//cX._s > bPost1 && cX._e >= aPre

		}
	}

	
	return rMsg;
}

Msg TreeNode::insertYintoNodeR(Msg msg)
{
	Msg rMsg; 


	return rMsg;
}