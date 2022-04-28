#ifndef _tproglink_h_
#define _tproglink_h_

#include <string>
#include "TMemoryManager.h"


#define TProgLineLength 80
#define MemSize 100

class TTextProg;
class TProgLink;

typedef char TStr[TProgLineLength];


//значение объекта класса для строки текста программы
class TProgLink {
protected:
	TProgLink* pNext, * pDown;
	static TMemoryManager MemHeader; 
	friend class TTextProg;
public:
	TStr str; //хранит строку //или стринг???
	int recD;
	static void InitMemSystem();
	static void TPrintFreeLink(); 
	void* operator new (size_t size); 
	void operator delete (void* pM); 
	static void MemoryCleaner(); 
	//TProgLink() {}

	//Destructor
	~TProgLink();
};
#endif
