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
	t.Read("prog.txt");
	t.TCompiller();
	t.printVector();
	t.Write("progout.txt");
}