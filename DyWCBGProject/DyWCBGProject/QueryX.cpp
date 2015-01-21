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
		for (int i = 0; i < _MX.size(); i++)
		{
			if (cmpXEndInc(_MX[i], x))
			{
				leftMX.push_back(_MX[i]);
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
			//in left
			return _leftChild->searchXMateRecur(x, delta);
		}
		else if (x._s > midY)
		{
			//in right
			vector<X> TMGLeft;
			for (int i = 0; i < _leftChild->_TXG.size(); i++)//all _TXG must be matched in curNode
			{
				if (cmpXEndInc(_leftChild->_TXG[i], x))
				{
					TMGLeft.push_back(_leftChild->_TXG[i]);
				}
			}
			delta = delta + (int)TMGLeft.size() - (int)_leftChild->_IYG.size();
			if (delta < 0)
			{
				//throw new exception();
				delta = 0;
			}
			return _rightChild->searchXMateRecur(x, delta);
		}
		else
		{
			vector<X> TMGLeft;
			for (int i = 0; i < _leftChild->_TXG.size(); i++)//all _TXG must be matched in curNode
			{
				if (cmpXEndInc(_leftChild->_TXG[i], x))
				{
					TMGLeft.push_back(_leftChild->_TXG[i]);
				}
			}
			delta = delta + (int)TMGLeft.size() - (int)_leftChild->_IYG.size();
			if (delta < 0)
			{
				//match in left
				return _leftChild->searchXMateRecurL(x);//delta = 0
			}
			else
			{
				//match in right
				return _rightChild->searchXMateRecurR(x, delta);
			}

		}
	}
}



Y TreeNode::searchXMateRecurL(X x, int delta)//delta is the count of x need to be in the right of x
{
	for (int i = 0; i < _parent->_MatchingG.size(); i++)
	{
		if (_parent->_MatchingG[i].x == x)
		{
			return _parent->_MatchingG[i].y;
		}
	}
	//if (_leftChild == NULL)
	//{
	//	//a leaf
	//	sort(_IYG.begin(), _IYG.end(), cmpYValueDec);
	//	return _IYG[delta];
	//}
	//else
	//{

	//}



	//int rightCount = 0;
	//vector<X> TM;
	//for (int i = 0; i < _MXLG.size(); i++)
	//{
	//	if (_MXLG[i]._e > midY)
	//	{
	//		TM.push_back(_MXLG[i]);
	//	}
	//}
	//Y bPost = betaPostforZLG(x._s);
	//Y bPre = betaPreforZLG(x._s);
	///*for (int i = 0; i < TM.size(); i++)
	//{
	//if (TM[i]._s >= x._s && cmpXEndInc(x, TM[i]))
	//{
	//rightCount++;
	//}
	//}
	//for (int i = 0; i < TM.size(); i++)
	//{
	//if (TM[i]._s >= x._s && cmpXEndInc(TM[i], x))
	//{
	//if (TM[i]._s > bPost)
	//{
	//rightCount++;
	//}
	//}
	//}*/
	//for (int i = 0; i < TM.size(); i++)
	//{
	//	if (TM[i]._s > bPost || TM[i]._s > bPre && TM[i]._s >= bPost && cmpXEndInc(x, TM[i]))
	//	{
	//		rightCount++;
	//	}
	//}
	//Y y;
	//return y;
}


Y TreeNode::searchXMateRecurR(X x, int delta)//delta is the count of x need to be in the left of x
{
	if (_leftChild == NULL)
	{
		//a leaf
		vector<X> leftMXG;
		for (int i = 0; i < _XG.size(); i++)
		{
			if (cmpXEndInc(_XG[i], x))
			{
				leftMXG.push_back(_XG[i]);
			}
		}
		int leftAll = leftMXG.size() + delta;
		sort(_YG.begin(), _YG.end(), cmpYValueInc);
		return _YG[leftAll];
	}
	else
	{
		vector<X> TMGLeft;
		for (int i = 0; i < _leftChild->_TXG.size(); i++)//all _TXG must be matched in curNode
		{
			if (cmpXEndInc(_leftChild->_TXG[i], x))
			{
				TMGLeft.push_back(_leftChild->_TXG[i]);
			}
		}
		if (delta + (int)TMGLeft.size() - (int)_leftChild->_IYG.size() < 0)
		{
			delta = delta + TMGLeft.size();
			return _leftChild->searchXMateRecurR(x, delta);
		}
		else
		{
			delta = delta + (int)TMGLeft.size() - (int)_leftChild->_IYG.size();
			return _rightChild->searchXMateRecurR(x, delta);
		}
	}
}