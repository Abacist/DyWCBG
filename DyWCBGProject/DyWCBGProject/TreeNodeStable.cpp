#include"Tree.h"


void TreeNode::updatet1t2inLeafX(Msg & msg)
{
	//update t1, t2
	msg._t1 = msg._aX._s;
	msg._t2 = msg._aX._e;

	Y temp = alphaPostforZRS(msg._aX._e);
	if (cmpYValueInc(msg._t2, temp))
	{
		msg._t2 = temp;
	}

	msg._stableYNumBetweent1t2 = 0;
	for (int i = 0; i < _MYS.size(); i++)
	{
		if (_MYS[i] <= msg._t2)
		{
			msg._stableYNumBetweent1t2++;
		}
	}
}


void TreeNode::updatet1t2inInternalNodeX(Msg & msg)
{
	Y t1 = msg._t1;
	Y t2 = msg._t2;
	int count = 0;
	for (int i = 0; i<_MYS.size(); i++)
	{
		if (_MYS[i] >= t1 && _MYS[i] <= t2)
		{
			count++;
		}
	}

	if (msg._aX._s < _rightChild->minY())
	{
		//from left
		
		if (t2 <= _leftChild->maxY() && count == msg._stableYNumBetweent1t2)
		{
			//t1 t2 keeps
		}
		else
		{
			//EE and ES
			Y bPre = betaPreforZLS(msg._aX._s);
			vector<X> RMXLS;
			for (int i = 0; i < _MXLS.size(); i++)
			{
				if (_MXLS[i]._s >= bPre)
				{
					RMXLS.push_back(_MXLS[i]);
				}
			}
			RMXLS.push_back(msg._aX);
			sort(RMXLS.begin(), RMXLS.end(), cmpXEndInc);
			X maxEnd = RMXLS[RMXLS.size() - 1];
			Y aPost = alphaPostforZRS(maxEnd._e);
			vector<X> RMXRS;
			Y bPre1 = bPre;
			for (int i = 0; i < _MXRS.size(); i++)
			{
				if (_MXRS[i]._e <= aPost)
				{
					RMXRS.push_back(_MXRS[i]);
				}
			}
			if (!RMXRS.empty())
			{
				X minBegin;
				sort(RMXRS.begin(), RMXRS.end(), cmpXBeginDec);
				minBegin = RMXRS[RMXRS.size() - 1];
				Y bPre1 = betaPreforZLS(minBegin._s);
			}
			msg._t1 = bPre1;
			msg._t2 = aPost;
		}
	}
	else
	{
		//from right
		if (count == msg._stableYNumBetweent1t2)
		{
			//keeps
		}
		else
		{
			Y aPost = alphaPostforZLS(msg._aX._e);
			vector<X> RMXRS;
			for (int i = 0; i < _MXRS.size(); i++)
			{
				if (_MXRS[i]._e <= aPost)
				{
					RMXRS.push_back(_MXRS[i]);
				}
			}
			X minBegin;
			sort(RMXRS.begin(), RMXRS.end(), cmpXBeginDec);
			minBegin = RMXRS[RMXRS.size() - 1];
			Y bPre1 = betaPreforZLS(minBegin._s);
			msg._t1 = bPre1;
			msg._t2 = aPost;
		}
	}

	msg._stableYNumBetweent1t2 = 0;
	for (int i = 0; i < _MYS.size(); i++)
	{
		if (_MYS[i] <= msg._t2 && _MYS[i]>=t1)
		{
			msg._stableYNumBetweent1t2++;
		}
	}
}

