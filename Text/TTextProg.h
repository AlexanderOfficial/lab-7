#ifndef _ttext_h_
#define _ttext_h_

#include "TProgLink.h"
#include "tstack.h"
//#include "TPostfix.h"
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
	bool operator == (const const_compiller& vc) const {
		return this->nameOfConst == vc.nameOfConst && this->valueOfDoubleConst == vc.valueOfDoubleConst
			&& this->valueOfIntConst == vc.valueOfIntConst && this->doubleOrInteger == vc.doubleOrInteger;
	}
};


struct var_compiller {
	string nameOfVar;
	double valueOfDoubleVar = 0;
	int valueOfIntVar = 0;
	bool doubleOrInteger = 0;
	bool operator == (const var_compiller&vc) const {
		return this->nameOfVar == vc.nameOfVar && this->valueOfDoubleVar == vc.valueOfDoubleVar
			&& this->valueOfIntVar == vc.valueOfIntVar && this->doubleOrInteger == vc.doubleOrInteger;
	}
};

struct forChange {
	string name;
	double meaningOf;//��������
	int a;
};

class TTextProg //TText
{
	TProgLink* pFirst;
	TProgLink* pCurr;
	TStack<TProgLink*> stack;
	//program_information proginf;
	/*struct program_information {
		string nameOfProgram;
		vector <const_compiller> constantic;
		vector <var_compiller> variki;
	} proginf;*/
	//TPostfix p();
	/*TPostfix* postf = new TPostfix();*/
public:
	struct posfix_information {
		string infix;
		string postfix;
	} postinf;
	struct program_information {
		string nameOfProgram;
		vector <const_compiller> constantic;
		vector <var_compiller> variki;
	} proginf;
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

	bool thisIsTheInitializationOfTheVariableOrConst(string input);
	bool initializeVariable(string input);
	forChange checkFunction(string input);

	//��� ��������� write
	void writeFunction(string input);
	void readFunction(string input);

	//��� ������ ; � ����� ������
	int searchForTheEndOfAProgramLine(string input) {
		int sizeOfString = input.size();
		if (input[sizeOfString-1] != ';'){ 
			//system("cls");
			cout <<"ERROR: Absence ""; """ << endl;
			cout << "       Line error  " << input << endl;
			return 1;
		}
		return 0;
	}

	int searchForTheEndOfAProgramLineNot(string input) {
		int sizeOfString = input.size();
		if (input[sizeOfString - 1] == ';') {
			//system("cls");
			cout << "ERROR: ����� �� ������ ���� ""; """ << endl;
			cout << "       Line error  " << input << endl;
			return 1;
		}
		return 0;
	}

	//�������� ������� if
	bool checkIfCondition(string input);
	//��������� ��������� ������ � ����� ����� �����
	bool checkIf(string inputLeft, string inputRight, string operation);

	bool checkVar(string input);
	bool checkConst(string input);
	int checkVarPosition(string input); //���������� �������, �� ������� ����� ��� ����������
	int checkConstPosition(string input);

	const_compiller getConst(string input);
	var_compiller getVar(string input);

	int itsMod(string inputLeft, string inputRight);
	int itsDiv(string inputLeft, string inputRight);

	void Read(std::string fn); //������ �����
	TProgLink* ReadRec(std::ifstream& ifs); //������ ������ �� �����

	void Write(std::string fn); //������ � ���� � ����������
	void WriteRec(std::ofstream& ofs, TProgLink* pWC); //����������� ������� ������

	int Priority(string val)
	{
		if ((val == "mod") || (val == "div")) return 2;
		if ((val == "*") || (val == "/")) return 2;
		if ((val == "+") || (val == "-")) return 1;
		return -1;
	}

	void SetInfix(string val) { postinf.infix = val; }
	string GetInfix() { return postinf.infix; }
	string GetPostfix() { return postinf.postfix; }
	string ToPostfix();
	double Calculate(vector <const_compiller> constant, vector <var_compiller> var);
	bool ChekInPostfix(int i);
	bool ChekInPostfix(string input);
	void setInfix(string input);

	void FindError(std::string fn);
	int countParenthesesInAString(string input) 
	{
		string left = "(";
		string right = ")";
		int n1 = 0, p1 = 0;
		int n2 = 0, p2 = 0;
		while ((p1 = input.find("(", p1)) != input.npos) { ++n1;  ++p1; }
		while ((p2 = input.find(")", p2)) != input.npos) { ++n2;  ++p2; }

		if (n1 != n2) {
			cout << "Quantity '(' does not match quantity ')'!" << endl;
			cout << "       Line error  " << input << endl;
			return  1;
			//exit(1);
		}
		else { return  0; }
	}
	string removeDoubleSlash(string input) 
	{
		auto pos = input.find("//");
		if (pos != string::npos) input.erase(pos);
		pos = input.find(";");
		if (pos != string::npos) input.erase(pos + 1);
		return input;
	}
};

