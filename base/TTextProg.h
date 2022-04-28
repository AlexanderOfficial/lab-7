#ifndef _ttext_h_
#define _ttext_h_

#include "TProgLink.h"
#include "tstack.h"
#include <string>
//модуль класса реазлизующий операцию над тексто
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
	string GetLine();  //взятие строки из программы

	//Методы структурной модификации

	//void InsNextLine(string astr);  //добавление следующей строки
	//void InsNextSection(string astr);  //добавление следующего подуровня
	//void InsDownLine(string astr);  //добавление нижней строки
	//void InsDownSection(string astr);  //добавление нижней части
	//void DelNext(); //удалите следующую ссылку
	//void DelDownLine();  //удалите нижнюю ссылку

	//Методы чтения и записи

	void Read();  //чтение файла
	TProgLink* ReadRec();  //чтение строк из файла
	void Write(); //запись в файл
	void WriteRec();  //рекурсивная функция записи
	void ConsolePrint();  //запись в консоль
	void ConsolePrintRec(); //функция рекурсивной печати на консоль

	//Методы навигации по тексту

	int Reset();   //установить на первую ссылку
	int IsEnd();  //проверка конец ли
	int GoNext();//перейти к следующей ссылке
};
#endif;