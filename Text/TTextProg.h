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

	void Read(std::string fn); //������ �����
	TProgLink* ReadRec(std::ifstream& ifs); //������ ������ �� �����

	void Write(std::string fn); //������ � ���� � ����������
	void WriteRec(std::ofstream& ofs, TProgLink* pWC); //����������� ������� ������

};
#endif;
