#include"Tree.h"

extern int verifyEachUpdate;




void Tree::insertXinTree(X x)
{
	TreeNode* curNode = locateLeaf(x);
	Msg msg = curNode->insertXintoLeaf(x);
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
			msg = curNode->insertXintoNodeL(msg);
		}
		else
		{
			msg = curNode->insertXintoNodeR(msg);
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
		cout << "X id:\t" << x._id << " pass" << endl;
	}

}


Msg TreeNode::insertXintoLeaf(X x)
{
	
	Msg msg;
	msg._aX = x;
	_X.push_back(x);

	msg._t1 = x._s;
	

	if (x._e > maxY())
	{
		msg._t2 = x._e;
		msg._aTX = x;
		_TX.push_back(x);
		//no update with stableCount
	}
	else
	{
		msg._t2 = alphaPostforZR(x._e);
		updateStableCount(msg);
		vector<X> RMXR;
		vector<Y> CIYR;
		getXReachableSetinR(msg._t2, RMXR, CIYR);
		RMXR.push_back(x);
		if (CIYR.empty())
		{
			//msg._replace = true;
			sort(RMXR.begin(), RMXR.end(), cmpXWeightInc);
			
			msg._aMX = x;
			_MXR.push_back(x);
			_MX.push_back(x);
			msg._bMX = RMXR[0];
			_MX.erase(find(_MX.begin(), _MX.end(), RMXR[0]));
			_MXR.erase(find(_MXR.begin(), _MXR.end(), RMXR[0]));
			msg._aIX = RMXR[0];
			_IX.push_back(RMXR[0]);
			
		}
		else
		{
			sort(CIYR.begin(), CIYR.end(), cmpYWeightInc);
			msg._aMX = x;
			_MXR.push_back(x);
			_MX.push_back(x);

			msg._aMY = CIYR[CIYR.size() - 1];
			_MYR.push_back(CIYR[CIYR.size() - 1]);
			_MY.push_back(CIYR[CIYR.size() - 1]);

			msg._bIY = CIYR[CIYR.size() - 1];
			_IY.erase(find(_IY.begin(), _IY.end(), CIYR[CIYR.size() - 1]));
		}
	}
	return msg;
}




Msg TreeNode::insertXintoNodeL(Msg msg)
{
	/*Y t1InChild = msg._t1, t2InChild = msg._t2;
	int countInChild = msg._stableYCount;*/
	//bool replaceInChild = msg._replace;

	Msg rMsg;
	rMsg._t1 = msg._t1;
	rMsg._t2 = msg._t2;
	rMsg._stableYCount = msg._stableYCount;
	//rMsg._replace = msg._replace;

	rMsg._aX = msg._aX;
	_X.push_back(msg._aX);

	if (msg._aX._e > maxY())//equal to t2>maxY()
	{
		rMsg._t1 = betaPreforZ(msg._aX._s);
		rMsg._aTX = msg._aX;
		_TX.push_back(msg._aX);
	}
	else
	{
		//deal with the aX
		updateStableCount(rMsg);
		if (rMsg._t2 >= _rightChild->minY() || rMsg._stableYCount > msg._stableYCount)
		{
			//EE and ES available
			performXEEESEE(msg, rMsg);
		}
		else
		{
			//rMsg._t2 < _rightChild->minY() && _stableCount = countInChild

			
			if (!msg._bIY.empty())
			{
				//success in L
				//t1 t2 stablecount keeps	
				rMsg._aMX = msg._aX;
				_MX.push_back(msg._aX);
				_MXL.push_back(msg._aX);

				rMsg._aMY = msg._aMY;
				_MY.push_back(msg._aMY);
				_MYL.push_back(msg._aMY);

				rMsg._bIY = msg._bIY;
				_IY.erase(find(_IY.begin(), _IY.end(), msg._bIY));
			}
			else
			{
				//replace in L
				if (find(_MXL.begin(), _MXL.end(), msg._bMX) != _MXL.end() || msg._aX == msg._aIX)
				{
					//t1 t2 stablecount keeps	
					//but t2 may not be a real t2
					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXL.push_back(msg._aX);

					rMsg._bMX = msg._bMX;
					_MX.erase(find(_MX.begin(), _MX.end(), msg._bMX));
					_MXL.erase(find(_MXL.begin(), _MXL.end(), msg._bMX));

					rMsg._aIX = msg._aIX;
					_IX.push_back(msg._aIX);
				}
				else
				{
					//EE and ES available
					performXEEESEE(msg, rMsg);
				}

				
			}
		}
	}


	return rMsg;
	
}

