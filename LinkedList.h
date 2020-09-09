// #pragma once
// ����� ���� ����Ʈ

#ifndef _LINKEDLIST
#define _LINKEDLIST
#define STACKSIZE 5
#include "ArrayStack.h"

template <typename T>
class DoublyNode
{
private:
	T data;

	DoublyNode<T>* prevPointer;						// �������
	DoublyNode<T>* nextPointer;						// �������

public:
	DoublyNode() {
		memset(&data, 0, sizeof(data));
		prevPointer = nullptr;
		nextPointer = nullptr;
	}

	DoublyNode(T _data) : data(_data), prevPointer(nullptr), nextPointer(nullptr) {};
	~DoublyNode() {};

	T GetData() { return data; }
	void SetData(T _data) { data = _data; }

	DoublyNode<T>* GetNextPointer() { return nextPointer; }
	DoublyNode<T>* GetPrevPointer() { return prevPointer; }
	void SetNextPointer(DoublyNode<T>* _nextPointer) { nextPointer = _nextPointer; }
	void SetPrevPointer(DoublyNode<T>* _prevPointer) { prevPointer = _prevPointer; }
};

template <typename T>
class LinkedList
{
private:
	DoublyNode<T>* headNode;				// ��� ���
	DoublyNode<T>* tailNode;					// ������ ���

	int numberOfNodes;

	ArrayStack<DoublyNode<T>*, STACKSIZE>* searchStack;
	DoublyNode<T>* searchNode;
public:
	LinkedList();
	~LinkedList();

	DoublyNode<T>* GetHeadNode() { return headNode; }
	DoublyNode<T>* GetTailNode() { return tailNode; }
	int GetNumberOfNodes() { return numberOfNodes; }

	void InsertFirst(T _data);
	void InsertLast(T _data);

	bool Remove(T _data);
	bool RemoveFirst();
	bool RemoveLast();
	DoublyNode<T>* RemoveFromListOnly(T _data);

	void Clear();

	// �ܼ� ��ȸ �˻�
	DoublyNode<T>* SearchNode(T _data);

	// �˻����� �ش� ����Ʈ�� �ٽ� �˻��Ҷ�
	// SearchStart -> SearchNext�� �˻� -> SearchEnd�� ���� �˻� ���� �ٽ� �ҷ�����
	void SearchStart();
	T SearchNext();
	void SearchEnd();
	bool SearchCheck();
};

template <typename T>
inline LinkedList<T>::LinkedList()
{
	headNode = new DoublyNode<T>();
	tailNode = new DoublyNode<T>();
	headNode->SetNextPointer(tailNode);
	tailNode->SetPrevPointer(headNode);

	numberOfNodes = 0;

	searchNode = nullptr;
	searchStack = new ArrayStack<DoublyNode<T>*, STACKSIZE>();
}

template <typename T>
inline LinkedList<T>::~LinkedList()
{
	DoublyNode<T>* targetNode = headNode->GetNextPointer();
	delete headNode;

	while (targetNode != nullptr) {
		headNode = targetNode;
		targetNode = targetNode->GetNextPointer();
		delete headNode;
	}
}

/// <summary>
/// LinkedList ���� �տ� ��� �߰�
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_data">������</param>
template<typename T>
inline void LinkedList<T>::InsertFirst(T _data)
{
	DoublyNode<T>* targetNode = new DoublyNode<T>(_data);
	DoublyNode<T>* headNextNode = headNode->GetNextPointer();
	targetNode->SetNextPointer(headNextNode);
	targetNode->SetPrevPointer(headNode);
	headNode->SetNextPointer(targetNode);

	headNextNode->SetPrevPointer(targetNode);
	numberOfNodes++;
}

/// <summary>
/// LinkedList ���� �ڿ� ��� �߰�
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_data">������</param>
template<typename T>
inline void LinkedList<T>::InsertLast(T _data)
{
	DoublyNode<T>* targetNode = new DoublyNode<T>(_data);
	DoublyNode<T>* tailPrevNode = tailNode->GetPrevPointer();
	targetNode->SetPrevPointer(tailPrevNode);
	targetNode->SetNextPointer(tailNode);
	tailNode->SetPrevPointer(targetNode);
	
	tailPrevNode->SetNextPointer(targetNode);
	numberOfNodes++;
}

/// <summary>
/// LinkedList���� ���� ������ ���� ���� ��带 ã�� ����
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_data">������</param>
/// <returns>������ �����ߴٸ� false ��ȯ</returns>
template<typename T>
inline bool LinkedList<T>::Remove(T _data)
{
	DoublyNode<T>* targetNode = headNode->GetNextPointer();
	if (targetNode == nullptr) {
		return false;
	}

	while (targetNode != nullptr)
	{
		if (targetNode->GetData() == _data)
		{
			DoublyNode<T>* prevNode = targetNode->GetPrevPointer();
			DoublyNode<T>* nextNode = targetNode->GetNextPointer();

			if (nextNode != nullptr) {
				prevNode->SetNextPointer(nextNode);
				nextNode->SetPrevPointer(prevNode);

				numberOfNodes--;
				delete targetNode;
				return true;
			}
		}

		targetNode = targetNode->GetNextPointer();
	}
	return false;
}

