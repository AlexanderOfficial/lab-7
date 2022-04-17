//#pragma once

#ifndef __TBASETABLE_H__
#define __TBASETABLE_H__

#include <vector>
#include <iostream>
struct Data
{
	std::string key;
	std::string polinomString;
};
//c��������� ��� ������
class TBaseTable {
public:
	virtual Data* find(const std::string key) = 0; //������ &key
	virtual void insert(const Data& data) = 0;
	virtual void deleteByKey(const std::string& key) = 0;
	virtual void print() = 0;
	virtual ~TBaseTable(){}
};

#endif