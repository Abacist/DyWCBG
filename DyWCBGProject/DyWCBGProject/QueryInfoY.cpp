#include"Tree.h"


Y TreeNode::getMaxYinMYRG(Y y)
{
	vector<Y> tempY = _MYRG;
	if (!y.empty())
	{
		tempY.push_back(y);
	}
	sort(tempY.begin(), tempY.end(), cmpYValueInc);
	return tempY[tempY.size() - 1];
}

Msg TreeNode::insertYintoLeafG(Y y)
{
	Msg rMsg;
	rMsg._aY = y;
	_YG.push_back(y);

	if (!_TXG.empty())
	{
		sort(_TXG.begin(), _TXG.end(), cmpXEndInc);
		X cX = _TXG[0];

		rMsg._aMY = y;
		_MYG.push_back(y);
		_MYRG.push_back(y);

		rMsg._aMX = cX;
		_MXG.push_back(cX);
		_MXRG.push_back(cX);

		rMsg._bTX = cX;
		_TXG.erase(find(_TXG.begin(), _TXG.end(), cX));
	}
	else
	{
		Y maxY = getMaxYinMYRG(y);

		rMsg._aMY = y;
		_MYG.push_back(y);
		_MYRG.push_back(y);

		rMsg._bMY = maxY;
		_MYG.erase(find(_MYG.begin(), _MYG.end(), maxY));
		_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), maxY));

		rMsg._aIY = maxY;
		_IYG.push_back(maxY);
	}

	return rMsg;
}
Msg TreeNode::insertYintoNodeLG(Msg msg)
{
	Msg rMsg;
	rMsg._aY = msg._aY;
	_YG.push_back(msg._aY);

	if (msg._bMY.empty() == false)
	{
		rMsg._aMY = msg._aY;
		_MYG.push_back(msg._aY);
		_MYLG.push_back(msg._aY);

		rMsg._bMY = msg._bMY;
		_MYG.erase(find(_MYG.begin(), _MYG.end(), msg._bMY));
		_MYLG.erase(find(_MYLG.begin(), _MYLG.end(), msg._bMY));

		rMsg._aIY = msg._bMY;
		_IYG.push_back(msg._bMY);
	}
	else
	{
		if (find(_MXRG.begin(), _MXRG.end(), msg._bTX) != _MXRG.end())
		{
			sort(_MYRG.begin(), _MYRG.end(), cmpYValueInc);
			Y bPost = betaPostforZRG(_MYRG[0]);
			vector<X> CTXG;
			for (int i = 0; i < _TXG.size(); i++)
			{
				if (_TXG[i]._s <= bPost)
				{
					CTXG.push_back(_TXG[i]);
				}
			}
			if (CTXG.empty())
			{
				vector<Y> newMYRG = getNewMYRG();
				sort(newMYRG.begin(), newMYRG.end(), cmpYValueDec);

				rMsg._aMY = msg._aY;
				_MYG.push_back(msg._aY);
				_MYLG.push_back(msg._aY);
				_MXLG.push_back(msg._bTX);
				_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), msg._bTX));

				rMsg._bMY = newMYRG[0];
				_MYG.erase(find(_MYG.begin(), _MYG.end(), newMYRG[0]));
				_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), newMYRG[0]));

				rMsg._aIY = newMYRG[0];
				_IYG.push_back(newMYRG[0]);
			}
			else
			{
				sort(CTXG.begin(), CTXG.end(), cmpXEndInc);
				rMsg._aMY = msg._aY;
				_MYG.push_back(msg._aY);
				_MYLG.push_back(msg._aY);
				_MXLG.push_back(msg._bTX);
				_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), msg._bTX));

				rMsg._aMX = CTXG[0];
				_MXG.push_back(CTXG[0]);
				_MXRG.push_back(CTXG[0]);

				rMsg._bTX = CTXG[0];
				_TXG.erase(find(_TXG.begin(), _TXG.end(), CTXG[0]));
			}

			
		}
		else
		{
			//still transfer
			rMsg._aMY = msg._aY;
			_MYG.push_back(msg._aY);
			_MYLG.push_back(msg._aY);

			rMsg._aMX = msg._bTX;
			_MXG.push_back(msg._bTX);
			_MXLG.push_back(msg._bTX);

			rMsg._bTX = msg._bTX;
			_TXG.erase(find(_TXG.begin(), _TXG.end(), msg._bTX));
		}
	}

	return rMsg;
}

Msg TreeNode::insertYintoNodeRG(Msg msg)
{
	Msg rMsg;
	rMsg._aY = msg._aY;
	_YG.push_back(msg._aY);


	Y bPost = betaPostforZRG(msg._aY);
	vector<X> CTXG;
	for (int i = 0; i < _TXG.size(); i++)
	{
		if (_TXG[i]._s <= bPost)
		{
			CTXG.push_back(_TXG[i]);
		}
	}

	if (CTXG.empty() == false)
	{
		sort(CTXG.begin(), CTXG.end(), cmpXEndInc);

		rMsg._aMY = msg._aY;
		_MYG.push_back(msg._aY);
		_MYRG.push_back(msg._aY);

		rMsg._aMX = CTXG[0];
		_MXG.push_back(CTXG[0]);
		_MXRG.push_back(CTXG[0]);

		rMsg._bTX = CTXG[0];
		_TXG.erase(find(_TXG.begin(), _TXG.end(), CTXG[0]));
	}
	else
	{
		//must preempt an Y in R
		vector<Y> newMYRG = getNewMYRG();
		newMYRG.push_back(msg._aY);
		sort(newMYRG.begin(), newMYRG.end(), cmpYValueDec);

		rMsg._aMY = msg._aY;
		_MYG.push_back(msg._aY);
		_MYRG.push_back(msg._aY);

		rMsg._bMY = newMYRG[0];
		_MYG.erase(find(_MYG.begin(), _MYG.end(), newMYRG[0]));
		_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), newMYRG[0]));

		rMsg._aIY = newMYRG[0];
		_IYG.push_back(newMYRG[0]);
	}
	return rMsg;
}



