#include"Tree.h"


void Tree::insertYinTree(Y y)
{
	if (find(_root->_Y.begin(), _root->_Y.end(), y) != _root->_Y.end())
	{
		//already inserted
		return;
	}
	//TreeNode* curNode = locateLeaf(y);
	Msg msg = _root->insertYintoLeaf(y);

}



Msg TreeNode::insertYintoLeaf(Y y)
{
	Msg msg;
	msg._aY = y;
	_Y.push_back(y);

	vector<X> CIXR;
	vector<Y> RMYR;
	Y aPre = alphaPreforZR(y);
	getYReachableSetinR(aPre, CIXR, RMYR);
	RMYR.push_back(y);

	if (CIXR.empty())
	{
		//replace
		sort(RMYR.begin(), RMYR.end(), cmpYWeightInc);
		msg._aMY = y;
		_MY.push_back(y);
		_MYR.push_back(y);

		msg._bMY = RMYR[0];
		_MY.erase(find(_MY.begin(), _MY.end(), RMYR[0]));
		_MYR.erase(find(_MYR.begin(), _MYR.end(), RMYR[0]));

		msg._aIY = RMYR[0];
		_IY.push_back(RMYR[0]);
	}
	else
	{
		//compense
		sort(CIXR.begin(), CIXR.end(), cmpXWeightInc);
		X cX = CIXR[CIXR.size() - 1];

		msg._aMY = y;
		_MY.push_back(y);
		_MYR.push_back(y);

		msg._aMX = cX;
		_MX.push_back(cX);
		_MXR.push_back(cX);

		msg._bIX = cX;
		_IX.erase(find(_IX.begin(), _IX.end(), cX));
	}
	
	return msg;
}



