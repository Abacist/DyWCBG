#include<iostream>
#include<fstream>
#include"Basic.h"
#include"Tree.h"

#pragma warning (disable:4018)
#pragma warning (disable:4012)

using namespace std;

const int mY =				30;
const int ur =				30;
int verifyEachUpdate =		1;		//0 not verify, !0 verify
int gen =					1;
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
			//cout << "============================Case " << cases++ << " passed!" << endl;
		}
		else
		{
			cout << endl << endl << endl << endl << "Update not satify, please check! Error code: " << flag << endl;
			throw new exception();
		}

		pTree->verifyGloverInfo(flag, errorNode);
		if (flag == 0)
		{
			cout << "============================Case " << cases++ << " passed!" << endl;
		}
		else
		{
			cout << endl << endl << endl << endl << "Glover info not satify, please check!" << endl;
			throw new exception();
		}

		//pTree->printMY();
		//pTree->printRMY();
		//getchar();

		//cout << "constructing glover info..." << endl;
		
		/*pTree->constructGloverInfo();
		for (int i = 0; i < pTree->_root->_MX.size(); i++)
		{
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
				cout << "Query X: " << pTree->_root->_MX[i]._id << "\tpass" << endl;
			}
			else
			{
				throw new exception();
			}
		}*/




		//cout << "Query X pass" << endl;
		////getchar();

		////pTree->constructGloverInfo();
		//for (int i = 0; i < pTree->_root->_MY.size(); i++)
		//{
		//	//cout << pTree->_root->_MY[i]._value << " will be query" << endl;
		//	X x1 = pTree->queryYMate(pTree->_root->_MY[i]._value);
		//	X x0;
		//	for (int j = 0; j < pTree->_root->_MatchingG.size(); j++)
		//	{
		//		if (pTree->_root->_MatchingG[j].y._value == pTree->_root->_MY[i]._value)
		//		{
		//			x0 = pTree->_root->_MatchingG[j].x;
		//			break;
		//		}

		//	}
		//	//cout << x0._e._value << endl;

		//	if (x0._e == x1._e)
		//	{
		//		cout << "Query Y: " << pTree->_root->_MY[i]._value << "\tpass" << endl;
		//	}
		//	else
		//	{
		//		throw new exception();
		//	}
		//}

		//getchar();

		//output for extended verify
		/*ofstream out("base.txt");
		out << pTree->_root->_Y.size() << endl;
		for (int i = 0; i < pTree->_root->_Y.size(); i++)
		{
			out << pTree->_root->_Y[i]._value << " " << 0 << endl;
		}
		out << pTree->_root->_MY.size() << endl;
		for (int i = 0; i < pTree->_root->_MY.size(); i++)
		{
			out << pTree->_root->_MY[i]._value << " " << 0 << endl;
		}

		for (int i = 0; i < pTree->_root->_MX.size(); i++)
		{
			out << 1 << " " << pTree->_root->_MX[i]._id <<" "<< pTree->_root->_MX[i]._s._value<<" "
				<< pTree->_root->_MX[i]._e._value<< " " << 0 << endl;
		}
		out << "$" << endl;
		out.close();

		ofstream mat("matchingStandard.txt");
		for (int i = 0; i < pTree->_root->_MatchingG.size(); i++)
		{
			mat << pTree->_root->_MatchingG[i].x._id << "\t" << pTree->_root->_MatchingG[i].y._value << endl;
		}
		mat.close();




		getchar();*/

	}
	return 0;
}

