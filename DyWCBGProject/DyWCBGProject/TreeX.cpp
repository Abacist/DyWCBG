#include"Tree.h"


Msg TreeNode::insertXintoLeaf(X x)
{
	Msg msg;
	msg._aX = x;
	_X.push_back(x);
	if (_Y.empty())
	{
		_IX.push_back(x);
		msg._aIX = x;
		return msg;
	}
	else
	{
		vector<Y> CIY;
		Y aPost = alphaPostforZR(x._e);
		for (int i = 0; i < _IY.size(); i++)
		{
			if (_IY[i] <= aPost)
			{
					CIY.push_back(_IY[i]);
			}
		}
		if (CIY.empty())
		{
			//replace an X
			vector<X> RMX;
			for (int i = 0; i < _MXR.size(); i++)
			{
				if (/*!aPost.empty() && */_MXR[i]._e <= aPost)
				{
					RMX.push_back(_MXR[i]);
				}
			}
			RMX.push_back(x);

			sort(RMX.begin(), RMX.end(), cmpXEndInc);
			X maxEndX = *(RMX.end() - 1);
			if (maxEndX._e > maxY())//maxY in Y or maxY in MY/MYR? or they are equivalent?
			{
				//transfer
				_MX.push_back(x);
				_MXR.push_back(x);
				msg._aMX = x;

				_MX.erase(find(_MX.begin(), _MX.end(), maxEndX));
				_MXR.erase(find(_MXR.begin(), _MXR.end(), maxEndX));
				msg._bMX = maxEndX;

				_TX.push_back(maxEndX);
				msg._aTX = maxEndX;

				return msg;
			}
			else
			{
				//infeasible
				sort(RMX.begin(), RMX.end(), cmpXWeightInc);
				X rx = RMX[0];

				_MX.push_back(x);
				_MXR.push_back(x);
				msg._aMX = x;

				_MX.erase(find(_MX.begin(), _MX.end(), rx));
				_MXR.erase(find(_MXR.begin(), _MXR.end(), rx));
				msg._bMX = rx;

				_IX.push_back(rx);
				msg._aIX = rx;

				return msg;
			}	
		}
		else
		{
			sort(CIY.begin(), CIY.end(), cmpYWeightInc);
			//Y cY = CIY[CIY.size() - 1];
			Y cy = *(CIY.end() - 1);
			_MX.push_back(x);
			_MXR.push_back(x);
			msg._aMX = x;

			_MY.push_back(cy);
			_MYR.push_back(cy);
			msg._aMY = cy;

			_IY.erase(find(_IY.begin(), _IY.end(), cy));
			msg._bIY = cy;
		}
	}


	return msg;
}



void Tree::insertXinTree(X x)
{
	TreeNode* curNode = locateLeaf(x);
	if (curNode != _root)
	{
		return ;
	}
	Msg msg = curNode->insertXintoLeaf(x);
}


