#pragma once
#include <iostream>
#include <vector>
#include "book.h"

using namespace wm;

namespace fh//fibonacci heap
{
	template<typename T>
	class FNode
	{
	public:
		T value;
		std::size_t degree;//number of children
		bool mark;
		FNode<T>* parent;
		FNode<T>* child;
		FNode<T>* right;
		FNode<T>* left;
		FNode(T value = T(), FNode<T>* parent = nullptr, FNode<T>* child = nullptr,
			FNode<T>* right = nullptr, FNode<T>* left = nullptr,
			std::size_t degree = 0, bool mark = false);
		void addChild(FNode<T>* node);//adds child to node
		void removeChild(FNode<T>* node);//removes child from node but don't delete it
	};
	template<typename T>
	class FibonacciHeap
	{
	private:
		std::vector<FNode<T>*> roots;
		std::size_t size;

		void printNode(FNode<T>* node, FNode<T>* begin);//writes the node to console
		void mergeLists(std::vector<FNode<T>*>& list);//unions root lists
		void addRoots(FNode<T>* node);//adds node and its brothers to root
		void consolidate();//seals the heap
		void link(FNode<T>* parent, FNode<T>* node);//links parent to node
		std::size_t findIndex(FNode<T>* node);//finds index of node in roots
		FNode<T>* findInTree(FNode<T>* root, FNode<T>* current, T value);//finds a node in tree
		FNode<T>* findNode(T value);//finds node in heap
		void cut(FNode<T>* node, FNode<T>* parent);
		void cascadingCut(FNode<T>* parent);
		void clearNode(FNode<T>* node);//deletes the node and children and brothers
	public:
		FibonacciHeap();
		void insert(T value);//creates and adds a node with value to heap
		void print();//writes a heap to concole
		void remove(T value);//removes a node with value from heap
		void merge(FibonacciHeap<T>& heap);//unions heap with this
		void decrease(T value, T newValue);//edits a value
		FNode<T>* getMin();//returns node with minimun value 
		FNode<T>* extractMin();//returns min node and removes it from heap
		~FibonacciHeap();
	};
	template<typename T>
	void swap(T& first, T& second);//swaps two values
	void setColor(int text, int background);//edits console color
	template<typename T>
	T minValue();
	template<>
	Event minValue();
}
namespace fh
{
	template<typename T>
	T minValue()
	{
		return std::numeric_limits<T>::min();
	}
	template<>
	Event minValue()
	{
		Event Event;
		Event.isMin = true;
		return Event;
	}
#include <Windows.h>
	void setColor(int text, int background)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	}
	template<typename T>
	void swap(T& first, T& second)
	{
		T temp = first;
		first = second;
		second = temp;
	}
	template<typename T>
	FNode<T>::FNode(T value, FNode<T>* parent, FNode<T>* child,
		FNode<T>* right, FNode<T>* left, std::size_t degree, bool mark):
		value{value}, parent{parent},child{child},right{right},left{left},
		degree{degree},mark{mark}{}
	template<typename T>
	void FNode<T>::addChild(FNode<T>* node)
	{
		if (!node) return;
		if (child)
		{
			node->right = child;
			node->left = child->left;
			child->left->right = node;
			child->left = node;		
		}
		else
		{
			node->left = node;
			node->right = node;
		}
		node->parent = this;
		child = node;
		degree++;
	}
	template<typename T>
	void FNode<T>::removeChild(FNode<T>* node)
	{
		if (!child || !node)return;
		FNode<T>* current = child;
		do
		{
			if (node == current)
			{
				if (current == current->right)
					child = nullptr;
				else
				{
					current->left->right = current->right;
					current->right->left = current->left;
					if (current == child)
						child = current->right;
				}
				degree--;
				return;
			}
			current = current->right;
		} while (current != child);
	}
	template<typename T>
	FibonacciHeap<T>::FibonacciHeap():size{0}{}
	template<typename T>
	void FibonacciHeap<T>::insert(T value)
	{
		roots.push_back(new FNode<T>{ value });
		
		if (roots.size() > 1 && roots[0]->value > roots[roots.size() - 1]->value)
				swap(roots[0], roots[roots.size() - 1]);
		
		size++;
	}
	template<typename T>
	void FibonacciHeap<T>::printNode(FNode<T>* node, FNode<T>* begin)
	{
		if (!node) return;
		if (node->mark) setColor(0, 7);
		std::cout << node->value;
		setColor(7,0);
		std::cout << " ";
		if (node->child) std::cout << "-> {";
		printNode(node->child, node->child);
		if (node->child) std::cout << "}";
		if (node->right && node->right != begin)
		{
			std::cout << ", ";
			printNode(node->right, begin);
		}
	}
	template<typename T>
	void FibonacciHeap<T>::print()
	{
		if (roots.size() == 0)
		{
			std::cout << "\nEmpty" << std::endl;
			return;
		}
		std::cout << "# Size: " << size;
		for (std::size_t i = 0; i < roots.size(); i++)
		{
			std::cout << "\n|" << std::endl;
			printNode(roots[i], roots[i]);
		}

		std::cout << std::endl << std::endl;
	}
	template<typename T>
	FNode<T>* FibonacciHeap<T>::getMin()
	{
		return roots[0];
	}
	template<typename T>
	void FibonacciHeap<T>::mergeLists(std::vector<FNode<T>*>& list)
	{
		if (roots.size() > 0 && list.size() > 0 && roots[0]->value > list[0]->value)
				swap(roots[0], list[0]);	
		for (std::size_t i = 0; i < list.size(); i++)
			roots.push_back(list[i]);
		list.clear();
	}
	template<typename T>
	void FibonacciHeap<T>::merge(FibonacciHeap<T>& heap)
	{
		mergeLists(heap.roots);
		this->size += heap.size;
		heap.size = 0;
	}
	template<typename T>
	void FibonacciHeap<T>::addRoots(FNode<T>* node)
	{
		if (!node) return;
		node->left = nullptr;
		node->parent = nullptr;
		roots.push_back(node);
		addRoots(node->right);
		node->right = nullptr;
	}
	template<typename T>
	std::size_t FibonacciHeap<T>::findIndex(FNode<T>* node)
	{
		for (std::size_t i = 0; i < roots.size(); i++)
			if (node == roots[i]) return i;
		return roots.size();
	}
	template<typename T>
	void FibonacciHeap<T>::link(FNode<T>* parent, FNode<T>* node)
	{
		roots.erase(roots.begin() + findIndex(node));
		parent->addChild(node);
		node->mark = false;
	}
	template<typename T>
	void FibonacciHeap<T>::consolidate()
	{
		if (roots.size() < 2) return;
		std::vector<FNode<T>*> array(size, nullptr);
		std::size_t i = 0;
		while (roots.size() > 0 && i < roots.size())
		{
			std::size_t degree = roots[i]->degree;
			FNode<T>* root = roots[i];
			while (array[degree])
			{
				FNode<T>* node = array[degree];
				if (root->value > node->value)
					swap(root, node);
				link(root, node);
				array[degree] = nullptr;
				degree++;
			}
			array[degree] = root;
			i = findIndex(root) + 1;
		}
		roots.clear();
		for (std::size_t i = 0; i < array.size(); i++)
		{
			if (array[i])
			{
				roots.push_back(array[i]);
				if (roots.size() > 1 && 
					roots[0]->value > roots[roots.size() - 1]->value)
					swap(roots[0], roots[roots.size() - 1]);
			}
		}
		array.clear();
	}
	template<typename T>
	FNode<T>* FibonacciHeap<T>::extractMin()
	{
		FNode<T>* node = getMin();
		if (!node) return nullptr;
		if (node->child || roots.size() > 1)
		{
			if (node->child && node->child->left)
				node->child->left->right = nullptr;
			addRoots(node->child);
		}	
		roots.erase(roots.begin());
		consolidate();
		size--;
		return node;
	}
	template<typename T>
	FNode<T>* FibonacciHeap<T>::findInTree(FNode<T>* root, FNode<T>* current, T value)
	{
		if (!root) return nullptr;
		if (root->value == value) return root;
		if (root->right != current)
		{
			FNode<T>* right = findInTree(root->right, current, value);
			if (right) return right;
		}
		if (root->value > value) return nullptr;
		return findInTree(root->child, root->child, value);
	}
	template<typename T>
	FNode<T>* FibonacciHeap<T>::findNode(T value)
	{
		for (std::size_t i = 0; i < roots.size(); i++)
		{
			if (value >= roots[i]->value)
			{
				FNode<T>* node = findInTree(roots[i], roots[i], value);
				if (node) return node;
			}
		}
		return nullptr;
	}
	template<typename T>
	void FibonacciHeap<T>::cut(FNode<T>* node, FNode<T>* parent)
	{
		parent->removeChild(node);
		node->parent = nullptr;
		node->right = nullptr;
		node->left = nullptr;
		node->mark = false;
		roots.push_back(node);
	}
	template<typename T>
	void FibonacciHeap<T>::cascadingCut(FNode<T>* parent)
	{
		if (!parent) return;
		FNode<T>* node = parent->parent;
		if (!node) return;
		if (parent->mark)
		{
			cut(parent, node);
			cascadingCut(node);
		}
		else
		{
			parent->mark = true;
		}
	}
	template<typename T>
	void FibonacciHeap<T>::decrease(T value, T newValue)
	{
		if (value < newValue)
		{
			std::cerr << "Error! The new key is larger than the current one." << std::endl;
			exit(-1);
			return;
		}
		if (value == newValue) return;
		FNode<T>* node = findNode(value);
		if (!node) return;
		node->value = newValue;
		FNode<T>* parent = node->parent;
		if (parent && parent->value > node->value)
		{
			cut(node, parent);
			cascadingCut(parent);
		}
		if (node->value < roots[0]->value)
			swap(roots[0], roots[findIndex(node)]);
	}
	template<typename T>
	void FibonacciHeap<T>::remove(T value)
	{
		T minVal = minValue<T>();
		decrease(value, minVal);
		if (roots[0]->value != minVal) return;
		FNode<T>* node = extractMin();
		if(node) delete node;
	}
	template<typename T>
	void FibonacciHeap<T>::clearNode(FNode<T>* node)
	{
		if (!node) return;
		clearNode(node->right);
		if(node->child && node->child->left)
			node->child->left->right = nullptr;
		clearNode(node->child);
		node->parent = nullptr;
		node->left = nullptr;
		node->right = nullptr;
		delete node;
	}
	template<typename T>
	FibonacciHeap<T>::~FibonacciHeap()
	{
		while (roots.size() > 0)
		{
			clearNode(roots[0]);
			roots.erase(roots.begin());
		}
	}
}