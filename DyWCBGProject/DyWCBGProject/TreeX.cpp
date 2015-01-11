#include"Tree.h"

extern int verifyEachUpdate;

Msg TreeNode::insertXintoLeaf(X x)
{
	
	Msg msg;
	msg._aX = x;
	_X.push_back(x);

	updatet1t2inLeafX(msg);
	
	if (_Y.empty())
	{
		throw new exception();
		_IX.push_back(x);
		msg._aIX = x;
		//return msg;
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

				//return msg;
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

				//return msg;
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
	
	updateStableSetinLeaf(msg);
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
	int countInChild = msg._stableYNumBetweent1t2;
	bool forceSwap = false;

	Msg rMsg;
	rMsg._t1 = msg._t1;
	rMsg._t2 = msg._t2;
	rMsg._stableYNumBetweent1t2 = msg._stableYNumBetweent1t2;
	rMsg._aX = msg._aX;
	_X.push_back(msg._aX);
	updatet1t2inInternalNodeX(rMsg);

	if (!msg._bIY.empty())
	{
		//success in child
		//must success in P

		vector<Y> CIYLCorrect, CIYRCorrect, CIYL2Correct, CIYL, CIYR, CIYL2;

		getCompensableYL(msg._aX, t1inChild, t2inChild, countInChild, CIYL, CIYR, CIYL2);
		if (verifyEachUpdate)
		{
			getCompensableYLForce(msg._aX, CIYLCorrect, CIYRCorrect, CIYL2Correct);
			int flag = verifyCIY(CIYLCorrect, CIYRCorrect, CIYL2Correct, CIYL, CIYR, CIYL2);
			if (flag)
			{
				throw new exception();
				int a = 1;
			}
		}


		if (CIYL.empty() && CIYR.empty() && CIYL2.empty())
		{
			throw new exception();
			//no possible in success case
		}
		else
		{
			vector<Y> CIY = CIYL;
			for (int i = 0; i < CIYR.size(); i++) CIY.push_back(CIYR[i]);
			for (int i = 0; i < CIYL2.size(); i++) CIY.push_back(CIYL2[i]);
			sort(CIY.begin(), CIY.end(), cmpYWeightInc);
			Y cY = CIY[CIY.size() - 1];
			if (find(CIYL.begin(), CIYL.end(), cY) != CIYL.end())
			{
				//success
				int allCount = 0;
				for (int i = 0; i < _MY.size(); i++)
				{
					if (_MY[i] >= t1inChild && _MY[i] <= t2inChild)
					{
						allCount++;
					}
				}
				
				if (t2inChild < _rightChild->minY() && countInChild == allCount)
				{
					//only to left
					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXL.push_back(msg._aX);

					rMsg._aMY = cY;
					_MY.push_back(cY);
					_MYL.push_back(cY);

					rMsg._bIY = cY;
					_IY.erase(find(_IY.begin(), _IY.end(), cY));
				}
				else
				{
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
					sort(RMXL.begin(), RMXL.end(), cmpXEndInc);
					X maxEnd = RMXL[RMXL.size() - 1];
					Y aPost = alphaPostforZR(maxEnd._e);
					vector<X> RMXR;
					for (int i = 0; i < _MXR.size(); i++)
					{
						if (_MXR[i]._e <= aPost)
						{
							RMXR.push_back(_MXR[i]);
						}
					}
					Y bPost = betaPostforZL(cY);
					vector<X> backX;
					for (int i = 0; i < RMXR.size(); i++)
					{
						if (RMXR[i]._s <= bPost)
						{
							backX.push_back(RMXR[i]);
						}
					}
					if (backX.empty())
					{
						rMsg._aMX = msg._aX;
						_MX.push_back(msg._aX);
						_MXL.push_back(msg._aX);

						rMsg._aMY = cY;
						_MY.push_back(cY);
						_MYL.push_back(cY);

						rMsg._bIY = cY;
						_IY.erase(find(_IY.begin(), _IY.end(), cY));
					}
					else
					{
						sort(backX.begin(), backX.end(), cmpXEndInc);
						if (cmpXEndInc(backX[0], maxEnd))
						{
							//swap
							rMsg._aMX = msg._aX;
							_MX.push_back(msg._aX);
							_MXL.push_back(msg._aX);
							_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
							_MXR.push_back(maxEnd);
							_MXR.erase(find(_MXR.begin(), _MXR.end(), backX[0]));
							_MXL.push_back(backX[0]);

							rMsg._aMY = cY;
							_MY.push_back(cY);
							_MYL.push_back(cY);

							rMsg._bIY = cY;
							_IY.erase(find(_IY.begin(), _IY.end(), cY));
						}
						else
						{
							rMsg._aMX = msg._aX;
							_MX.push_back(msg._aX);
							_MXL.push_back(msg._aX);

							rMsg._aMY = cY;
							_MY.push_back(cY);
							_MYL.push_back(cY);

							rMsg._bIY = cY;
							_IY.erase(find(_IY.begin(), _IY.end(), cY));
						}
					}
				}
				
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
				
				sort(RMXL.begin(), RMXL.end(), cmpXEndInc);
				X maxEnd = RMXL[RMXL.size() - 1];


				if (find(CIYR.begin(), CIYR.end(), cY) != CIYR.end())
				{
					rMsg._aMX = msg._aX;
					_MX.push_back(msg._aX);
					_MXL.push_back(msg._aX);
					_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
					_MXR.push_back(maxEnd);

					rMsg._aMY = cY;
					_MY.push_back(cY);
					_MYR.push_back(cY);

					rMsg._bIY = cY;
					_IY.erase(find(_IY.begin(), _IY.end(), cY));
				}
				else
				{
					vector<X> RMXR;
					Y aPost = alphaPostforZR(maxEnd._e);
					for (int i = 0; i < _MXR.size(); i++)
					{
						if (_MXR[i]._e <= aPost)
						{
							RMXR.push_back(_MXR[i]);
						}
					}
					Y bPost = betaPostforZL(cY);
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
					_MXL.push_back(msg._aX);
					_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
					_MXR.push_back(maxEnd);
					_MXR.erase(find(_MXR.begin(), _MXR.end(), backX[0]));
					_MXL.push_back(backX[0]);

					rMsg._aMY = cY;
					_MY.push_back(cY);
					_MYL.push_back(cY);

					rMsg._bIY = cY;
					_IY.erase(find(_IY.begin(), _IY.end(), cY));

					
					
					
					
				}
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
							throw new exception();
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

								sort(RMXR.begin(), RMXR.end(), cmpXBeginDec);
								X minBegin = RMXR[RMXR.size() - 1];

								vector<X> RMXL2;
								Y bPre = betaPreforZL(minBegin._s);

								for (int i = 0; i < _MXL.size(); i++)
								{
									if (_MXL[i]._s >= bPre)
									{
										if (find(RMXL.begin(), RMXL.end(), _MXL[i]) == RMXL.end())
										{
											RMXL2.push_back(_MXL[i]);
										}
									}
								}
								X aIXL2;
								if (!RMXL2.empty())
								{
									sort(RMXL2.begin(), RMXL2.end(), cmpXWeightInc);
									aIXL2 = RMXL2[0];
								}
								if (aIXL2.empty() || cmpXWeightInc(aIXL, aIXL2) || cmpXWeightInc(aIXR, aIXL2))
								{
									if (cmpXWeightInc(aIXL, aIXR))
									{
										//may need swap
										vector<X> backX;
										Y bPost = betaPostforZL(aIXL._s);
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
										_MXL.push_back(msg._aX);

										rMsg._bMX = aIXL;
										_MX.erase(find(_MX.begin(), _MX.end(), aIXL));
										_MXL.erase(find(_MXL.begin(), _MXL.end(), aIXL));

										rMsg._aIX = aIXL;
										_IX.push_back(aIXL);

										//swap
										if (!backX.empty() && cmpXEndInc(backX[0], maxEnd) && aIXL != msg._aX)
										{
											_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
											_MXR.push_back(maxEnd);
											_MXR.erase(find(_MXR.begin(), _MXR.end(), backX[0]));
											_MXL.push_back(backX[0]);
											forceSwap = true;
										}
									}
									else
									{
										rMsg._aMX = msg._aX;
										_MX.push_back(msg._aX);
										_MXL.push_back(msg._aX);
										_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));

										rMsg._bMX = aIXR;
										_MX.erase(find(_MX.begin(), _MX.end(), aIXR));
										_MXR.erase(find(_MXR.begin(), _MXR.end(), aIXR));
										_MXR.push_back(maxEnd);

										rMsg._aIX = aIXR;
										_IX.push_back(aIXR);
									}
								}
								else
								{
									vector<X> backX;
									Y bPost = betaPostforZL(aIXL2._s);
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
									_MXL.push_back(msg._aX);
									_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
									_MXR.push_back(maxEnd);
									_MXR.erase(find(_MXR.begin(), _MXR.end(), backX[0]));
									_MXL.push_back(backX[0]);

									rMsg._bMX = aIXL2;
									_MX.erase(find(_MX.begin(), _MX.end(), aIXL2));
									_MXL.erase(find(_MXL.begin(), _MXL.end(), aIXL2));

									rMsg._aIX = aIXL2;
									_IX.push_back(aIXL2);

									forceSwap = true;
								}
							}
							else
							{
								throw new exception();
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
						throw new exception();
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
			//tbd
			/*vector<Y> CIYL, CIYR, CIYL2;
			getCompensableYLForce(msg._aX, CIYL, CIYR, CIYL2);*/
			vector<Y> CIYLCorrect, CIYRCorrect, CIYL2Correct, CIYL, CIYR, CIYL2;
			
			getCompensableYL(msg._aX, t1inChild, t2inChild, countInChild, CIYL, CIYR, CIYL2);
			if (verifyEachUpdate)
			{
				getCompensableYLForce(msg._aX, CIYLCorrect, CIYRCorrect, CIYL2Correct);
				int flag = verifyCIY(CIYLCorrect, CIYRCorrect, CIYL2Correct, CIYL, CIYR, CIYL2);
				if (flag)
				{
					throw new exception();
					int a = 1;
				}
			}
			


			if (CIYL.empty() && CIYR.empty() && CIYL2.empty())
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
							sort(RMXR.begin(), RMXR.end(), cmpXBeginDec);
							X minBegin = RMXR[RMXR.size() - 1];

							vector<X> RMXL2;
							Y bPre = betaPreforZL(minBegin._s);

							for (int i = 0; i < _MXL.size(); i++)
							{
								if (_MXL[i]._s >= bPre)
								{
									if (find(RMXL.begin(), RMXL.end(), _MXL[i]) == RMXL.end())
									{
										RMXL2.push_back(_MXL[i]);
									}
								}
							}
							X aIXL2;
							if (!RMXL2.empty())
							{
								sort(RMXL2.begin(), RMXL2.end(), cmpXWeightInc);
								aIXL2 = RMXL2[0];
							}
							if (aIXL2.empty() || cmpXWeightInc(aIXL, aIXL2) || cmpXWeightInc(aIXR, aIXL2))
							{
								if (cmpXWeightInc(aIXL, aIXR))
								{
									//may need swap
									vector<X> backX;
									Y bPost = betaPostforZL(aIXL._s);
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
									_MXL.push_back(msg._aX);

									rMsg._bMX = aIXL;
									_MX.erase(find(_MX.begin(), _MX.end(), aIXL));
									_MXL.erase(find(_MXL.begin(), _MXL.end(), aIXL));

									rMsg._aIX = aIXL;
									_IX.push_back(aIXL);

									//swap
									if (!backX.empty() && cmpXEndInc(backX[0], maxEnd) && aIXL != msg._aX)
									{
										_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
										_MXR.push_back(maxEnd);
										_MXR.erase(find(_MXR.begin(), _MXR.end(), backX[0]));
										_MXL.push_back(backX[0]);
										forceSwap = true;
									}
								}
								else
								{
									rMsg._aMX = msg._aX;
									_MX.push_back(msg._aX);
									_MXL.push_back(msg._aX);
									_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));

									rMsg._bMX = aIXR;
									_MX.erase(find(_MX.begin(), _MX.end(), aIXR));
									_MXR.erase(find(_MXR.begin(), _MXR.end(), aIXR));
									_MXR.push_back(maxEnd);

									rMsg._aIX = aIXR;
									_IX.push_back(aIXR);
								}
							}
							else
							{
								vector<X> backX;
								Y bPost = betaPostforZL(aIXL2._s);
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
								_MXL.push_back(msg._aX);
								_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
								_MXR.push_back(maxEnd);
								_MXR.erase(find(_MXR.begin(), _MXR.end(), backX[0]));
								_MXL.push_back(backX[0]);

								rMsg._bMX = aIXL2;
								_MX.erase(find(_MX.begin(), _MX.end(), aIXL2));
								_MXL.erase(find(_MXL.begin(), _MXL.end(), aIXL2));

								rMsg._aIX = aIXL2;
								_IX.push_back(aIXL2);

								forceSwap = true;
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
			else
			{
				vector<Y> CIY = CIYL;
				for (int i = 0; i < CIYR.size(); i++) CIY.push_back(CIYR[i]);
				for (int i = 0; i < CIYL2.size(); i++) CIY.push_back(CIYL2[i]);
				sort(CIY.begin(), CIY.end(), cmpYWeightInc);
				Y cY = CIY[CIY.size() - 1];
				if (find(CIYL.begin(), CIYL.end(), cY) != CIYL.end())
				{
					//success
					int allCount = 0;
					for (int i = 0; i < _MY.size(); i++)
					{
						if (_MY[i] >= t1inChild && _MY[i] <= t2inChild)
						{
							allCount++;
						}
					}

					if (t2inChild < _rightChild->minY() && countInChild == allCount)
					{
						//only to left
						rMsg._aMX = msg._aX;
						_MX.push_back(msg._aX);
						_MXL.push_back(msg._aX);

						rMsg._aMY = cY;
						_MY.push_back(cY);
						_MYL.push_back(cY);

						rMsg._bIY = cY;
						_IY.erase(find(_IY.begin(), _IY.end(), cY));
					}
					else
					{
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
						sort(RMXL.begin(), RMXL.end(), cmpXEndInc);
						X maxEnd = RMXL[RMXL.size() - 1];
						Y aPost = alphaPostforZR(maxEnd._e);
						vector<X> RMXR;
						for (int i = 0; i < _MXR.size(); i++)
						{
							if (_MXR[i]._e <= aPost)
							{
								RMXR.push_back(_MXR[i]);
							}
						}
						Y bPost = betaPostforZL(cY);
						vector<X> backX;
						for (int i = 0; i < RMXR.size(); i++)
						{
							if (RMXR[i]._s <= bPost)
							{
								backX.push_back(RMXR[i]);
							}
						}
						if (backX.empty())
						{
							rMsg._aMX = msg._aX;
							_MX.push_back(msg._aX);
							_MXL.push_back(msg._aX);

							rMsg._aMY = cY;
							_MY.push_back(cY);
							_MYL.push_back(cY);

							rMsg._bIY = cY;
							_IY.erase(find(_IY.begin(), _IY.end(), cY));
						}
						else
						{
							sort(backX.begin(), backX.end(), cmpXEndInc);
							if (cmpXEndInc(backX[0], maxEnd))
							{
								//swap
								rMsg._aMX = msg._aX;
								_MX.push_back(msg._aX);
								_MXL.push_back(msg._aX);
								_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
								_MXR.push_back(maxEnd);
								_MXR.erase(find(_MXR.begin(), _MXR.end(), backX[0]));
								_MXL.push_back(backX[0]);

								rMsg._aMY = cY;
								_MY.push_back(cY);
								_MYL.push_back(cY);

								rMsg._bIY = cY;
								_IY.erase(find(_IY.begin(), _IY.end(), cY));
							}
							else
							{
								rMsg._aMX = msg._aX;
								_MX.push_back(msg._aX);
								_MXL.push_back(msg._aX);

								rMsg._aMY = cY;
								_MY.push_back(cY);
								_MYL.push_back(cY);

								rMsg._bIY = cY;
								_IY.erase(find(_IY.begin(), _IY.end(), cY));
							}
						}
					}
					//vector<X> RMXL = getReachableSetinLeftPart(msg._aX);//tbd
					//RMXL.push_back(msg._aX);
					//sort(RMXL.begin(), RMXL.end(), cmpXEndInc);
					//X maxEnd = RMXL[RMXL.size() - 1];
					////for phi 8
					//if (maxEnd._e <= _leftChild->maxY())
					//{
					//	rMsg._aMX = msg._aX;
					//	_MX.push_back(msg._aX);
					//	_MXL.push_back(msg._aX);

					//	rMsg._aMY = cY;
					//	_MY.push_back(cY);
					//	_MYL.push_back(cY);

					//	rMsg._bIY = cY;
					//	_IY.erase(find(_IY.begin(), _IY.end(), cY));
					//}
					//else
					//{
					//	Y aPost = alphaPostforZR(maxEnd._e);
					//	vector<X> RMXR;
					//	for (int i = 0; i < _MXR.size(); i++)
					//	{
					//		if (_MXR[i]._e <= aPost)
					//		{
					//			RMXR.push_back(_MXR[i]);
					//		}
					//	}
					//	Y bPost = betaPostforZL(cY);
					//	vector<X> backX;
					//	for (int i = 0; i < RMXR.size(); i++)
					//	{
					//		if (RMXR[i]._s <= bPost)
					//		{
					//			backX.push_back(RMXR[i]);
					//		}
					//	}
					//	if (backX.empty())
					//	{
					//		rMsg._aMX = msg._aX;
					//		_MX.push_back(msg._aX);
					//		_MXL.push_back(msg._aX);

					//		rMsg._aMY = cY;
					//		_MY.push_back(cY);
					//		_MYL.push_back(cY);

					//		rMsg._bIY = cY;
					//		_IY.erase(find(_IY.begin(), _IY.end(), cY));
					//	}
					//	else
					//	{
					//		sort(backX.begin(), backX.end(), cmpXEndInc);
					//		if (cmpXEndInc(backX[0], maxEnd))
					//		{
					//			//swap
					//			rMsg._aMX = msg._aX;
					//			_MX.push_back(msg._aX);
					//			_MXL.push_back(msg._aX);
					//			_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
					//			_MXR.push_back(maxEnd);
					//			_MXR.erase(find(_MXR.begin(), _MXR.end(), backX[0]));
					//			_MXL.push_back(backX[0]);

					//			rMsg._aMY = cY;
					//			_MY.push_back(cY);
					//			_MYL.push_back(cY);

					//			rMsg._bIY = cY;
					//			_IY.erase(find(_IY.begin(), _IY.end(), cY));
					//		}
					//		else
					//		{
					//			rMsg._aMX = msg._aX;
					//			_MX.push_back(msg._aX);
					//			_MXL.push_back(msg._aX);

					//			rMsg._aMY = cY;
					//			_MY.push_back(cY);
					//			_MYL.push_back(cY);

					//			rMsg._bIY = cY;
					//			_IY.erase(find(_IY.begin(), _IY.end(), cY));
					//		}
					//	}

					//}

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

					sort(RMXL.begin(), RMXL.end(), cmpXEndInc);
					X maxEnd = RMXL[RMXL.size() - 1];


					if (find(CIYR.begin(), CIYR.end(), cY) != CIYR.end())
					{
						rMsg._aMX = msg._aX;
						_MX.push_back(msg._aX);
						_MXL.push_back(msg._aX);
						_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
						_MXR.push_back(maxEnd);

						rMsg._aMY = cY;
						_MY.push_back(cY);
						_MYR.push_back(cY);

						rMsg._bIY = cY;
						_IY.erase(find(_IY.begin(), _IY.end(), cY));
					}
					else
					{
						vector<X> RMXR;
						Y aPost = alphaPostforZR(maxEnd._e);
						for (int i = 0; i < _MXR.size(); i++)
						{
							if (_MXR[i]._e <= aPost)
							{
								RMXR.push_back(_MXR[i]);
							}
						}
						Y bPost = betaPostforZL(cY);
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
						_MXL.push_back(msg._aX);
						_MXL.erase(find(_MXL.begin(), _MXL.end(), maxEnd));
						_MXR.push_back(maxEnd);
						_MXR.erase(find(_MXR.begin(), _MXR.end(), backX[0]));
						_MXL.push_back(backX[0]);

						rMsg._aMY = cY;
						_MY.push_back(cY);
						_MYL.push_back(cY);

						rMsg._bIY = cY;
						_IY.erase(find(_IY.begin(), _IY.end(), cY));





					}
				}



			}

			
		}
	}

	updateStableSetinInternalNode(rMsg, forceSwap);
	return rMsg;
	
}


