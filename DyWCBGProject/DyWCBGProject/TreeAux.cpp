#include"Tree.h"


Tree::Tree(vector<Y> vY)
{
	_root = new TreeNode(vY);
}


void Tree::insertXinTree(X x)
{
	TreeNode* curNode = locateLeaf(x);
	Msg msg = curNode->insertXintoLeaf(x);
}

void Tree::insertYinTree(Y y)
{
	if (find(_root->_Y.begin(), _root->_Y.end(), y) != _root->_Y.end())
	{
		//already inserted
		return;
	}
	TreeNode* curNode = locateLeaf(y);
	Msg msg = curNode->insertYintoLeaf(y);

}


TreeNode* Tree::locateLeaf(X x)
{
	TreeNode* node = _root;

	while (x._s != node->minY())
	{
		if (node->_rightChild != NULL)//not a leaf
		{
			if (x._s >= node->_rightChild->minY())
			{
				node = node->_rightChild;
			}
			else
			{
				node = node->_leftChild;
			}
		}
		else 
		{
			node->splitNode(x);
			int flag; TreeNode* errorNode;
			verifyInvariantsRecur(flag, errorNode, node);
			if (flag != 0)
			{
				throw new exception("Split Error");
			}

			node = node->_rightChild;

		}
	}
	while (node->_leftChild != NULL) // to leaf
	{
		node = node->_leftChild;
	}

	return node;
}

TreeNode* Tree::locateLeaf(Y y)
{
	TreeNode* node = _root;
	while (node->_rightChild != NULL)
	{
		if (y < node->_rightChild->minY())
		{
			node = node->_leftChild;
		}
		else
		{
			node = node->_rightChild;
		}
	}

	return node;
}

void Tree::verifyInvariantsRecur(int& flag, TreeNode*& errorNode)
{

	verifyInvariantsRecur(flag, errorNode, _root);
}

void Tree::verifyInvariantsRecur(int& flag, TreeNode*& errorNode, TreeNode* curRoot)
{
	if (curRoot->_leftChild == NULL)
	{
		flag = curRoot->verifyNodeInvariants();
		if (flag == 0)
		{
			errorNode = NULL;
		}
	}
	else
	{
		verifyInvariantsRecur(flag, errorNode, curRoot->_leftChild);
		if (flag != 0)
		{
			return ;
		}
		verifyInvariantsRecur(flag, errorNode, curRoot->_rightChild);
		if (flag != 0)
		{
			return;
		}
		return verifyInvariantsRecur(flag, errorNode, curRoot);
	}
}