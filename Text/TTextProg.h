#ifndef _ttext_h_
#define _ttext_h_

#include "TProgLink.h"
#include "tstack.h"
#include <string>

class TTextProg
{
	TProgLink* pFirst;
	TProgLink* pCurr;
	TStack<TProgLink*> stack;

public:

	TTextProg(); //constructor

	void Read(std::string fn); //чтение файла
	TProgLink* ReadRec(std::ifstream& ifs); //чтение строки из файла

	void Write(std::string fn); //запить в файл с табул€цией
	void WriteRec(std::ofstream& ofs, TProgLink* pWC); //рекурсивна€ функци€ записи

};
#endif;
