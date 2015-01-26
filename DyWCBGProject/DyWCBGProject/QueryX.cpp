#include"Tree.h"

void getGloverInfo(vector<X> allX, vector<Y> allY, vector<Edge>& M, vector<Y> & IY)//no unmatched X
{
	M.clear();
	IY.clear();
	vector<X> XX = allX;
	vector<Y> YY = allY;
	M.clear();
	sort(YY.begin(), YY.end(), cmpYValueInc);

	for (int i = 0; i < YY.size(); i++)
	{
		vector<X> selectedX;
		for (int j = 0; j < XX.size(); j++)
		{
			if (XX[j]._s <= YY[i] && XX[j]._e >= YY[i])
			{
				selectedX.push_back(XX[j]);
			}
		}

		if (selectedX.size() == 0)
		{
			IY.push_back(YY[i]);
			continue;
		}
		else
		{
			X x = selectedX[0];
			for (int j = 0; j < selectedX.size(); j++)
			{
				if (cmpXEndInc(selectedX[j], x))
				{
					x = selectedX[j];
				}
			}
			Edge e(x, YY[i]);
			M.push_back(e);
			vector<X>::iterator it = find(XX.begin(), XX.end(), x);
			XX.erase(it);
		}
	}
	return;
}


void Tree::constructGloverInfo()
{
	constructGloverInfo(_root, _root->_MX, _root->_MY);
}