void TreeNode::performXEEESEE(Msg msgInChild, Msg & rMsg)
{
	X ix = rMsg._aX;
	Y bPre = betaPreforZL(ix._s);
	vector<X> RMXL, RMXR, RMXL2;
	vector<Y> CIYL, CIYR, CIYL2;
	//EE
	getXReachableSetinL(bPre, RMXL, CIYL);
	RMXL.push_back(ix);
	//ES
	sort(RMXL.begin(), RMXL.end(), cmpXEndInc);
	Y aPost = alphaPostforZR(RMXL[RMXL.size() - 1]._e);
	getXReachableSetinR(aPost, RMXR, CIYR);
	//EE2
	Y bPre1 = bPre;
	if (!RMXR.empty())
	{
		sort(RMXR.begin(), RMXR.end(), cmpXBeginDec);
		Y bPreNew = betaPreforZL(RMXR[RMXR.size() - 1]._s);
		if (bPreNew < bPre1)
		{
			bPre1 = bPreNew;
		}
		getXReachableSet2inL(bPre1, bPre, RMXL2, CIYL2);
		
	}
	

	rMsg._t1 = bPre1;
	rMsg._t2 = aPost;
	updateStableCount(rMsg);

	//test code
	/*if (verifyCIY(ix, CIYL, CIYR, CIYL2) != 0)
	{
		throw new exception();
	}*/

	if (CIYL.empty() && CIYR.empty() && CIYL2.empty())
	{
		//replace
		X rX = getMinWeightRX(RMXL, RMXR, RMXL2);
		if (find(RMXL.begin(), RMXL.end(), rX) != RMXL.end())
		{
			if (rX == ix)
			{
				rMsg._aMX = ix;
				rMsg._bMX = ix;
				rMsg._aIX = ix;
				_IX.push_back(ix);
			}
			else
			{
				X bX = getBackXfromMXR(betaPostforZL(rX._s), alphaPostforZR(RMXL[RMXL.size() - 1]._e));

				rMsg._aMX = ix;
				_MX.push_back(ix);
				_MXL.push_back(ix);
				if (!bX.empty() && cmpXEndInc(bX, RMXL[RMXL.size() - 1]))
				{
					_MXL.erase(find(_MXL.begin(), _MXL.end(), RMXL[RMXL.size() - 1]));
					_MXR.erase(find(_MXR.begin(), _MXR.end(), bX));
					_MXL.push_back(bX);
					_MXR.push_back(RMXL[RMXL.size() - 1]);
				}

				rMsg._bMX = rX;
				_MX.erase(find(_MX.begin(), _MX.end(), rX));
				_MXL.erase(find(_MXL.begin(), _MXL.end(), rX));

				rMsg._aIX = rX;
				_IX.push_back(rX);
			}
		}
		else if (find(RMXR.begin(), RMXR.end(), rX) != RMXR.end())
		{
			X fX = RMXL[RMXL.size() - 1];
			rMsg._aMX = ix;
			_MX.push_back(ix);
			_MXL.push_back(ix);
			_MXL.erase(find(_MXL.begin(), _MXL.end(), fX));

			rMsg._bMX = rX;
			_MXR.push_back(fX);
			_MXR.erase(find(_MXR.begin(), _MXR.end(), rX));
			_MX.erase(find(_MX.begin(), _MX.end(), rX));

			rMsg._aIX = rX;
			_IX.push_back(rX);
		}
		else
		{
			X fX = RMXL[RMXL.size() - 1];
			Y bPost = betaPostforZL(rX._s);
			X bX = getBackXfromMXR(bPost, aPost);

			rMsg._aMX = ix;
			_MX.push_back(ix);
			_MXL.push_back(ix);
			_MXL.erase(find(_MXL.begin(), _MXL.end(), fX));
			_MXR.push_back(fX);
			_MXR.erase(find(_MXR.begin(), _MXR.end(), bX));
			_MXL.push_back(bX);

			rMsg._bMX = rX;
			_MX.erase(find(_MX.begin(), _MX.end(), rX));
			_MXL.erase(find(_MXL.begin(), _MXL.end(), rX));

			rMsg._aIX = rX;
			_IX.push_back(rX);
		}
	}
	else
	{
		Y cY = getMaxWeightCY(CIYL, CIYR, CIYL2);
		if (find(CIYL.begin(), CIYL.end(), cY) != CIYL.end())
		{
			X bX = getBackXfromMXR(betaPostforZL(cY), alphaPostforZR(RMXL[RMXL.size() - 1]._e));

			rMsg._aMX = ix;
			_MX.push_back(ix);
			_MXL.push_back(ix);
			if (!bX.empty() && cmpXEndInc(bX, RMXL[RMXL.size() - 1]))
			{
				_MXL.erase(find(_MXL.begin(), _MXL.end(), RMXL[RMXL.size() - 1]));
				_MXR.erase(find(_MXR.begin(), _MXR.end(), bX));
				_MXL.push_back(bX);
				_MXR.push_back(RMXL[RMXL.size() - 1]);
			}

			rMsg._aMY = cY;
			_MY.push_back(cY);
			_MYL.push_back(cY);

			rMsg._bIY = cY;
			_IY.erase(find(_IY.begin(), _IY.end(), cY));
		}
		else if (find(CIYR.begin(), CIYR.end(), cY) != CIYR.end())
		{
			X fX = RMXL[RMXL.size() - 1];
			rMsg._aMX = ix;
			_MX.push_back(ix);
			_MXL.push_back(ix);
			_MXL.erase(find(_MXL.begin(), _MXL.end(), fX));
			_MXR.push_back(fX);
			
			rMsg._aMY = cY;
			_MY.push_back(cY);
			_MYR.push_back(cY);

			rMsg._bIY = cY;
			_IY.erase(find(_IY.begin(), _IY.end(), cY));
		}
		else
		{
			Y bPost = betaPostforZL(cY);
			X bX = getBackXfromMXR(bPost, aPost);
			X fX = RMXL[RMXL.size() - 1];

			rMsg._aMX = ix;
			_MX.push_back(ix);
			_MXL.push_back(ix);
			_MXL.erase(find(_MXL.begin(), _MXL.end(), fX));
			_MXR.push_back(fX);
			_MXR.erase(find(_MXR.begin(), _MXR.end(), bX));
			_MXL.push_back(bX);

			rMsg._aMY = cY;
			_MY.push_back(cY);
			_MYL.push_back(cY);

			rMsg._bIY = cY;
			_IY.erase(find(_IY.begin(), _IY.end(), cY));

		}
	}
}


