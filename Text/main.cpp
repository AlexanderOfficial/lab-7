#include <conio.h>
#include <iostream>
#include <string>
#include "TTextProg.h"

using namespace std;

TTextMem TProgLink::MemHeader;


int main() 
{
	setlocale(LC_ALL, "Russian");
	TProgLink::InitMemSystem(100);
	TTextProg t;
	//////t.FindError("prog.pas");
	//////t.Read("prog.pas");
	t.FindError("test2.pas");
	t.Read("test2.pas");
	t.printVector();
	t.TCompiller();
	t.printVector();
	t.printVector();
	t.Write("progout.txt");
	//TProgLink::InitMemSystem(100);
	//TTextProg t;
	//var_compiller new_var;
	//t.itsVar("Res: double=7,123;");
	//new_var = t.getVar("Res");
}