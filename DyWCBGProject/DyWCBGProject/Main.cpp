#include<iostream>
#include<fstream>
#include"Basic.h"
#include"Tree.h"

#pragma warning (disable:4018)
#pragma warning (disable:4012)

using namespace std;

const int mY =				50;
const int ur =				200;
int verifyEachUpdate =		0;		//0 not verify, !0 verify
int gen =					1;

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
				if (x._id == 3)
				{
					int a = 1;
				}
				pTree->insertXinTree(x);
				if (verifyEachUpdate)
				{
					int flag;
					TreeNode* errorNode;
					pTree->verifyInvariantsRecur(flag, errorNode);
					if (flag == 0)
					{
						//cout << "Insert Y pass, id " << y._id << endl;
					}
					else
					{
						cout << endl << endl << endl << endl << "After Insert X, Not satify, please check! Error code: " << flag << endl
							<< "X id:" << x._id << endl;
						goto End;
					}
				}

			}break;


			case '2':
			{

			}break;
			case '3':
			{
				//insert Y
				Y y;
				in >> y;
				if (y._value == 5)
				{
					int a = 1;
				}
				pTree->insertYinTree(y);
				if (verifyEachUpdate)
				{
					int flag;
					TreeNode* errorNode;
					pTree->verifyInvariantsRecur(flag, errorNode);
					if (flag == 0)
					{
						//cout << "Insert Y pass, id " << y._id << endl;
					}
					else
					{
						cout << endl << endl << endl << endl << "After Insert Y, Not satify, please check! Error code: " << flag << endl
							<< "Y value:" << y._value << endl;
						goto End;
					}
				}


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

	}
End:
	return 0;
}

