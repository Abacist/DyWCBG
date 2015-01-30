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
	Msg msg = curNode->insertYintoLeaf(y);
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
	updateQueryInfo(msg);
	if (verifyEachUpdate)
	{
		cout << "Y id:\t" << y._value << "\tpass" << endl;
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
		Y rY = getMinWeightRY(RMY);
		if (rY == iy)
		{
			rMsg._aMY = iy;
			rMsg._bMY = iy;
			rMsg._aIY = iy;
			_IY.push_back(rY);
		}
		else if (rY <= bPost)
		{
			vector<X> RMXLForward;
			Y bPre = betaPreforZL(rY);
			for (int i = 0; i < _MXL.size(); i++)
			{
				if (_MXL[i]._s >= bPre && _MXL[i]._e >= aPre)
				{
					RMXLForward.push_back(_MXL[i]);
				}
			}
			sort(RMXLForward.begin(), RMXLForward.end(), cmpXEndInc);
			X maxEnd;
			if (!RMXLForward.empty())
			{
				maxEnd = RMXLForward[RMXLForward.size() - 1];
			}
			X bX = getMineBackXfromMXR(bPost, alphaPostforZR(maxY()));//only one?

			rMsg._aMY = iy;
			_MY.push_back(iy);
			_MYL.push_back(iy);

			rMsg._bMY = rY;
			_MY.erase(find(_MY.begin(), _MY.end(), rY));
			_MYL.erase(find(_MYL.begin(), _MYL.end(), rY));

			if (!bX.empty() && cmpXEndInc(bX, maxEnd))
			{
				_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
				_MXR.erase(find(_MXR.begin(), _MXR.end(), bX));
				_MXL.push_back(bX);
				_MXR.push_back(maxEnd);
			}

			rMsg._aIY = rY;
			_IY.push_back(rY);



		}
		else if (rY > bPost && rY <= bPost1)
		{
			vector<X> RMXLForward;
			Y bPre = betaPreforZL(rY);
			for (int i = 0; i < _MXL.size(); i++)
			{
				if (_MXL[i]._s >= bPre && _MXL[i]._e >= aPre)
				{
					RMXLForward.push_back(_MXL[i]);
				}
			}
			sort(RMXLForward.begin(), RMXLForward.end(), cmpXEndInc);
			X maxEnd = RMXLForward[RMXLForward.size() - 1];
			X bX = getMineBackXfromMXR(bPost, alphaPostforZR(maxY()));

			rMsg._aMY = iy;
			_MY.push_back(iy);
			_MYL.push_back(iy);
			_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
			_MXR.push_back(maxEnd);
			_MXR.erase(find(_MXR.begin(), _MXR.end(), bX));
			_MXL.push_back(bX);

			rMsg._bMY = rY;
			_MY.erase(find(_MY.begin(), _MY.end(), rY));
			_MYL.erase(find(_MYL.begin(), _MYL.end(), rY));

			rMsg._aIY = rY;
			_IY.push_back(rY);
		}
		else
		{
			X bX = getMineBackXfromMXR(bPost, alphaPostforZR(maxY()));

			rMsg._aMY = iy;
			_MY.push_back(iy);
			_MYL.push_back(iy);
			_MXR.erase(find(_MXR.begin(), _MXR.end(), bX));
			_MXL.push_back(bX);

			rMsg._bMY = rY;
			_MY.erase(find(_MY.begin(), _MY.end(), rY));
			_MYR.erase(find(_MYR.begin(), _MYR.end(), rY));

			rMsg._aIY = rY;
			_IY.push_back(rY);
		}
	}
	else
	{
		//compense
		X cX = getMaxWeightCX(CIX);
		X bX = getMineBackXfromMXR(bPost, alphaPostforZR(maxY()));//may be empty

		vector<X> RMXLForward;
		Y bPre = betaPreforZL(cX._s);
		for (int i = 0; i < _MXL.size(); i++)
		{
			if (_MXL[i]._s >= bPre && _MXL[i]._e >= aPre)
			{
				RMXLForward.push_back(_MXL[i]);
			}
		}
		if (cX._e >= aPre)
		{
			RMXLForward.push_back(cX);
		}
		sort(RMXLForward.begin(), RMXLForward.end(), cmpXEndInc);
		X maxEnd;
		if (!RMXLForward.empty())
		{
			maxEnd = RMXLForward[RMXLForward.size() - 1];
		}

		if (cX._s > bPost || !bX.empty() && !maxEnd.empty() && cmpXEndInc(bX, maxEnd))
		{
			//bX back
			rMsg._aMX = cX;
			_MX.push_back(cX);
			_MXL.push_back(cX);
			_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
			_MXR.push_back(maxEnd);
			_MXR.erase(find(_MXR.begin(), _MXR.end(), bX));
			_MXL.push_back(bX);

			rMsg._aMY = iy;
			_MY.push_back(iy);
			_MYL.push_back(iy);

			rMsg._bIX = cX;
			_IX.erase(find(_IX.begin(), _IX.end(), cX));

		}
		else
		{
			//directly add to left
			rMsg._aMX = cX;
			_MX.push_back(cX);
			_MXL.push_back(cX);

			rMsg._aMY = iy;
			_MY.push_back(iy);
			_MYL.push_back(iy);

			rMsg._bIX = cX;
			_IX.erase(find(_IX.begin(), _IX.end(), cX));
		}
	}
	updateNewIXMY(msg, rMsg);
	return rMsg;
}

