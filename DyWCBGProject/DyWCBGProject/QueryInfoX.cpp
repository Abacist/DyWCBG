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


Msg TreeNode::deleteXfromLeafG(X x)
{
	Msg rMsg;
	rMsg._bX = x;
	_XG.erase(find(_XG.begin(), _XG.end(), x));

	if (find(_TXG.begin(), _TXG.end(), x) != _TXG.end())
	{
		rMsg._bTX = x;
		_TXG.erase(find(_TXG.begin(), _TXG.end(), x));
	}
	else
	{
		if (!_TXG.empty())
		{
			sort(_TXG.begin(), _TXG.end(), cmpXEndInc);
			X cX = _TXG[0];

			rMsg._bMX = x;
			_MXG.erase(find(_MXG.begin(), _MXG.end(), x));
			_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), x));

			rMsg._aMX = cX;
			_MXG.push_back(cX);
			_MXRG.push_back(cX);

			rMsg._bTX = cX;
			_TXG.erase(find(_TXG.begin(), _TXG.end(), cX));
		}
		else
		{
			Y maxY = getMaxYinMYRG();

			rMsg._bMX = x;
			_MXG.erase(find(_MXG.begin(), _MXG.end(), x));
			_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), x));

			rMsg._bMY = maxY;
			_MYG.erase(find(_MYG.begin(), _MYG.end(), maxY));
			_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), maxY));

			rMsg._aIY = maxY;
			_IYG.push_back(maxY);
		}
	}
	return rMsg;
}


Msg TreeNode::deleteXfromNodeLG(Msg msg)
{
	Msg rMsg;
	rMsg._bX = msg._bX;
	_XG.erase(find(_XG.begin(), _XG.end(), msg._bX));
	if (find(_TXG.begin(), _TXG.end(), msg._bX) != _TXG.end())
	{
		rMsg._bTX = msg._bX;
		_TXG.erase(find(_TXG.begin(), _TXG.end(), msg._bX));
	}
	else
	{
		if (find(_MXLG.begin(), _MXLG.end(), msg._bX) != _MXLG.end())
		{
			//match in left
			if (msg._bMY.empty() == false)
			{
				rMsg._bMX = msg._bX;
				_MXG.erase(find(_MXG.begin(), _MXG.end(), msg._bX));
				_MXLG.erase(find(_MXLG.begin(), _MXLG.end(), msg._bX));

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

						rMsg._bMX = msg._bX;
						_MXG.erase(find(_MXG.begin(), _MXG.end(), msg._bX));
						_MXLG.erase(find(_MXLG.begin(), _MXLG.end(), msg._bX));
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

						rMsg._bMX = msg._bX;
						_MXG.erase(find(_MXG.begin(), _MXG.end(), msg._bX));
						_MXLG.erase(find(_MXLG.begin(), _MXLG.end(), msg._bX));
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
					rMsg._bMX = msg._bX;
					_MXG.erase(find(_MXG.begin(), _MXG.end(), msg._bX));
					_MXLG.erase(find(_MXLG.begin(), _MXLG.end(), msg._bX));

					rMsg._aMX = msg._bTX;
					_MXG.push_back(msg._bTX);
					_MXLG.push_back(msg._bTX);

					rMsg._bTX = msg._bTX;
					_TXG.erase(find(_TXG.begin(), _TXG.end(), msg._bTX));
				}
			}
		}
		else
		{
			//match in right
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

				rMsg._bMX = msg._bX;
				_MXG.erase(find(_MXG.begin(), _MXG.end(), msg._bX));
				_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), msg._bX));

				rMsg._bMY = newMYRG[0];
				_MYG.erase(find(_MYG.begin(), _MYG.end(), newMYRG[0]));
				_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), newMYRG[0]));

				rMsg._aIY = newMYRG[0];
				_IYG.push_back(newMYRG[0]);
			}
			else
			{
				sort(CTXG.begin(), CTXG.end(), cmpXEndInc);

				rMsg._bMX = msg._bX;
				_MXG.erase(find(_MXG.begin(), _MXG.end(), msg._bX));
				_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), msg._bX));

				rMsg._aMX = CTXG[0];
				_MXG.push_back(CTXG[0]);
				_MXRG.push_back(CTXG[0]);

				rMsg._bTX = CTXG[0];
				_TXG.erase(find(_TXG.begin(), _TXG.end(), CTXG[0]));

			}
		}
	}

	return rMsg;
}

Msg TreeNode::deleteXfromNodeRG(Msg msg)
{
	Msg rMsg;
	rMsg._bX = msg._bX;
	_XG.erase(find(_XG.begin(), _XG.end(), msg._bX));

	if (find(_TXG.begin(), _TXG.end(), msg._bX) != _TXG.end())
	{
		rMsg._bTX = msg._bX;
		_TXG.erase(find(_TXG.begin(), _TXG.end(), msg._bX));
	}
	else
	{
		Y bPost = betaPostforZRG(msg._bX._s);
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

			rMsg._bMX = msg._bX;
			_MXG.erase(find(_MXG.begin(), _MXG.end(), msg._bX));
			_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), msg._bX));

			rMsg._aMX = CTXG[0];
			_MXG.push_back(CTXG[0]);
			_MXRG.push_back(CTXG[0]);

			rMsg._bTX = CTXG[0];
			_TXG.erase(find(_TXG.begin(), _TXG.end(), CTXG[0]));
		}
		else
		{
			vector<Y> newMYRG = getNewMYRG();
			newMYRG.push_back(msg._aY);
			sort(newMYRG.begin(), newMYRG.end(), cmpYValueDec);

			rMsg._bMX = msg._bX;
			_MXG.erase(find(_MXG.begin(), _MXG.end(), msg._bX));
			_MXRG.erase(find(_MXRG.begin(), _MXRG.end(), msg._bX));

			rMsg._bMY = newMYRG[0];
			_MYG.erase(find(_MYG.begin(), _MYG.end(), newMYRG[0]));
			_MYRG.erase(find(_MYRG.begin(), _MYRG.end(), newMYRG[0]));

			rMsg._aIY = newMYRG[0];
			_IYG.push_back(newMYRG[0]);
		}
	}

	return rMsg;
}





