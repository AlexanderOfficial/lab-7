#ifndef _ttextlink_h_
#define _ttextlink_h_

#include <string>

#define TTextLineLength 80
#define MemSize 100

class TTextProg;
class TProgLink;

typedef char TStr[TTextLineLength];

struct TTextMem 
{
	TProgLink* pFirst;    // ��������� �� ������ ����� ������
	TProgLink* pLast;     // ��������� �� ��������� ����� ������
	TProgLink* pFree;     // ��������� �� ������ ��������� �����
	friend class TProgLink;
};

//�������� ������� ������ ��� ������ ������ ���������
class TProgLink 
{
protected:
	TProgLink* pNext, * pDown;
	static TTextMem MemHeader; //memory management system
	friend class TTextProg;
public:

	TStr str; //������ ������ //��� ������???
	int recD;
	static void InitMemSystem(int size = MemSize); //������������� ������
	void* operator new (size_t size); //������������� ������
	void operator delete (void* pM); //������������ ������

	//�����������
	TProgLink(const TStr c = NULL, TProgLink* pn = NULL, TProgLink* pd = NULL) 
	{
		recD = 0;
		pNext = pn;
		pDown = pd;
		if (c == NULL)
			str[0] = '\0';
		else
			strcpy_s(str, c);
	}

	//����������
	~TProgLink() 
	{
		///
	}
};
#endif
