#pragma once
#include <iostream>

namespace bt//binary tree
{
	template<typename T>
	class Node
	{
	public:
		Node<T>* left;
		Node<T>* right;
		T value;
		Node(T value, Node<T>* left = nullptr, Node<T>* right = nullptr);
	};
	template<typename T>
	class BinaryTree
	{
	private:
		Node<T>* root;

		void printNode(Node<T>* node);//writes node to console
	public:
		BinaryTree();
		void insert(T value);//adds node to tree
		Node<T>* search(T value);//returns node with value
		void print();//writes tree to console
	};
}
namespace bt
{
	template<typename T>
	Node<T>::Node(T value, Node<T>* left, Node<T>* right) :
		value{value}, left{left}, right{right} {}
	template<typename T>
	BinaryTree<T>::BinaryTree():root(nullptr){}
	template<typename T>
	void BinaryTree<T>::insert(T value)
	{
		auto current = root;
		auto node = new Node<T>(value);
		while (current)
		{
			if (value < current->value)
			{
				if (current->left) current = current->left;
				else
				{
					current->left = node;
					current = current->left;
					break;
				}
			}	
			if (value > current->value)
			{
				if (current->right) current = current->right;
				else
				{
					current->right = node;
					current = current->right;
					break;
				}
			}
		}
		if (!current) current = node;
		if (!root) root = current;
	}
	template<typename T>
	Node<T>* BinaryTree<T>::search(T value)
	{
		auto current = root;
		while (current)
		{
			if (value < current->value)
				current = current->left;
			if (value > current->value)
				current = current->right;
			if (value == current->value) return current;
		}
		return nullptr;
	}
	template<typename T>
	void BinaryTree<T>::printNode(Node<T>* node)
	{
		if (!node) return;
		std::cout << node->value << " ";
		if (node->left || node->right) std::cout << "->{ ";
		printNode(node->left);
		if(node->left && node->right) std::cout << ", ";
		printNode(node->right);
		if (node->left || node->right) std::cout << "}";
	}
	template<typename T>
	void BinaryTree<T>::print()
	{
		printNode(root);
		std::cout << std::endl;
	}
}