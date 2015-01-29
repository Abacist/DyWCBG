#include"Tree.h"



Y TreeNode::getMaxWeightCY(vector<Y> CIYL, vector<Y> CIYR, vector<Y> CIYL2)
{
	vector<Y> allCIY = CIYL;
	for (int i = 0; i < CIYR.size(); i++) allCIY.push_back(CIYR[i]);
	for (int i = 0; i < CIYL2.size(); i++) allCIY.push_back(CIYL2[i]);
	sort(allCIY.begin(), allCIY.end(), cmpYWeightInc);
	return allCIY[allCIY.size() - 1];
}

X TreeNode::getMinWeightRX(vector<X> RMXL, vector<X> RMXR, vector<X> RMXL2)
{
	vector<X> allRMX = RMXL;
	for (int i = 0; i < RMXR.size(); i++) allRMX.push_back(RMXR[i]);
	for (int i = 0; i < RMXL2.size(); i++) allRMX.push_back(RMXL2[i]);
	sort(allRMX.begin(), allRMX.end(), cmpXWeightInc);
	return allRMX[0];
}

void TreeNode::getYReachableSetinLeaf(Y apre, vector<X> & CIXR, vector<Y> & RMYR)
{
	CIXR.clear();
	RMYR.clear();
	vector<X> CIXRBase;
	vector<Y> RMYRBase;

	CIXRBase = _IX;
	RMYRBase = _MYR;

	for (int i = 0; i < CIXRBase.size(); i++)
	{
		if (CIXRBase[i]._e >= apre)
		{
			CIXR.push_back(CIXRBase[i]);
		}
	}
	for (int i = 0; i < RMYRBase.size(); i++)
	{
		if (RMYRBase[i] >= apre)
		{
			RMYR.push_back(RMYRBase[i]);
		}
	}
}

void TreeNode::getThreeTightPoints(Y iy, Y & bPost, Y & bPost1, Y & aPre)
{
	bPost = betaPostforZL(iy);
	X bX = getMineBackXfromMXR(bPost, alphaPostforZR(maxY()));
	if (!bX.empty())
	{
		aPre = alphaPreforZR(bX._e);
		X fX = getMaxsForwardXFromMXL(bPost, aPre);
		if (!fX.empty())
		{
			bPost1 = betaPostforZL(fX._s);
		}
		else
		{
			bPost1._value = INT_MIN;
		}
		if (bPost1 < bPost)
		{
			bPost1 = bPost;
		}
		
	}
	else
	{
		bPost1 = bPost;
		aPre._value = INT_MAX;
	}
	
}

void TreeNode::getYReachableSetinInternalNode(Msg msg, vector<X> & CIX, vector<Y> & RMY)
{
	CIX.clear();
	RMY.clear();
	vector<X> CIXBase;
	vector<Y> RMYBase;
	Y t1, t2;
	if (msg._aY < _rightChild->minY())
	{
		//from left
		Y bPost, bPost1, aPre;
		getThreeTightPoints(msg._aY, bPost, bPost1, aPre);
		t1 = bPost1;
		t2 = aPre;
	}
	else
	{
		t2 = alphaPreforZR(msg._aY);
		X fX = getMaxsForwardXFromMXL(betaPreforZL(minY()), t2);
		t1 = betaPostforZL(fX._s);
	}
	
	vector<X> CIXBaseTest = _newIX;
	if (!msg._bIX.empty())
	{
		CIXBaseTest.push_back(msg._bIX);
	}
	vector<Y> RMYBaseTest = _newMY;
	if (!msg._aIY.empty() && msg._aIY != msg._aY)
	{
		RMYBaseTest.push_back(msg._aIY);
	}

	RMYBase = RMYBaseTest;
	CIXBase = CIXBaseTest;

	/*for (int i = 0; i < _IX.size(); i++)
	{
		if (find(_leftChild->_IX.begin(), _leftChild->_IX.end(), _IX[i]) == _leftChild->_IX.end() &&
			find(_rightChild->_IX.begin(), _rightChild->_IX.end(), _IX[i]) == _rightChild->_IX.end())
		{
			CIXBase.push_back(_IX[i]);
		}
	}
	for (int i = 0; i < _MY.size(); i++)
	{
		if (find(_leftChild->_MY.begin(), _leftChild->_MY.end(), _MY[i]) == _leftChild->_MY.end() &&
			find(_rightChild->_MY.begin(), _rightChild->_MY.end(), _MY[i]) == _rightChild->_MY.end())
		{
			RMYBase.push_back(_MY[i]);
		}
	}


	if (RMYBase.size() != RMYBaseTest.size())
	{
		throw new exception();
	}
	else
	{
		sort(RMYBase.begin(), RMYBase.end(), cmpYValueInc);
		sort(RMYBaseTest.begin(), RMYBaseTest.end(), cmpYValueInc);
		for (int i = 0; i < RMYBase.size(); i++)
		{
			if (RMYBase[i] != RMYBaseTest[i])
			{
				throw new exception();
			}
		}
	}

	if (CIXBase.size() != CIXBaseTest.size())
	{
		throw new exception();
	}
	else
	{
		sort(CIXBase.begin(), CIXBase.end(), cmpXID);
		sort(CIXBaseTest.begin(), CIXBaseTest.end(), cmpXID);
		for (int i = 0; i < CIXBaseTest.size(); i++)
		{
			if (CIXBase[i] != CIXBaseTest[i])
			{
				throw new exception();
			}
		}
	}*/

	for (int i = 0; i < CIXBase.size(); i++)
	{
		if (CIXBase[i]._s <= t1 || CIXBase[i]._e >= t2)
		{
			CIX.push_back(CIXBase[i]);
		}
	}

	for (int i = 0; i < RMYBase.size(); i++)
	{
		if (RMYBase[i] <= t1 || RMYBase[i] >= t2)
		{
			RMY.push_back(RMYBase[i]);
		}
	}
}