void TreeNode::updateStableSetinLeaf(Msg msg)
{
	if (!msg._bIY.empty() && msg._aX._e <= maxY() || !msg._aTX.empty() && msg._aX._e <= maxY())
	{
		vector<Y> cIYS, IYS = _IYS;
		for (int i = 0; i < IYS.size(); i++)
		{
			if (IYS[i] <= msg._t2)
			{
				cIYS.push_back(IYS[i]);
			}
		}
		sort(cIYS.begin(), cIYS.end(), cmpYWeightInc);
		_MXS.push_back(msg._aX);
		_MXRS.push_back(msg._aX);
		_MYS.push_back(cIYS[cIYS.size() - 1]);
		_MYRS.push_back(cIYS[cIYS.size() - 1]);
		_IYS.erase(find(_IYS.begin(), _IYS.end(), cIYS[cIYS.size() - 1]));
	}
	else if (!msg._aIX.empty())
	{
		_MXS.push_back(msg._aX);
		_MXRS.push_back(msg._aX);
		_MXS.erase(find(_MXS.begin(), _MXS.end(), msg._aIX));
		_MXRS.erase(find(_MXRS.begin(), _MXRS.end(), msg._aIX));
	}
}

void TreeNode::updateStableSetinInternalNode(Msg msg, Y t1inChild, Y t2inChild)
{
	if (msg._aX._e > maxY())
	{
		//no change
	}
	else
	{
		if (msg._aX._s <= _leftChild->maxY())
		{
			//from left
			/*if (t2inChild == msg._t2)
			{*///interval keeps
			if (!msg._bIY.empty() || !msg._aTX.empty())
			{
				//augment
				_MXS.push_back(msg._aX);

				vector<Y> cIYS;
				for (int i = 0; i < _IYS.size(); i++)
				{
					if (_IYS[i] >= msg._t1 && _IYS[i] <= msg._t2)
					{
						cIYS.push_back(_IYS[i]);
					}
				}
				sort(cIYS.begin(), cIYS.end(), cmpYWeightInc);
				Y cY = cIYS[cIYS.size() - 1]; 
				_MYS.push_back(cY);
				_IYS.erase(find(_IYS.begin(), _IYS.end(), cY));

				if (msg._t2 <= _leftChild->maxY())
				{
					_MXLS.push_back(msg._aX);
					_MYLS.push_back(cY);
				}
				else
				{
					if (cY >= _rightChild->minY())
					{
						
						//the origin interval may to right
						vector<X> RMXLS;
						Y bPre = betaPreforZLS(msg._aX._s);//equal to t1?
						for (int i = 0; i < _MXLS.size(); i++)
						{
							if (_MXLS[i]._s >= bPre)
							{
								RMXLS.push_back(_MXLS[i]);
							}
						}
						RMXLS.push_back(msg._aX);
						sort(RMXLS.begin(), RMXLS.end(), cmpXEndInc);
						_MXLS.push_back(msg._aX);
						_MXLS.erase(find(_MXLS.begin(), _MXLS.end(), RMXLS[RMXLS.size() - 1]));
						_MXRS.push_back(RMXLS[RMXLS.size() - 1]);
						_MYRS.push_back(cY);
					}
					else
					{
						

						vector<X> RMXLS;
						Y bPre = betaPreforZLS(msg._aX._s);//equal to t1?
						for (int i = 0; i < _MXLS.size(); i++)
						{
							if (_MXLS[i]._s >= bPre)
							{
								RMXLS.push_back(_MXLS[i]);
							}
						}
						RMXLS.push_back(msg._aX);
						sort(RMXLS.begin(), RMXLS.end(), cmpXEndInc);
						X maxEnd = RMXLS[RMXLS.size() - 1];

						Y bPost = betaPostforZLS(cY);
						Y aPost = alphaPostforZRS(maxEnd._e);
						vector<X> backX;
						for (int i = 0; i < _MXRS.size(); i++)
						{
							if (_MXRS[i]._e <= aPost && _MXRS[i]._s <= bPost)
							{
								backX.push_back(_MXRS[i]);
							}
						}
						sort(backX.begin(), backX.end(), cmpXEndInc);

						if (cY >= bPre)
						{
							//direct or swap
							if (!backX.empty()&&cmpXEndInc(backX[0], maxEnd))
							{
								//swap
								_MXLS.push_back(msg._aX);
								_MXLS.erase(find(_MXLS.begin(), _MXLS.end(), maxEnd));
								_MXRS.push_back(maxEnd);
								_MXRS.erase(find(_MXRS.begin(), _MXRS.end(), backX[0]));
								_MXLS.push_back(backX[0]);
								_MYLS.push_back(cY);
							}
							else
							{
								_MXLS.push_back(msg._aX);
								_MYLS.push_back(cY);
							}
						}
						else
						{
							//forward and back
							
							_MXLS.push_back(msg._aX);
							_MXLS.erase(find(_MXLS.begin(), _MXLS.end(), maxEnd));
							_MXRS.push_back(maxEnd);
							_MXRS.erase(find(_MXRS.begin(), _MXRS.end(), backX[0]));
							_MXLS.push_back(backX[0]);
							_MYLS.push_back(cY);
						}
					}
				}
			}
			else
			{
				_MXS.push_back(msg._aX);
				_MXS.erase(find(_MXS.begin(), _MXS.end(), msg._aIX));
				//infeasible
				if (find(_MXRS.begin(), _MXRS.end(), msg._aIX) != _MXRS.end())
				{
					//in right
					vector<X> RMXLS;
					Y bPre = betaPreforZLS(msg._aX._s);
					for (int i = 0; i < _MXLS.size(); i++)
					{
						if (_MXLS[i]._s >= bPre)
						{
							RMXLS.push_back(_MXLS[i]);
						}
					}
					RMXLS.push_back(msg._aX);
					sort(RMXLS.begin(), RMXLS.end(), cmpXEndInc);
					_MXLS.push_back(msg._aX);
					_MXLS.erase(find(_MXLS.begin(), _MXLS.end(), RMXLS[RMXLS.size() - 1]));
					_MXRS.push_back(RMXLS[RMXLS.size() - 1]);
				}
				else
				{
					//in left or kick itself
					if (msg._aIX._s >= t1inChild)
					{
						//direct
						_MXLS.push_back(msg._aX);
						_MXLS.erase(find(_MXLS.begin(), _MXLS.end(), msg._aIX));
					}
					else
					{
						vector<X> RMXLS;
						Y bPre = betaPreforZLS(msg._aX._s);//equal to t1?
						for (int i = 0; i < _MXLS.size(); i++)
						{
							if (_MXLS[i]._s >= bPre)
							{
								RMXLS.push_back(_MXLS[i]);
							}
						}
						RMXLS.push_back(msg._aX);
						sort(RMXLS.begin(), RMXLS.end(), cmpXEndInc);
						X maxEnd = RMXLS[RMXLS.size() - 1];

						Y bPost = betaPostforZLS(msg._aIX._s);
						Y aPost = alphaPostforZRS(maxEnd._e);
						vector<X> backX;
						for (int i = 0; i < _MXRS.size(); i++)
						{
							if (_MXRS[i]._e <= aPost && _MXRS[i]._s <= bPost)
							{
								backX.push_back(_MXRS[i]);
							}
						}
						sort(backX.begin(), backX.end(), cmpXEndInc);

						_MXLS.push_back(msg._aX);
						_MXLS.erase(find(_MXLS.begin(), _MXLS.end(), maxEnd));
						_MXRS.push_back(maxEnd);
						_MXRS.erase(find(_MXRS.begin(), _MXRS.end(), backX[0]));
						_MXLS.push_back(backX[0]);
						_MXLS.erase(find(_MXLS.begin(), _MXLS.end(), msg._aIX));
					}
				}
			}

			//}
			//else
			//{
			//	//interval change
			//	//t2 becomes bigger, t1 may become smaller

			//}
		}
		else
		{
			//from right
			if (!msg._bIY.empty() || !msg._aTX.empty())
			{
				//augment
				_MXS.push_back(msg._aX);

				vector<Y> cIYS;
				for (int i = 0; i < _IYS.size(); i++)
				{
					if (_IYS[i] >= msg._t1 && _IYS[i] <= msg._t2)
					{
						cIYS.push_back(_IYS[i]);
					}
				}
				sort(cIYS.begin(), cIYS.end(), cmpYWeightInc);
				Y cY = cIYS[cIYS.size() - 1];
				_MYS.push_back(cY);
				_IYS.erase(find(_IYS.begin(), _IYS.end(), cY));


				if (cY >= _rightChild->minY())
				{
					_MXRS.push_back(msg._aX);
					_MYRS.push_back(cY);
				}
				else
				{
					Y aPost = alphaPostforZRS(msg._aX._e);
					Y bPost = alphaPostforZLS(cY);
					vector<X> backX;
					for (int i = 0; i < _MXRS.size(); i++)
					{
						if (_MXRS[i]._e <= aPost && _MXRS[i]._s <= bPost)
						{
							backX.push_back(_MXRS[i]);
						}
					}
					sort(backX.begin(), backX.end(), cmpXEndInc);
					_MXRS.push_back(msg._aX);
					_MXRS.erase(find(_MXRS.begin(), _MXRS.end(), backX[0]));
					_MXLS.push_back(backX[0]);
					_MYLS.push_back(cY);
				}


			}
			else
			{
				//infeasible, replace
				_MXS.push_back(msg._aX);
				_MXS.erase(find(_MXS.begin(), _MXS.end(), msg._aIX));

				if (find(_MXLS.begin(), _MXLS.end(), msg._aIX) != _MXLS.end())
				{
					Y aPost = alphaPostforZRS(msg._aX._e);
					Y bPost = alphaPostforZLS(msg._aIX._s);
					vector<X> backX;
					for (int i = 0; i < _MXRS.size(); i++)
					{
						if (_MXRS[i]._e <= aPost && _MXRS[i]._s <= bPost)
						{
							backX.push_back(_MXRS[i]);
						}
					}
					sort(backX.begin(), backX.end(), cmpXEndInc);
					_MXRS.push_back(msg._aX);
					_MXRS.erase(find(_MXRS.begin(), _MXRS.end(), backX[0]));
					_MXLS.push_back(backX[0]);
					_MXLS.erase(find(_MXLS.begin(), _MXLS.end(), msg._aIX));
				}
				else
				{
					_MXRS.push_back(msg._aX);
					_MXRS.erase(find(_MXRS.begin(), _MXRS.end(), msg._aIX));
				}
			}


		}
	}
}

