//#ifndef _tliststack_h
//#define _tliststack_h
//
//#include <iostream>
//
////ссылка на список
//template <class T>
//struct TNode 
//{
//	T val; //зачение
//	TNode<T>* pNext; //указатель на следующую ссылку
//};
//
//
//template <class T>
//class TStack 
//{
//	TNode<T>* pFirst;
//public:
//
//	//конструктор
//	TStack() 
//	{
//		pFirst = NULL;
//	}
//
//	//деструктор
//	~TStack() 
//	{
//		TNode<T>* tmp = pFirst;
//		if (tmp == NULL)
//			delete tmp;
//		while (pFirst != NULL) 
//		{
//			pFirst = pFirst->pNext;
//			delete tmp;
//			tmp = pFirst;
//		}
//	}
//
//	//контруктор копирования
//	TStack(const TStack<T>& st) 
//	{
//		TNode<T>* tmp = st.pFirst;
//		if (tmp == NULL)
//			pFirst = tmp;
//		while (tmp != NULL) 
//		{
//			Push(tmp->val);
//			tmp = tmp->pNext;
//		}
//		delete tmp;
//	}
//
//	//перегрузка =
//	TStack<T> operator=(const TStack<T>& st) 
//	{
//		if (this != &st) 
//		{
//			if (!IsEmpty())
//				Clear();
//			else {
//				TNode<T>* tmp = st.pFirst;
//				if (tmp == NULL)
//					pFirst = tmp;
//				while (tmp != NULL) 
//				{
//					Push(tmp->val);
//					tmp = tmp->pNext;
//				}
//				delete tmp;
//			}
//		}
//		return *this;
//	}
//
//	//проверка на пустоту
//	bool IsEmpty() const 
//	{
//		return pFirst == NULL;
//	}
//
//	//проверка на полноту
//	bool IsFull() const 
//	{
//		TNode<T>* tmp;
//		tmp = new TNode<T>;
//		if (tmp == NULL)
//			return 1;
//		else 
//		{
//			delete tmp;
//			return 0;
//		}
//	}
//
//	//запушить в стек
//	void Push(const T& a) 
//	{
//		if (IsFull())
//			throw - 1;
//		else 
//		{
//			TNode<T>* tmp;
//			tmp = new TNode<T>;
//			tmp->pNext = pFirst;
//			tmp->val = a;
//			pFirst = tmp;
//		}
//	}
//
//	//извлечение из стека
//	T Pop() 
//	{
//		if (IsEmpty())
//			throw - 1;
//		else 
//		{
//			T res = pFirst->val;
//			TNode<T>* tmp;
//			tmp = pFirst;
//			pFirst = pFirst->pNext;
//			delete tmp;
//			return res;
//		}
//	}
//
//	//вершина стека
//	T Top() 
//	{
//		if (IsEmpty())
//			throw - 1;
//		else
//			return pFirst->val;
//	}
//
//	//очищение стека
//	void Clear() 
//	{
//		TNode<T>* tmp = pFirst;
//		while (pFirst != NULL) 
//		{
//			pFirst = pFirst->pNext;
//			delete tmp;
//			tmp = pFirst;
//		}
//	}
//
//	bool GetSize() 
//	{
//		return size;
//	}
//};
//#endif 
//
