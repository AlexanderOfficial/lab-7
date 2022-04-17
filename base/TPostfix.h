//#pragma once

#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "TStack.h"
#include "TBaseTable.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	string operands = "+-*/";
	int priority[4] = { 1,1,2,2 };
	bool isCorrect(string str);
public:
	TPostfix(string inf = "a+b")
	{
		if (!isCorrect(inf))
			throw exception();
		unsigned int l = inf.length();
		for (unsigned int i = 0; i < l; i++)
			if (inf[i] != ' ')
				infix += inf[i];
		if (infix.length() < 1)
			throw exception();
	}
	//TPostfix(string val) { infix = val; }
	int Priority(char val)
	{
		if ((val == '*') || (val == '/')) return 2;
		if ((val == '+') || (val == '-')) return 1;
		return -1;
	}
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	bool ChekInPostfix(int i);
	string ToPostfix();
};

#endif