//class TPostfix
//{
//	string infix;
//	string postfix;
//public:
//	TPostfix(string val) { infix = val; }
//	TPostfix() { infix = " "; }
//	int Priority(char val)
//	{
//		if ((val == '*') || (val == '/')) return 2;
//		if ((val == '+') || (val == '-')) return 1;
//		return -1;
//	}
//	void SetInfix(string val) { infix = val; }
//	string GetInfix() { return infix; }
//	string GetPostfix() { return postfix; }
//	//string ToPostfix();
//	//double Calculate(vector <const_compiller> constant, vector <var_compiller> var);
//	bool ChekInPostfix(int i);
//};


//string TTextProg::ToPostfix()
//{
//	char result[MaxStackSize];
//	int result_pos = 0;
//	TStack<char> stack_(MaxStackSize);
//	for (int i = 0; i < infix.length(); i++)
//	{
//		//--1-- ��������� � ���������� �������� � ����������� ������ � ������� �� ��������� � �������� �������
//		if ((infix[i] != '(') && (infix[i] != ')') && (infix[i] != '+') && (infix[i] != '-') && (infix[i] != '*') && (infix[i] != '/'))
//		{
//			result[result_pos++] = infix[i];
//			result[result_pos] = '\0';
//		}
//		//--2-- ����������� ������ ������� � ����
//		if (infix[i] == '(')
//			stack_.Push(infix[i]);
//		//--3-- p���������� ������ ����������� �� ����� � ����������� ������ ��� �������� �� ��������� ����������� ������, ����������� ������
//		//��������� �� �����
//		if (infix[i] == ')')
//		{
//			while (stack_.Top() != '(')//����
//			{
//				result[result_pos++] = ' ';
//				result[result_pos++] = stack_.Pop();
//				result[result_pos] = '\0';
//			}
//			stack_.Pop();
//		}
//		if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/'))
//		{
//			result[result_pos++] = ' ';
//			// ���� � ����� ����� ��� ������ ����� ����������� ������, �������� �������� � ����
//			if (stack_.IsEmpty() || stack_.Top() == '(')
//				stack_.Push(infix[i]);
//			// ���� ����� �������� ����� ������� ���������, ��� ������� �������� � �����, �� ����� �������� ������� � ����
//			else if (Priority(infix[i]) > Priority(stack_.Top()))
//				stack_.Push(infix[i]);
//			else
//			{
//				while (!stack_.IsEmpty() && Priority(infix[i]) <= Priority(stack_.Top()))
//				{
//					// � ����������� ������
//					result[result_pos++] = stack_.Pop();
//					result[result_pos] = '\0';
//				}
//				result[result_pos++] = ' ';
//				// ����� �������� �������� � ����
//				stack_.Push(infix[i]);
//			}
//		}
//	}
//	// ���������� �������� � ����� � �����
//	while (!stack_.IsEmpty())
//	{
//		result[result_pos++] = ' ';
//		result[result_pos++] = stack_.Pop();
//		result[result_pos] = '\0';
//	}
//	postfix = result;
//	return postfix;
//};

//double TPostfix::Calculate(vector <const_compiller> constant, vector <var_compiller> var)
//{
//	double array_double[MaxStackSize];
//	string prom_res;
//	double variables;
//	int j = 0;
//	TStack<double> stack(MaxStackSize);
//
//	for (int i = 0; i < postfix.length(); i++)
//	{
//		if (ChekInPostfix(i))
//		{
//			if (postfix[i] != ' ')
//				prom_res = prom_res + postfix[i];
//			if ((postfix[i] == ' ') && ChekInPostfix(i - 1))
//			{
//				size_t found = prom_res.find_first_not_of("0123456789");
//				if ((found == std::string::npos) && (postfix[i] == ' '))
//				{
//					array_double[j] = stoi(prom_res); // ������������� ������� � ���� int
//					//cout << "b" << "["<< j << "]="<< b[j] << endl;
//				}
//				else // ��� ��������� �� ������
//				{
//					string str = "";
//					while (postfix[i - 1] != ' ')
//					{
//						str += postfix[i - 1];
//						i++;
//					}
//					for (int k = 0; k < constant.size(); k++)
//					{
//						if (str == constant[k].nameOfConst)
//						{
//							if (constant[k].doubleOrInteger == 0)
//								array_double[j] = constant[k].valueOfDoubleConst;
//							if (constant[k].doubleOrInteger == 1)
//								array_double[j] = constant[k].valueOfIntConst;
//						}
//					}
//					//cout << postfix[i - 1] << "=";
//					//cin >> variables;
//					//array_double[j] = variables;
//				}
//				stack.Push((double)array_double[j]);
//				prom_res = "";
//				j++;
//			}
//		}
//		else
//		{ // ��������� ��������� ��� �������� �� ����� � ���������� �������� ��� ����, ����� �� ������� �����
//			double tmp1 = stack.Pop();
//			double tmp2 = stack.Pop();
//			if (postfix[i] == '+')
//			{
//				stack.Push(tmp2 + tmp1);
//			}
//			if (postfix[i] == '-')
//			{
//				stack.Push(tmp2 - tmp1);
//			}
//			if (postfix[i] == '/')
//			{
//				if (tmp1 == 0) // ������� �� ���� ���������� 
//					throw exception();
//				stack.Push(tmp2 / tmp1);
//			}
//			if (postfix[i] == '*')
//			{
//				stack.Push(tmp2 * tmp1);
//			}
//		}
//
//	}
//	return stack.Pop();
//};

#endif;
