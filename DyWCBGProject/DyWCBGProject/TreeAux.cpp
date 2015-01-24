#include<Windows.h>
#include<fstream>
#include"Tree.h"


Tree::Tree(vector<Y> vY)
{
	_root = new TreeNode(vY);
}


Tree::Tree(vector<Y> YBase, vector<Y> vY)
{
	_root = new TreeNode(YBase, vY);
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
		else
		{
			errorNode = curRoot;
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
		flag = curRoot->verifyNodeInvariants();
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


void Tree::printMY()
{
	ofstream my("MY.txt");
	printMY(_root, my);
	my.close();
	getchar();
}

void Tree::printMY(TreeNode* curRoot, ofstream & my)
{
	if (curRoot->_leftChild ==  NULL)
	{
		return;
	}
	else
	{
		sort(curRoot->_MYL.begin(), curRoot->_MYL.end(), cmpYValueInc);
		my << "MYL.:";
		for (int i = 0; i < curRoot->_MYL.size(); i++)
		{
			my << curRoot->_MYL[i]._value << " ";
		}

		sort(curRoot->_MYR.begin(), curRoot->_MYR.end(), cmpYValueInc);
		my << "MYR.:";
		for (int i = 0; i < curRoot->_MYR.size(); i++)
		{
			my << curRoot->_MYR[i]._value << " ";
		}

		my << endl;

		sort(curRoot->_leftChild->_MY.begin(), curRoot->_leftChild->_MY.end(), cmpYValueInc);
		my << "L.MY:";
		for (int i = 0; i < curRoot->_leftChild->_MY.size(); i++)
		{
			my << curRoot->_leftChild->_MY[i]._value << " ";
		}

		sort(curRoot->_rightChild->_MY.begin(), curRoot->_rightChild->_MY.end(), cmpYValueInc);
		my << "R.MY:";
		for (int i = 0; i < curRoot->_rightChild->_MY.size(); i++)
		{
			my << curRoot->_rightChild->_MY[i]._value << " ";
		}

		my << endl << endl;

		printMY(curRoot->_leftChild, my);
		printMY(curRoot->_rightChild, my);
	}
}

void Tree::printRMY()
{
	int range = _root->_IY.size();

	SYSTEMTIME lpsystime;
	GetLocalTime(&lpsystime);
	srand(lpsystime.wMinute * 1000 + lpsystime.wMilliseconds);

	int index = rand() % (range);
	Y aY = _root->_IY[index];
	
	vector<Y> RMY;

	for (int i = 0; i < _root->_MY.size(); i++)
	{
		vector<X> tempX = _root->_MX;
		vector<Y> tempY = _root->_MY;
		tempY.erase(find(tempY.begin(), tempY.end(), _root->_MY[i]));
		tempY.push_back(aY);
		vector<X> tempMX;
		formGloverMatching(tempX, tempY, tempMX);
		if (tempMX.size() == tempX.size())
		{
			RMY.push_back(_root->_MY[i]);
		}
	}

	ofstream out("RMY.txt");
	sort(RMY.begin(), RMY.end(), cmpYValueInc);
	sort(_root->_MY.begin(), _root->_MY.end(), cmpYValueInc);

	out << "RMY: ";
	for (int i = 0; i < RMY.size(); i++)
	{
		out << RMY[i]._value << " ";
	}
	out << endl << "_MY: ";
	for (int i = 0; i < _root->_MY.size(); i++)
	{
		out << _root->_MY[i]._value << " ";
	}
	out << endl;
	out.close();
	getchar();
}