Msg TreeNode::insertXintoNodeL(Msg msg)
{
	Msg rMsg;
	rMsg._aX = msg._aX;
	_X.push_back(msg._aX);
	if (!msg._bIY.empty())
	{
		//success in L
		//really complex TBD
		//the key point is to calculate the replaceable set/compensable set of inserted X
		

		if (find(_IY.begin(), _IY.end(), msg._bIY) == _IY.end())
		{
			//msg.bIY is not in P
			//determine replaceable set in left part first
			vector<X> RMXL;
			Y bPre = betaPreforZL(msg._aX._s);
			for (int i = 0; i < _MXL.size(); i++)
			{
				if (_MXL[i]._s >= bPre)
				{
					RMXL.push_back(_MXL[i]);
				}
			}
			RMXL.push_back(msg._aX);
			//replaceable set got

			vector<Y> IYL = getIYL();
			vector<Y> CIYL;
			for (int i = 0; i<IYL.size(); i++)
			{
				if (IYL[i] >= bPre)
				{
					CIYL.push_back(IYL[i]);
				}
			}
			Y cYL;
			if (!CIYL.empty())
			{
				sort(CIYL.begin(), CIYL.end(), cmpYWeightInc);
				cYL = CIYL[CIYL.size() - 1];
			}
			

			//determine maxEnd
			X maxEnd;
			sort(RMXL.begin(), RMXL.end(), cmpXEndInc);
			maxEnd = RMXL[RMXL.size() - 1];

			//determine CIY in right part
			vector<Y> IYR = getIYR();
			Y aPost = alphaPostforZR(maxEnd._e);
			vector<Y> CIYR;
			for (int i = 0; i < IYR.size(); i++)
			{
				if (IYR[i] <= aPost)
				{
					CIYR.push_back(IYR[i]);
				}
			}
			Y cYR;
			if (!CIYR.empty())
			{
				sort(CIYR.begin(), CIYR.end(), cmpYWeightInc);
				cYR = CIYR[CIYR.size() - 1];
			}
			
			if (cYL.empty() && cYR.empty())
			{
				throw new exception();
			}

			if (cmpYWeightInc(cYR, cYL))
			{
				//left is heavier
				rMsg._bIY = cYL;
				_IY.erase(find(_IY.begin(), _IY.end(), cYL));

				rMsg._aMX = msg._aX;
				_MX.push_back(msg._aX);
				_MXL.push_back(msg._aX);

				rMsg._aMY = cYL;
				_MY.push_back(cYL);
				_MYL.push_back(cYL);
			}
			else
			{
				rMsg._bIY = cYR;
				_IY.erase(find(_IY.begin(), _IY.end(), cYR));

				rMsg._aMY = cYR;
				_MY.push_back(cYR);
				_MYR.push_back(cYR);

				rMsg._aMX = msg._aX;
				_MX.push_back(msg._aX);
				_MXL.push_back(msg._aX);
				_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
				_MXR.push_back(maxEnd);
			}
		}
		else
		{
			//msg.bIY is in P
			if (msg._aX._e > _leftChild->maxY())
			{
				//in left , add this _bIY, or add one from L.MX\cap P.IY
				vector<Y> CIYL;
				CIYL.push_back(msg._bIY);
				vector<Y> newIY;
				for (int i = 0; i < _leftChild->_MY.size(); i++)
				{
					if (find(_IY.begin(), _IY.end(), _leftChild->_MY[i]) != _IY.end())
					{
						newIY.push_back(_leftChild->_MY[i]);
					}
				}
				//determine compensable set in left, to be verify
				for (int i = 0; i < newIY.size(); i++)
				{
					if (newIY[i] <= msg._aX._e && newIY[i] >= msg._aX._s)
					{
						CIYL.push_back(newIY[i]);
					}
				}
				sort(CIYL.begin(), CIYL.end(), cmpYWeightInc);
				Y cYL = CIYL[CIYL.size() - 1];

				//determine replaceable set in left part first
				vector<X> RMXL;
				Y bPre = betaPreforZL(msg._aX._s);
				for (int i = 0; i < _MXL.size(); i++)
				{
					if (_MXL[i]._s >= bPre)
					{
						RMXL.push_back(_MXL[i]);
					}
				}
				RMXL.push_back(msg._aX);
				//replaceable set got
				
				//determine maxEnd
				X maxEnd;
				sort(RMXL.begin(), RMXL.end(), cmpXEndInc);
				maxEnd = RMXL[RMXL.size() - 1];
				
				//determine CIY in right part
				vector<Y> IYR = getIYR();
				Y aPost = alphaPostforZR(maxEnd._e);
				vector<Y> CIYR;
				for (int i = 0; i < IYR.size(); i++)
				{
					if (IYR[i] <= aPost)
					{
						CIYR.push_back(IYR[i]);
					}
				}
				Y cYR;
				if (!CIYR.empty())
				{
					sort(CIYR.begin(), CIYR.end(), cmpYWeightInc);
					cYR = CIYR[CIYR.size() - 1];
				}
				if (cmpYWeightInc(cYR, cYL))
				{
					//left is heavier
					rMsg._bIY = cYL;
					_IY.erase(find(_IY.begin(), _IY.end(), cYL));

					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXL.push_back(msg._aX);

					rMsg._aMY = cYL;
					_MY.push_back(cYL);
					_MYL.push_back(cYL);
				}
				else
				{
					rMsg._bIY = cYR;
					_IY.erase(find(_IY.begin(), _IY.end(), cYR));

					rMsg._aMY = cYR;
					_MY.push_back(cYR);
					_MYR.push_back(cYR);

					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXL.push_back(msg._aX);
					_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
					_MXR.push_back(maxEnd);
				}
			}
			else
			{
				rMsg._bIY = msg._bIY;
				_IY.erase(find(_IY.begin(), _IY.end(), msg._bIY));

				rMsg._aMX = msg._aMX;
				_MX.push_back(msg._aMX);
				_MXL.push_back(msg._aX);

				rMsg._aMY = msg._aMY;
				_MY.push_back(msg._aMY);
				_MYL.push_back(msg._bIY);
			}
		}
	}
	else
	{
		//fail in L

		if (!msg._aIX.empty())
		{
			//infeasible
			if (msg._aIX == msg._aX)
			{
				//kick it self
				rMsg._aIX = msg._aX;
				_IX.push_back(msg._aX);

				rMsg._aMX = msg._aX;
				rMsg._bMX = msg._aX;
			}
			else
			{
				if (find(_MXL.begin(), _MXL.end(), msg._aIX) != _MXL.end())
				{
					//still in
					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXL.push_back(msg._aX);

					rMsg._bMX = msg._aIX;
					_MX.erase(find(_MX.begin(), _MX.end(), msg._aIX));
					_MXL.erase(find(_MXL.begin(), _MXL.end(), msg._aIX));

					rMsg._aIX = msg._aIX;
					_IX.push_back(msg._aIX);
					
				}
				else
				{
					//determine replaceable set in left part first
					vector<X> RMXL;
					Y bPre = betaPreforZL(msg._aX._s);
					for (int i = 0; i < _MXL.size(); i++)
					{
						if (_MXL[i]._s >= bPre)
						{
							RMXL.push_back(_MXL[i]);
						}
					}
					RMXL.push_back(msg._aX);
					//replaceable set got
					
					sort(RMXL.begin(), RMXL.end(), cmpXWeightInc);
					X aIXL = RMXL[0];

					//determine maxEnd
					X maxEnd;
					sort(RMXL.begin(), RMXL.end(), cmpXEndInc);
					maxEnd = RMXL[RMXL.size() - 1];

					if (maxEnd._e >= _rightChild->minY())
					{
						//may to right, infeasible or transfer
						Y aPost = alphaPostforZR(maxEnd._e);
						vector<X> RMXR;
						for (int i = 0; i < _MXR.size(); i++)
						{
							if (_MXR[i]._e <= aPost)
							{
								RMXR.push_back(_MXR[i]);
							}
						}
						vector<X> transferTest = RMXR;
						transferTest.push_back(maxEnd);
						sort(transferTest.begin(), transferTest.end(), cmpXEndInc);
						if (transferTest[transferTest.size() - 1]._e > _rightChild->maxY())
						{
							//transfer
							rMsg._aMX = msg._aX;
							_MX.push_back(msg._aX);
							_MXL.push_back(msg._aX);
							_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));

							rMsg._bMX = transferTest[transferTest.size() - 1];
							_MXR.push_back(maxEnd);
							_MXR.erase(find(_MXR.begin(), _MXR.end(), transferTest[transferTest.size() - 1]));
							_MX.erase(find(_MX.begin(), _MX.end(), transferTest[transferTest.size() - 1]));

							rMsg._aTX = transferTest[transferTest.size() - 1];
							_TX.push_back(transferTest[transferTest.size() - 1]);

						}
						else
						{
							if (!RMXR.empty())
							{
								sort(RMXR.begin(), RMXR.end(), cmpXWeightInc);
								X aIXR = RMXR[0];
								if (cmpXWeightInc(aIXL, aIXR))
								{
									rMsg._aMX = msg._aX;
									_MX.push_back(msg._aX);
									_MXL.push_back(msg._aX);

									rMsg._bMX = aIXL;
									_MX.erase(find(_MX.begin(), _MX.end(), aIXL));
									_MXL.erase(find(_MXL.begin(), _MXL.end(), aIXL));

									rMsg._aIX = aIXL;
									_IX.push_back(aIXL);
								}
								else
								{
									rMsg._aMX = msg._aX;
									_MX.push_back(msg._aX);
									_MXL.push_back(msg._aX);
									_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));

									rMsg._bMX = aIXR;
									_MX.erase(find(_MX.begin(), _MX.end(), aIXR));
									_MXR.push_back(maxEnd);

									rMsg._aIX = aIXR;
									_IX.push_back(aIXR);
								}
							}
							else
							{
								rMsg._aMX = msg._aX;
								_MX.push_back(msg._aX);
								_MXL.push_back(msg._aX);

								rMsg._bMX = aIXL;
								_MX.erase(find(_MX.begin(), _MX.end(), aIXL));
								_MXL.erase(find(_MXL.begin(), _MXL.end(), aIXL));

								rMsg._aIX = aIXL;
								_IX.push_back(aIXL);
							}
						}
					}
					else
					{
						rMsg._aMX = msg._aX;
						_MX.push_back(msg._aX);
						_MXL.push_back(msg._aX);

						rMsg._bMX = aIXL;
						_MX.erase(find(_MX.begin(), _MX.end(), aIXL));
						_MXL.erase(find(_MXL.begin(), _MXL.end(), aIXL));

						rMsg._aIX = aIXL;
						_IX.push_back(aIXL);
					}

				}
			}
		}
		else
		{
			//transfer

			//determine CIYL
			Y bPre = betaPreforZL(msg._aX._s);
			vector<Y> CIYL, IYL = getIYL();
			for (int i = 0; i < IYL.size(); i++)
			{
				if (IYL[i] >= bPre)
				{
					CIYL.push_back(IYL[i]);
				}
			}
			Y cYL;
			if (!CIYL.empty())
			{
				sort(CIYL.begin(), CIYL.end(), cmpYWeightInc);
				cYL = CIYL[CIYL.size() - 1];
			}

			//determine replaceable set in left part first
			vector<X> RMXL;
			for (int i = 0; i < _MXL.size(); i++)
			{
				if (_MXL[i]._s >= bPre)
				{
					RMXL.push_back(_MXL[i]);
				}
			}
			RMXL.push_back(msg._aX);
			//replaceable set got

			//determine maxEnd
			X maxEnd;
			sort(RMXL.begin(), RMXL.end(), cmpXEndInc);
			maxEnd = RMXL[RMXL.size() - 1];

			/*if (maxEnd._e < _rightChild->minY())
			{
				throw new exception();
			}*/

			//determine CIY in right part
			vector<Y> IYR = getIYR();
			Y aPost = alphaPostforZR(maxEnd._e);
			vector<Y> CIYR;
			for (int i = 0; i < IYR.size(); i++)
			{
				if (IYR[i] <= aPost)
				{
					CIYR.push_back(IYR[i]);
				}
			}

			Y cYR;
			if (!CIYR.empty())
			{
				sort(CIYR.begin(), CIYR.end(), cmpYWeightInc);
				cYR = CIYR[CIYR.size() - 1];
			}

			if (!cYL.empty() || !cYR.empty())
			{
				//conpense
				if (cmpYWeightInc(cYL, cYR))
				{
					//right is heavier
					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXL.push_back(msg._aX);
					_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
					_MXR.push_back(maxEnd);

					rMsg._aMY = cYR;
					_MY.push_back(cYR);
					_MYR.push_back(cYR);

					rMsg._bIY = cYR;
					_IY.erase(find(_IY.begin(), _IY.end(), cYR));
				}
				else
				{
					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXL.push_back(msg._aX);

					rMsg._aMY = cYL;
					_MY.push_back(cYL);
					_MYL.push_back(cYL);

					rMsg._bIY = cYL;
					_IY.erase(find(_IY.begin(), _IY.end(), cYL));
				}
				
			}
			else
			{
				sort(RMXL.begin(), RMXL.end(), cmpXWeightInc);
				X aIXL = RMXL[0];
				vector<X> RMXR;
				for (int i = 0; i < _MXR.size(); i++)
				{
					if (_MXR[i]._e <= aPost)
					{
						RMXR.push_back(_MXR[i]);
					}
				}
				vector<X> transferTest = RMXR;
				transferTest.push_back(maxEnd);
				sort(transferTest.begin(), transferTest.end(), cmpXEndInc);
				if (transferTest[transferTest.size() - 1]._e > _rightChild->maxY())
				{
					//transfer
					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXL.push_back(msg._aX);
					_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));

					rMsg._bMX = transferTest[transferTest.size() - 1];
					_MXR.push_back(maxEnd);
					_MXR.erase(find(_MXR.begin(), _MXR.end(), transferTest[transferTest.size() - 1]));
					_MX.erase(find(_MX.begin(), _MX.end(), transferTest[transferTest.size() - 1]));

					rMsg._aTX = transferTest[transferTest.size() - 1];
					_TX.push_back(transferTest[transferTest.size() - 1]);

				}
				else
				{
					if (!RMXR.empty())
					{
						sort(RMXR.begin(), RMXR.end(), cmpXWeightInc);
						X aIXR = RMXR[0];
						if (cmpXWeightInc(aIXL, aIXR))
						{
							rMsg._aMX = msg._aX;
							_MX.push_back(msg._aX);
							_MXL.push_back(msg._aX);

							rMsg._bMX = aIXL;
							_MX.erase(find(_MX.begin(), _MX.end(), aIXL));
							_MXL.erase(find(_MXL.begin(), _MXL.end(), aIXL));

							rMsg._aIX = aIXL;
							_IX.push_back(aIXL);
						}
						else
						{
							rMsg._aMX = msg._aX;
							_MX.push_back(msg._aX);
							_MXL.push_back(msg._aX);
							_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));

							rMsg._bMX = aIXR;
							_MX.erase(find(_MX.begin(), _MX.end(), aIXR));
							_MXR.push_back(maxEnd);

							rMsg._aIX = aIXR;
							_IX.push_back(aIXR);
						}
					}
					else
					{
						rMsg._aMX = msg._aX;
						_MX.push_back(msg._aX);
						_MXL.push_back(msg._aX);

						rMsg._bMX = aIXL;
						_MX.erase(find(_MX.begin(), _MX.end(), aIXL));
						_MXL.erase(find(_MXL.begin(), _MXL.end(), aIXL));

						rMsg._aIX = aIXL;
						_IX.push_back(aIXL);
					}
				}
			}

		}
	}

	return rMsg;
	
}


