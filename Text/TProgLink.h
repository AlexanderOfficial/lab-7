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
	TProgLink(const TStr c = NULL, TProgLink* pn = NULL, TProgLink* pd = NULL) {
		recD = 0;
		pNext = pn;
		pDown = pd;
		if (c == NULL) { str[0] = '\0'; }
		else { strcpy_s(str, c); }
	}

	////������� ��� ��������� �� ������
	//void ToNext();
	//void ToDown();
	//void ToPrev();
	//void ToFirst();

	////������� ��� �����������
	//void InsNextLine(char* s);
	//void InsNextSection(char* s);
	//void InsDownLine(char* s);
	//void InsDownSection(char* s);
	//void DelNext();
	//void DelDown();
	//void ToStart();

	////������� ��� ������ � ������
	//void Read(char* pFileName);
	////void PrintText(Zveno* ptl);
	//void Print();
	////void WriteText(ofstream& ofs, Zveno* tl);
	//void Write(char* pFileName);

	////������ �� ������ � ������� ���������
	//int IsEnd();
	//void GoNext();
	//void Reset();
	////��� ���������� �������� �����
	//void PointerCreate();
	//void PointerDelete();






	//����������
	~TProgLink() {}
};
#endif
