#ifndef _ttext_h_
#define _ttext_h_

#include "TProgLink.h"
#include "tstack.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;




struct const_compiller {
	string nameOfConst;
	double valueOfDoubleConst = 0;
	int valueOfIntConst = 0;
};


struct var_compiller {
	string nameOfVar;
	double valueOfDoubleVar = 0;
	int valueOfIntVar = 0;
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

	//��� ����������
	bool itsVar(string hS);
	bool itsConst(string hS);
	void printVector();


	void Read(std::string fn); //������ �����
	TProgLink* ReadRec(std::ifstream& ifs); //������ ������ �� �����

	void Write(std::string fn); //������ � ���� � ����������
	void WriteRec(std::ofstream& ofs, TProgLink* pWC); //����������� ������� ������

};
#endif;