#ifndef _ttext_h_
#define _ttext_h_

#include "TProgLink.h"
#include "tstack.h"
#include <string>
//������ ������ ������������ �������� ��� ������
class TTextProg
{
	TProgLink* pFirst;
	TProgLink* pCurr;
	TStack<TProgLink*> stack;

public:

	TTextProg(); 
	void GoFirstLink(); 
	void GoDownLink();  
	void GoNextLink();  
	void GoPrevLink(); 
	string GetLine();  //������ ������ �� ���������

	//������ ����������� �����������

	//void InsNextLine(string astr);  //���������� ��������� ������
	//void InsNextSection(string astr);  //���������� ���������� ���������
	//void InsDownLine(string astr);  //���������� ������ ������
	//void InsDownSection(string astr);  //���������� ������ �����
	//void DelNext(); //������� ��������� ������
	//void DelDownLine();  //������� ������ ������

	//������ ������ � ������

	void Read();  //������ �����
	TProgLink* ReadRec();  //������ ����� �� �����
	void Write(); //������ � ����
	void WriteRec();  //����������� ������� ������
	void ConsolePrint();  //������ � �������
	void ConsolePrintRec(); //������� ����������� ������ �� �������

	//������ ��������� �� ������

	int Reset();   //���������� �� ������ ������
	int IsEnd();  //�������� ����� ��
	int GoNext();//������� � ��������� ������
};
#endif;