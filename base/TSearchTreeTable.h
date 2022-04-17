#ifndef __TSEARCH_TREE_TABLE_H__
#define __TSEARCH_TREE_TABLE_H__

#include "TBaseTable.h"
#include <string>

using namespace std;
//реализация поискового дерева

struct TreeNode
{
	Data d;
	int diff;
	TreeNode* pRight;
	TreeNode* pLeft;
	TreeNode* pParent;
};

class TSearchTreeTable : public TBaseTable {	
	TreeNode* pRoot;
public:
	TSearchTreeTable() : TBaseTable() { pRoot = nullptr;}
	void balance(int& a, int& b, int p);
	void rotateLeft(TreeNode* a);
	void rotateRight(TreeNode* a);
	void rotateBigLeft(TreeNode* a);
	void rotateBigRight(TreeNode* a);
	void changeBalance(TreeNode* p, int a);
	void insert(const Data& d);
	Data* find(const string key); //убрали &key
	void deleteByKey(const string& key);
	void print();
	~TSearchTreeTable(){}
};
#endif