Y TreeNode::alphaPostforZLS(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXLS;
	tempY = _MYLS;
	if (tempY.empty())
	{
		return y;
	}
	else
	{
		sort(tempY.begin(), tempY.end(), cmpYValueInc);
		sort(tempZ.begin(), tempZ.end(), cmpXEndInc);
		Y tY;
		//will not be empty
		if (y < tempY[0])
		{
			return y;
		}
		else
		{
			tY = tempZ[tempZ.size() - 1]._e;

			int i = 0;
			while (i + 1 <= tempY.size())
			{
				if (tempY[i] <= y)
				{
					i++;
				}
				else
				{
					break;
				}
			}
			i--;
			//found the maxmal Y0 such that Y0<=y


			for (; i + 2 <= tempY.size(); i++)
			{
				if (tempZ[i]._e < tempY[i + 1])
				{
					//tight
					tY = tempZ[i]._e;
					break;
				}
			}
			//else tY keeps tempZ[tempZ.size() - 1]._e;	

			if (tY < y)
			{
				tY = y;
			}//without this jude, RMX is right, but CIY is not right
			return tY;

		}
	}

}


Y TreeNode::alphaPostforZRS(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXRS;
	tempY = _MYRS;
	if (tempY.empty())
	{
		return y;
	}
	else
	{
		sort(tempY.begin(), tempY.end(), cmpYValueInc);
		sort(tempZ.begin(), tempZ.end(), cmpXEndInc);
		Y tY;
		//will not be empty
		if (y < tempY[0])
		{
			return y;
		}
		else
		{
			tY = tempZ[tempZ.size() - 1]._e;

			int i = 0;
			while (i + 1 <= tempY.size())
			{
				if (tempY[i] <= y)
				{
					i++;
				}
				else
				{
					break;
				}
			}
			i--;
			//found the maxmal Y0 such that Y0<=y


			for (; i + 2 <= tempY.size(); i++)
			{
				if (tempZ[i]._e < tempY[i + 1])
				{
					//tight
					tY = tempZ[i]._e;
					break;
				}
			}
			//else tY keeps tempZ[tempZ.size() - 1]._e;	

			if (tY < y)
			{
				tY = y;
			}//without this jude, RMX is right, but CIY is not right
			return tY;

		}
	}

}

