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
	curNode->_IYG.clear();
	curNode->_IYLG.clear();
	curNode->_IYRG.clear();
	curNode->_MXG.clear();
	curNode->_MXLG.clear();
	curNode->_MXRG.clear();
	curNode->_MYG.clear();
	curNode->_MYLG.clear();
	curNode->_MYRG.clear();
	curNode->_TXG.clear();
	vector<X> tempMX, tempTX;
	Y ye = curNode->maxY();
	for (int i = 0; i < MX.size(); i++)
	{
		if (MX[i]._e > ye)
		{
			tempTX.push_back(MX[i]);
		}
		else
		{
			tempMX.push_back(MX[i]);
		}
	}
	sort(tempTX.begin(), tempTX.end(), cmpXEndInc);
	for (int i = 0; i < tempTX.size(); i++)
	{
		vector<X> test = tempMX;
		test.push_back(tempTX[i]);
		vector<X> vZ;
		formGloverMatching(test, curNode->_YG, vZ);
		if (vZ.size() == test.size())
		{
			tempMX.push_back(tempTX[i]);
		}
		else
		{
			curNode->_TXG.push_back(tempTX[i]);
		}
	}
	curNode->_MXG = tempMX;
	getGloverInfo(curNode->_MXG, curNode->_YG, curNode->_MatchingG, curNode->_IYG);

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
		vector<X> leftMX;
		for (int i = 0; i < _MXG.size(); i++)
		{
			if (cmpXEndInc(_MXG[i], x))
			{
				leftMX.push_back(_MXG[i]);
			}
		}
		sort(_YG.begin(), _YG.end(), cmpYValueInc);
		return _YG[delta + leftMX.size()];
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
			for (int i = 0; i < _leftChild->_TXG.size(); i++)//all matched in P's right part
			{
				if (cmpXEndInc(_leftChild->_TXG[i], x))
				{
					leftTM.push_back(_leftChild->_TXG[i]);
				}
			}
			vector<X> TMin;
			for (int i = 0; i < _leftChild->_MXG.size(); i++)
			{
				if (cmpXEndInc(x, _leftChild->_MXG[i]))
				{
					TMin.push_back(_leftChild->_MXG[i]);
				}
			}
			delta = delta - (int)TMin.size() - (int)_leftChild->_IYG.size();
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
			if (find(_MXRG.begin(), _MXRG.end(), x) != _MXRG.end())
			{
				//still match in right
				vector<X> leftTM;
				for (int i = 0; i < _leftChild->_TXG.size(); i++)
				{
					if (cmpXEndInc(_leftChild->_TXG[i], x))
					{
						leftTM.push_back(_leftChild->_TXG[i]);
					}
				}
				vector<X> TMin;
				for (int i = 0; i < _leftChild->_MXG.size(); i++)
				{
					if (cmpXEndInc(x, _leftChild->_MXG[i]))
					{
						TMin.push_back(_leftChild->_MXG[i]);
					}
				}
				delta = delta - (int)TMin.size() - (int)_leftChild->_IYG.size();
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
				for (int i = 0; i < _MXLG.size(); i++)
				{
					if (cmpXEndInc(_MXLG[i], x))
					{
						leftMX.push_back(_MXLG[i]);
					}
				}
				int temp = delta + leftMX.size();
				if (temp >= _leftChild->_YG.size())
				{
					//match in right
					vector<X> leftTM;
					for (int i = 0; i < _leftChild->_TXG.size(); i++)
					{
						if (cmpXEndInc(_leftChild->_TXG[i], x))
						{  
							leftTM.push_back(_leftChild->_TXG[i]);
						}
					}
					return _rightChild->searchXMateRecur(x, temp - (int)_leftChild->_YG.size() + (int)leftTM.size());
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