Msg TreeNode::insertXintoNodeR(Msg msg)
{
	Msg rMsg;
	rMsg._t1 = msg._t1;
	rMsg._t2 = msg._t2;
	rMsg._stableYCount = msg._stableYCount;
	rMsg._aX = msg._aX;
	_X.push_back(msg._aX);

	if (msg._aX._e > maxY())//equal to t2>maxY()
	{
		rMsg._t1 = betaPreforZ(msg._aX._s);
		rMsg._aTX = msg._aX;
		_TX.push_back(msg._aX);
	}
	else
	{
		//deal with the aX
		updateStableCount(rMsg);
		if (rMsg._stableYCount > msg._stableYCount)
		{
			//EE and ES available
			performXESEE(msg, rMsg);
		}
		else
		{
			//rMsg._stableYCount == msg._stableYCount, no new matched X, but may be replace
			if (!msg._bIY.empty())
			{
				//success in R
				//t1 t2 stablecount keeps	
				rMsg._aMX = msg._aX;
				_MX.push_back(msg._aX);
				_MXR.push_back(msg._aX);

				rMsg._aMY = msg._aMY;
				_MY.push_back(msg._aMY);
				_MYR.push_back(msg._aMY);

				rMsg._bIY = msg._bIY;
				_IY.erase(find(_IY.begin(), _IY.end(), msg._bIY));
			}
			else
			{
				if (find(_MXR.begin(), _MXR.end(), msg._bMX) != _MXR.end() || msg._aX == msg._aIX)
				{
					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXR.push_back(msg._aX);

					rMsg._bMX = msg._bMX;
					_MX.erase(find(_MX.begin(), _MX.end(), msg._bMX));
					_MXR.erase(find(_MXR.begin(), _MXR.end(), msg._bMX));

					rMsg._aIX = msg._aIX;
					_IX.push_back(msg._aIX);
				}
				else
				{
					performXESEE(msg, rMsg);
				}
			}
		}
	}

	return rMsg;
}


