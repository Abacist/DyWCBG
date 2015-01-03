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

vector<Y> TreeNode::getYL()
{
	vector<Y> YL;
	if (_leftChild != NULL)
	{
		Y midY = _rightChild->minY();
		for (int i = 0; i < _Y.size(); i++)
		{
			if (_Y[i] >= midY)
			{
				YL.push_back(_Y[i]);
			}
		}
	}
	return YL;
}
vector<Y> TreeNode::getYR()
{
	vector<Y> YR;
	if (_leftChild != NULL)
	{
		Y midY = _rightChild->minY();
		for (int i = 0; i < _Y.size(); i++)
		{
			if (_Y[i] >= midY)
			{
				YR.push_back(_Y[i]);
			}
		}
	}
	else
	{
		YR = _Y;
	}
	return YR;
}

vector<Y> TreeNode::getIYL()
{
	vector<Y> IYL;
	vector<Y> YL = getYL();
	for (int i = 0; i < YL.size(); i++)
	{
		if (find(_IY.begin(), _IY.end(), YL[i]) != _IY.end())
		{
			IYL.push_back(YL[i]);
		}
	}
	return IYL;
}

vector<Y> TreeNode::getIYR()
{
	vector<Y> IYR;
	vector<Y> YR = getYR();
	for (int i = 0; i < YR.size(); i++)
	{
		if (find(_IY.begin(), _IY.end(), YR[i]) != _IY.end())
		{
			IYR.push_back(YR[i]);
		}
	}
	return IYR;
}

//aPost must exists in DW case
Y TreeNode::alphaPostforZR(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXR;
	tempY = _MYR;
	if (tempY.empty())
	{
		return y;
	}
	else
	{
		sort(tempY.begin(), tempY.end(), cmpYValueInc);
		sort(tempZ.begin(), tempZ.end(), cmpXEndInc);
		Y tY;
		//will not be empty
		if (y < tempY[0])
		{
			return y;
		}
		else
		{
			tY = tempZ[tempZ.size() - 1]._e;

			int i = 0;
			while (i + 1 <= tempY.size())
			{
				if (tempY[i] <= y)
				{
					i++;
				}
				else
				{
					break;
				}
			}
			i--;
			//found the maxmal Y0 such that Y0<=y


			for (; i + 2 <= tempY.size(); i++)
			{
				if (tempZ[i]._e < tempY[i + 1])
				{
					//tight
					tY = tempZ[i]._e;
					break;
				}
			}
			//else tY keeps tempZ[tempZ.size() - 1]._e;	

			if (tY < y)
			{
				tY = y;
			}//without this jude, RMX is right, but CIY is not right
			return tY;

		}
	}
	
}

//bPre must exists in DW case
Y TreeNode::betaPreforZL(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXL;
	tempY = _MYL;
	if (tempY.empty())
	{
		return y;
	}
	else
	{
		sort(tempY.begin(), tempY.end(), cmpYValueDec);
		sort(tempZ.begin(), tempZ.end(), cmpXBeginDec);
		Y tY;
		//will not be empty
		if (y > tempY[0])
		{
			return y;
		}
		else
		{
			tY = tempZ[tempZ.size() - 1]._s;

			int i = 0;
			while (i + 1 <= tempY.size())
			{
				if (tempY[i] >= y)
				{
					i++;
				}
				else
				{
					break;
				}
			}
			i--;
			//found the maxmal Y0 such that Y0>=y


			for (; i + 2 <= tempY.size(); i++)
			{
				if (tempZ[i]._s > tempY[i + 1])
				{
					//tight
					tY = tempZ[i]._s;
					break;
				}
			}
			//else tY keeps tempZ[tempZ.size() - 1]._s;	

			if (tY > y)
			{
				tY = y;
			}
			return tY;

		}
	}

}

//must exists
Y TreeNode::alphaPreforZR(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXR;
	tempY = _MYR;
	if (tempY.empty())
	{
		/*throw new exception();*/
		return y;
	}
	else
	{
		sort(tempY.begin(), tempY.end(), cmpYValueInc);
		sort(tempZ.begin(), tempZ.end(), cmpXEndInc);
		Y tY;
		if (y <= tempY[0])
		{
			return y;
		}
		else
		{
			tY = tempY[0];
			if (find(tempY.begin(), tempY.end(), y) == tempY.end())
			{
				tempY.push_back(y);
				sort(tempY.begin(), tempY.end(), cmpYValueInc);
			}
			int i = 0;
			int tightIndex = -1;
			while (true)
			{
				if (tempY[i] == y)
				{
					i--;
					break;
				}
				else
				{
					if (tempZ[i]._e < tempY[i + 1])
					{
						//tight
						tightIndex = i;
						//break;
					}
					i++;
				}
			}
			if (tightIndex != -1)
			{
				tY = tempY[tightIndex + 1];
			}
			return tY;

		}
	}
	
}

