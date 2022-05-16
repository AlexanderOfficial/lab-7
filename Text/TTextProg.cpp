#define _CRT_SECURE_NO_WARNINGS
#include "..//Text/TTextProg.h"
#include "..//Text/TProgLink.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

static int recD;

vector <string> ivector = { "if","var","const","else", "Read", "Write" };

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


void TTextProg::TCompiller()
{
	recD = 0;
	recTCompiller(pFirst);
}

void TTextProg::recTCompiller(TProgLink* pWC)
{
	program_information progInf;
	string helpString;
	string helpString2;
	for (int i = 0; i < recD; i++)
	{
		cout << "   ";
	}
	helpString = string(pWC->str);
	//cout << helpString << endl;

	if (helpString.find("program", 0) == 0) 
	{
		helpString = helpString.erase(0, 7);
		progInf.nameOfProgram = helpString;
		cout << helpString << endl;
	}
	if (helpString.find("const", 0) == 0) 
	{
		cout << "Константы: " << endl;
		isConst = 1;
		recTCompiller(pWC->pDown);
		isConst = 0;
	}

	if (helpString.find("var", 0) == 0)
	{
		cout << "Переменные: " << endl;
		isVar = 1;
		recTCompiller(pWC->pDown);
		isVar = 0;
	}
	
	if (pWC->pDown)
	{
		recD++;
		recTCompiller(pWC->pDown);
	}
	if ((isConst == 1)||(isVar == 1))
	{
		helpString = string(pWC->str);
		if (isVar == 1)
			itsVar(helpString);
		if (isConst == 1)
			itsConst(helpString);
	}
	if (pWC->pNext)
	{
		
		recTCompiller(pWC->pNext);
		recD++;
	}
	recD--;
}
//https://server.179.ru/tasks/cpp/total/161.html
bool TTextProg::itsVar(string hS)
{
	int i = 0;
	//pi: double = 3,1515926;
	string helpString1;
	string helpString2;
	string helpString3;
	while (hS[i] != ':') 
	{
		helpString1 = helpString1 + hS[i];
		i++;
	}
	var_compiller newVar;
	newVar.nameOfVar = helpString1;
	cout << "Name " << newVar.nameOfVar << endl;
	helpString1 = "";
	if (hS[i] == ',')
	{
		do
		{
			i++;
			helpString1 = helpString1 + hS[i];
		} while (hS[i] != ':');
	}
	if (hS[i] == ':')
	{
		do 
		{
			i++;
			if(hS[i] != ' ')
				helpString1 = helpString1 + hS[i];
		} while (hS[i] != '=' && hS[i] != ';');
	}
	if (helpString1 == "double;" || helpString1 == "double=")
	{
		helpString1 = "";
		do
		{
			i++;
			if (hS[i] != ' ')
				helpString1 = helpString1 + hS[i];
		} while (hS[i] != ';');
		newVar.valueOfDoubleVar = atof(helpString1.c_str());
		proginf.variki.push_back(newVar);
		cout << "Значение " << newVar.valueOfDoubleVar << endl;
	}
	if (helpString1 == "integer;" || helpString1 == "integer=")
	{
		helpString1 = "";
		do
		{
			i++;
			if (hS[i] != ' ')
				helpString1 = helpString1 + hS[i];
		} while (hS[i] != ';');
		newVar.valueOfIntVar = atof(helpString1.c_str());
		proginf.variki.push_back(newVar);
		cout << "Значение " << newVar.valueOfIntVar << endl;
	}

	return 0;
}

bool TTextProg::itsConst(string hS)
{
	int i = 0;
	//pi: double = 3,1515926;
	string helpString1;
	string helpString2;
	string helpString3;
	while (hS[i] != ':')
	{
		helpString1 = helpString1 + hS[i];
		i++;
	}
	const_compiller newConst;
	newConst.nameOfConst = helpString1;
	cout << "Name " << newConst.nameOfConst << endl;
	helpString1 = "";
	if (hS[i] == ',')
	{
		do
		{
			i++;
			helpString1 = helpString1 + hS[i];
		} while (hS[i] != ':');
	}
	if (hS[i] == ':')
	{
		do
		{
			i++;
			if (hS[i] != ' ')
				helpString1 = helpString1 + hS[i];
		} while (hS[i] != '=' && hS[i] != ';');
	}
	if (helpString1 == "double;" || helpString1 == "double=")
	{
		helpString1 = "";
		do
		{
			i++;
			if (hS[i] != ' ')
				helpString1 = helpString1 + hS[i];
		} while (hS[i] != ';');
		newConst.valueOfDoubleConst = atof(helpString1.c_str());
		proginf.constantic.push_back(newConst);
		cout << "Значение " << newConst.valueOfDoubleConst << endl;
	}
	if (helpString1 == "integer;" || helpString1 == "integer=")
	{
		helpString1 = "";
		do
		{
			i++;
			if (hS[i] != ' ')
				helpString1 = helpString1 + hS[i];
		} while (hS[i] != ';');
		newConst.valueOfIntConst = atof(helpString1.c_str());
		proginf.constantic.push_back(newConst);
		cout << "Значение^ " << newConst.valueOfIntConst << endl;
	}

	return 0;
}

void TTextProg::printVector()
{
	var_compiller dopinf;
	for (int i = 0; i < proginf.variki.size(); i++) 
	{
		dopinf = proginf.variki[i];
		cout << "Имя: " << dopinf.nameOfVar << endl;
		cout << "Значение integer = " <<dopinf.valueOfIntVar << endl;
		cout << "Значение double = " <<dopinf.valueOfDoubleVar << endl;
	}
	cout << "------------------------------------------------------" << endl;
	const_compiller dopinf2;
	for (int i = 0; i < proginf.constantic.size(); i++) 
	{
		dopinf2 = proginf.constantic[i];
		cout << "Имя: " << dopinf2.nameOfConst << endl;
		cout << "Значение integer = " << dopinf2.valueOfIntConst << endl;
		cout << "Значение double = " << dopinf2.valueOfDoubleConst << endl;
	}
}
