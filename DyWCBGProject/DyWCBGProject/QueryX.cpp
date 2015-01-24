#include"Tree.h"


Y Tree::queryXMate(int id)
{
	//Glover Info has been maintained
	X x;
	x._id = id;
	vector<X>::iterator it = find(_root->_MX.begin(), _root->_MX.end(), x);
	if (it == _root->_MX.end())
	{
		Y y;
		return y;
	}
	else
	{
		x = *it;
		return _root->searchXMateRecur(x);
	}
}


Y TreeNode::searchXMateRecur(X x, int delta)//delta means how many X need to be matched in the left of x in curNode
{
	if (_leftChild == NULL)
	{
		vector<X> leftMX;
		for (int i = 0; i < _MX.size(); i++)
		{
			if (cmpXEndInc(_MX[i], x))
			{
				leftMX.push_back(_MX[i]);
			}
		}
		return _Y[delta + leftMX.size()];
	}
	else
	{
		Y midY = _leftChild->maxY();
		if (x._e <= midY)
		{
			//match in P's left
			return _leftChild->searchXMateRecur(x, delta);
		}
		else if (x._s > midY)
		{
			vector<X> leftTM;
			for (int i = 0; i < _leftChild->_TX.size(); i++)//all matched in P's right part
			{
				if (cmpXEndInc(_leftChild->_TX[i], x))
				{
					leftTM.push_back(_leftChild->_TX[i]);
				}
			}
			vector<X> TMin;
			for (int i = 0; i < _leftChild->_MX.size(); i++)
			{
				if (cmpXEndInc(x, _leftChild->_MX[i]))
				{
					TMin.push_back(_leftChild->_MX[i]);
				}
			}
			delta = delta - (int)TMin.size() - (int)_leftChild->_IY.size();
			if (delta < 0)
			{
				delta = 0;
			}
			delta = delta + (int)leftTM.size();
			if (delta < 0)
			{
				//delta = 0;
				throw new exception();
			}
			return _rightChild->searchXMateRecur(x, delta);
		}
		else
		{
			//x.s<=midY and x.e>midY
			if (find(_MXR.begin(), _MXR.end(), x) != _MXR.end())
			{
				//still match in right
				vector<X> leftTM;
				for (int i = 0; i < _leftChild->_TX.size(); i++)
				{
					if (cmpXEndInc(_leftChild->_TX[i], x))
					{
						leftTM.push_back(_leftChild->_TX[i]);
					}
				}
				vector<X> TMin;
				for (int i = 0; i < _leftChild->_MX.size(); i++)
				{
					if (cmpXEndInc(x, _leftChild->_MX[i]))
					{
						TMin.push_back(_leftChild->_MX[i]);
					}
				}
				delta = delta - (int)TMin.size() - (int)_leftChild->_IY.size();
				if (delta < 0)
				{
					delta = 0;
				}
				delta = delta + (int)leftTM.size();
				return _rightChild->searchXMateRecur(x, delta);
			}
			else
			{
				vector<X> leftMX;
				for (int i = 0; i < _MXL.size(); i++)
				{
					if (cmpXEndInc(_MXL[i], x))
					{
						leftMX.push_back(_MXL[i]);
					}
				}
				int temp = delta + leftMX.size();
				if (temp >= _leftChild->_Y.size())
				{
					//match in right
					vector<X> leftTM;
					for (int i = 0; i < _leftChild->_TX.size(); i++)
					{
						if (cmpXEndInc(_leftChild->_TX[i], x))
						{
							leftTM.push_back(_leftChild->_TX[i]);
						}
					}
					return _rightChild->searchXMateRecur(x, temp - (int)_leftChild->_Y.size() + (int)leftTM.size());
				}
				else
				{
					//match in left
					return _leftChild->searchXMateRecur(x, delta);
				}
			}
		}
	}
}