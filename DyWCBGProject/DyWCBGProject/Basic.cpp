#include<fstream>
#include<Windows.h>
#include"Basic.h"
#pragma warning (disable:4018)

void generator(char* fileName, int maxY, int updateRange, int weightRange)
{
	vector<X> curExistsX;
	vector<Y> curExistsY;

	ofstream out(fileName);
	
	SYSTEMTIME lpsystime;
	GetLocalTime(&lpsystime);
	srand(lpsystime.wMinute * 1000 + lpsystime.wMilliseconds);

	out << 1 << endl;
	Y y0;
	y0._value = 1;
	y0._w = rand() % weightRange;
	curExistsY.push_back(y0);
	out << y0._value << " " << y0._w << endl;

	/*out << maxY << endl;
	for (int i = 1; i <= maxY; i++)
	{
		Y y0;
		y0._value = i;
		y0._w = rand() % weightRange;
		curExistsY.push_back(y0);
		out << y0._value << " " << y0._w << endl;
	}*/


	/*y0._value = maxY;
	y0._w = rand() % weightRange;
	curExistsY.push_back(y0);
	out << y0._value << " " << y0._w << endl;*/


	int i = 1;
	while (i<=updateRange)
	{
		if (rand() % 2 == 0)
		{
			//generate X
			int s = rand() % maxY + 1;
			int e = rand() % (maxY)+1;
			if (s > e)
			{
				int temp = e;
				e = s;
				s = temp;
			}
			int w = rand() % weightRange;
			X x;
			x._id = i++;
			x._s._value = s;
			x._e._value = e;
			x._w = w;
			if (find(curExistsY.begin(), curExistsY.end(), x._s) == curExistsY.end())
			{
				Y ys;
				ys._value = x._s._value;
				ys._w = rand() % weightRange;
				curExistsY.push_back(ys);
				out << 3<<" "<<ys._value << " " << ys._w << endl;
			}
			if (x._e <= maxY && (find(curExistsY.begin(), curExistsY.end(), x._e) == curExistsY.end()))
			{
				Y ye;
				ye._value = x._e._value;
				ye._w = rand() % weightRange;
				curExistsY.push_back(ye);
				out << 3<<" "<<ye._value << " " << ye._w << endl;
			}
			out << 1 << " " << x._id << " " << x._s._value << " " << x._e._value << " " << x._w << endl;
			curExistsX.push_back(x);
		}
		else
		{
			//generate Y
			Y y;
			y._value = rand() % maxY + 1;
			y._w = rand() % weightRange;
			if (find(curExistsY.begin(), curExistsY.end(), y) == curExistsY.end())
			{
				curExistsY.push_back(y);
				out << 3 << " " << y._value << " " << y._w << endl;
			}

		}
		
	}
	out << '$' << endl;


	out.close();
}

Y::Y()
{
	_value = INT_MIN;
	_w = INT_MIN;
}

bool Y::empty()
{
	Y y1;
	y1._value = INT_MIN;
	Y y2;
	y2._value = INT_MAX;
	return *this == y1 || *this == y2;
}
bool Y::operator<(const Y& y)
{
	return this->_value < y._value;
}
bool Y::operator<=(const Y& y)
{
	return this->_value <= y._value;
}
bool Y::operator>(const Y& y)
{
	return this->_value > y._value;
}
bool Y::operator>=(const Y& y)
{
	return this->_value >= y._value;
}
bool Y::operator==(const Y& y)
{
	return this->_value == y._value;
}
bool Y::operator!=(const Y& y)
{
	return this->_value != y._value;
}

bool Y::operator<(const int& y)
{
	return this->_value < y;
}
bool Y::operator<=(const int& y)
{
	return this->_value <= y;
}
bool Y::operator>(const int& y)
{
	return this->_value > y;
}
bool Y::operator>=(const int& y)
{
	return this->_value >= y;
}
bool Y::operator==(const int& y)
{
	return this->_value == y;
}
bool Y::operator!=(const int& y)
{
	return this->_value != y;
}


bool X::empty()
{
	X x1;
	x1._id = INT_MIN;
	X x2;
	x2._id = INT_MAX;
	return *this == x1 || *this == x2;
}
bool X::operator==(const X& x)
{
	return this->_id == x._id;
}
bool X::operator!=(const X& x)
{
	return !(*this == x);
}

X::X()
{
	_id = INT_MIN;
	_s._value = INT_MIN;
	_s._w = INT_MIN;
	_e._value = INT_MIN;
	_e._w = INT_MIN;
	_w = INT_MIN;
}

Edge::Edge(X x, Y y)
{
	this->x = x;
	this->y = y;
}

Msg::Msg()
{
	X x;
	Y y;

	_aX = _bX = _aMX = _bMX = _aIX = _bIX = _aTX = _bTX = x;
	_t1 = _t2 = _aY = _bY = _aMY = _bMY = _aIY = _bIY = y;
	_stableYCount = 0;
	//_replace = false;
}

ostream& operator<<(ostream& os, const Y& rhs)
{
	os << rhs._value << rhs._w;
	return os;
}

ostream& operator<<(ostream& os, const X& rhs)
{
	os << "X: " << rhs._id << " " << rhs._s << " " << rhs._e << " " << rhs._w;
	return os;
}

