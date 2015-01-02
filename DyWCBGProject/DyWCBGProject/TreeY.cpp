#include"Tree.h"


Msg TreeNode::insertYintoLeaf(Y y)
{
	Msg msg;
	msg._aY = y;
	_Y.push_back(y);

	if (_X.empty())
	{
		_IY.push_back(y);
		msg._aIY = y;
		return msg;
	}
	else
	{
		vector<X> CIX, CTX;
		Y aPre = alphaPreforZR(y);
		for (int i = 0; i < _IX.size(); i++)
		{
			if (/*!aPre.empty() && */_IX[i]._e >= aPre/* || aPre.empty()*/)
			{
				CIX.push_back(_IX[i]);
			}
		}
		CTX = _TX;
		if (CIX.empty() && CTX.empty())
		{
			//calculate replaceable set RMY
			vector<Y> RMY;

			for (int i = 0; i < _MYR.size(); i++) //in leaf, MYR == MY
			{
				if (/*!aPre.empty() && */_MYR[i] >= aPre /*|| aPre.empty()*/)
				{
					RMY.push_back(_MYR[i]);
				}
			}

			RMY.push_back(y);
			sort(RMY.begin(), RMY.end(), cmpYWeightInc);
			Y ry = RMY[0];

			_MY.push_back(y);
			_MYR.push_back(y);
			msg._aMY = y;

			_MY.erase(find(_MY.begin(), _MY.end(), ry));
			_MYR.erase(find(_MYR.begin(), _MYR.end(), ry));
			msg._bMY = ry;

			_IY.push_back(ry);
			msg._aIY = ry;

			return msg;
		}
		else
		{
			if (!CIX.empty())
			{
				sort(CIX.begin(), CIX.end(), cmpXWeightInc);
				X cx = CIX[CIX.size() - 1];

				_MX.push_back(cx);
				_MXR.push_back(cx);
				msg._aMX = cx;

				_MY.push_back(y);
				_MYR.push_back(y);
				msg._aMY = y;
				
				_IX.erase(find(_IX.begin(), _IX.end(), cx));
				msg._bIX = cx;
				return msg;
			}
			else
			{
				//CTX not empty
				sort(CTX.begin(), CTX.end(), cmpXEndInc);
				X cx = CTX[0];

				_MX.push_back(cx);
				_MXR.push_back(cx);
				msg._aMX = cx;

				_MY.push_back(y);
				_MYR.push_back(y);
				msg._aMY = y;

				_TX.erase(find(_TX.begin(), _TX.end(), cx));
				msg._bTX = cx;
				return msg;
			}
		}
	}
}


void Tree::insertYinTree(Y y)
{
	if (find(_root->_Y.begin(), _root->_Y.end(), y) != _root->_Y.end())
	{
		//already inserted
		return;
	}
	//TreeNode* curNode = locateLeaf(y);
	Msg msg = _root->insertYintoLeaf(y);

}