void Tree::constructGloverInfo(TreeNode* curNode, vector<X> MX, vector<Y> MY)
{
	curNode->_YG = MY;
	curNode->_XG = MX;
	vector<X> tempMX;
	Y ye = curNode->maxY();
	for (int i = 0; i < MX.size(); i++)
	{
		if (MX[i]._e > ye)
		{
			curNode->_TXG.push_back(MX[i]);
		}
		else
		{
			tempMX.push_back(MX[i]);
		}
	}
	curNode->_MXG = tempMX;
	getGloverInfo(tempMX, MY, curNode->_MatchingG, curNode->_IYG);
	Y midY;
	if (curNode->_leftChild != NULL)
	{
		midY = curNode->_leftChild->maxY();
	}
	for (int i = 0; i < curNode->_MatchingG.size(); i++)
	{
		curNode->_MYG.push_back(curNode->_MatchingG[i].y);
		if (curNode->_MatchingG[i].y <= midY)
		{
			curNode->_MXLG.push_back(curNode->_MatchingG[i].x);
			curNode->_MYLG.push_back(curNode->_MatchingG[i].y);
		}
		else
		{
			curNode->_MXRG.push_back(curNode->_MatchingG[i].x);
			curNode->_MYRG.push_back(curNode->_MatchingG[i].y);
		}
	}
	for (int i = 0; i < curNode->_IYG.size(); i++)
	{
		if (curNode->_IYG[i] <= midY)
		{
			curNode->_IYLG.push_back(curNode->_IYG[i]);
		}
		else
		{
			curNode->_IYRG.push_back(curNode->_IYG[i]);
		}
	}
	if (curNode->_leftChild == NULL)
	{
		return;
	}
	else
	{
		vector<Y> MYL, MYR;
		vector<X> MXL, MXR;
		Y y0 = curNode->_leftChild->maxY();
		for (int i = 0; i < MY.size(); i++)
		{
			if (MY[i] <= y0)
			{
				MYL.push_back(MY[i]);
			}
			else
			{
				MYR.push_back(MY[i]);
			}
		}
		for (int i = 0; i < MX.size(); i++)
		{
			if (MX[i]._s <= y0)
			{
				MXL.push_back(MX[i]);
			}
			else
			{
				MXR.push_back(MX[i]);
			}
		}
		constructGloverInfo(curNode->_leftChild, MXL, MYL);
		constructGloverInfo(curNode->_rightChild, MXR, MYR);
		
	}

}


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
		//directly to a leaf
		vector<X> leftMX;
		for (int i = 0; i < _MXG.size(); i++)
		{
			if (cmpXEndInc(_MXG[i], x))
			{
				leftMX.push_back(_MXG[i]);
			}
		}
		int leftAll = leftMX.size() + delta;
		sort(_YG.begin(), _YG.end(), cmpYValueInc);
		return _YG[leftAll];
	}
	else
	{
		Y midY = _leftChild->maxY();
		if (x._e <= midY)
		{
			int tempL = getCount(x, delta);
			delta = delta + tempL;
			return _leftChild->searchXMateRecur(x, delta);
		}
		else if (x._s > midY)
		{
			//must match in right
			vector<X> FXL, FXR;
			for (int i = 0; i < _MXLG.size(); i++)
			{
				if (_MXLG[i]._e > midY)
				{
					FXL.push_back(_MXLG[i]);
				}
			}
			for (int i = 0; i < _MXRG.size(); i++)
			{
				if (_MXRG[i]._s <= midY)
				{
					FXR.push_back(_MXRG[i]);
				}
			}
			int tempL = 0;
			for (int i = 0; i < FXL.size(); i++)
			{
				if (cmpXEndInc(x, FXL[i]))
				{
					tempL++;
				}
			}
			int tempR = 0;
			for (int i = 0; i < FXR.size(); i++)
			{
				if (cmpXEndInc(FXR[i], x))
				{
					tempR++;
				}
			}
			delta = delta - (int)_IYLG.size() - tempL;
			if (delta < 0)
			{
				delta = 0;
			}
			delta = delta + tempR;
			return _rightChild->searchXMateRecur(x, delta);
		}
		else
		{
			if (find(_MXRG.begin(), _MXRG.end(), x) != _MXRG.end())
			{
				vector<X> FXL, FXR;
				for (int i = 0; i < _MXLG.size(); i++)
				{
					if (_MXLG[i]._e > midY)
					{
						FXL.push_back(_MXLG[i]);
					}
				}
				for (int i = 0; i < _MXRG.size(); i++)
				{
					if (_MXRG[i]._s <= midY)
					{
						FXR.push_back(_MXRG[i]);
					}
				}
				int tempL = 0;
				for (int i = 0; i < FXL.size(); i++)
				{
					if (cmpXEndInc(x, FXL[i]))
					{
						tempL++;
					}
				}
				int tempR = 0;
				for (int i = 0; i < FXR.size(); i++)
				{
					if (cmpXEndInc(FXR[i], x))
					{
						tempR++;
					}
				}
				delta = delta - (int)_IYLG.size() - tempL;
				if (delta < 0)
				{
					delta = 0;
				}
				delta = delta + tempR;
				return _rightChild->searchXMateRecur(x, delta);
			}
			else
			{
				vector<X> leftMX;
				for (int i = 0; i < _MXLG.size(); i++)
				{
					if (cmpXEndInc(_MXLG[i], x))
					{
						leftMX.push_back(_MXLG[i]);
					}
				}
				int temp = (int)leftMX.size() + delta;
				if (temp >= _leftChild->_YG.size())
				{
					vector<X> FXR;
					for (int i = 0; i < _MXRG.size(); i++)
					{
						if (_MXRG[i]._s <= midY)
						{
							FXR.push_back(_MXRG[i]);
						}
					}
					int tempR = 0;
					for (int i = 0; i < FXR.size(); i++)
					{
						if (cmpXEndInc(FXR[i], x))
						{
							tempR++;
						}
					}
					return _rightChild->searchXMateRecur(x, temp - (int)_leftChild->_YG.size() + tempR);
				}
				else
				{
					int tempL = getCount(x, delta);
					delta = delta + tempL;
					return _leftChild->searchXMateRecur(x, delta);
				}
			}
		}
	}
}