istream& operator>>(istream& input, X& x)
{
	input >> x._id >> x._s._value >> x._e._value >> x._w;
	return input;
}

istream& operator>>(istream& input, Y& y)
{
	input >> y._value >> y._w;
	return input;
}

bool operator<(int s, Y y)
{
	return s < y._value;
}

bool operator<=(int s, Y y)
{
	return s <= y._value;
}

bool operator>(int s, Y y)
{
	return s > y._value;
}

bool operator>=(int s, Y y)
{
	return s >= y._value;
}

bool operator==(int s, Y y)
{
	return s == y._value;
}

bool operator!=(int s, Y y)
{
	return s != y._value;
}


bool cmpYValueInc(Y y1, Y y2)
{
	return y1._value < y2._value;
}

bool cmpYValueDec(Y y1, Y y2)
{
	return y1._value > y2._value;
}

bool cmpYWeightInc(Y y1, Y y2)
{
	if (y1._w < y2._w)
	{
		return true;
	}
	if (y1._w == y2._w && y1._value > y2._value)
	{
		return true;
	}
	return false;
}

bool cmpXEndInc(X x1, X x2)
{
	if (x1._e < x2._e)
	{
		return true;
	}
	if (x1._e == x2._e && x1._s < x2._s)
	{
		return true;
	}
	if (x1._e == x2._e && x1._s == x2._s && x1._id < x2._id)
	{
		return true;
	}
	return false;
}

bool cmpXBeginDec(X x1, X x2)
{
	if (x1._s > x2._s)
	{
		return true;
	}
	if (x1._s == x2._s && x1._id > x2._id)
	{
		return true;
	}
	return false;

}

bool cmpXWeightInc(X x1, X x2)
{
	if (x1._w < x2._w)
	{
		return true;
	}
	if (x1._w == x2._w)
	{
		return !cmpXEndInc(x1, x2);
	}
	return false;
}

bool cmpXID(X x1, X x2)
{
	return x1._id < x2._id;
}



void formGloverMatching(const vector<X> vX, const vector<Y> vY, vector<X>& vZ)
{
	vector<X> XX = vX;
	vector<Y> YY = vY;
	vZ.clear();
	sort(YY.begin(), YY.end(), cmpYValueInc);

	for (int i = 0; i < YY.size(); i++)
	{
		vector<X> selectedX;
		for (int j = 0; j < XX.size(); j++)
		{
			if (XX[j]._s <= YY[i] && XX[j]._e >= YY[i])
			{
				selectedX.push_back(XX[j]);
			}
		}

		if (selectedX.size() == 0)
		{
			continue;
		}
		else
		{
			X x = selectedX[0];
			for (int j = 0; j < selectedX.size(); j++)
			{
				if (cmpXEndInc(selectedX[j], x))
				{
					x = selectedX[j];
				}
			}

			vZ.push_back(x);
			vector<X>::iterator it = find(XX.begin(), XX.end(), x);
			XX.erase(it);
			if (vZ.size() == vX.size() || vZ.size() == vY.size())
			{
				return;
			}
		}
	}
	return;
}

void formPlaxtonMWM(const vector<X> vX, const vector<Y> vY, vector<X>& vZ, vector<Y>& vMY)
{
	vector<X> XX = vX;
	vector<Y> YY = vY;

	sort(XX.begin(), XX.end(), cmpXWeightInc);
	sort(YY.begin(), YY.end(), cmpYValueInc);

	vZ.clear();
	for (int i = XX.size() - 1; i >= 0; i--)
	{
		vector<X> tmpZ;
		vZ.push_back(XX[i]);
		formGloverMatching(vZ, YY, tmpZ);
		if (tmpZ.size() < vZ.size())
		{
			vector<X>::iterator it = find(vZ.begin(), vZ.end(), XX[i]);
			vZ.erase(it);
		}
		if (vZ.size() == vX.size() || vZ.size() == vY.size())
		{
			break;
		}
	}
	//vZ finished
	vMY.clear();
	sort(YY.begin(), YY.end(), cmpYWeightInc);
	for (int i = YY.size() - 1; i >= 0; i--)
	{
		vector<X> tempZ;
		vMY.push_back(YY[i]);
		formGloverMatching(vZ, vMY, tempZ);
		if (tempZ.size() < vMY.size())
		{
			vMY.erase(find(vMY.begin(), vMY.end(), YY[i]));
		}
		if (vMY.size() == vZ.size())
		{
			break;
		}
	}
}



bool setEqual(vector<X> x1, vector<X> x2)
{
	if (x1.size() != x2.size())
	{
		return false;
	}
	else
	{

		sort(x1.begin(), x1.end(), cmpXID);
		sort(x2.begin(), x2.end(), cmpXID);
		for (int i = 0; i < x1.size(); i++)
		{
			if (x1[i] != x2[i])
			{
				return false;
			}
		}
		return true;
	}
}

bool setEqual(vector<Y> x1, vector<Y> x2)
{
	if (x1.size() != x2.size())
	{
		return false;
	}
	else
	{

		sort(x1.begin(), x1.end(), cmpYValueInc);
		sort(x2.begin(), x2.end(), cmpYValueInc);
		for (int i = 0; i < x1.size(); i++)
		{
			if (x1[i] != x2[i])
			{
				return false;
			}
		}
		return true;
	}
}