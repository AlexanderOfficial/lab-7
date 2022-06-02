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
	TProgLink* pFirst;    // Указатель на первое звено памяти
	TProgLink* pLast;     // Указатель на последнее звено памяти
	TProgLink* pFree;     // Указатель на первое свободное звено
	friend class TProgLink;
};

//значение объекта класса для строки текста программы
class TProgLink 
{
protected:
	TProgLink* pNext, * pDown;
	static TTextMem MemHeader; //memory management system
	friend class TTextProg;
public:

	TStr str; //хранит строку //или стринг???
	int recD;
	static void InitMemSystem(int size = MemSize); //инициализация памяти
	void* operator new (size_t size); //распределение ссылок
	void operator delete (void* pM); //освобождение ссылки

	//конструктор
	TProgLink(const TStr c = NULL, TProgLink* pn = NULL, TProgLink* pd = NULL) {
		recD = 0;
		pNext = pn;
		pDown = pd;
		if (c == NULL) { str[0] = '\0'; }
		else { strcpy_s(str, c); }
	}

	////Функции для навигации по списку
	//void ToNext();
	//void ToDown();
	//void ToPrev();
	//void ToFirst();

	////Функции для модификации
	//void InsNextLine(char* s);
	//void InsNextSection(char* s);
	//void InsDownLine(char* s);
	//void InsDownSection(char* s);
	//void DelNext();
	//void DelDown();
	//void ToStart();

	////Функции для работы с файлом
	//void Read(char* pFileName);
	////void PrintText(Zveno* ptl);
	//void Print();
	////void WriteText(ofstream& ofs, Zveno* tl);
	//void Write(char* pFileName);

	////Проход по списку с помощью итератора
	//int IsEnd();
	//void GoNext();
	//void Reset();
	////Для маркировки текущего звена
	//void PointerCreate();
	//void PointerDelete();






	//деструктор
	~TProgLink() {}
};
#endif