int TreeNode::getCount(X x, int delta)
{
	int result = 0;
	Y midY = _leftChild->maxY();
	vector<X> FXL;
	for (int i = 0; i < _MXLG.size(); i++)
	{
		if (_MXLG[i]._e > midY && _MXLG[i] != x)
		{
			FXL.push_back(_MXLG[i]);
		}
	}
	//Y ys = minY();
	//if (x._s < ys)
	//{
	//	for (int i = 0; i < FXL.size(); i++)
	//	{
	//		if (cmpXEndInc(x, FXL[i]))
	//		{
	//			continue;
	//		}
	//		else
	//		{
	//			Y bPre = betaPreforZLG(FXL[i]._s);
	//			if (bPre == ys)
	//			{
	//				result++;
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	//Y bPreX = betaPreforZLG(x._s);
	//	//Y bPostX = betaPostforZLG(x._s);
	//	int left = 0;
	//	for (int i = 0; i < FXL.size(); i++)
	//	{
	//		if (FXL[i]._s < x._s)
	//		{
	//			if (cmpXEndInc(FXL[i], x))
	//			{
	//				result++;
	//			}
	//			else
	//			{
	//				left++;
	//			}
	//		}
	//		else if (FXL[i]._s == x._s)
	//		{
	//			if (FXL[i]._id < x._s)
	//			{
	//				result++;
	//			}
	//		}
	//		/*if (FXL[i]._s < bPreX)
	//		{
	//			if (cmpXEndInc(x, FXL[i]))
	//			{
	//				leftbPre++;
	//			}
	//			else
	//			{
	//				result++;
	//			}
	//		}
	//		else
	//		{
	//			Y bPreF = betaPreforZLG(FXL[i]._s);
	//			if (bPreF == bPreX && cmpXEndInc(FXL[i], x))
	//			{
	//				result++;
	//			}
	//		}*/
	//	}
	//	if (delta < left)
	//	{
	//		result += (left - delta);
	//	}
	//}
	TreeNode* p = this;
	while (p->_parent != NULL)
	{
		p = p->_parent;
	}
	Y mY;
	for (int i = 0; i < p->_MatchingG.size(); i++)
	{
		if (p->_MatchingG[i].x == x)
		{
			mY = p->_MatchingG[i].y;
		}
	}
	for (int i = 0; i < FXL.size(); i++)
	{
		for (int j = 0; j < p->_MatchingG.size(); j++)
		{
			if (p->_MatchingG[j].x == FXL[i])
			{
				if (p->_MatchingG[j].y < mY)
				{
					result++;
				}
			}
		}
	}
	
	return result;

}


//bPre must exists in DW case
Y TreeNode::betaPreforZLG(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXLG;
	tempY = _MYLG;
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
Y TreeNode::betaPostforZLG(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXLG;
	tempY = _MYLG;
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


//Y TreeNode::searchXMateRecurL(X x, int delta)//delta is the count of x need to be in the right of x
//{
//	for (int i = 0; i < _parent->_MatchingG.size(); i++)
//	{
//		if (_parent->_MatchingG[i].x == x)
//		{
//			return _parent->_MatchingG[i].y;
//		}
//	}
//}
//
//
//Y TreeNode::searchXMateRecurR(X x, int delta)//delta is the count of x need to be in the left of x
//{
//	if (_leftChild == NULL)
//	{
//		//a leaf
//		vector<X> leftMXG;
//		for (int i = 0; i < _XG.size(); i++)
//		{
//			if (cmpXEndInc(_XG[i], x))
//			{
//				leftMXG.push_back(_XG[i]);
//			}
//		}
//		int leftAll = leftMXG.size() + delta;
//		sort(_YG.begin(), _YG.end(), cmpYValueInc);
//		return _YG[leftAll];
//	}
//	else
//	{
//		vector<X> TMGLeft;
//		for (int i = 0; i < _leftChild->_TXG.size(); i++)//all _TXG must be matched in curNode
//		{
//			if (cmpXEndInc(_leftChild->_TXG[i], x))
//			{
//				TMGLeft.push_back(_leftChild->_TXG[i]);
//			}
//		}
//		if (delta + (int)TMGLeft.size() - (int)_leftChild->_IYG.size() < 0)
//		{
//			delta = delta + TMGLeft.size();
//			return _leftChild->searchXMateRecurR(x, delta);
//		}
//		else
//		{
//			delta = delta + (int)TMGLeft.size() - (int)_leftChild->_IYG.size();
//			return _rightChild->searchXMateRecurR(x, delta);
//		}
//	}
//}

