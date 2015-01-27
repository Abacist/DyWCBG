#include"Tree.h"


//X Tree::queryYMate(int value)
//{
//	//Glover Info has been maintained
//	Y y;
//	y._value = value;
//	vector<Y>::iterator it = find(_root->_MY.begin(), _root->_MY.end(), y);
//	if (it == _root->_MY.end())
//	{
//		X x;
//		return x;
//	}
//	else
//	{
//		y = *it;
//		vector<X> addX;
//		vector<Y> leftY;
//		TreeNode* curNode = _root;
//		while (y <= curNode->_leftChild->maxY())
//		{
//			curNode = curNode->_leftChild;
//			if (curNode->_leftChild == NULL)
//			{
//				break;
//			}
//		}
//		if (curNode->_leftChild != NULL)
//		{
//			for (int i = 0; i < curNode->_leftChild->_TXG.size(); i++)
//			{
//				addX.push_back(curNode->_leftChild->_TXG[i]);
//			}
//			curNode = curNode->_rightChild;
//		}
//		while (true)
//		{
//			if (curNode->_leftChild == NULL)
//			{
//				for (int i = 0; i < curNode->_YG.size(); i++)
//				{
//					if (curNode->_YG[i]> y)
//					{
//						break;
//					}
//					else
//					{
//						leftY.push_back(curNode->_YG[i]);
//						if (i < (int)curNode->_MXG.size())
//						{
//							addX.push_back(curNode->_MXG[i]);
//						}
//					}
//				}
//				break;
//			}
//			else
//			{
//				Y midY = curNode->_leftChild->maxY();
//				if (y <= midY)
//				{
//					curNode = curNode->_leftChild;
//				}
//				else
//				{
//					for (int i = 0; i < curNode->_leftChild->_MXG.size(); i++)
//					{
//						addX.push_back(curNode->_leftChild->_MXG[i]);
//					}
//					for (int i = 0; i < curNode->_leftChild->_TXG.size(); i++)
//					{
//						addX.push_back(curNode->_leftChild->_TXG[i]);
//					}
//					for (int i = 0; i < curNode->_leftChild->_YG.size(); i++)
//					{
//						leftY.push_back(curNode->_leftChild->_YG[i]);
//					}
//					curNode = curNode->_rightChild;
//				}
//			}
//		}
//		sort(addX.begin(), addX.end(), cmpXEndInc);
//		sort(leftY.begin(), leftY.end(), cmpYValueInc);
//		for (int i = 0; i < leftY.size(); i++)
//		{
//			if (leftY[i] == y)
//			{
//				return addX[i];
//			}
//		}
//
//
//	}
//}



X Tree::queryYMate(int value)
{
	Y y;
	y._value = value;
	vector<Y>::iterator it = find(_root->_MY.begin(), _root->_MY.end(), y);
	if (it == _root->_MY.end())
	{
		X x;
		return x;
	}
	else
	{
		
		y = *it;
		X x;
		x._e = getYMateEnd(y);
		return x;
	}
}


Y Tree::getYMateEnd(Y y)
{
	int lb = y._value, ub = _root->maxY()._value;

	X testX;
	testX._id = 10000;
	testX._s._value = y._value;
	testX._w = 1;
	testX._e._value = y._value;
	Y my0 = getTestXMate(testX);
	if (my0.empty())
	{
		return y;
	}
	while (true)
	{
		testX._e._value = ub;
		Y my = getTestXMate(testX);
		cout << "X end: " << testX._e._value << "\tMate: " << my._value << endl;
		if (!my.empty() && my <= y)
		{
			int diff = ub - lb + 1;
			lb = ub;
			ub = ub + diff / 2;
		}
		else
		{
			if (ub <= lb + 1)
			{
				break;
			}
			ub = (ub + lb) / 2;

		}
	}
	y._value = lb + 1;
	return y;
}

Y Tree::getTestXMate(X testX)
{
	vector<X> allX = _root->_MX;
	for (int i = 0; i < allX.size(); i++)
	{
		allX[i]._w = 1;
	}
	allX.push_back(testX);
	vector<Y> allY = _root->_Y;
	for (int i = 0; i < allY.size(); i++)
	{
		allY[i]._w = 0;
		if (find(_root->_MY.begin(), _root->_MY.end(), allY[i]) != _root->_MY.end())
		{
			allY[i]._w = 1;
		}
	}
	Tree* pTree = new Tree(allY);
	for (int i = 0; i < allX.size(); i++)
	{
		pTree->insertXinTree(allX[i]);
	}
	pTree->constructGloverInfo();
	return pTree->queryXMate(testX._id);
}