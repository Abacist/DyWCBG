#include"Tree.h"

TreeNode::TreeNode(vector<Y> vY)
{
	_Y = vY;
	_IY = vY;
	_rightChild = NULL;
	_leftChild = NULL;
	_parent = NULL;
}


Y TreeNode::maxY()
{
	sort(_Y.begin(), _Y.end(), cmpYValueDec);
	return _Y[0];
}

Y TreeNode::minY()
{
	sort(_Y.begin(), _Y.end(), cmpYValueInc);
	return _Y[0];
}

Y TreeNode::alphaPostforZR(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXR;
	tempY = _MYR;
	sort(tempY.begin(), tempY.end(), cmpYValueInc);
	sort(tempZ.begin(), tempZ.end(), cmpXEndInc);
	Y tY;
	tY._value = INT_MAX;
	for (int i = tempZ.size() - 1; i >= 0; i--)
	{
		if (tempY[i] == tempZ[i]._e && tempY[i] >= y)
		{
			tY = tempY[i];
		}
	}
	if (tY.empty() && !tempY.empty() && *(tempY.end() - 1) > y && !tempZ.empty() && tempZ.size() == tempY.size())
	{
		//return tempY[tempY.size() - 1];
		return tempZ[tempZ.size() - 1]._e;
	}
	return tY;
}

Y TreeNode::alphaPreforZR(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXR;
	tempY = _MYR;
	sort(tempY.begin(), tempY.end(), cmpYValueInc);
	sort(tempZ.begin(), tempZ.end(), cmpXEndInc);
	Y tY;
	for (int i = 0; i < tempZ.size(); i++)
	{
		if (tempY[i] == tempZ[i]._e && tempY[i] < y)
		{
			tY = tempY[i];
		}
	}
	return tY;
}

void TreeNode::splitNode(X insertedX)
{
	//split


	//update sets
}


int TreeNode::verifyNodeInvariants()
{
	{
		vector<X> vZ;
		formGloverMatching(_X, _Y, vZ);
		if (vZ.size() != _MX.size())
			return 1;
	}

	{
		for (int i = 0; i < _TX.size(); i++)
		{
			if (_TX[i]._e <= maxY())
			{
				return 2;
			}
		}
		for (int i = 0; i < _IX.size(); i++)
		{
			if (_IX[i]._e > maxY())
			{
				return 2;
			}
		}
	}

	{
		vector<X> TML;
		for (int i = 0; i < _MX.size(); i++)
		{
			if (_MX[i]._e > maxY())
			{
				TML.push_back(_MX[i]);
			}
		}
		for (int i = 0; i < TML.size(); i++)
		{
			for (int j = 0; j < _IX.size(); j++)
			{
				vector<X> tempX = _MX;
				vector<X> vZ;
				tempX.push_back(_IX[j]);
				tempX.erase(find(tempX.begin(), tempX.end(), TML[i]));
				formGloverMatching(tempX, _Y, vZ);
				if (vZ.size() == _MX.size())
				{
					return 3;
				}
			}
		}
	}

	{
		vector<X> TML;
		for (int i = 0; i < _MX.size(); i++)
		{
			if (_MX[i]._e > maxY())
			{
				TML.push_back(_MX[i]);
			}
		}
		for (int i = 0; i < TML.size(); i++)
		{
			for (int j = 0; j < _TX.size(); j++)
			{
				if (cmpXEndInc(_TX[j], TML[i]))
				{
					vector<X> tempX = _MX;
					vector<X> vZ;
					tempX.push_back(_TX[j]);
					tempX.erase(find(tempX.begin(), tempX.end(), TML[i]));
					formGloverMatching(tempX, _Y, vZ);
					if (vZ.size() == _MX.size())
					{
						return 4;
					}
				}
			}
		}
	}

	{
		vector<X> XmT = _MX;
		for (int i = 0; i < _IX.size(); i++)
		{
			XmT.push_back(_IX[i]);
		}
		vector<X> vX;
		vector<Y> vY;
		formPlaxtonMWM(XmT, _Y, vX, vY);
		sort(_MX.begin(), _MX.end(), cmpXID);
		sort(vX.begin(), vX.end(), cmpXID);
		sort(_MY.begin(), _MY.end(), cmpYValueInc);
		sort(vY.begin(), vY.end(), cmpYValueInc);
		if (_MX.size() != vX.size())
		{
			return 5;
		}
		else
		{
			for (int i = 0; i < _MX.size(); i++)
			{
				if (_MX[i] != vX[i])
				{
					return 5;
				}
			}
		}

		if (_MY.size() != vY.size())
		{
			return 6;
		}
		else
		{
			for (int i = 0; i < _MY.size(); i++)
			{
				if (_MY[i] != vY[i])
				{
					return 6;
				}
			}
		}

	}
	return 0;
}