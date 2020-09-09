// #pragma once
// �ܹ��� ���� ����Ʈ�� �̿��� ���� ����

#ifndef _STACK
#define _STACK

template <typename T>
class ReverseNode
{
private:
	T data;
	ReverseNode<T>* prevPointer;					// ���� ���

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
	ReverseNode<T>* topNode;			// ��� ���
	int numberOfNodes;						// ��� ����

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