Y TreeNode::betaPreforZLS(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXLS;
	tempY = _MYLS;
	if (tempY.empty())
	{
		return y;
	}
	else
	{
		sort(tempY.begin(), tempY.end(), cmpYValueDec);
		sort(tempZ.begin(), tempZ.end(), cmpXBeginDec);
		Y tY;
		//will not be empty
		if (y > tempY[0])
		{
			return y;
		}
		else
		{
			tY = tempZ[tempZ.size() - 1]._s;

			int i = 0;
			while (i + 1 <= tempY.size())
			{
				if (tempY[i] >= y)
				{
					i++;
				}
				else
				{
					break;
				}
			}
			i--;
			//found the maxmal Y0 such that Y0>=y


			for (; i + 2 <= tempY.size(); i++)
			{
				if (tempZ[i]._s > tempY[i + 1])
				{
					//tight
					tY = tempZ[i]._s;
					break;
				}
			}
			//else tY keeps tempZ[tempZ.size() - 1]._s;	

			if (tY > y)
			{
				tY = y;
			}
			return tY;

		}
	}

}

Y TreeNode::alphaPreforZRS(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXRS;
	tempY = _MYRS;
	if (tempY.empty())
	{
		/*throw new exception();*/
		return y;
	}
	else
	{
		sort(tempY.begin(), tempY.end(), cmpYValueInc);
		sort(tempZ.begin(), tempZ.end(), cmpXEndInc);
		Y tY;
		if (y <= tempY[0])
		{
			return y;
		}
		else
		{
			tY = tempY[0];
			if (find(tempY.begin(), tempY.end(), y) == tempY.end())
			{
				tempY.push_back(y);
				sort(tempY.begin(), tempY.end(), cmpYValueInc);
			}
			int i = 0;
			int tightIndex = -1;
			while (true)
			{
				if (tempY[i] == y)
				{
					i--;
					break;
				}
				else
				{
					if (tempZ[i]._e < tempY[i + 1])
					{
						//tight
						tightIndex = i;
						//break;
					}
					i++;
				}
			}
			if (tightIndex != -1)
			{
				tY = tempY[tightIndex + 1];
			}
			return tY;

		}
	}

}


