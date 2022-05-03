#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include "TProgLink.h"
#include "TTextProg.h"


void TProgLink::InitMemSystem(int size) {
	MemHeader.pFirst = (TProgLink*) new char[sizeof(TProgLink) * size];
	MemHeader.pFree = MemHeader.pFirst;
	MemHeader.pLast = MemHeader.pFirst + (size - 1);
	TProgLink* pLink = MemHeader.pFirst;

	//memory markup
	for (int i = 0; i < size - 1; i++) {
		pLink->str[0] = '\0';
		pLink->pNext = pLink + 1;
		pLink++;
	}
	pLink->pNext = NULL;
}

void* TProgLink::operator new(size_t size) {
	TProgLink* pLink = MemHeader.pFree;
	if (MemHeader.pFree) {
		MemHeader.pFree = pLink->pNext;
	}
	return pLink;
}

void TProgLink::operator delete(void* pM) {
	TProgLink* pLink = (TProgLink*)pM;
	pLink->pNext = MemHeader.pFree;
	MemHeader.pFree = pLink;
}

