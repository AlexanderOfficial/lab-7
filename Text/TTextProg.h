#ifndef _ttext_h_
#define _ttext_h_

#include "TProgLink.h"
#include "tstack.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;


//0 - double
//1 - integer

struct const_compiller {
	string nameOfConst;
	double valueOfDoubleConst = 0;
	int valueOfIntConst = 0;
	bool doubleOrInteger = 0;
};


struct var_compiller {
	string nameOfVar;
	double valueOfDoubleVar = 0;
	int valueOfIntVar = 0;
	bool doubleOrInteger = 0;
};

struct forChange {
	string name;
	double meaningOf;//значение
	int a;
};

class TTextProg //TText
{
	TProgLink* pFirst;
	TProgLink* pCurr;
	TStack<TProgLink*> stack;
	//program_information proginf;
	struct program_information {
		string nameOfProgram;
		vector <const_compiller> constantic;
		vector<var_compiller> variki;
	} proginf;
public:
	//struct program_information {
	//	string nameOfProgram;
	//	vector <const_compiller> constantic;
	//	vector<var_compiller> variki;
	//};
	TTextProg(); //constructor
	void TCompiller();
	void recTCompiller(TProgLink* pWC);

	//дл€ переменных
	bool itsVar(string hS);
	bool itsConst(string hS);
	void printVector();

	bool thisIsTheInitializationOfTheVariableOrConst(string input);
	bool initializeVariable(string input);
	forChange checkFunction(string input);





	void Read(std::string fn); //чтение файла
	TProgLink* ReadRec(std::ifstream& ifs); //чтение строки из файла

	void Write(std::string fn); //запить в файл с табул€цией
	void WriteRec(std::ofstream& ofs, TProgLink* pWC); //рекурсивна€ функци€ записи

};
#endif;
