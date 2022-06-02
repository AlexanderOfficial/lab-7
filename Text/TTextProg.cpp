#define _CRT_SECURE_NO_WARNINGS
#include "..//Text/TTextProg.h"
#include "..//Text/TProgLink.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <windows.h>
using namespace std;

static int recD;

vector <string> ivector = { "if","var","const","else", "Read", "Write" };

TTextProg::TTextProg() 
{
	pFirst = NULL;
	pCurr = NULL; ///
	TStack<TProgLink> stack;
}

//чтение
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
bool isElse = false;
TProgLink* TTextProg::ReadRec(ifstream& ifs)
{
	TProgLink* pHead, * pRC, * tmp;
	pHead = pRC = NULL;
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

//запись
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

//компиляция
void TTextProg::TCompiller()
{
	recD = 0;
	recTCompiller(pFirst);
}
bool checkNameProgram = false; //для бросания исключения если в начале не было program
void TTextProg::recTCompiller(TProgLink* pWC)
{
	bool check;
	program_information progInf;
	string helpString;
	string helpString2;
	//for (int i = 0; i < recD; i++)
	//{
	//	cout << "   ";
	//}
	helpString = string(pWC->str);
	//cout <<"LOCAL __________" << helpString << endl;
	if (helpString.find("program ", 0) == 0) 
	{ 

		searchForTheEndOfAProgramLine(helpString);
		helpString.pop_back(); //убрал в конце ;
		helpString = helpString.erase(0, 7);
		progInf.nameOfProgram = helpString;
		string str = progInf.nameOfProgram;
		wstring temp  = std::wstring(str.begin(), str.end());
		LPCWSTR wideString = temp.c_str();
		SetConsoleTitle(wideString);
		checkNameProgram = true;
	}
	if (checkNameProgram == false) { //проверка что не было имени программы, кидаем ошибку
		//Нет директивы, определяющей имя программы.
		cout << "There is no directive specifying the name of the program." << endl; 
		cout << "Please add the <program ""NameFile"";> directive at the beginning of the program." << endl;
		exit(1);
	}
	if (helpString.find("const", 0) == 0) 
	{
		isConst = 1;
		recTCompiller(pWC->pDown);
		isConst = 0;
	}
	if (helpString.find("var", 0) == 0) {
		isVar = 1;
		recTCompiller(pWC->pDown);
		isVar = 0;
	}
	if (helpString.find("begin", 0) == 0)
	{
		isBegin = 1;
		recTCompiller(pWC->pDown);
		isBegin = 0;
		return;
	}	
	if (helpString.find("write(", 0) == 0)
	{
		writeFunction(helpString);
	}
	if (helpString.find("Read(", 0) == 0){
		readFunction(helpString);
	}
	if (helpString.find("if", 0) != -1) //// -1 - не нашел //нашел
	{ //сделать проверку на then
		helpString = string(pWC->str);
		if (checkIfCondition(helpString) == true) {
			if (pWC->pDown)
			{
				recD++;
				recTCompiller(pWC->pDown);
			}
			if (pWC->pNext)
			{
				pWC = pWC->pNext;
			}
			if (pWC->pNext)
			{
				pWC = pWC->pNext;
				recTCompiller(pWC);
			}
		}
		else
		{
			pWC = pWC->pNext;
		}

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
	if ((isBegin == 1)&&(helpString.find(":=",0)!=-1))
	{
		helpString = string(pWC->str);
		checkFunction(helpString); 
	}
	if (pWC->pNext)
	{
		
		recTCompiller(pWC->pNext);
		recD++;
	}
	recD--;
}

//поиск ошибок
void TTextProg::FindError(std::string fn)
{
	int checkTestError = 0; //0 - отсуствие ошибок
	ifstream ifs(fn);
	if (!ifs.is_open()) // вызов метода is_open()
	{
		cout << "File not open!\n\n" << endl;
		throw exception();
	}
	recD = 0;
	TProgLink* pHead, * pRC, * tmp;
	pHead = pRC = NULL;
	char word2[81];
	string stroka = "";
	ifs.getline(tstr, 80, '\n');
	stroka = tstr;
	stroka = removeDoubleSlash(stroka);
	//cout << stroka << endl;
	bool flag = false;
	bool checkNameProgram2 = false;
	//проверка, что первым не цифра в любой строке
	//скобки
	//
	while (!ifs.eof())
	{
		while (stroka.length() > 0 && stroka[0] == ' ')
			stroka.erase(0, 1);
		stroka = removeDoubleSlash(stroka);
		checkTestError = checkTestError + countParenthesesInAString(stroka);
		if (stroka.find("program ", 0) == 0 && stroka.length() < 7)
		{
			checkTestError = checkTestError + searchForTheEndOfAProgramLine(stroka);
			checkNameProgram2 = true;
			flag = true;
		}
		if (checkNameProgram2 == true) { //проверка что не было имени программы, кидаем ошибку
		//Нет директивы, определяющей имя программы.
			cout << "There is no directive specifying the name of the program." << endl;
			cout << "Please add the <program ""NameFile"";> directive at the beginning of the program." << endl;
			checkNameProgram2 = false;
		}
		if (stroka.find("if(", 0) == 0 && stroka.find(")then", 0) != -1)
		{
			checkTestError = checkTestError + searchForTheEndOfAProgramLineNot(stroka);
			flag = true;
		}
		if (stroka.find("if(", 0) == 0 && stroka.find(")then", 0) == -1)
		{
			cout << "ERROR: No <than> after <if> in the string: " << stroka << endl;
			checkTestError = checkTestError + 1;
			flag = true;
		}
		if (stroka.find("else", 0) == 0)
		{
			checkTestError = checkTestError + searchForTheEndOfAProgramLineNot(stroka);
			flag = true;
		}
		if (stroka.find("const", 0) == 0)
		{
			checkTestError = checkTestError + searchForTheEndOfAProgramLineNot(stroka);
			flag = true;
		}
		if (stroka.find("var", 0) == 0)
		{
			checkTestError = checkTestError + searchForTheEndOfAProgramLineNot(stroka);
			flag = true;
		}
		if (stroka.find("end", 0) == 0)
		{
			checkTestError = checkTestError + searchForTheEndOfAProgramLineNot(stroka);
			flag = true;
		}
		if (stroka.find("begin", 0) == 0)
		{
			checkTestError = checkTestError + searchForTheEndOfAProgramLineNot(stroka);
			flag = true;
		}
		if (flag == false)
		{
			checkTestError = checkTestError + searchForTheEndOfAProgramLine(stroka);
		}
		ifs.getline(tstr, 80, '\n');
		flag = false;
		stroka = tstr;
	}
	if (checkTestError != 0) {
		cout << " Errors have been found in the program. Numer of errors: "  << checkTestError << endl;
		cout << " !The program completed its work with an error! " << endl;
		exit(1);
	}
}

bool TTextProg::checkIfCondition(string input) 
{
	string helpString1, helpString2, helpString3;
	int i = 0;
	while (input[i] != '(') 
	{
		helpString1 = helpString1 + input[i];
		i++;
	}
	i++;
	while (input[i] != ')') 
	{
		helpString2 = helpString2 + input[i];
		i++;
	}
	if (helpString2.find("==", 0) != -1) // если нашли сравнение внутри if
	{
		// разбираем helpstring2
		int k = 0;
		string leftPart, rightPart;
		//if (d mod 2 == 0) then
		while ((helpString2[k] != '=') && (helpString2[k+1] != '=')) 
		{
			leftPart = leftPart + helpString2[k];
			k++;
		}
		while (helpString2[k] == '='|| helpString2[k] == ' ')
		{
			k++;
		}
		while (k!= helpString2.size()) {
			rightPart = rightPart + helpString2[k];
			k++;
		}
		//cout << "хххххх leftPart=" << leftPart << endl;
		//cout << "хххххх rightPart=" << rightPart << endl;
		return checkIf(leftPart, rightPart, "==");
		//вот тут должен быть поиск правой и левой части по константам

	}
	if (helpString2.find("!=", 0) != -1) // если нашли сравнение внутри if
	{
		// разбираем helpstring2
		int k = 0;
		string leftPart, rightPart;
		//if (d mod 2 == 0) then
		while ((helpString2[k] != ' ') && (helpString2[k+1] != '!') && (helpString2[k + 2] != '='))
		{
			leftPart = leftPart + helpString2[k];
			k++;
		}
		while (helpString2[k] == '=' || helpString2[k] == ' ' || helpString2[k] == '!')
		{
			k++;
		}
		while (k != helpString2.size()) 
		{
			rightPart = rightPart + helpString2[k];
			k++;
		}
		//cout << "хххххх leftPart=" << leftPart << endl;
		//cout << "хххххх rightPart=" << rightPart << endl;
		return checkIf(leftPart, rightPart, "!=");
		//вот тут должен быть поиск правой и левой части по константам

	}

}

bool TTextProg::checkIf(string inputLeft, string inputRight, string operation)
{
	//облегченная версия
	string lP, rP;
	//lP = 0;
	//rP = 0;
	//если левая или правая части константы или переменные
	for (int i = 0; i < proginf.constantic.size(); i++) 
	{
		if (inputLeft == proginf.constantic[i].nameOfConst) 
		{
			if (proginf.constantic[i].doubleOrInteger == 0)
			{
				lP = to_string(proginf.constantic[i].valueOfDoubleConst);
				//cout << " хххххх Левая часть = " << inputLeft << " = " << lP << endl;
			}
			if (proginf.constantic[i].doubleOrInteger == 1)
			{
				lP = to_string(proginf.constantic[i].valueOfIntConst);
				//cout << " хххххх Левая часть = " << inputLeft << " = " << lP << endl;
			}
		}
		if (inputRight == proginf.constantic[i].nameOfConst)
		{
			if (proginf.constantic[i].doubleOrInteger == 0)
			{
				lP = to_string(proginf.constantic[i].valueOfDoubleConst);
				//cout << " хххххх Правая часть = " << inputRight << " = " << lP << endl;
			}
			if (proginf.constantic[i].doubleOrInteger == 1)
			{
				lP = to_string(proginf.constantic[i].valueOfIntConst);
				//cout << " хххххх Правая часть = " << inputRight << " = " << lP << endl;
			}
		}
	}
	for (int i = 0; i < proginf.variki.size(); i++)
	{
		if (inputLeft == proginf.variki[i].nameOfVar)
		{
			if (proginf.variki[i].doubleOrInteger == 0)
			{
				lP = to_string(proginf.variki[i].valueOfDoubleVar);
				//cout << "хххххх Левая часть = " << inputLeft << " = " << lP << endl;
			}
			if (proginf.variki[i].doubleOrInteger == 1)
			{
				lP = to_string(proginf.variki[i].valueOfIntVar);
				//cout << " хххххх Левая часть = " << inputLeft << " = " << lP << endl;
			}
		}
		if (inputRight == proginf.variki[i].nameOfVar)
		{
			if (proginf.variki[i].doubleOrInteger == 0)
			{
				lP = to_string(proginf.variki[i].valueOfDoubleVar);
				//cout << "хххххх Правая часть = " << inputRight << " = " << lP << endl;
			}
			if (proginf.variki[i].doubleOrInteger == 1)
			{
				lP = to_string(proginf.variki[i].valueOfIntVar);
				//cout << "хххххх Правая часть = " << inputRight << " = " << lP << endl;
			}
		}
	}
	if ((checkConst(inputRight) == true && checkConst(inputLeft)) || //если обе константы
		(checkVar(inputRight) == true && checkVar(inputLeft)) || //если обе переменные
		(checkConst(inputRight) == true && checkVar(inputLeft)) || //если одна константа, а другая переменная
		(checkVar(inputRight) == true && checkConst(inputLeft)))
	{
		if (operation == "==")
			return lP == rP;
		if (operation == "!=")
			return lP != rP;
	}

	//если в левой части есть mod
	if (inputLeft.find(" mod ", 0) != -1){
		//if(d mod 2 == 0)
		int k = 0;
		string lPMod, rPMod;

		while (inputLeft[k] != ' ') 
		{
			lPMod = lPMod + inputLeft[k];
			k++;
		}
		k += 5;
		while (k != inputLeft.size()) 
		{
			rPMod = rPMod + inputLeft[k];
			k++;
		}
		lP = to_string(itsMod(lPMod, rPMod));
	}
	//если в правой части есть mod
	if (inputRight.find(" mod ", 0) != -1)
	{
		//if(d mod 2 == 0)
		int k = 0;
		string lPMod, rPMod;

		while (inputRight[k] != ' ')
		{
			lPMod = lPMod + inputRight[k];
			k++;
		}
		k += 5;
		while (inputRight[k] != ' ')
		{
			rPMod = rPMod + inputRight[k];
			k++;
		}
		rP = to_string(itsMod(lPMod, rPMod));
	}
	if (lP == "") 
	{ 
		lP = inputLeft; 
	}
	if (rP == "") 
	{ 
		rP = inputRight; 
	}	
	if (operation == "==" && stoi(lP) == stoi(rP))
	{ 
		return true; 
	}
	if (operation == "==" && stoi(lP) != stoi(rP))
	{
		return false;
	}
	if (operation == "!=" && stoi(lP) != stoi(rP))
	{
		return true;
	}
	if (operation == "!=" && stoi(lP) == stoi(rP))
	{
		return false;
	}
}

int TTextProg::itsMod(string inputLeft, string inputRight)
{
	int k = 0;

	const_compiller const1;
	const_compiller const2;

	var_compiller var1;
	var_compiller var2;
	
	//проверяем есть ли константы
	if (checkConst(inputLeft) == true) 
	{
		const1 = getConst(inputLeft);
	}
	if (checkConst(inputRight) == true)
	{
		const2 = getConst(inputRight);
	}
	
	//проверяем есть ли переменные
	if (checkVar(inputLeft) == true)
	{
		var1 = getVar(inputLeft);
	}
	if (checkVar(inputRight) == true)
	{
		var2 = getVar(inputRight);
	}

	//если оба var
	if (checkVar(inputRight) == true && checkVar(inputLeft) == true)
	{
		if (var1.doubleOrInteger == 0 && var2.doubleOrInteger == 0)
		return (int)var1.valueOfDoubleVar % (int)var2.valueOfDoubleVar;

		if (var1.doubleOrInteger == 1 && var2.doubleOrInteger == 0)
			return var1.valueOfIntVar % (int)var2.valueOfDoubleVar;

		if (var1.doubleOrInteger == 0 && var2.doubleOrInteger == 1)
			return (int)var1.valueOfDoubleVar % var2.valueOfIntVar;

		if (var1.doubleOrInteger == 1 && var2.doubleOrInteger == 1)
			return var1.valueOfIntVar % var2.valueOfIntVar;
	}

	//если оба const
	if (checkConst(inputRight) == true && checkConst(inputLeft) == true)
	{
		if (const1.doubleOrInteger == 0 && const2.doubleOrInteger == 0)
			return (int)const1.valueOfDoubleConst % (int)const2.valueOfDoubleConst;
		if (const1.doubleOrInteger == 1 && const2.doubleOrInteger == 0)
			return const1.valueOfIntConst % (int)const2.valueOfDoubleConst;
		if (const1.doubleOrInteger == 0 && const2.doubleOrInteger == 1)
			return (int)const1.valueOfDoubleConst % const2.valueOfIntConst;
		if (const1.doubleOrInteger == 1 && const2.doubleOrInteger == 1)
			return const1.valueOfIntConst % const2.valueOfIntConst;
	}

	//если левый константа, а правый переменная
	if (checkConst(inputLeft) == true && checkVar(inputRight) == true)
	{
		if (const1.doubleOrInteger == 0 && var2.doubleOrInteger == 0)
			return (int)const1.valueOfDoubleConst % (int)var2.valueOfDoubleVar;
		if (const1.doubleOrInteger == 1 && var2.doubleOrInteger == 0)
			return const1.valueOfIntConst % (int)var2.valueOfDoubleVar;
		if (const1.doubleOrInteger == 0 && var2.doubleOrInteger == 1)
			return (int)const1.valueOfDoubleConst % var2.valueOfIntVar;
		if (const1.doubleOrInteger == 1 && var2.doubleOrInteger == 1)
			return const1.valueOfIntConst % var2.valueOfIntVar;
	}

	//если левый переменная, а правый константа
	if (checkVar(inputLeft) == true && checkConst(inputRight) == true)
	{
		if (var1.doubleOrInteger == 0 && const2.doubleOrInteger == 0)
			return (int)var1.valueOfDoubleVar % (int)const2.valueOfDoubleConst;
		if (var1.doubleOrInteger == 1 && const2.doubleOrInteger == 0)
			return var1.valueOfIntVar % (int)const2.valueOfDoubleConst;
		if (var1.doubleOrInteger == 0 && const2.doubleOrInteger == 1)
			return (int)var1.valueOfDoubleVar % const2.valueOfIntConst;
		if (var1.doubleOrInteger == 1 && const2.doubleOrInteger == 1)
			return var1.valueOfIntVar % const2.valueOfIntConst;
	}

	//если слева константа, а справа число
	if (checkConst(inputLeft) == true)
	{
		if (const1.doubleOrInteger == 0)
			return (int)const1.valueOfDoubleConst % stoi(inputRight);
		if (const1.doubleOrInteger == 1)
			return const1.valueOfIntConst % stoi(inputRight);
	}

	//если слева переменная, а справа число
	if (checkVar(inputLeft) == true)
	{
		if (var1.doubleOrInteger == 0)
			return (int)var1.valueOfDoubleVar % stoi(inputRight);
		if (var1.doubleOrInteger == 1)
			return var1.valueOfIntVar % stoi(inputRight);
	}

	//если слева число, а справа константа
	if (checkConst(inputLeft) == true)
	{
		if (const2.doubleOrInteger == 0)
			return stoi(inputRight) % (int)const2.valueOfDoubleConst;
		if (const2.doubleOrInteger == 1)
			return stoi(inputRight) % const2.valueOfIntConst;
	}

	//если слева число, а справа переменная
	if (checkVar(inputLeft) == true)
	{
		if (var2.doubleOrInteger == 0)
			return stoi(inputRight) % (int)var2.valueOfDoubleVar;
		if (var2.doubleOrInteger == 1)
			return stoi(inputRight) % var2.valueOfIntVar;
	}

	if (stoi(inputRight) == 0)
		throw exception();
	return stoi(inputLeft) % stoi(inputRight);
}

int TTextProg::itsDiv(string inputLeft, string inputRight)
{
	int k = 0;

	const_compiller const1;
	const_compiller const2;

	var_compiller var1;
	var_compiller var2;

	//проверяем есть ли константы
	if (checkConst(inputLeft) == true)
	{
		const1 = getConst(inputLeft);
	}
	if (checkConst(inputRight) == true)
	{
		const2 = getConst(inputRight);
	}

	//проверяем есть ли переменные
	if (checkVar(inputLeft) == true)
	{
		var1 = getVar(inputLeft);
	}
	if (checkVar(inputRight) == true)
	{
		var2 = getVar(inputRight);
	}

	//если оба var
	if (checkVar(inputRight) == true && checkVar(inputLeft) == true)
	{
			return var1.valueOfIntVar / var2.valueOfIntVar;
	}

	//если оба const
	if (checkConst(inputRight) == true && checkConst(inputLeft) == true)
	{
			return const1.valueOfIntConst / const2.valueOfIntConst;
	}

	//если левый константа, а правый переменная
	if (checkConst(inputLeft) == true && checkVar(inputRight) == true)
	{
			return const1.valueOfIntConst / var2.valueOfIntVar;
	}

	//если левый переменная, а правый константа
	if (checkVar(inputLeft) == true && checkConst(inputRight) == true)
	{
			return var1.valueOfIntVar / const2.valueOfIntConst;
	}

	//если слева константа, а справа число
	if (checkConst(inputLeft) == true)
	{
			return const1.valueOfIntConst / stoi(inputRight);
	}

	//если слева переменная, а справа число
	if (checkVar(inputLeft) == true)
	{
			return var1.valueOfIntVar / stoi(inputRight);
	}

	//если слева число, а справа константа
	if (checkConst(inputLeft) == true)
	{
			return stoi(inputRight) / const2.valueOfIntConst;
	}

	//если слева число, а справа переменная
	if (checkVar(inputLeft) == true)
	{
			return stoi(inputRight) / var2.valueOfIntVar;
	}


	if (stoi(inputRight) == 0)
		throw exception();
	return stoi(inputLeft) / stoi(inputRight);
}

bool TTextProg::checkVar(string input)
{
	for (int i = 0; i < proginf.variki.size(); i++)
	{
		if (input == proginf.variki[i].nameOfVar)
		{
			return true;
		}
	};
	return false;
}

int TTextProg::checkVarPosition(string input)
{
	for (int i = 0; i < proginf.variki.size(); i++)
	{
		if (input == proginf.variki[i].nameOfVar)
		{
			return i;
		}
	};
}

int TTextProg::checkConstPosition(string input)
{
	for (int i = 0; i < proginf.constantic.size(); i++)
	{
		if (input == proginf.constantic[i].nameOfConst)
		{
			return i;
		}
	};
}

bool TTextProg::checkConst(string input)
{
	for (int i = 0; i < proginf.constantic.size(); i++)
	{
		if (input == proginf.constantic[i].nameOfConst)
		{
			return true;
		}
	};
	return false;
}

const_compiller TTextProg::getConst(string input)
{
	for (int i = 0; i < proginf.constantic.size(); i++)
	{
		if (input == proginf.constantic[i].nameOfConst)
		{
			return proginf.constantic[i];
		}
	};
}

var_compiller TTextProg::getVar(string input)
{
	for (int i = 0; i < proginf.variki.size(); i++)
	{
		if (input == proginf.variki[i].nameOfVar)
		{
			return proginf.variki[i];
		}
	};
}

void TTextProg::writeFunction(string input){
	string helpString1;//для самого write
	string helpString2;//для тела
	string helpString3;
	//write("   Введите вещественное число");
	//write("Result = ", Res);
	int i = 0;
	while (input[i] != '(') {
		helpString1 = helpString1 + input[i];
		i++;
	}
	if (input[i] == '(') {
		i++;//убирает скобку
	}
	if (input[i] == '"') {
		i++;//убирает "
	}
	while (input[i] != '"')
	{
		helpString2 = helpString2 + input[i];
		i++;
	}

	if (input[i] == '"') {
		i++;//перепрыгиваем через завершающую ковычку
	}

	while (input[i] == ',' || input[i] == ' ') {
		i++;
	} 
	if (input[i] == ')')
	{
		cout << helpString2 << endl;
		return;
	}
	if (input[i] == ',') { i++; }
	while (input[i] != ')') {
		helpString3 += input[i];
		i++;
	}
	//cout << "после запятой: " << helpString3 << endl;
	if (checkVar(helpString3) == true)
	{
		if(proginf.variki[checkVarPosition(helpString3)].doubleOrInteger == 0)
			cout << helpString2 << proginf.variki[checkVarPosition(helpString3)].valueOfDoubleVar << endl;
		if (proginf.variki[checkVarPosition(helpString3)].doubleOrInteger == 1)
			cout << helpString2 << proginf.variki[checkVarPosition(helpString3)].valueOfIntVar << endl;
	}
	if (checkConst(helpString3) == true)
	{
		if (proginf.constantic[checkConstPosition(helpString3)].doubleOrInteger == 0)
			cout << helpString2 << proginf.constantic[checkConstPosition(helpString3)].valueOfDoubleConst << endl;
		if (proginf.constantic[checkConstPosition(helpString3)].doubleOrInteger == 1)
			cout << helpString2 << proginf.constantic[checkConstPosition(helpString3)].valueOfIntConst << endl;
	}
	if(checkVar(helpString3) != true && checkConst(helpString3) != true)
	{
		system("cls");
		cout << "ERROR: Using an uninitialized variable" << helpString3 << endl;
		exit(0);
		/*throw exception();*/
	}
	if (input[i] == '\n') {

	}
	//cout << helpString2 << endl;
}

void TTextProg::readFunction(string input) {
	//Read(num2);
	string helpString1;//для самого read
	string helpString2;//для тела
	int i = 0;
	while (input[i] != '(')
	{
		helpString1 = helpString1 + input[i];
		i++;
	}
	if (input[i] == '(') {
		i++;//убирает скобку
	}
	//проверка есть ли такая переменная (НЕ КОНСТАНТА)
	while (input[i] != ')')
	{
		helpString2 = helpString2 + input[i];
		i++;
	}
	for (int i = 0; i < proginf.constantic.size(); i++) 
	{
		if (helpString2 == proginf.constantic[i].nameOfConst) 
		{
			system("cls");
			cout << "ERROR: You can't change the value of a constant! " << endl;
			throw exception();
			return;
		}
	}
	int forVarInt = 0;
	double forVarDouble = 0;
	for (int i = 0; i < proginf.variki.size(); i++) {
		if (helpString2 == proginf.variki[i].nameOfVar) {
			if (proginf.variki[i].doubleOrInteger == 0)
			{
				cin >> forVarDouble;
				proginf.variki[i].valueOfDoubleVar = forVarDouble;
				//cout << "Присвоили к " << proginf.variki[i].nameOfVar << " = " << proginf.variki[i].valueOfDoubleVar << endl;
			}
			if (proginf.variki[i].doubleOrInteger == 1)
			{
				cin >> forVarInt;
				proginf.variki[i].valueOfIntVar = forVarInt;
				//cout << "Присвоили к " << proginf.variki[i].nameOfVar << " = " << proginf.variki[i].valueOfIntVar << endl;
			}
			return;
		}
	}
	cout << helpString2 << endl;
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
	//cout << "Name " << newVar.nameOfVar << endl;
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
		//cout << "Значение " << newVar.valueOfDoubleVar << endl;
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
		newVar.doubleOrInteger = 1;
		proginf.variki.push_back(newVar);
		//cout << "Значение " << newVar.valueOfIntVar << endl;
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
	//cout << "Name " << newConst.nameOfConst << endl;
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
		newConst.doubleOrInteger = 0;
		newConst.valueOfDoubleConst = atof(helpString1.c_str());
		proginf.constantic.push_back(newConst);
	//	cout << "Значение: " << newConst.valueOfDoubleConst << endl;
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
		newConst.doubleOrInteger = 1;
		newConst.valueOfIntConst = atof(helpString1.c_str());
		proginf.constantic.push_back(newConst);
		//cout << "Значение: " << newConst.valueOfIntConst << endl;
	}

	return 0;
}

void TTextProg::printVector()
{
	cout << "------------------------------------------------------" << endl;
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

bool TTextProg::thisIsTheInitializationOfTheVariableOrConst(string input)
{ //тут именно инициализация переменных 
	forChange forCh;
	forCh = checkFunction(input);
	return 0;
}

bool TTextProg::initializeVariable(string input)
{
	return false;
}


forChange TTextProg::checkFunction(string input)
{
	string helpString1;
	string helpString2;
	forChange newChange;
	int i = 0;
	while (input[i] != ':')
	{
		helpString1 = helpString1 + input[i];
		i++;
	}
	while (input[i] != ';')
	{
		if ((input[i] != '=') && (input[i] != ' ')&& (input[i] != ':') && (input.find(" mod ", 0) == -1) && (input.find(" div ", 0) == -1))
		{
			helpString2 = helpString2 + input[i];
			//i++;
		}
		if ((input.find(" mod ", 0) != -1) || (input.find(" div ", 0) != -1))
			if ((input[i] != '=') && (input[i] != ':'))
			{
				helpString2 = helpString2 + input[i];
				//i++;
			}
		i++;
	}
	//тут я типо делаю поиск сначала на константам переменным, потом по уже for if и тд
	const_compiller const_comp;
	//если хотим присвоить к константе, то исключение
	if (checkConst(helpString1) == true)
	{
		cout << "ERROR: You cannot change the value of a constant." << endl;
		throw exception();
		return newChange;
	}
	
	//поиск по переменным векторам
	var_compiller var_comp1;
	var_compiller var_comp2;
	if (checkVar(helpString1) == true)
	{
		var_comp1 = getVar(helpString1);
	}
	if (checkVar(helpString2) == true)
	{
		var_comp2 = getVar(helpString2);
	}
	if (checkVar(helpString1) == true && checkVar(helpString2) == true)
	{
		if (var_comp1.doubleOrInteger == 0 && var_comp2.doubleOrInteger == 0)
		{
			var_comp1.valueOfDoubleVar = var_comp2.valueOfDoubleVar;
			//cout << "Присвоили к " << var_comp1.nameOfVar << " = " << var_comp1.valueOfDoubleVar << endl;
		}
		if (var_comp1.doubleOrInteger == 1 && var_comp2.doubleOrInteger == 1)
		{
			var_comp1.valueOfIntVar = var_comp2.valueOfIntVar;
			//cout << "Присвоили к " << var_comp1.nameOfVar << " = " << var_comp1.valueOfIntVar << endl;
		}
		if (var_comp1.doubleOrInteger == 1 && var_comp2.doubleOrInteger == 0)
		{
			system("cls");
			cout << "ERROR: Cannot assign type double to int " << endl;
			cout << "Line error: " << input << endl;
			throw exception();
		}
		if (var_comp1.doubleOrInteger == 0 && var_comp2.doubleOrInteger == 1)
		{
			system("cls");
			cout << "ERROR: Cannot assign type int to double " << endl;
			cout << "Line error: " << input << endl;
			throw exception();
		}
		newChange.a = 0;
		proginf.variki[checkVarPosition(var_comp1.nameOfVar)] = var_comp1;
		return newChange; //0 значит есть среди констант
	}
	if (checkVar(helpString1) == true && checkVar(helpString2) == false &&
		(helpString2.find("+", 0) == -1) && (helpString2.find("-", 0) == -1)
		&& (helpString2.find("*", 0) == -1) && (helpString2.find("/", 0) == -1)
		&& (helpString2.find(" mod ", 0) == -1) && (helpString2.find(" div ", 0) == -1))
	{
		if (var_comp1.doubleOrInteger == 0)
		{
			var_comp1.valueOfDoubleVar = atof(helpString2.c_str());
			//cout << "Присвоили к " << var_comp1.nameOfVar << " = " << var_comp1.valueOfDoubleVar << endl;
		}
		if (var_comp1.doubleOrInteger == 1) 
		{
			var_comp1.valueOfIntVar = atof(helpString2.c_str());
			//cout << "Присвоили к " << var_comp1.nameOfVar << " = " << var_comp1.valueOfIntVar << endl;
		}
		newChange.a = 0;
		proginf.variki[checkVarPosition(var_comp1.nameOfVar)] = var_comp1;
		return newChange; //0 значит есть среди констант
	}
	if ((checkVar(helpString1) == true && checkVar(helpString2) == false )&&(
		(helpString2.find("+", 0) != -1) || (helpString2.find("-", 0) != -1)
		|| (helpString2.find("*", 0) != -1) || (helpString2.find("/", 0) != -1)
		|| (helpString2.find(" mod ", 0) != -1) || (helpString2.find(" div ", 0) != -1)))
	{
		if (var_comp1.doubleOrInteger == 0)
		{
			setInfix(helpString2);
			ToPostfix();
			var_comp1.valueOfDoubleVar = Calculate(proginf.constantic,proginf.variki);
			//cout << "Присвоили к " << var_comp1.nameOfVar << " = " << var_comp1.valueOfDoubleVar << endl;
		}
		if (var_comp1.doubleOrInteger == 1)
		{
			setInfix(helpString2);
			ToPostfix();
			var_comp1.valueOfIntVar = Calculate(proginf.constantic, proginf.variki);
			//cout << "Присвоили к " << var_comp1.nameOfVar << " = " << var_comp1.valueOfIntVar << endl;
		}
		newChange.a = 0;
		proginf.variki[checkVarPosition(var_comp1.nameOfVar)] = var_comp1;
		return newChange; //0 значит есть среди констант
	}
	system("cls");
	cout << "No such variable found!" << endl;
	cout << "Line error: " << input << endl;
	throw exception();
	return newChange;
}
/////////
bool TTextProg::ChekInPostfix(int i)
{
	if ((postinf.postfix[i] != '+') && (postinf.postfix[i] != '-') && (postinf.postfix[i] != '*') && (postinf.postfix[i] != '/'))
		return true;
	return false;
};
bool TTextProg::ChekInPostfix(string input)
{
	if ((input != "+") && (input != "-") && (input != "*") && (input != "/") && (input != "mod") && (input != "div"))
		return true;
	return false;
};
string TTextProg::ToPostfix()
{
	string result = "";
	string str = "";
	string operation = "";
	int result_pos = 0;
	TStack<string> stack_(MaxStackSize);
	for (int i = 0; i < postinf.infix.length(); i++)
	{
		while (postinf.infix[i] == ' ')
		{
			i++;
		}
		//--1-- Константы и переменные кладутся в формируемую запись в порядке их появления в исходном массиве
		while ((postinf.infix[i] != '(') && (postinf.infix[i] != ')') && (postinf.infix[i] != '+') && (postinf.infix[i] != '-') && 
			(postinf.infix[i] != '*') && (postinf.infix[i] != '/') && (postinf.infix[i] != ' ') && (postinf.infix[i] != '\0'))
		{
			str += postinf.infix[i];
			i++;
		}
		if (str != "mod" && str != "div" && str != "")
		{
			result += str;
			str = "";
		}
		if (str == "mod" || str == "div")
		{
			
			operation = str;
			str = "";
		}
		//--2-- открывающая скобка кладётся в стек
		if (postinf.infix[i] == '(')
		{
			operation = postinf.infix[i];
			stack_.Push(operation);
			operation = "";
		}
		//--3-- pакрывающая скобка выталкивает из стека в формируемую запись все операции до ближайшей открывающей скобки, открывающая скобка
		//удаляется из стека
		if (postinf.infix[i] == ')')
		{
			while (stack_.Top() != "(")//пока
			{
				result += ' ';
				result += stack_.Pop();
			}
			stack_.Pop();
		}
		if ((postinf.infix[i] == '+') || (postinf.infix[i] == '-') || (postinf.infix[i] == '*') 
			|| (postinf.infix[i] == '/') || (operation == "mod") || (operation == "div"))
		{
			if (operation == "")
				operation = postinf.infix[i];
			result += ' ';
			// если в стеке пусто или вверху стека открывающая скобка, операции кладутся в стек
			if (stack_.IsEmpty() || stack_.Top() == "(")
				stack_.Push(operation);
			// если новая операции имеет бОльший приоритет, чем верхняя операции в стеке, то новая операции кладётся в стек
			else if (Priority(operation) > Priority(stack_.Top()))
				stack_.Push(operation);
			else
			{
				while (!stack_.IsEmpty() && Priority(operation) <= Priority(stack_.Top()))
				{
					// в формируемую запись
					result += stack_.Pop();
				}
				result += ' ';
				stack_.Push(operation);
			}
		}
		operation = "";
	}
	// оставшиеся операции в стеке в ответ
	while (!stack_.IsEmpty())
	{
		result += ' ';
		result += stack_.Pop();
	}
	postinf.postfix = result;
	return postinf.postfix;
};

double TTextProg::Calculate(vector <const_compiller> constant, vector <var_compiller> var)
{
	double array_double[MaxStackSize];
	string prom_res;
	double variables;
	int j = 0;
	TStack<double> stack(MaxStackSize);

	for (int i = 0; i < postinf.postfix.length(); i++)
	{
		while (postinf.postfix[i] != ' ' && postinf.postfix[i] != '\0')
		{
			prom_res = prom_res + postinf.postfix[i];
			i++;
		}
		if (ChekInPostfix(prom_res))
		{
			if ((postinf.postfix[i] == ' ') && ChekInPostfix(i - 1))
			{
				size_t found = prom_res.find_first_not_of("0123456789");
				if ((found == std::string::npos) && (postinf.postfix[i] == ' '))
				{
					array_double[j] = stoi(prom_res); // преобразовать символы к типу int
				}
				else // для выражений на буквах
				{
					for (int k = 0; k < constant.size(); k++)
					{
						if (prom_res == constant[k].nameOfConst)
						{
							if (constant[k].doubleOrInteger == 0)
								array_double[j] = constant[k].valueOfDoubleConst;
							if (constant[k].doubleOrInteger == 1)
								array_double[j] = constant[k].valueOfIntConst;
						}
					}
					for (int k = 0; k < var.size(); k++)
					{
						if (prom_res == var[k].nameOfVar)
						{
							if (var[k].doubleOrInteger == 0)
								array_double[j] = var[k].valueOfDoubleVar;
							if (var[k].doubleOrInteger == 1)
								array_double[j] = var[k].valueOfIntVar;
						}
					}
				}
				stack.Push((double)array_double[j]);
				prom_res = "";
				j++;
			}
		}
		else
		{ // выгружаем последние два элемента из стека и производим действие над ними, ответ на вершину стека
			double tmp1 = stack.Pop();
			double tmp2 = stack.Pop();
			if (prom_res == "+")
			{
				stack.Push(tmp2 + tmp1);
			}
			if (prom_res == "-")
			{
				stack.Push(tmp2 - tmp1);
			}
			if (prom_res == "/")
			{
				if (tmp1 == 0) {
					cout << "ERROR: Division by zero is not possible." << endl;
					throw exception();
				}
				stack.Push(tmp2 / tmp1);
			}
			if (prom_res == "*")
			{
				stack.Push(tmp2 * tmp1);
			}
			if (prom_res == "mod")
			{
				if (tmp1 == 0) {
					cout << "ERROR: Division by zero is not possible." << endl;
					throw exception();
				}
				stack.Push(itsMod(to_string(tmp2), to_string(tmp1)));
			}
			if (prom_res == "div")
			{
				if (tmp1 == 0) {
					cout << "ERROR: Division by zero is not possible." << endl;
					throw exception();
				}
				stack.Push(itsDiv(to_string(tmp2), to_string(tmp1)));
			}
			prom_res = "";
		}

	}
	return stack.Pop();
};
void TTextProg::setInfix(string input)
{
	postinf.infix = input;
}