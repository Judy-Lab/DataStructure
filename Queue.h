// #pragma once
// 단방향 연결 리스트를 이용한 큐 구현

#ifndef _QUEUE
#define _QUEUE

template <typename T>
class SinglyNode
{
private:
	T data;
	SinglyNode<T>* nextPointer;						// 다음노드

public:
	SinglyNode() {
		memset(&data, 0, sizeof(data));
		nextPointer = nullptr;
	}

	SinglyNode(T _data) : data(_data), nextPointer(nullptr) {};
	~SinglyNode() {};

	T GetData() { return data; }
	void SetData(T _data) { data = _data; }

	SinglyNode<T>* GetNextPointer() { return nextPointer; }
	void SetNextPointer(SinglyNode<T>* _nextPointer) { nextPointer = _nextPointer; }
};

template <typename T>
class Queue
{
private:
	SinglyNode<T>* frontNode;
	SinglyNode<T>* backNode;

	int numberOfNodes;
public:
	Queue();
	~Queue();

	int GetNumberOfNodes() { return numberOfNodes; }
	T GetFrontNode() { return frontNode->GetData(); }

	void Enqueue(T _data);
	bool Dequeue(T& _data);
	bool IsEmpty();
};

#endif

template<typename T>
inline Queue<T>::Queue()
{
	frontNode = nullptr;
	backNode = nullptr;
}

template<typename T>
inline Queue<T>::~Queue()
{
	SinglyNode<T>* targetNode = frontNode;
	if (frontNode == nullptr) {
		return;
	}
	else if (frontNode == backNode) {
		delete frontNode;
		return;
	}

	while (targetNode != nullptr)
	{
		frontNode = targetNode;
		targetNode = targetNode->nextPointer();
		delete frontNode;
	}
}

template<typename T>
inline void Queue<T>::Enqueue(T _data)
{
	SinglyNode<T>* targetNode = new SinglyNode<T>(_data);

	if (frontNode == nullptr) {
		frontNode = backNode = targetNode;
	}
	else if (frontNode == backNode) {
		frontNode->SetNextPointer(targetNode);
		backNode = targetNode;
	}
	else {
		backNode->SetNextPointer(targetNode);
		backNode = targetNode;
	}

	numberOfNodes++;
}

template<typename T>
inline bool Queue<T>::Dequeue(T& _data)
{
	SinglyNode<T>* targetNode = frontNode;
	if (targetNode == nullptr) {
		return false;
	}
	
	_data = targetNode->GetData();
	delete targetNode;

	if (frontNode != backNode) {
		frontNode = frontNode->nextPointer();
	}
	else {
		frontNode = backNode = nullptr;
	}

	numberOfNodes--;
	return true;
}

template<typename T>
inline bool Queue<T>::IsEmpty()
{
	if (frontNode == nullptr) {
		return true;
	}
	return false;
}
