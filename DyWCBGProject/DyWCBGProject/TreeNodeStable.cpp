#include"Tree.h"


void TreeNode::updatet1t2inLeafX(Msg & msg)
{
	//update t1, t2
	msg._t1 = msg._aX._s;
	msg._t2 = msg._aX._e;

	Y temp = alphaPostforZRS(msg._aX._e);
	if (cmpYValueInc(msg._t2, temp))
	{
		msg._t2 = temp;
	}

	msg._stableYNumBetweent1t2 = 0;
	for (int i = 0; i < _MYS.size(); i++)
	{
		if (_MYS[i] <= msg._t2)
		{
			msg._stableYNumBetweent1t2++;
		}
	}
}

void TreeNode::updateStableSetinLeaf(Msg msg)
{
	if (!msg._bIY.empty() && msg._aX._e <= maxY() || !msg._aTX.empty() && msg._aX._e <= maxY())
	{
		vector<Y> cIYS, IYS = _IYS;
		for (int i = 0; i < IYS.size(); i++)
		{
			if (IYS[i] <= msg._t2)
			{
				cIYS.push_back(IYS[i]);
			}
		}
		sort(cIYS.begin(), cIYS.end(), cmpYWeightInc);
		_MXS.push_back(msg._aX);
		_MXRS.push_back(msg._aX);
		_MYS.push_back(cIYS[cIYS.size() - 1]);
		_MYRS.push_back(cIYS[cIYS.size() - 1]);
		_IYS.erase(find(_IYS.begin(), _IYS.end(), cIYS[cIYS.size() - 1]));
	}
	else if (!msg._aIX.empty())
	{
		_MXS.push_back(msg._aX);
		_MXRS.push_back(msg._aX);
		_MXS.erase(find(_MXS.begin(), _MXS.end(), msg._aIX));
		_MXRS.erase(find(_MXRS.begin(), _MXRS.end(), msg._aIX));
	}
}

Y TreeNode::alphaPostforZLS(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXLS;
	tempY = _MYLS;
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


Y TreeNode::alphaPostforZRS(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXRS;
	tempY = _MYRS;
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

Y TreeNode::betaPreforZLS(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXLS;
	tempY = _MYLS;
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

Y TreeNode::alphaPreforZRS(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXRS;
	tempY = _MYRS;
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


Y TreeNode::betaPostforZLS(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXLS;
	tempY = _MYLS;
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
//
//vector<Y> TreeNode::getIYS()
//{
//	vector<Y> IYS;
//	for (int i = 0; i < _IY.size(); i++)
//	{
//		if (find(_MYS.begin(), _MYS.end(), _IY[i]) == _MYS.end())
//		{
//			IYS.push_back(_IY[i]);
//		}
//	}
//	return IYS;
//}