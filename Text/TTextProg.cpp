#define _CRT_SECURE_NO_WARNINGS
#include "..//Text/TTextProg.h"
#include "..//Text/TProgLink.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

static int recD;

TTextProg::TTextProg() {
	pFirst = NULL;
	pCurr = NULL; ///
	TStack<TProgLink> stack;
}

void TTextProg::Read(std::string fn) {
	ifstream ifs(fn);
	recD = 0;
	pFirst = ReadRec(ifs);
}

TProgLink* TTextProg::ReadRec(ifstream& ifs) {
	TProgLink* pHead, * pRC, * tmp;
	pHead = pRC = NULL;
	char tstr[81];
	while (!ifs.eof()) {
		ifs.getline(tstr, 80, '\n');
		if ((tstr[0] == 'e')&& (tstr[1] == 'n')&& (tstr[2] == 'd')) {
			break;
		}
		else
			if ((tstr[0] == 'b')&& (tstr[1] == 'e')&& (tstr[2] == 'g')) {
				pRC->pDown = ReadRec(ifs);
			}
			else {
				tmp = new TProgLink(tstr);
				if (pHead == NULL) {
					pHead = pRC = tmp;
				}
				else {
					pRC->pNext = tmp;
					pRC = pRC->pNext;
				}
			}
		if (!pRC->pDown) {
		}
	}
	return pHead;
}

void TTextProg::Write(std::string fn) {
	ofstream ofs(fn);
	recD = 0;
	WriteRec(ofs, pFirst);
}

void TTextProg::WriteRec(ofstream& ofs, TProgLink* pWC) {
	for (int i = 0; i < recD; i++) {
		ofs << "   ";
	}
	ofs << pWC->str << endl;

	if (pWC->pDown) {
		recD++;
		ofs << "begin" << endl;
		WriteRec(ofs, pWC->pDown);
		ofs << "end" << endl;
	}
	if (pWC->pNext) {
		WriteRec(ofs, pWC->pNext);
		recD++;
	}
	recD--;
}