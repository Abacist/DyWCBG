#include"Tree.h"


Msg TreeNode::insertXintoLeaf(X x)
{
	Msg msg;
	msg._aX = x;
	_X.push_back(x);
	if (_Y.empty())
	{
		_IX.push_back(x);
		msg._aIX = x;
		return msg;
	}
	else
	{
		vector<Y> CIY;
		Y aPost = alphaPostforZR(x._e);
		for (int i = 0; i < _IY.size(); i++)
		{
			if (_IY[i] <= aPost)
			{
					CIY.push_back(_IY[i]);
			}
		}
		if (CIY.empty())
		{
			//replace an X
			vector<X> RMX;
			for (int i = 0; i < _MXR.size(); i++)
			{
				if (/*!aPost.empty() && */_MXR[i]._e <= aPost)
				{
					RMX.push_back(_MXR[i]);
				}
			}
			RMX.push_back(x);

			sort(RMX.begin(), RMX.end(), cmpXEndInc);
			X maxEndX = *(RMX.end() - 1);
			if (maxEndX._e > maxY())//maxY in Y or maxY in MY/MYR? or they are equivalent?
			{
				//transfer
				_MX.push_back(x);
				_MXR.push_back(x);
				msg._aMX = x;

				_MX.erase(find(_MX.begin(), _MX.end(), maxEndX));
				_MXR.erase(find(_MXR.begin(), _MXR.end(), maxEndX));
				msg._bMX = maxEndX;

				_TX.push_back(maxEndX);
				msg._aTX = maxEndX;

				return msg;
			}
			else
			{
				//infeasible
				sort(RMX.begin(), RMX.end(), cmpXWeightInc);
				X rx = RMX[0];

				_MX.push_back(x);
				_MXR.push_back(x);
				msg._aMX = x;

				_MX.erase(find(_MX.begin(), _MX.end(), rx));
				_MXR.erase(find(_MXR.begin(), _MXR.end(), rx));
				msg._bMX = rx;

				_IX.push_back(rx);
				msg._aIX = rx;

				return msg;
			}	
		}
		else
		{
			sort(CIY.begin(), CIY.end(), cmpYWeightInc);
			//Y cY = CIY[CIY.size() - 1];
			Y cy = *(CIY.end() - 1);
			_MX.push_back(x);
			_MXR.push_back(x);
			msg._aMX = x;

			_MY.push_back(cy);
			_MYR.push_back(cy);
			msg._aMY = cy;

			_IY.erase(find(_IY.begin(), _IY.end(), cy));
			msg._bIY = cy;
		}
	}


	return msg;
}



void Tree::insertXinTree(X x)
{
	//TreeNode* curNode = locateLeaf(x);
	Msg msg = _root->insertXintoLeaf(x);
}