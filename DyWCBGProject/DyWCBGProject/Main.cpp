#include<iostream>
#include<fstream>
#include"Basic.h"
#include"Tree.h"

#pragma warning (disable:4018)
#pragma warning (disable:4012)

using namespace std;

const int mY =				8;
const int ur =				15;
int verifyEachUpdate =		1;		//0 not verify, !0 verify
int gen =					0;
int breakID =				3;

void generator(char* fileName = "input.txt", int MaxY = mY, int UpdateRange = ur, int WeightRange = 1000);

int main()
{
	int cases = 1;

	while (true)
	{
		if (gen)
		{
			generator(); 
		}
		ifstream in("input.txt");
		if (!in)
		{
			cout << "input file open error" << endl;
			return 0;
		}
		//get the range of Y
		int rangeOfY;
		in >> rangeOfY;
		vector<Y> tempVecY;
		for (int i = 0; i < rangeOfY; i++)
		{
			Y temp;
			in >> temp;
			tempVecY.push_back(temp);
		}
		Tree* pTree = new Tree(tempVecY);

		char command;
		while (!in.eof())
		{
			in >> command;
			if (command == '#')
			{
				char s[100];
				in.get(s, 100, '\n');
				continue;
			}
			if (command == '$')
			{
				break;
			}

			switch (command)
			{
				//insert an X
			case '1':
			{
				X x;
				in >> x;
				if (x._id == breakID)
				{
					int a = 1;
				}
				pTree->insertXinTree(x);
			
			}break;



			case '2':
			{

			}break;
			case '3':
			{
				//insert Y
				Y y;
				in >> y;
				if (y._value == breakID)
				{
					int a = 1;
				}
				pTree->insertYinTree(y);
				


			}break;
			case '4':
			{

			}break;
			case '5':
			{

			}break;
			case '6':
			{
				X x;
				in >> x;
			}break;
			case '7':
			{

			}break;
			case '8':
			{
				Y y;
				in >> y;

			}break;
			}


		}
		in.close();
		//verify
		int flag;
		TreeNode* errorNode;
		pTree->verifyInvariantsRecur(flag, errorNode);
		if (flag == 0)
		{
			cout << "============================Case " << cases++ << " passed!" << endl;
		}
		else
		{
			cout << endl << endl << endl << endl << "Not satify, please check! Error code: " << flag << endl;
			goto End;
		}

		//pTree->printMY();
		//pTree->printRMY();
		//getchar();

		cout << "constructing glover info..." << endl;
		pTree->constructGloverInfo();

		for (int i = 0; i < pTree->_root->_MX.size(); i++)
		{
			if (pTree->_root->_MX[i]._id == 14)
			{
				int a = 0;
			}
			Y y1 = pTree->queryXMate(pTree->_root->_MX[i]._id);
			Y y0;
			for (int j = 0; j < pTree->_root->_MatchingG.size(); j++)
			{
				if (pTree->_root->_MatchingG[j].x._id == pTree->_root->_MX[i]._id)
				{
					y0 = pTree->_root->_MatchingG[j].y;
					break;
				}

			}
			if (y0 == y1)
			{
				cout << "Query X: " << pTree->_root->_MX[i]._id << "\tPass!" << endl;
			}
			else
			{
				throw new exception();
			}
		}
	}
End:
	return 0;
}