/// <summary>
/// LinkedList���� ���� ������ ��带 ����
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns>������ �����ߴٸ� false ��ȯ</returns>
template<typename T>
inline bool LinkedList<T>::RemoveFirst()
{
	DoublyNode<T>* headNodePointer = headNode;
	DoublyNode<T>* targetNode = headNodePointer->GetNextPointer();
	if (targetNode == nullptr) {
		return false;
	}
	DoublyNode<T>* targetNextNode = targetNode->GetNextPointer();

	headNodePointer->SetNextPointer(targetNextNode);
	if (targetNextNode != nullptr) {
		targetNextNode->SetPrevPointer(headNodePointer);
	}

	numberOfNodes--;
	delete targetNode;
	return true;
}

/// <summary>
/// LinkedList���� ���� �������� �ִ� ��带 ����
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns>������ �����ߴٸ� false ��ȯ</returns>
template<typename T>
inline bool LinkedList<T>::RemoveLast()
{
	DoublyNode<T>* targetNode = tailNode;
	if (targetNode == headNode) {
		return false;
	}
	DoublyNode<T>* targetPrevNode = tailNode->GetPrevPointer();
	tailNode = targetPrevNode;

	numberOfNodes--;
	delete targetNode;
	return true;
}

/// <summary>
/// LinkedList���� ���� �����͸� ���� ��带 �����ϵ�, ��忡 �Ҵ�� �޸𸮸� �������� ����
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_data">������</param>
/// <returns>������ �����ߴٸ� nullptr ��ȯ</returns>
template<typename T>
inline DoublyNode<T>* LinkedList<T>::RemoveFromListOnly(T _data)
{
	DoublyNode<T>* targetNode = headNode->GetNextPointer();
	if (targetNode == nullptr) {
		return nullptr;
	}

	while (targetNode != nullptr)
	{
		if (targetNode->GetData() == _data)
		{
			DoublyNode<T>* prevNode = targetNode->GetPrevPointer();
			DoublyNode<T>* nextNode = targetNode->GetNextPointer();

			if (nextNode != nullptr) {
				prevNode->SetNextPointer(nextNode);
				nextNode->SetPrevPointer(prevNode);

				numberOfNodes--;
				return targetNode;
			}
		}

		targetNode = targetNode->GetNextPointer();
	}
	return nullptr;
}

/// <summary>
/// LinkedList�� ���
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
inline void LinkedList<T>::Clear()
{
	DoublyNode<T>* targetNode = headNode->GetNextPointer();
	if (targetNode == tailNode) {
		return;
	}

	DoublyNode<T>* deleteNode;
	while (targetNode != tailNode) {
		deleteNode = targetNode;
		targetNode = targetNode->GetNextPointer();
		delete deleteNode;
	}

	numberOfNodes = 0;
	headNode->SetNextPointer(tailNode);
	headNode->SetPrevPointer(nullptr);
	tailNode->SetPrevPointer(headNode);
	tailNode->SetNextPointer(nullptr);
}

/// <summary>
/// LinkedList���� �ش� �����Ϳ� ���� �����͸� ���� ��带 ã�� ��ȯ
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_data">������</param>
/// <returns>Ž���� �����ߴٸ� nullptr ��ȯ</returns>
template<typename T>
inline DoublyNode<T>* LinkedList<T>::SearchNode(T _data)
{
	DoublyNode<T>* targetNode = headNode->GetNextPointer();
	if (targetNode == nullptr) {
		return nullptr;
	}

	while (targetNode != nullptr)
	{
		if (targetNode->GetData() == _data)
		{
			return targetNode;
		}

		targetNode = targetNode->GetNextPointer();
	}

	return nullptr;
}

/// <summary>
/// Ž�����̴� ��带 ���ÿ� �����ϰ�, ó������ �ٽ� Ž��
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
inline void LinkedList<T>::SearchStart()
{
	if (searchNode != nullptr) {
		searchStack->Push(searchNode);
		searchNode = nullptr;
	}
}

/// <summary>
/// ���� Ž������ ����� ���� ��带 ��ȯ / int������ ���ø� ����ȭ
/// </summary>
/// <returns>������ ��� ���� ��, ȣ��� -1 ��ȯ</returns>
template<>
inline int LinkedList<int>::SearchNext()
{
	if (searchNode == nullptr) {
		searchNode = headNode;
	}

	searchNode = searchNode->GetNextPointer();
	if (searchNode != nullptr) {
		return searchNode->GetData();
	}

	return -1;
}

/// <summary>
/// ���� Ž������ ����� ���� ��带 ��ȯ
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns>������ ��� ���� ��, ȣ��� nullptr ��ȯ</returns>
template<typename T>
inline T LinkedList<T>::SearchNext()
{
	if (searchNode == nullptr) {
		searchNode = headNode;
	}

	searchNode = searchNode->GetNextPointer();
	if (searchNode != nullptr) {
		return searchNode->GetData();
	}

	return nullptr;
}

/// <summary>
/// Ž���� ���� �Ŀ� ���ÿ� ����Ǿ� �ִ� ���� Ž�� ������ ����
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
inline void LinkedList<T>::SearchEnd()
{
	if (searchStack->GetNumberOfData() != 0) {
		searchStack->Pop(searchNode);
	}
}

/// <summary>
/// ���� LinkedList�� Ž�������� üũ
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns>Ž�����̶�� true��ȯ</returns>
template<typename T>
inline bool LinkedList<T>::SearchCheck()
{
	if (searchNode == nullptr) {
		return false;
	}
	else {
		return true;
	}
}

#endif