Y TreeNode::betaPostforZLS(Y y)
{
	vector<X> tempZ;
	vector<Y> tempY;
	tempZ = _MXLS;
	tempY = _MYLS;
	if (tempY.empty())
	{
		/*throw new exception();*/
		return y;
	}
	else
	{
		sort(tempY.begin(), tempY.end(), cmpYValueDec);
		sort(tempZ.begin(), tempZ.end(), cmpXBeginDec);
		Y tY;
		if (y >= tempY[0])
		{
			return y;
		}
		else
		{
			tY = tempY[0];
			if (find(tempY.begin(), tempY.end(), y) == tempY.end())
			{
				tempY.push_back(y);
				sort(tempY.begin(), tempY.end(), cmpYValueDec);
			}
			int i = 0;
			int tightIndex = -1;
			while (true)
			{
				if (tempY[i] == y)
				{
					i--;
					break;
				}
				else
				{
					if (tempZ[i]._s > tempY[i + 1])
					{
						//tight
						tightIndex = i;
						//break;
					}
					i++;
				}
			}

			if (tightIndex != -1)
			{
				tY = tempY[tightIndex + 1];
			}
			return tY;

		}
	}

}
//
//vector<Y> TreeNode::getIYS()
//{
//	vector<Y> IYS;
//	for (int i = 0; i < _IY.size(); i++)
//	{
//		if (find(_MYS.begin(), _MYS.end(), _IY[i]) == _MYS.end())
//		{
//			IYS.push_back(_IY[i]);
//		}
//	}
//	return IYS;
//}