Msg TreeNode::insertXintoNodeR(Msg msg)
{
	Msg rMsg;
	rMsg._aX = msg._aX;
	_X.push_back(msg._aX);
	/*if (!msg._bIY.empty())
	{*/
		//success
		if (!msg._bIY.empty() && find(_IY.begin(), _IY.end(), msg._bIY) != _IY.end())
		{
			//success and still in
			rMsg._aMX = msg._aX;
			_MX.push_back(msg._aX);
			_MXR.push_back(msg._aX);

			rMsg._bIY = msg._bIY;
			_IY.erase(find(_IY.begin(), _IY.end(), msg._bIY));

			rMsg._aMY = msg._aMY;
			_MY.push_back(msg._aMY);
			_MYR.push_back(msg._aMY);
		}
		else
		{
			Y aPost = alphaPostforZR(msg._aX._e);
			vector<X> RMXR;
			vector<Y> CIYR, IYR = getIYR();
			for (int i = 0; i < _MXR.size(); i++)
			{
				if (_MXR[i]._e <= aPost)
				{
					RMXR.push_back(_MXR[i]);
				}
			}
			RMXR.push_back(msg._aX);
			for (int i = 0; i < IYR.size(); i++)
			{
				if (IYR[i] <= aPost)
				{
					CIYR.push_back(IYR[i]);
				}
			}

			sort(RMXR.begin(), RMXR.end(), cmpXBeginDec);
			X minBegin = RMXR[RMXR.size() - 1];
			Y bPre = betaPreforZL(minBegin._s);
			vector<X> RMXL;
			vector<Y> CIYL, IYL = getIYL();
			for (int i = 0; i < _MXL.size(); i++)
			{
				if (_MXL[i]._s >= bPre)
				{
					RMXL.push_back(_MXL[i]);
				}
			}
			for (int i = 0; i < IYL.size(); i++)
			{
				if (IYL[i] >= bPre)
				{
					CIYL.push_back(IYL[i]);
				}
			}

			if (CIYL.empty() && CIYR.empty())
			{
				//insert fail
				vector<X> transferTest = RMXR;
				sort(transferTest.begin(), transferTest.end(), cmpXEndInc);
				if (transferTest[transferTest.size() - 1]._e > _rightChild->maxY())
				{
					//transfer
					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXR.push_back(msg._aX);

					rMsg._bMX = transferTest[transferTest.size() - 1];
					_MXR.erase(find(_MXR.begin(), _MXR.end(), transferTest[transferTest.size() - 1]));
					_MX.erase(find(_MX.begin(), _MX.end(), transferTest[transferTest.size() - 1]));

					rMsg._aTX = transferTest[transferTest.size() - 1];
					_TX.push_back(transferTest[transferTest.size() - 1]);

				}
				else
				{
					X aIXR, aIXL;
					sort(RMXR.begin(), RMXR.end(), cmpXWeightInc);
					aIXR = RMXR[0];
					if (!RMXL.empty())
					{
						sort(RMXL.begin(), RMXL.end(), cmpXWeightInc);
						aIXL = RMXL[0];
						if (cmpXWeightInc(aIXL, aIXR))
						{
							Y bPost = betaPostforZL(aIXL._s);
							vector<X> backX;
							for (int i = 0; i < RMXR.size(); i++)
							{
								if (RMXR[i]._s <= bPost)
								{
									backX.push_back(RMXR[i]);
								}
							}
							sort(backX.begin(), backX.end(), cmpXEndInc);

							rMsg._aMX = msg._aX;
							_MX.push_back(msg._aX);
							_MXR.push_back(msg._aX);
							_MXR.erase(find(_MXR.begin(), _MXR.end(), backX[0]));
							_MXL.push_back(backX[0]);

							rMsg._bMX = aIXL;
							_MXL.push_back(backX[0]);
							_MXL.erase(find(_MXL.begin(), _MXL.end(), aIXL));

							rMsg._aIX = aIXL;
							_IX.push_back(aIXL);
						}
						else
						{
							rMsg._aMX = msg._aX;
							_MX.push_back(msg._aX);
							_MXR.push_back(msg._aX);

							rMsg._bMX = aIXR;
							_MX.erase(find(_MX.begin(), _MX.end(), aIXR));
							_MXR.erase(find(_MXR.begin(), _MXR.end(), aIXR));

							rMsg._aIX = aIXR;
							_IX.push_back(aIXR);
						}
					}
					else
					{
						rMsg._aMX = msg._aX;
						_MX.push_back(msg._aX);
						_MXR.push_back(msg._aX);

						rMsg._bMX = aIXR;
						_MX.erase(find(_MX.begin(), _MX.end(), aIXR));
						_MXR.erase(find(_MXR.begin(), _MXR.end(), aIXR));

						rMsg._aIX = aIXR;
						_IX.push_back(aIXR);
					}

					
						
					
				}
			}
			else
			{
				//insert success
				Y cYL, cYR;
				if (!CIYL.empty())
				{
					sort(CIYL.begin(), CIYL.end(), cmpYWeightInc);
					cYL = CIYL[CIYL.size()-1];
				}
				if (!CIYR.empty())
				{
					sort(CIYR.begin(), CIYR.end(), cmpYWeightInc);
					cYR = CIYR[CIYR.size()-1];
				}
				if (cmpYWeightInc(cYL, cYR))
				{
					//right is heavier
					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXR.push_back(msg._aX);

					rMsg._bIY = cYR;
					_IY.erase(find(_IY.begin(), _IY.end(), cYR));

					rMsg._aMY = cYR;
					_MY.push_back(cYR);
					_MYR.push_back(cYR);
				}
				else
				{
					//need calculate the backX
					Y bPost = betaPostforZL(cYL);
					vector<X> backX;
					for (int i = 0; i < RMXR.size(); i++)
					{
						if (RMXR[i]._s <= bPost)
						{
							backX.push_back(RMXR[i]);
						}
					}
					sort(backX.begin(), backX.end(), cmpXEndInc);
					
					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXR.push_back(msg._aX);
					_MXR.erase(find(_MXR.begin(), _MXR.end(), backX[0]));
					_MXL.push_back(backX[0]);

					rMsg._aMY = cYL;
					_MYR.push_back(cYL);
					_MY.push_back(cYL);

					rMsg._bIY = cYL;
					_IY.erase(find(_IY.begin(), _IY.end(), cYL));

					
				}
				
			}

		}
	//}
	//else
	//{
	//	//fail
	//}
	return rMsg;
}