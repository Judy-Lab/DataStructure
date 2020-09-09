// #pragma once
// 이진탐색트리

#ifndef _TREE
#define _TREE

#include <iostream>
#include "Queue.h"

template <typename T>
class BinaryTreeNode
{
private:
	T data;

	BinaryTreeNode<T>* rightNode;
	BinaryTreeNode<T>* leftNode;
public:
	BinaryTreeNode(T _data) : data(_data), rightNode(nullptr), leftNode(nullptr) { };

	T GetData() { return data; };
	void SetData(T _data) { data = _data; };

	BinaryTreeNode<T>* GetRightNode() { return rightNode; };
	BinaryTreeNode<T>* GetLeftNode() { return leftNode; }
	void SetRightNode(BinaryTreeNode<T>* _node) { rightNode = _node; }
	void SetLeftNode(BinaryTreeNode<T>* _node) { leftNode = _node; }
};

class BinaryTree
{
private:
	BinaryTreeNode<int>* rootNode;

public:
	BinaryTree();
	BinaryTree(int _data);

	BinaryTreeNode<int>* GetRootNode() { return rootNode; }

	bool AddNode(int _data);
	bool DeleteNode(BinaryTreeNode<int>* _node);
	BinaryTreeNode<int>* SearchNode(int _data);

	void PrintTree(BinaryTreeNode<int>* _node);
};

inline BinaryTree::BinaryTree()
{
	rootNode = nullptr;
}

inline BinaryTree::BinaryTree(int _data)
{
	rootNode = new BinaryTreeNode<int>(_data);
}

/// <summary>
/// 해당 데이터가 복사된 노드 추가
/// </summary>
/// <param name="_data">데이터</param>
/// <returns>루트노드를 추가했다면 false 반환</returns>
inline bool BinaryTree::AddNode(int _data)
{
	if (rootNode == nullptr) {
		rootNode = new BinaryTreeNode<int>(_data);
		return false;;
	}

	BinaryTreeNode<int>* targetNode = rootNode;
	while (targetNode != nullptr)
	{
		if (targetNode->GetData() < _data) {
			if (targetNode->GetRightNode() == nullptr) {
				targetNode->SetRightNode(new BinaryTreeNode<int>(_data));
				break;
			}
			else {
				targetNode = targetNode->GetRightNode();
			}
		}
		else {
			if (targetNode->GetLeftNode() == nullptr) {
				targetNode->SetLeftNode(new BinaryTreeNode<int>(_data));
				break;
			}
			else {
				targetNode = targetNode->GetLeftNode();
			}
		}
	}

	return true;
}

/// <summary>
/// 해당 노드를 찾아 삭제함
/// </summary>
/// <param name="_node"></param>
/// <returns>삭제 실패시 false 반환</returns>
inline bool BinaryTree::DeleteNode(BinaryTreeNode<int>* _node)
{
	if (rootNode == nullptr) {
		return false;
	}
	else if (_node == rootNode) {
		if (_node->GetLeftNode() == nullptr && _node->GetRightNode() == nullptr) {
			delete _node;
			rootNode = nullptr;
			return true;
		}
		else if (_node->GetLeftNode() == nullptr) {
			rootNode = rootNode->GetRightNode();
			delete _node;
			return true;
		}
		else if (_node->GetRightNode() == nullptr) {
			rootNode = rootNode->GetLeftNode();
			delete _node;
			return true;
		}
		else {
			rootNode = rootNode->GetRightNode();
			rootNode->SetLeftNode(_node->GetLeftNode());
			delete _node;
			return true;
		}
	}

	BinaryTreeNode<int>* targetNode = rootNode;
	BinaryTreeNode<int>* parantNode = rootNode;
	while (targetNode != nullptr)
	{
		if (_node->GetData() < targetNode->GetData()) {
			parantNode = targetNode;
			if (targetNode->GetLeftNode() == nullptr) {
				return false;
			}
			targetNode = targetNode->GetLeftNode();
		}
		else if (_node->GetData() > targetNode->GetData()) {
			parantNode = targetNode;
			if (targetNode->GetRightNode() == nullptr) {
				return false;
			}
			targetNode = targetNode->GetRightNode();
		}
		else {
			if (targetNode->GetLeftNode() == nullptr && targetNode->GetRightNode() == nullptr) {
				delete targetNode;
				return true;
			}
			else if (targetNode->GetRightNode() == nullptr) {
				if (parantNode->GetLeftNode() == targetNode) {
					parantNode->SetLeftNode(targetNode->GetLeftNode());
				}
				else {
					parantNode->SetRightNode(targetNode->GetLeftNode());
				}
				delete targetNode;
				return true;
			}
			else {
				if (parantNode->GetLeftNode() == targetNode) {
					parantNode->SetLeftNode(targetNode->GetRightNode());
				}
				else {
					parantNode->SetRightNode(targetNode->GetRightNode());
				}
				delete targetNode;
				return true;
			}
		}
	}

	return false;
}

/// <summary>
/// 해당 데이터를 가진 노드 탐색
/// </summary>
/// <param name="_data"></param>
/// <returns>탐색 실패시 nullptr 반환</returns>
inline BinaryTreeNode<int>* BinaryTree::SearchNode(int _data)
{
	if (rootNode == nullptr) {
		return nullptr;
	}

	BinaryTreeNode<int>* targetNode = rootNode;
	while (targetNode != nullptr)
	{
		if (targetNode->GetData() < _data) {
			targetNode = targetNode->GetLeftNode();
		}
		else if (targetNode->GetData() > _data) {
			targetNode = targetNode->GetRightNode();
		}
		else {
			return targetNode;
		}
	}
}

/// <summary>
/// 노드 출력
/// </summary>
/// <param name="_node"></param>
inline void BinaryTree::PrintTree(BinaryTreeNode<int>* _node)
{
	if (_node != nullptr) {
		PrintTree(_node->GetLeftNode());
		std::cout << _node->GetData() << std::endl;
		PrintTree(_node->GetRightNode());
	}
}

#endif
