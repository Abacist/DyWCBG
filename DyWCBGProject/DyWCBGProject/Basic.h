#pragma once
#pragma warning (disable:4018)

#include<iostream>
#include<set>
#include<list>
#include<vector>
#include<stack>
#include<algorithm>

using namespace std;


class Y
{
public:
	int _value;	
	int _w;
	Y();


	bool empty();
	bool operator<(const Y& y);
	bool operator<=(const Y& y);
	bool operator>(const Y& y);
	bool operator>=(const Y& y);
	bool operator==(const Y& y);
	bool operator!=(const Y& y);
	bool operator<(const int& y);
	bool operator<=(const int& y);
	bool operator>(const int& y);
	bool operator>=(const int& y);
	bool operator==(const int& y);
	bool operator!=(const int& y);
};

ostream& operator<<(ostream& os, const Y& rhs);

class X
{
public:
	int _id;	

	Y _s;
	Y _e;
	int _w;	
	X();
	bool empty();
	bool operator==(const X& x);
	bool operator!=(const X& x);
};

ostream& operator<<(ostream& os, const X& rhs);


class Edge
{
public:
	X x;
	Y y;
	Edge(X x, Y y);
};

class Msg
{
public:
	
	X _aX;
	X _bX;
	Y _aY;
	Y _bY;

	X _aMX;
	X _bMX;
	X _aTX;
	X _bTX;
	X _aIX;
	X _bIX;

	Y _aMY;
	Y _bMY;
	Y _aIY;
	Y _bIY;

	//next two domains are for insert X
	Y _t1;
	Y _t2;
	//t1 t2 is the stable reachable Y range of the inserted X in child before the X is inserted
	int _stableYCount;
	//bool _replace;
	//when insert X, tight == true means this x has been inserted into child and returned tight(replace an X)

	Msg();

};

bool cmpYValueInc(Y y1, Y y2);
bool cmpYValueDec(Y, Y);
bool cmpYWeightInc(Y y1, Y y2);
bool cmpXEndInc(X x1, X x2);
bool cmpXBeginDec(X, X);
bool cmpXWeightInc(X x1, X x2);
bool cmpXID(X x1, X x2);


bool setEqual(vector<X>, vector<X>);
bool setEqual(vector<Y>, vector<Y>);

void formGloverMatching(const vector<X> vX, const vector<Y> vY, vector<X>& vZ);
void formPlaxtonMWM(const vector<X> vX, const vector<Y> vY, vector<X>& vZ, vector<Y>& vMY);
void getGloverInfo(vector<X> allX, vector<Y> allY, vector<Edge> & M, vector<Y> & IY);

bool operator<(int s, Y y);

bool operator<=(int s, Y y);

bool operator>(int s, Y y);

bool operator>=(int s, Y y);

bool operator==(int s, Y y);

bool operator!=(int s, Y y);

istream& operator>>(istream& input, X& x);

istream& operator>>(istream& input, Y& y);