Msg TreeNode::insertXintoNodeR(Msg msg)
{
	Y t1inChild = msg._t1, t2inChild = msg._t2;
	int countInChild = msg._stableYNumBetweent1t2;

	Msg rMsg;
	rMsg._t1 = msg._t1;
	rMsg._t2 = msg._t2;
	rMsg._stableYNumBetweent1t2 = msg._stableYNumBetweent1t2;
	rMsg._aX = msg._aX;
	_X.push_back(msg._aX);
	updatet1t2inInternalNodeX(rMsg);
	
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
		if (!msg._aIX.empty() &&
			(find(_MXR.begin(), _MXR.end(), msg._aIX) != _MXR.end() || msg._aIX == msg._aX))
		{
			//infeasible and still in
			rMsg._aMX = msg._aX;
			_MXR.push_back(msg._aX);
			_MX.push_back(msg._aX);

			rMsg._bMX = msg._aIX;
			_MX.erase(find(_MX.begin(), _MX.end(), msg._aIX));
			_MXR.erase(find(_MXR.begin(), _MXR.end(), msg._aIX));

			rMsg._aIX = msg._aIX;
			_IX.push_back(msg._aIX);
		}
		else if (!msg._aTX.empty() &&
			(find(_MXR.begin(), _MXR.end(), msg._aTX) != _MXR.end() || msg._aTX == msg._aX))
		{
			//transfer and still in
			rMsg._aMX = msg._aX;
			_MXR.push_back(msg._aX);
			_MX.push_back(msg._aX);

			rMsg._bMX = msg._aTX;
			_MX.erase(find(_MX.begin(), _MX.end(), msg._aTX));
			_MXR.erase(find(_MXR.begin(), _MXR.end(), msg._aTX));

			rMsg._aTX = msg._aTX;
			_TX.push_back(msg._aTX);
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
							//_MXL.push_back(backX[0]);
							_MXL.erase(find(_MXL.begin(), _MXL.end(), aIXL));
							_MX.erase(find(_MX.begin(), _MX.end(), aIXL));

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
					cYL = CIYL[CIYL.size() - 1];
				}
				if (!CIYR.empty())
				{
					sort(CIYR.begin(), CIYR.end(), cmpYWeightInc);
					cYR = CIYR[CIYR.size() - 1];
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
					_MYL.push_back(cYL);
					_MY.push_back(cYL);

					rMsg._bIY = cYL;
					_IY.erase(find(_IY.begin(), _IY.end(), cYL));


				}

			}
		}


	}
	updateStableSetinInternalNode(rMsg);
	return rMsg;
}