void TreeNode::splitNode(X x)
{
	//split
	vector<Y> leftVecY, rightVecY;
	int i = 0;

	// split the values into two, one to left leaf, the other to right leaf
	while (_Y[i]._value < x._s)
	{
		leftVecY.push_back(_Y[i]);
		i++;
	}
	while (i < _Y.size())
	{
		rightVecY.push_back(_Y[i]);
		i++;
	}
	// build the structure of the triple first, then insert the new variable
	TreeNode* leftChild = new TreeNode(leftVecY);
	TreeNode* rightChild = new TreeNode(rightVecY);

	//leftChild->_X = _X;	// copy the variables from the parent

	_leftChild = leftChild;
	_rightChild = rightChild;
	leftChild->_parent = this;
	rightChild->_parent = this;
	//update sets

	vector<X> allX = _X;
	_X.clear();
	_MX.clear();
	_MXL.clear();
	_MXR.clear();
	_IX.clear();
	_TX.clear();
	_MY.clear();
	_MYL.clear();
	_MYR.clear();
	_IY.clear();
	_IY = _Y;

	for (int i = 0; i < allX.size(); i++)
	{
		Msg msg = _leftChild->insertXintoLeaf(allX[i]);
		int flag1 = _leftChild->verifyNodeInvariants();

		insertXintoNodeL(msg);
		int flag = verifyNodeInvariants();
		if (flag == 0)
		{
			//cout << i << " pass!" << endl;
		}
		else
		{
			__debugbreak();
		}
	}
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

	{
		vector<X> tempX1 = _X;
		vector<X> tempX2 = _MX;
		for (int i = 0; i < _IX.size(); i++) tempX2.push_back(_IX[i]);
		for (int i = 0; i < _TX.size(); i++) tempX2.push_back(_TX[i]);
		if (tempX1.size() != tempX2.size())
		{
			return 101;
		}
		else
		{
			sort(tempX1.begin(), tempX1.end(), cmpXID);
			sort(tempX2.begin(), tempX2.end(), cmpXID);
			for (int i = 0; i < tempX1.size(); i++)
			{
				if (tempX1[i] != tempX2[i])
				{
					return 101;
				}
			}
		}
	}

	{
		vector<X> tempX1 = _MX;
		vector<X> tempX2 = _MXL;
		for (int i = 0; i < _MXR.size(); i++) tempX2.push_back(_MXR[i]);
		if (tempX1.size() != tempX2.size())
		{
			return 102;
		}
		else
		{
			sort(tempX1.begin(), tempX1.end(), cmpXID);
			sort(tempX2.begin(), tempX2.end(), cmpXID);
			for (int i = 0; i < tempX1.size(); i++)
			{
				if (tempX1[i] != tempX2[i])
				{
					return 102;
				}
			}
		}
	}

	{
		vector<Y> tempX1 = _Y;
		vector<Y> tempX2 = _MY;
		for (int i = 0; i < _IY.size(); i++) tempX2.push_back(_IY[i]);
		if (tempX1.size() != tempX2.size())
		{
			return 103;
		}
		else
		{
			sort(tempX1.begin(), tempX1.end(), cmpYValueDec);
			sort(tempX2.begin(), tempX2.end(), cmpYValueDec);
			for (int i = 0; i < tempX1.size(); i++)
			{
				if (tempX1[i] != tempX2[i])
				{
					return 103;
				}
			}
		}
	}

	{
		vector<Y> tempX1 = _MY;
		vector<Y> tempX2 = _MYL;
		for (int i = 0; i < _MYR.size(); i++) tempX2.push_back(_MYR[i]);
		if (tempX1.size() != tempX2.size())
		{
			return 103;
		}
		else
		{
			sort(tempX1.begin(), tempX1.end(), cmpYValueDec);
			sort(tempX2.begin(), tempX2.end(), cmpYValueDec);
			for (int i = 0; i < tempX1.size(); i++)
			{
				if (tempX1[i] != tempX2[i])
				{
					return 103;
				}
			}
		}
	}


	return 0;
}