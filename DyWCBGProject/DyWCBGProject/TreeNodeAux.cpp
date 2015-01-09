#include"Tree.h"

TreeNode::TreeNode(vector<Y> vY)
{
	_Y = vY;
	_IY = vY;
	_IYS = vY;
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
			if (_Y[i] < midY)
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
Y TreeNode::alphaPostforZL(Y y)
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


//must exists
Y TreeNode::betaPostforZL(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXL;
	tempY = _MYL;
	if (tempY.empty())
	{
		/*throw new exception();*/
		return y;
	}
	else
	{
		sort(tempY.begin(), tempY.end(), cmpYValueDec);
		sort(tempZ.begin(), tempZ.end(), cmpXBeginDec);
		Y tY;
		if (y >= tempY[0])
		{
			return y;
		}
		else
		{
			tY = tempY[0];
			if (find(tempY.begin(), tempY.end(), y) == tempY.end())
			{
				tempY.push_back(y);
				sort(tempY.begin(), tempY.end(), cmpYValueDec);
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
					if (tempZ[i]._s > tempY[i + 1])
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

vector<X> TreeNode::getReachableSetinLeftPart(X x)
{
	vector<X> allX = _MXL;
	vector<Y> allY = _MYL;

	vector<X> R;
	for (int i = 0; i < allX.size(); i++)
	{
		vector<X> tempX = allX;
		tempX.erase(find(tempX.begin(), tempX.end(), allX[i]));
		tempX.push_back(x);
		vector<X> MX;
		formGloverMatching(tempX, allY, MX);
		if (MX.size() == tempX.size())
		{
			R.push_back(allX[i]);
		}
	}
	return R;
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

	_MXS.clear();
	_MXLS.clear();
	_MXRS.clear();
	_MYS.clear();
	_MYLS.clear();
	_MYRS.clear();
	_IYS = _Y;

	for (int i = 0; i < allX.size(); i++)
	{
		Msg msg = _leftChild->insertXintoLeaf(allX[i]);
		//int flag1 = _leftChild->verifyNodeInvariants();

		insertXintoNodeL(msg);
		int flag1 = verifyNodeInvariants();
		int flag2 = _leftChild->verifyNodeInvariants();
		if (flag2 == 0 && flag1 == 0)
		{
			//cout << i << " pass!" << endl;
		}
		else
		{
			throw new exception();
		}
	}
}


void TreeNode::getStableSet(vector<X> & MXS, vector<Y> & MYS)
{
	MXS.clear();
	MYS.clear();
	vector<X> XS;
	Y maxy = maxY();
	for (int i = 0; i < _X.size(); i++)
	{
		if (_X[i]._e <= maxy)
		{
			XS.push_back(_X[i]);
		}
	}
	formPlaxtonMWM(XS, _Y, MXS, MYS);
}

//vector<X> TreeNode::getStableReachableSet(X x)
//{
//	vector<X> MXS;
//	vector<Y> MYS;
//	getStableSet(MXS, MYS);
//	vector<X> s;
//	for (int i = 0; i < MXS.size(); i++)
//	{
//		vector<X> tempX = MXS;
//		tempX.push_back(x);
//		tempX.erase(find(tempX.begin(), tempX.end(), MXS[i]));
//		vector<X> vZ;
//		formGloverMatching(tempX, MYS, vZ);
//		if (tempX.size() == vZ.size())
//		{
//			s.push_back(MXS[i]);
//		}
//	}
//	return s;
//}


void TreeNode::getCompensableYL(X x, Y t1, Y t2, int stableCountinChild, vector<Y> & CIYL, vector<Y> & CIYR, vector<Y> & CIYL2)
{
	CIYL.clear();
	CIYR.clear();
	CIYL2.clear();

	int allCount = 0;
	for (int i = 0; i < _MY.size(); i++)
	{
		if (_MY[i] >= t1 && _MY[i] <= t2)
		{
			allCount++;
		}
	}

	if (t2 < _rightChild->minY() && stableCountinChild == allCount)
	{
		//directly calculate
		for (int i = 0; i < _IY.size(); i++)
		{
			if (_IY[i] >= t1 && _IY[i] <= t2)
			{
				CIYL.push_back(_IY[i]);
			}
		}
	}
	else
	{
		//EE and ES
		Y bPre = betaPreforZL(x._s);
		vector<Y> IYL = getIYL();
		for (int i = 0; i < IYL.size(); i++)
		{
			if (IYL[i] >= bPre)
			{
				CIYL.push_back(IYL[i]);
			}
		}
		vector<X> RMXL;
		for (int i = 0; i < _MXL.size(); i++)
		{
			if (_MXL[i]._s >= bPre)
			{
				RMXL.push_back(_MXL[i]);
			}
		}
		RMXL.push_back(x);

		sort(RMXL.begin(), RMXL.end(), cmpXEndInc);
		X maxEnd = RMXL[RMXL.size() - 1];

		Y aPost = alphaPostforZR(maxEnd._e);
		vector<Y> IYR = getIYR();
		for (int i = 0; i < IYR.size(); i++)
		{
			if (IYR[i] <= aPost)
			{
				CIYR.push_back(IYR[i]);
			}
		}

		vector<X> RMXR;
		for (int i = 0; i < _MXR.size(); i++)
		{
			if (_MXR[i]._e <= aPost)
			{
				RMXR.push_back(_MXR[i]);
			}
		}

		if (!RMXR.empty())
		{
			sort(RMXR.begin(), RMXR.end(), cmpXBeginDec);
			X minBegin = RMXR[RMXR.size() - 1];

			vector<X> RMXL2;
			Y bPre1 = betaPreforZL(minBegin._s);

			for (int i = 0; i < IYL.size(); i++)
			{
				if (IYL[i] >= bPre1)
				{
					if (find(CIYL.begin(), CIYL.end(), IYL[i]) == CIYL.end())
					{
						CIYL2.push_back(IYL[i]);
					}
				}
			}
		}
		
	}
}

void TreeNode::getCompensableYLForce(X x, vector<Y> & CIYL, vector<Y> & CIYR, vector<Y> & CIYL2)
{
	CIYL.clear();
	CIYR.clear();
	CIYL2.clear();
	vector<X> tempX;
	vector<Y> tempY;
	//CIYL directly
	tempX = _MXL;
	tempX.push_back(x);
	tempY = _MYL;
	vector<Y> IYL = getIYL();
	for (int i = 0; i < IYL.size(); i++)
	{
		vector<Y> tempY1 = tempY;
		tempY1.push_back(IYL[i]);
		vector<X> vZ;
		formGloverMatching(tempX, tempY1, vZ);
		if (vZ.size() == tempY1.size())
		{
			CIYL.push_back(IYL[i]);
		}
	}
	//CIYR
	tempX = _MX;
	tempX.push_back(x);
	tempY = _MY;
	vector<Y> IYR = getIYR();
	for (int i = 0; i < IYR.size(); i++)
	{
		vector<Y> tempY1 = tempY;
		tempY1.push_back(IYR[i]);
		vector<X> vZ;
		formGloverMatching(tempX, tempY1, vZ);
		if (vZ.size() == tempY1.size())
		{
			CIYR.push_back(IYR[i]);
		}
	}
	//CIYL1
	tempX = _MX;
	tempX.push_back(x);
	tempY = _MY;
	vector<Y> IYL2 = getIYL();
	for (int i = 0; i < IYL2.size(); i++)
	{
		vector<Y> tempY1 = tempY;
		tempY1.push_back(IYL2[i]);
		vector<X> vZ;
		formGloverMatching(tempX, tempY1, vZ);
		if (vZ.size() == tempY1.size())
		{
			if (find(CIYL.begin(), CIYL.end(), IYL2[i]) == CIYL.end())
			{
				CIYL2.push_back(IYL2[i]);
			}
		}
	}
}

int TreeNode::verifyCIY(vector<Y> CIYLCorrect, vector<Y> CIYRCorrect, vector<Y> CIYL2Correct, vector<Y> CIYL, vector<Y> CIYR, vector<Y> CIYL2)
{
	if (CIYLCorrect.size() != CIYL.size())
	{
		return 1;
	}
	else
	{
		sort(CIYLCorrect.begin(), CIYLCorrect.end(), cmpYValueInc);
		sort(CIYL.begin(), CIYL.end(), cmpYValueInc);
		for (int i = 0; i < CIYL.size(); i++)
		{
			if (CIYL[i] != CIYLCorrect[i])
			{
				return 1;
			}
		}
	}
	if (CIYRCorrect.size() != CIYR.size())
	{
		return 2;
	}
	else
	{
		sort(CIYRCorrect.begin(), CIYRCorrect.end(), cmpYValueInc);
		sort(CIYR.begin(), CIYR.end(), cmpYValueInc);
		for (int i = 0; i < CIYR.size(); i++)
		{
			if (CIYR[i] != CIYRCorrect[i])
			{
				return 2;
			}
		}
	}
	if (CIYL2Correct.size() != CIYL2.size())
	{
		return 3;
	}
	else
	{
		sort(CIYL2Correct.begin(), CIYL2Correct.end(), cmpYValueInc);
		sort(CIYL2.begin(), CIYL2.end(), cmpYValueInc);
		for (int i = 0; i < CIYL2.size(); i++)
		{
			if (CIYL2[i] != CIYL2Correct[i])
			{
				return 3;
			}
		}
	}
	return 0;
}


int TreeNode::verifyNodeInvariants()
{
	//return 0;
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
		vector<Y> tempY;
		vector<X> vZ;
		if (_MXL.size() != _MYL.size() || _MXR.size() != _MYR.size())
			return 7;
		tempY = _MYL;
		formGloverMatching(_MXL, tempY, vZ);
		if (vZ.size() != _MXL.size())
			return 7;
		tempY = _MYR;
		formGloverMatching(_MXR, tempY, vZ);
		if (vZ.size() != _MXR.size())
			return 7;
	}

	{
		if (_rightChild != NULL)
		{
			vector<X> TML;
			vector<X> TMR;
			vector<Y> YL;
			vector<Y> YR;
			for (int i = 0; i < _MXL.size(); i++)
			{
				if (_MXL[i]._e >= _rightChild->minY())
				{
					TML.push_back(_MXL[i]);
				}
			}
			for (int i = 0; i < _MXR.size(); i++)
			{
				if (_MXR[i]._s < _rightChild->minY())
				{
					TMR.push_back(_MXR[i]);
				}
			}
			YL = _MYL;
			YR = _MYR;
			if (!TML.empty() && !TMR.empty())
			{
				for (int i = 0; i < TML.size(); i++)
				{
					for (int j = 0; j < TMR.size(); j++)
					{
						if (cmpXEndInc(TMR[j], TML[i]))
						{
							vector<X> vZL, vZR;
							vector<X> tempZL = _MXL;
							vector<X> tempZR = _MXR;
							tempZL.push_back(TMR[j]);
							tempZR.push_back(TML[i]);
							tempZR.erase(find(tempZR.begin(), tempZR.end(), TMR[j]));
							tempZL.erase(find(tempZL.begin(), tempZL.end(), TML[i]));
							vector<X> ZLNew, ZRNew;
							formGloverMatching(tempZL, YL, vZL);
							formGloverMatching(tempZR, YR, vZR);
							if (vZL.size() == _MXL.size() && vZR.size() == _MXR.size())
							{
								return 8;
							}
						}
					}
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

	{
		//if (_leftChild == NULL)
		{
			vector<X> MXS;
			vector<Y> MYS;
			getStableSet(MXS, MYS);
			sort(MXS.begin(), MXS.end(), cmpXID);
			sort(_MXS.begin(), _MXS.end(), cmpXID);
			if (MXS.size() != _MXS.size())
			{
				return 201;
			}
			else
			{
				for (int i = 0; i < MXS.size(); i++)
				{
					if (MXS[i] != _MXS[i])
					{
						return 201;
					}
				}
			}
			sort(MYS.begin(), MYS.end(), cmpYValueInc);
			sort(_MYS.begin(), _MYS.end(), cmpYValueInc);
			if (MYS.size() != _MYS.size())
			{
				return 201;
			}
			else
			{
				for (int i = 0; i < MYS.size(); i++)
				{
					if (MYS[i] != _MYS[i])
					{
						return 201;
					}
				}
			}
		}
	}

	{
		vector<Y> tempY;
		vector<X> vZ;
		if (_MXRS.size() != _MYRS.size() || _MXLS.size() != _MYLS.size())
			return 202;
		tempY = _MYRS;
		formGloverMatching(_MXRS, tempY, vZ);
		if (vZ.size() != _MXRS.size())
			return 202;
		tempY = _MYLS;
		formGloverMatching(_MXLS, tempY, vZ);
		if (vZ.size() != _MXLS.size())
			return 202;
	}

	{
		if (_rightChild != NULL)
		{
			vector<X> TML;
			vector<X> TMR;
			vector<Y> YL;
			vector<Y> YR;
			for (int i = 0; i < _MXLS.size(); i++)
			{
				if (_MXLS[i]._e >= _rightChild->minY())
				{
					TML.push_back(_MXLS[i]);
				}
			}
			for (int i = 0; i < _MXRS.size(); i++)
			{
				if (_MXRS[i]._s < _rightChild->minY())
				{
					TMR.push_back(_MXRS[i]);
				}
			}
			YL = _MYLS;
			YR = _MYRS;
			if (!TML.empty() && !TMR.empty())
			{
				for (int i = 0; i < TML.size(); i++)
				{
					for (int j = 0; j < TMR.size(); j++)
					{
						if (cmpXEndInc(TMR[j], TML[i]))
						{
							vector<X> vZL, vZR;
							vector<X> tempZL = _MXLS;
							vector<X> tempZR = _MXRS;
							tempZL.push_back(TMR[j]);
							tempZR.push_back(TML[i]);
							tempZR.erase(find(tempZR.begin(), tempZR.end(), TMR[j]));
							tempZL.erase(find(tempZL.begin(), tempZL.end(), TML[i]));
							vector<X> ZLNew, ZRNew;
							formGloverMatching(tempZL, YL, vZL);
							formGloverMatching(tempZR, YR, vZR);
							if (vZL.size() == _MXLS.size() && vZR.size() == _MXRS.size())
							{
								return 203;
							}
						}
					}
				}
			}

		}
	}


	return 0;
}