Msg TreeNode::deleteYfromLeafG(Y y)
{
	Msg rMsg;
	rMsg._bY = y;
	_YG.erase(find(_YG.begin(), _YG.end(), y));

	if (find(_IYG.begin(), _IYG.end(), y) != _IYG.end())
	{
		rMsg._bIY = y;
		_IYG.erase(find(_IYG.begin(), _IYG.end(), y));
	}
	else
	{
		if (_IYG.empty())
		{
			X maxEnd = getMaxEndXinMXRG();
			rMsg._bMY = y;
			_MYG.erase(find(_MYG.begin(), _MYG.end(), y));
			_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), y));

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

			rMsg._bMY = y;
			_MYG.erase(find(_MYG.begin(), _MYG.end(), y));
			_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), y));

			rMsg._aMY = cY;
			_MYG.push_back(cY);
			_MYRG.push_back(cY);

			rMsg._bIY = cY;
			_IYG.erase(find(_IYG.begin(), _IYG.end(), cY));
		}
	}

	return rMsg;
}

Msg TreeNode::deleteYfromNodeLG(Msg msg)
{
	Msg rMsg;
	rMsg._bY = msg._bY;
	_YG.erase(find(_YG.begin(), _YG.end(), msg._bY));

	if (find(_IYG.begin(), _IYG.end(), msg._bY) != _IYG.end())
	{
		rMsg._bIY = msg._bY;
		_IYG.erase(find(_IYG.begin(), _IYG.end(), msg._bY));
	}
	else
	{
		if (!msg._aMY.empty())
		{
			rMsg._bMY = msg._bMY;
			_MYG.erase(find(_MYG.begin(), _MYG.end(), msg._bMY));
			_MYLG.erase(find(_MYLG.begin(), _MYLG.end(), msg._bMY));

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

				rMsg._bMY = msg._bMY;
				_MYG.erase(find(_MYG.begin(), _MYG.end(), msg._bMY));
				_MYLG.erase(find(_MYLG.begin(), _MYLG.end(), msg._bMY));
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

				rMsg._bMY = msg._bMY;
				_MYG.erase(find(_MYG.begin(), _MYG.end(), msg._bMY));
				_MYLG.erase(find(_MYLG.begin(), _MYLG.end(), msg._bMY));
				_MXLG.erase(find(_MXLG.begin(), _MXLG.end(), msg._aTX));
				_MXRG.push_back(msg._aTX);

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
Msg TreeNode::deleteYfromNodeRG(Msg msg)
{
	Msg rMsg;
	rMsg._bY = msg._bY;
	_YG.erase(find(_YG.begin(), _YG.end(), msg._bY));

	if (find(_IYG.begin(), _IYG.end(), msg._bY) != _IYG.end())
	{
		rMsg._bIY = msg._bY;
		_IYG.erase(find(_IYG.begin(), _IYG.end(), msg._bY));
	}
	else
	{
		if (!msg._aTX.empty())
		{
			if (find(_MXRG.begin(), _MXRG.end(), msg._aTX) != _MXRG.end())
			{
				rMsg._bMY = msg._bY;
				_MYG.erase(find(_MYG.begin(), _MYG.end(), msg._bY));
				_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), msg._bY));

				rMsg._bMX = msg._aTX;
				_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), msg._aTX));
				_MXG.erase(find(_MXG.begin(), _MXG.end(), msg._aTX));

				rMsg._aTX = msg._aTX;
				_TXG.push_back(msg._aTX);
			}
			else
			{
				X maxEnd = getMaxEndXinMXRG();

				rMsg._bMY = msg._bY;
				_MYG.erase(find(_MYG.begin(), _MYG.end(), msg._bY));
				_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), msg._bY));

				rMsg._bMX = maxEnd;
				_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), maxEnd));
				_MXG.erase(find(_MXG.begin(), _MXG.end(), maxEnd));

				rMsg._aTX = maxEnd;
				_TXG.push_back(maxEnd);
			}
		}
		else
		{
			vector<Y> IYRG = getIYRG();
			if (find(IYRG.begin(), IYRG.end(), msg._aMY) != IYRG.end())
			{
				rMsg._bMY = msg._bMY;
				_MYG.erase(find(_MYG.begin(), _MYG.end(), msg._bMY));
				_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), msg._bMY));

				rMsg._aMY = msg._aMY;
				_MYG.push_back(msg._aMY);
				_MYRG.push_back(msg._aMY);

				rMsg._bIY = msg._aMY;
				_IYG.erase(find(_IYG.begin(), _IYG.end(), msg._aMY));
			}
			else
			{
				if (IYRG.empty())
				{
					X maxEnd = getMaxEndXinMXRG(msg._aX);

					rMsg._bMY = msg._bY;
					_MYG.erase(find(_MYG.begin(), _MYG.end(), msg._bY));
					_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), msg._bY));

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

					rMsg._bMY = msg._bY;
					_MYG.erase(find(_MYG.begin(), _MYG.end(), msg._bY));
					_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), msg._bY));

					rMsg._aMY = cY;
					_MYG.push_back(cY);
					_MYRG.push_back(cY);

					rMsg._bIY = cY;
					_IYG.erase(find(_IYG.begin(), _IYG.end(), cY));
				}
			}
		}
	}

	return rMsg;
}
