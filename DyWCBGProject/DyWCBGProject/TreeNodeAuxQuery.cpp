#include"Tree.h"

Y TreeNode::betaPostforZRG(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXRG;
	tempY = _MYRG;
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


vector<Y> TreeNode::getNewMYRG()
{
	vector<Y> newMYRG;
	for (int i = 0; i < _MYRG.size(); i++)
	{
		if (find(_rightChild->_MYG.begin(), _rightChild->_MYG.end(), _MYRG[i]) == _rightChild->_MYG.end())
		{
			newMYRG.push_back(_MYRG[i]);
		}
	}
	return newMYRG;
}




void Tree::updateQueryInfo(Msg msg)//final msg, returned by root
{
	if (msg._aX.empty() == false)
	{
		//insert X
		if (msg._bMX.empty() == false)
		{
			//preempt
			if (msg._bMX != msg._aX)
			{
				deleteXfromTreeG(msg._bMX);
				insertXinTreeG(msg._aX);
			}
		}
		else if (msg._aMY.empty() == false)
		{
			//success
			insertYinTreeG(msg._aMY);
			insertXinTreeG(msg._aX);
		}
		else
		{
			throw new exception();
		}
	}
	else if (msg._aY.empty() == false)
	{
		//insert Y
		if (msg._bMY.empty() == false)
		{
			//preempt
			if (msg._bMY != msg._aY)
			{
				insertYinTreeG(msg._aY);
				deleteYfromTreeG(msg._bMY);
			}
		}
		else if (msg._aMX.empty() == false)
		{
			//success
			insertYinTreeG(msg._aY);
			insertXinTreeG(msg._aMX);
		}
		else
		{
			throw new exception();
		}
	}
	else
	{
		//not complete yet
		throw new exception();
	}
}


void Tree::insertXinTreeG(X x)
{
	TreeNode* curNode = locateLeaf(x);
	Msg msg = curNode->insertXintoLeafG(x);
	TreeNode* child = curNode;
	curNode = curNode->_parent;
	while (curNode != NULL)
	{
		if (child == curNode->_leftChild)
		{
			msg = curNode->insertXintoNodeLG(msg);
		}
		else
		{
			msg = curNode->insertXintoNodeRG(msg);
		}
		child = curNode;
		curNode = curNode->_parent;
	}
}



void Tree::deleteXfromTreeG(X x)
{

}


void Tree::insertYinTreeG(Y y)
{
	TreeNode* curNode = locateLeaf(y);
	Msg msg = curNode->insertYintoLeafG(y);
	TreeNode* child = curNode;
	curNode = curNode->_parent;
	while (curNode != NULL)
	{
		if (child == curNode->_leftChild)
		{
			msg = curNode->insertYintoNodeLG(msg);
		}
		else
		{
			msg = curNode->insertYintoNodeRG(msg);
		}
		child = curNode;
		curNode = curNode->_parent;
	}
}


void Tree::deleteYfromTreeG(Y y)
{

}


void Tree::verifyGloverInfo(int& flag, TreeNode*& errorNode)
{
	constructGloverInfo();
	verifyGloverInfo(flag, errorNode, _root);
}

void Tree::verifyGloverInfo(int& flag, TreeNode*& errorNode, TreeNode* curRoot)
{
	if (curRoot->_leftChild == NULL)
	{
		flag = curRoot->verifyGSets();
		if (flag == 0)
		{
			errorNode = NULL;
		}
		else
		{
			errorNode = curRoot;
		}
	}
	else
	{
		verifyGloverInfo(flag, errorNode, curRoot->_leftChild);
		if (flag != 0)
		{
			return;
		}
		verifyGloverInfo(flag, errorNode, curRoot->_rightChild);
		if (flag != 0)
		{
			return;
		}
		flag = curRoot->verifyGSets();
		if (flag == 0)
		{
			errorNode = NULL;
		}
		else
		{
			errorNode = curRoot;
		}
	}
}



int TreeNode::verifyGSets()
{
	if (!setEqual(_YG, _YGTest))
	{
		return 1;
	}
	if (!setEqual(_XG, _XGTest))
	{
		return 1;
	}
	if (!setEqual(_IYG, _IYGTest))
	{
		return 1;
	}
	if (!setEqual(_MYG, _MYGTest))
	{
		return 1;
	}
	if (!setEqual(_MYLG, _MYLGTest))
	{
		return 1;
	}
	if (!setEqual(_MYRG, _MYRGTest))
	{
		return 1;
	}
	if (!setEqual(_MXG, _MXGTest))
	{
		return 1;
	}
	if (!setEqual(_MXLG, _MXRGTest))
	{
		return 1;
	}
	if (!setEqual(_TXG, _TXGTest))
	{
		return 1;
	}
	return 0;
}