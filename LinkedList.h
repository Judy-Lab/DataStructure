// #pragma once
// 양방향 연결 리스트

#ifndef _LINKEDLIST
#define _LINKEDLIST
#define STACKSIZE 5
#include "ArrayStack.h"

template <typename T>
class DoublyNode
{
private:
	T data;

	DoublyNode<T>* prevPointer;						// 이전노드
	DoublyNode<T>* nextPointer;						// 다음노드

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
	DoublyNode<T>* headNode;				// 헤드 노드
	DoublyNode<T>* tailNode;					// 마지막 노드

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

	// 단순 순회 검색
	DoublyNode<T>* SearchNode(T _data);

	// 검색중인 해당 리스트를 다시 검색할때
	// SearchStart -> SearchNext로 검색 -> SearchEnd로 이전 검색 정보 다시 불러오기
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
/// LinkedList 가장 앞에 노드 추가
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_data">데이터</param>
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
/// LinkedList 가장 뒤에 노드 추가
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_data">데이터</param>
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
/// LinkedList에서 같은 데이터 값을 가진 노드를 찾아 삭제
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_data">데이터</param>
/// <returns>삭제에 실패했다면 false 반환</returns>
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
/// LinkedList에서 가장 앞쪽의 노드를 삭제
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns>삭제에 실패했다면 false 반환</returns>
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
/// LinkedList에서 가장 마지막에 있는 노드를 삭제
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns>삭제에 실패했다면 false 반환</returns>
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
/// LinkedList에서 같은 데이터를 가진 노드를 삭제하되, 노드에 할당된 메모리를 해제하지 않음
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_data">데이터</param>
/// <returns>삭제에 실패했다면 nullptr 반환</returns>
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
/// LinkedList를 비움
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
/// LinkedList에서 해당 데이터와 같은 데이터를 가진 노드를 찾아 반환
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_data">데이터</param>
/// <returns>탐색에 실패했다면 nullptr 반환</returns>
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
/// 탐색중이던 노드를 스택에 저장하고, 처음부터 다시 탐색
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
/// 현재 탐색중인 노드의 다음 노드를 반환 / int형으로 템플릿 전문화
/// </summary>
/// <returns>마지막 노드 도달 후, 호출시 -1 반환</returns>
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
/// 현재 탐색중인 노드의 다음 노드를 반환
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns>마지막 노드 도달 후, 호출시 nullptr 반환</returns>
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
/// 탐색이 끝난 후에 스택에 저장되어 있던 이전 탐색 정보를 꺼냄
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
/// 현재 LinkedList를 탐색중인지 체크
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns>탐색중이라면 true반환</returns>
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