void TreeNode::performXESEE(Msg msgInChild, Msg & rMsg)
{
	X ix = rMsg._aX;
	vector<X> RMXL, RMXR;
	vector<Y> CIYL, CIYR;
	Y aPost = alphaPostforZR(ix._e);
	getXReachableSetinR(aPost, RMXR, CIYR);
	RMXR.push_back(ix);

	sort(RMXR.begin(), RMXR.end(), cmpXBeginDec);
	Y bPre = betaPreforZL(RMXR[RMXR.size() - 1]._s);
	getXReachableSetinL(bPre, RMXL, CIYL);

	rMsg._t1 = bPre;
	rMsg._t2 = aPost;
	updateStableCount(rMsg);

	if (CIYL.empty() && CIYR.empty())
	{
		//replace
		X rX = getMinWeightRX(RMXL, RMXR);
		if (find(_MXL.begin(), _MXL.end(), rX) != _MXL.end())
		{
			Y bPost = betaPostforZL(rX._s);
			X bX = getBackXfromMXR(bPost, aPost);

			rMsg._aMX = ix;
			_MX.push_back(ix);
			_MXR.push_back(ix);
			_MXR.erase(find(_MXR.begin(), _MXR.end(), bX));
			_MXL.push_back(bX);

			rMsg._bMX = rX;
			_MX.erase(find(_MX.begin(), _MX.end(), rX));
			_MXL.erase(find(_MXL.begin(), _MXL.end(), rX));

			rMsg._aIX = rX;
			_IX.push_back(rX);
		}
		else
		{
			rMsg._aMX = ix;
			_MX.push_back(ix);
			_MXR.push_back(ix);

			rMsg._bMX = rX;
			_MX.erase(find(_MX.begin(), _MX.end(), rX));
			_MXR.erase(find(_MXR.begin(), _MXR.end(), rX));

			rMsg._aIX = rX;
			_IX.push_back(rX);
		}

	}
	else
	{
		Y cY = getMaxWeightCY(CIYL, CIYR);
		if (find(CIYR.begin(), CIYR.end(), cY) != CIYR.end())
		{
			rMsg._aMX = ix;
			_MX.push_back(ix);
			_MXR.push_back(ix);

			rMsg._aMY = cY;
			_MY.push_back(cY);
			_MYR.push_back(cY);

			rMsg._bIY = cY;
			_IY.erase(find(_IY.begin(), _IY.end(), cY));
		}
		else
		{
			Y bPost = betaPostforZL(cY);
			X bX = getBackXfromMXR(bPost, aPost);

			rMsg._aMX = ix;
			_MX.push_back(ix);
			_MXR.push_back(ix);
			_MXR.erase(find(_MXR.begin(), _MXR.end(), bX));
			_MXL.push_back(bX);

			rMsg._aMY = cY;
			_MY.push_back(cY);
			_MYL.push_back(cY);

			rMsg._bIY = cY;
			_IY.erase(find(_IY.begin(), _IY.end(), cY));
		}
	}
}