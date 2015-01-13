#include"Tree.h"

extern int verifyEachUpdate;

Msg TreeNode::insertXintoLeaf(X x)
{
	
	Msg msg;
	msg._aX = x;
	_X.push_back(x);

	
	return msg;
}



void Tree::insertXinTree(X x)
{
	TreeNode* curNode = locateLeaf(x);
	Msg msg = curNode->insertXintoLeaf(x);
	int flag = 0;
	if (verifyEachUpdate)
	{
		flag = curNode->verifyNodeInvariants();
		if (flag)
		{
			throw new exception();
		}
	}
	TreeNode* child = curNode;
	curNode = curNode->_parent;
	while (curNode != NULL)
	{
		if (child == curNode->_leftChild)
		{
			msg = curNode->insertXintoNodeL(msg);
		}
		else
		{
			msg = curNode->insertXintoNodeR(msg);
		}
		if (verifyEachUpdate)
		{
			flag = curNode->verifyNodeInvariants();
			if (flag)
			{
				throw new exception();
			}
		}
		child = curNode;
		curNode = curNode->_parent;
	}
	if (verifyEachUpdate)
	{
		cout << "X id:\t" << x._id << " pass" << endl;
	}
	
}


Msg TreeNode::insertXintoNodeL(Msg msg)
{
	Y t1inChild = msg._t1, t2inChild = msg._t2;
	int countInChild = msg._stableYCount;
	bool forceSwap = false;

	Msg rMsg;
	rMsg._t1 = msg._t1;
	rMsg._t2 = msg._t2;
	rMsg._stableYCount = msg._stableYCount;
	rMsg._aX = msg._aX;
	_X.push_back(msg._aX);

	return rMsg;
	
}


Msg TreeNode::insertXintoNodeR(Msg msg)
{
	Y t1inChild = msg._t1, t2inChild = msg._t2;
	int countInChild = msg._stableYCount;
	bool forceSwap = false;

	Msg rMsg;
	rMsg._t1 = msg._t1;
	rMsg._t2 = msg._t2;
	rMsg._stableYCount = msg._stableYCount;
	rMsg._aX = msg._aX;
	_X.push_back(msg._aX);

	return rMsg;
}