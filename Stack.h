// #pragma once
// 단방향 연결 리스트를 이용한 스택 구현

#ifndef _STACK
#define _STACK

template <typename T>
class ReverseNode
{
private:
	T data;
	ReverseNode<T>* prevPointer;					// 이전 노드

public:
	ReverseNode() {
		memset(&data, 0, sizeof(data));
		prevPointer = nullptr;
	}

	ReverseNode(T _data) : data(_data), prevPointer(nullptr) {};
	~ReverseNode() {};

	T GetData() { return data; }
	void SetData(T _data) { data = _data; }

	ReverseNode<T>* GetPrevPointer() { return prevPointer; }
	void SetPrevPointer(ReverseNode<T>* _prevPointer) { prevPointer = _prevPointer; }
};

template <typename T>
class Stack
{
private:
	ReverseNode<T>* topNode;			// 상단 노드
	int numberOfNodes;						// 노드 갯수

public:
	Stack();
	~Stack();

	ReverseNode<T>* GetTopNode() { return topNode; };
	int GetNumberOfNodes() { return numberOfNodes; }

	void Push(T _data);
	T Pop();
	bool isEmpty();
};

template<typename T>
inline Stack<T>::Stack()
{
	topNode = nullptr;
	numberOfNodes = 0;
}

template<typename T>
inline Stack<T>::~Stack()
{
	ReverseNode<T>* targetNode = topNode;

	while (targetNode != nullptr)
	{
		ReverseNode<T>* targetPrevNode = targetNode->GetPrevPointer();

		delete targetNode;
		targetNode = targetPrevNode;
	}
}

template<typename T>
inline void Stack<T>::Push(T _data)
{
	ReverseNode<T>* targetNode = new ReverseNode<T>(_data);
	targetNode->SetPrevPointer(topNode);

	topNode = targetNode;
	numberOfNodes++;
}

template<typename T>
inline T Stack<T>::Pop()
{
	ReverseNode<T>* targetNode = topNode;
	topNode = targetNode->GetPrevPointer();

	T data = targetNode->GetData();
	numberOfNodes--;

	delete targetNode;
	return data;
}

template<typename T>
inline bool Stack<T>::isEmpty()
{
	if (topNode == nullptr && numberOfNodes == 0) {
		return true;
	}
	return false;
}

#endif
