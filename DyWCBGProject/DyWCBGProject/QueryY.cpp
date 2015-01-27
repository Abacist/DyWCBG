#include"Tree.h"


X Tree::queryYMate(int value)
{
	//Glover Info has been maintained
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
		vector<X> addX;
		vector<Y> leftY;
		TreeNode* curNode = _root;
		while (y <= curNode->_leftChild->maxY())
		{
			curNode = curNode->_leftChild;
			if (curNode->_leftChild == NULL)
			{
				break;
			}
		}
		if (curNode->_leftChild != NULL)
		{
			for (int i = 0; i < curNode->_leftChild->_TXG.size(); i++)
			{
				addX.push_back(curNode->_leftChild->_TXG[i]);
			}
			curNode = curNode->_rightChild;
		}
		while (true)
		{
			if (curNode->_leftChild == NULL)
			{
				for (int i = 0; i < curNode->_YG.size(); i++)
				{
					if (curNode->_YG[i]> y)
					{
						break;
					}
					else
					{
						leftY.push_back(curNode->_YG[i]);
						if (i < (int)curNode->_MXG.size())
						{
							addX.push_back(curNode->_MXG[i]);
						}
					}
				}
				break;
			}
			else
			{
				Y midY = curNode->_leftChild->maxY();
				if (y <= midY)
				{
					curNode = curNode->_leftChild;
				}
				else
				{
					for (int i = 0; i < curNode->_leftChild->_MXG.size(); i++)
					{
						addX.push_back(curNode->_leftChild->_MXG[i]);
					}
					for (int i = 0; i < curNode->_leftChild->_TXG.size(); i++)
					{
						addX.push_back(curNode->_leftChild->_TXG[i]);
					}
					for (int i = 0; i < curNode->_leftChild->_YG.size(); i++)
					{
						leftY.push_back(curNode->_leftChild->_YG[i]);
					}
					curNode = curNode->_rightChild;
				}
			}
		}
		sort(addX.begin(), addX.end(), cmpXEndInc);
		sort(leftY.begin(), leftY.end(), cmpYValueInc);
		for (int i = 0; i < leftY.size(); i++)
		{
			if (leftY[i] == y)
			{
				return addX[i];
			}
		}


	}
}