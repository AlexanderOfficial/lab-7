#define _CRT_SECURE_NO_WARNINGS
#include "..//Text/TTextProg.h"
#include "..//Text/TProgLink.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

static int recD;

TTextProg::TTextProg() 
{
	pFirst = NULL;
	pCurr = NULL; ///
	TStack<TProgLink> stack;
}

void TTextProg::Read(std::string fn) 
{
	ifstream ifs(fn);
	recD = 0;
	pFirst = ReadRec(ifs);
}

bool isBegin = false;
bool isConst = false;
bool isVar = false;
char tstr[81];
char tstrBegin[81] = {'b','e','g','i','n','\0'};
int numBegin = 0;
TProgLink* TTextProg::ReadRec(ifstream& ifs)
{
	TProgLink* pHead, * pRC, * tmp;
	pHead = pRC = NULL;
	//char tstr[81];
	//char tstrPred[81];
	char word2[81];
	ifs.getline(tstr, 80, '\n');
	while (!ifs.eof())
	{
		while (tstr[0] == ' ')
		{
			strcpy(word2, &tstr[1]);
			strcpy(tstr, word2);
		}
		if ((tstr[0] == 'c') && (tstr[1] == 'o') && (tstr[2] == 'n') && (tstr[3] == 's') && (tstr[4] == 't'))
		{
			isConst = true; 
			tmp = new TProgLink(tstr);
			if (pHead == NULL)
			{
				pHead = pRC = tmp;
			}
			else
			{
				pRC->pNext = tmp;
				pRC = pRC->pNext;
			}
			do 
			{
				pRC->pDown = ReadRec(ifs);
			} while ((tstr[0] != 'v') && (tstr[1] != 'a') && (tstr[2] != 'r'));

		}

		if ((tstr[0] == 'v') && (tstr[1] == 'a') && (tstr[2] == 'r') && (isConst == false))
		{
			isVar = true;
			tmp = new TProgLink(tstr);
			if (pHead == NULL)
			{
				pHead = pRC = tmp;
			}
			else
			{
				pRC->pNext = tmp;
				pRC = pRC->pNext;
			}
			do
			{
				pRC->pDown = ReadRec(ifs);
			} while ((tstr[0] != 'b') && (tstr[1] != 'e') && (tstr[2] != 'g') && (tstr[3] != 'i') && (tstr[4] != 'n'));
		}
		if ((tstr[0] == 'b') && (tstr[1] == 'e') && (tstr[2] == 'g') && (tstr[3] == 'i') && (tstr[4] == 'n') && (isVar == true))
		{
			numBegin = 1;
			isVar = false;
			break;
		}

		if ((tstr[0] == 'e') && (tstr[1] == 'n') && (tstr[2] == 'd') && (tstr[3] == '\0'))
		{
			break;
		}
		if ((tstr[0] == 'v') && (tstr[1] == 'a') && (tstr[2] == 'r') && (isConst == true))
		{
			isConst = false;
			break;
		}
		else
			if ((tstr[0] == 'b') && (tstr[1] == 'e') && (tstr[2] == 'g') && (tstr[3] == 'i') && (tstr[4] == 'n') && (isVar == false))
			{

				if (numBegin == 1)
				{
					tmp = new TProgLink(tstrBegin);
					if (pHead == NULL)
					{
						pHead = pRC = tmp;
					}
					else
					{
						pRC->pNext = tmp;
						pRC = pRC->pNext;
					}
					numBegin = 0;
				}
				pRC->pDown = ReadRec(ifs);
				//numBegin = 0;
			}
			else 
			{
				while (tstr[0] == ' ')
				{
					strcpy(word2, &tstr[1]);
					strcpy(tstr, word2);
				}
				tmp = new TProgLink(tstr);
				if (pHead == NULL)
				{
					pHead = pRC = tmp;
				}
				else
				{
					pRC->pNext = tmp;
					pRC = pRC->pNext;
				}
			}
		if ((tstr[0] == 'e') && (tstr[1] == 'n') && (tstr[2] == 'd') && (tstr[3] == '.'))
		{
			tmp = new TProgLink(tstr);
			if (pHead == NULL)
			{
				pHead = pRC = tmp;
			}
			else
			{
				pRC->pNext = tmp;
				pRC = pRC->pNext;
			}
			break;
		}
		if (!pRC->pDown)
		{

		}
		ifs.getline(tstr, 80, '\n');
	}
	return pHead;
}


void TTextProg::Write(std::string fn) 
{
	ofstream ofs(fn);
	recD = 0;
	WriteRec(ofs, pFirst);
}


void TTextProg::WriteRec(ofstream& ofs, TProgLink* pWC) 
{
	for (int i = 0; i < recD; i++) 
	{
		ofs << "   ";
	}
	ofs << pWC->str << endl;

	if (pWC->pDown) 
	{
		recD++;
		WriteRec(ofs, pWC->pDown);
	}
	if (pWC->pNext) 
	{
		WriteRec(ofs, pWC->pNext);
		recD++;
	}
	recD--;
}