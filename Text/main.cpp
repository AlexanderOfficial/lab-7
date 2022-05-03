#include <conio.h>
#include <iostream>
#include <string>
#include "TTextProg.h"

using namespace std;

TTextMem TProgLink::MemHeader;


int main() 
{
	TProgLink::InitMemSystem(100);
	TTextProg t;
	t.Read("prog.txt");
	t.Write("progout.txt");
}