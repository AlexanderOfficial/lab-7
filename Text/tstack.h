#ifndef _TSTACK_
#define _TSTACK_

template <class T>
class TStack {
	T* arr;
	int size;
	int num;

public:

	//конструктор
	TStack(int _size = 10) {
		if (_size <= 0) throw _size;
		size = _size;
		arr = new T[size];
		num = -1;
	}

	//деструктор
	~TStack() {
		delete[] arr;
	}

	//конструктор копирования
	TStack(const TStack& St) {
		size = St.size;
		arr = new T[size];
		num = St.num;
		for (int i = 0; i <= num; i++)
			arr[i] = St.arr[i];
	}

	//запушить в стек
	void Push(const T& el) {
		if (IsFull()) throw num;
		else {
			arr[++num] = el;
		}
	}

	//извлечь из стека
	T Pop() {
		if (IsEmpty()) throw num;
		else {
			return arr[num--];
		}
	}

	//вершина стека
	T Top() {
		if (num == -1) throw num;
		return arr[num];
	}

	//проверка на пустоту
	bool IsEmpty() const {
		if (num == -1)
			return true;
		return false;
	}

	//проверка на полноту
	bool IsFull() const {
		if (num == size - 1)
			return true;
		return false;
	}

	//ощичение стека
	void Clear() {
		num = -1;
	}

	bool GetSize() {
		return size;
	}
};
#endif 

