#include"Tree.h"

X TreeNode::getMaxEndXinMXRG(X x)
{
	vector<X> tempX = _MXRG;
	tempX.push_back(x);
	sort(tempX.begin(), tempX.end(), cmpXEndInc);
	return tempX[tempX.size() - 1];
}


Msg TreeNode::insertXintoLeafG(X x)
{
	Msg rMsg;
	rMsg._aX = x;
	_XG.push_back(x);

	if (_MXG.size() == _YG.size())
	{
		X maxEnd = getMaxEndXinMXRG(x);
		rMsg._aMX = x;
		_MXG.push_back(x);
		_MXRG.push_back(x);

		rMsg._bMX = maxEnd;
		_MXG.erase(find(_MXG.begin(), _MXG.end(), maxEnd));
		_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), maxEnd));

		rMsg._aTX = maxEnd;
		_TXG.push_back(maxEnd);
	}
	else
	{
		sort(_IYG.begin(), _IYG.end(), cmpYValueInc);
		Y cY = _IYG[0];

		rMsg._aMX = x;
		_MXG.push_back(x);
		_MXRG.push_back(x);

		rMsg._aMY = cY;
		_MYG.push_back(cY);
		_MYRG.push_back(cY);

		rMsg._bIY = cY;
		_IYG.erase(find(_IYG.begin(), _IYG.end(), cY));
	}
	return rMsg;
}

Msg TreeNode::insertXintoNodeLG(Msg msg)
{
	Msg rMsg;
	rMsg._aX = msg._aX;
	_XG.push_back(msg._aX);

	if (!msg._aMY.empty())
	{
		rMsg._aMX = msg._aX;
		_MXG.push_back(msg._aX);
		_MXLG.push_back(msg._aX);

		rMsg._aMY = msg._aMY;
		_MYG.push_back(msg._aMY);
		_MYLG.push_back(msg._aMY);

		rMsg._bIY = msg._aMY;
		_IYG.erase(find(_IYG.begin(), _IYG.end(), msg._aMY));
	}
	else
	{
		if (_MXRG.size() == getYRG().size())
		{
			X maxEnd = getMaxEndXinMXRG(msg._aTX);

			rMsg._aMX = msg._aX;
			_MXG.push_back(msg._aX);
			_MXLG.push_back(msg._aX);
			_MXLG.erase(find(_MXLG.begin(), _MXLG.end(), msg._aTX));

			rMsg._bMX = maxEnd;
			_MXRG.push_back(msg._aTX);
			_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), maxEnd));
			_MXG.erase(find(_MXG.begin(), _MXG.end(), maxEnd));

			rMsg._aTX = maxEnd;
			_TXG.push_back(maxEnd);
		}
		else
		{
			vector<Y> IYRG = getIYRG();
			sort(IYRG.begin(), IYRG.end(), cmpYValueInc);
			Y cY = IYRG[0];

			rMsg._aMX = msg._aX;
			_MXG.push_back(msg._aX);
			_MXLG.push_back(msg._aX);
			_MXLG.erase(find(_MXLG.begin(), _MXLG.end(), msg._aTX));
			_MXRG.push_back(msg._aTX);

			rMsg._aMY = cY;
			_MYG.push_back(cY);
			_MYRG.push_back(cY);

			rMsg._bIY = cY;
			_IYG.erase(find(_IYG.begin(), _IYG.end(), cY));
		}
	}
	return rMsg;
}


Msg TreeNode::insertXintoNodeRG(Msg msg)
{
	Msg rMsg;
	rMsg._aX = msg._aX;
	_XG.push_back(msg._aX);

	if (!msg._aTX.empty())
	{
		if (find(_MXRG.begin(), _MXRG.end(), msg._aTX) != _MXRG.end() || msg._aTX == msg._aX)
		{
			rMsg._aMX = msg._aX;
			_MXG.push_back(msg._aX);
			_MXRG.push_back(msg._aX);

			rMsg._bMX = msg._aTX;
			_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), msg._aTX));
			_MXG.erase(find(_MXG.begin(), _MXG.end(), msg._aTX));

			rMsg._aTX = msg._aTX;
			_TXG.push_back(msg._aTX);
		}
		else
		{
			X maxEnd = getMaxEndXinMXRG(msg._aX);

			rMsg._aMX = msg._aX;
			_MXG.push_back(msg._aX);
			_MXRG.push_back(msg._aX);

			rMsg._bMX = maxEnd;
			_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), maxEnd));
			_MXG.erase(find(_MXG.begin(), _MXG.end(), maxEnd));

			rMsg._aTX = maxEnd;
			_TXG.push_back(maxEnd);
		}
	}
	else
	{
		//success in R
		vector<Y> IYRG = getIYRG();
		if (find(IYRG.begin(), IYRG.end(), msg._aMY) != IYRG.end())
		{
			rMsg._aMX = msg._aX;
			_MXG.push_back(msg._aX);
			_MXRG.push_back(msg._aX);

			rMsg._aMY = msg._aMY;
			_MYG.push_back(msg._aMY);
			_MYRG.push_back(msg._aMY);

			rMsg._bIY = msg._aMY;
			_IYG.erase(find(_IYG.begin(), _IYG.end(), msg._aMY));
		}
		else
		{
			if (_MXRG.size() == getYRG().size())
			{
				X maxEnd = getMaxEndXinMXRG(msg._aX);

				rMsg._aMX = msg._aX;
				_MXG.push_back(msg._aX);
				_MXRG.push_back(msg._aX);

				rMsg._bMX = maxEnd;
				_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), maxEnd));
				_MXG.erase(find(_MXG.begin(), _MXG.end(), maxEnd));

				rMsg._aTX = maxEnd;
				_TXG.push_back(maxEnd);
			}
			else
			{
				vector<Y> IYRG = getIYRG();
				sort(IYRG.begin(), IYRG.end(), cmpYValueInc);
				Y cY = IYRG[0];

				rMsg._aMX = msg._aX;
				_MXG.push_back(msg._aX);
				_MXRG.push_back(msg._aX);

				rMsg._aMY = cY;
				_MYG.push_back(cY);
				_MYRG.push_back(cY);

				rMsg._bIY = cY;
				_IYG.erase(find(_IYG.begin(), _IYG.end(), cY));
			}
		}
	}

	return rMsg;
}






