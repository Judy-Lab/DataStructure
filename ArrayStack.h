// #pragma once
// 배열을 이용한 스택 구현

#ifndef _ARRAYSTACK
#define _ARRAYSTACK

template<class T, int _size>
class ArrayStack
{
private:
	T* dataArray;
	int sizeOfArray;

	int numberOfData;
public:
	ArrayStack();
	~ArrayStack();

	int GetNumberOfData() { return numberOfData; }

	bool Push(T _data);
	bool Pop(T& _outData);	

	void Clear();
	bool IsEmpty();
};

#endif

template<class T, int _size>
inline ArrayStack<T, _size>::ArrayStack()
{
	sizeOfArray = _size;
	numberOfData = 0;
	dataArray = new T[sizeOfArray];
}

template<class T, int _size>
inline ArrayStack<T, _size>::~ArrayStack()
{
	delete dataArray;
}


template<class T, int _size>
inline bool ArrayStack<T, _size>::Push(T _data)
{
	if (numberOfData == sizeOfArray) {
		return false;
	}

	dataArray[numberOfData - 1] = _data;
	numberOfData++;
	return true;
}

template<class T, int _size>
inline bool ArrayStack<T, _size>::Pop(T& _outData)
{
	if (IsEmpty()) {
		return false;
	}

	_outData = dataArray[numberOfData - 1];
	numberOfData--;
	return true;
}

template<class T, int _size>
inline void ArrayStack<T, _size>::Clear()
{
	for (int i = 0; i < numberOfData; i++) {
		delete dataArray[i];
	}

	numberOfData = 0;
}

template<class T, int _size>
inline bool ArrayStack<T, _size>::IsEmpty()
{
	if (numberOfData == 0) {
		return true;
	}
	return false;
}