Msg TreeNode::insertYintoNodeR(Msg msg)
{
	Msg rMsg;
	rMsg._aY = msg._aY;
	_Y.push_back(msg._aY);
	Y iy = msg._aY;

	Y aPre = alphaPreforZR(msg._aY);
	X fX = getMaxsForwardXFromMXL(betaPreforZL(minY()), aPre);
	Y bPost = betaPostforZL(fX._s);

	vector<X> CIX;
	vector<Y> RMY;
	getYReachableSetinInternalNode(msg, CIX, RMY);
	RMY.push_back(iy);

	if (CIX.empty())
	{
		//replace
		Y rY = getMinWeightRY(RMY);
		if (rY >= aPre || rY == iy)
		{
			rMsg._aMY = iy;
			_MY.push_back(iy);
			_MYR.push_back(iy);

			rMsg._bMY = rY;
			_MY.erase(find(_MY.begin(), _MY.end(), rY));
			_MYR.erase(find(_MYR.begin(), _MYR.end(), rY));

			rMsg._aIY = rY;
			_IY.push_back(rY);
		}
		else
		{
			vector<X> RMXLForward;
			Y bPre = betaPreforZL(rY);
			for (int i = 0; i < _MXL.size(); i++)
			{
				if (_MXL[i]._s >= bPre && _MXL[i]._e >= aPre)
				{
					RMXLForward.push_back(_MXL[i]);
				}
			}
			
			sort(RMXLForward.begin(), RMXLForward.end(), cmpXEndInc);
			X maxEnd = RMXLForward[RMXLForward.size() - 1];
			
			rMsg._aMY = iy;
			_MY.push_back(iy);
			_MYR.push_back(iy);
			_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
			_MXR.push_back(maxEnd);

			rMsg._bMY = rY;
			_MY.erase(find(_MY.begin(), _MY.end(), rY));
			_MYL.erase(find(_MYL.begin(), _MYL.end(), rY));

			rMsg._aIY = rY;
			_IY.push_back(rY);
			
		}

	}
	else
	{
		//compense
		X cX = getMaxWeightCX(CIX);
		vector<X> RMXLForward;
		Y bPre = betaPreforZL(cX._s);
		for (int i = 0; i < _MXL.size(); i++)
		{
			if (_MXL[i]._s >= bPre && _MXL[i]._e >= aPre)
			{
				RMXLForward.push_back(_MXL[i]);
			}
		}
		if (cX._e >= aPre)
		{
			RMXLForward.push_back(cX);
		}
		sort(RMXLForward.begin(), RMXLForward.end(), cmpXEndInc);
		X maxEnd;
		if (!RMXLForward.empty())
		{
			maxEnd = RMXLForward[RMXLForward.size() - 1];
		}

		if (cX._e < aPre || !maxEnd.empty() && cmpXEndInc(cX, maxEnd))
		{
			//forward maxEnd
			rMsg._aMX = cX;
			_MX.push_back(cX);
			_MXL.push_back(cX);
			_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
			_MXR.push_back(maxEnd);

			rMsg._aMY = iy;
			_MY.push_back(iy);
			_MYR.push_back(iy);

			rMsg._bIX = cX;
			_IX.erase(find(_IX.begin(), _IX.end(), cX));
		}
		else
		{
			//directly add to right
			rMsg._aMX = cX;
			_MX.push_back(cX);
			_MXR.push_back(cX);

			rMsg._aMY = iy;
			_MY.push_back(iy);
			_MYR.push_back(iy);

			rMsg._bIX = cX;
			_IX.erase(find(_IX.begin(), _IX.end(), cX));
		}

	}

	updateNewIXMY(msg, rMsg);
	return rMsg;
}