#pragma once
#include <iostream>
#include <vector>
#include "book.h"

using namespace wm;

namespace bh//binomial heap
{
	template<typename T>
	class BNode
	{
	public:
		T value;
		BNode* parent;
		BNode* right;
		BNode* child;
		std::size_t degree;
		BNode(T value = T(), BNode* parent = nullptr, BNode* right = nullptr,
			BNode* child = nullptr, std::size_t degree = 0);
	};
	template<typename T>
	class BinomialHeap
	{
	private:
		std::vector<BNode<T>*> roots;

		void mergeLists(std::vector<BNode<T>*>& list);//unions two lists to one
		void mergeNode(BNode<T>* parent, BNode<T>* child);//makes a node 'child' child of node 'parent'
		void printNode(BNode<T>* node);//writes a value of node to display
		void addRoots(BNode<T>* child);//adds a child(and right brothers) to root list 
		void removeRoot(BNode<T>* root);//deletes the root and all children
		BNode<T>* findNode(T value);//finds node by value
		BNode<T>* findInTree(BNode<T>* root, T value);//finds node in tree 
		void makeCorrect(BNode<T>* node);//swaps node and parent if node value < parent value
		void setParent(BNode<T>* node, BNode<T>* parent);//adds parent to node and brothers
		void clearNode(BNode<T>* node);//deletes the node and children and brothers
	public:
		BinomialHeap();
		void merge(BinomialHeap& heap);//unions the heap and that heap
		void insert(T value);//adds the node to heap
		BNode<T>* getMin();//returns the node with minimum value
		BNode<T>* extractMin();//returns and removes from heap the minimum node
		void decrease(T value, T newValue);//decreases value of node
		void remove(T value);//deletes the node by value
		void print();//writes a heap to dispaly
		~BinomialHeap();
	};
	template<typename T>
	T minValue();
	template<>
	Book minValue();
}
namespace bh
{
	template<typename T>
	BinomialHeap<T>::BinomialHeap():roots(std::vector<BNode<T>*>()){}
	template<typename T>
	BNode<T>::BNode(T value, BNode* parent, BNode* right, BNode* child, std::size_t degree)
		:value(value),parent(parent), right(right),child(child),degree(degree) {}
	template<typename T>
	void BinomialHeap<T>::mergeNode(BNode<T>* parent, BNode<T>* child)
	{
		child->right = parent->child;
		parent->child = child;
		child->parent = parent;
		parent->degree++;
	}
	template<typename T>
	void BinomialHeap<T>::merge(BinomialHeap& heap)
	{
		mergeLists(heap.roots);
		for (std::size_t i = 1; i < roots.size(); i++)
		{
			if (i + 1 < roots.size() && roots[i - 1]->degree == roots[i]->degree &&
				roots[i]->degree == roots[i + 1]->degree) i++;
			if (roots[i - 1]->degree == roots[i]->degree)
			{
				if (roots[i - 1]->value < roots[i]->value)
				{
					mergeNode(roots[i - 1], roots[i]);
					roots.erase(roots.begin() + i);	
				}		 
				else
				{
					mergeNode(roots[i], roots[i - 1]);
					roots.erase(roots.begin() + (i - 1));
				}
				i--;
			}
		}
		heap.roots.clear();
	}
	template<typename T>
	void BinomialHeap<T>::mergeLists(std::vector<BNode<T>*>& thelist)
	{
		std::vector<BNode<T>*> newList;
		std::size_t i = 0, j = 0;
		while (i < roots.size() && j < thelist.size())
		{
			if (roots[i]->degree > thelist[j]->degree)
			{
				newList.push_back(thelist[j]);
				j++;
			}
			else
			{
				newList.push_back(roots[i]);
				i++;
			}
		}
		while (j < thelist.size())
		{
			newList.push_back(thelist[j]);
			j++;
		}
		while (i < roots.size())
		{
			newList.push_back(roots[i]);
			i++;
		}
		roots = newList;
	}
	template<typename T>
	void BinomialHeap<T>::insert(T value)
	{
		if (roots.size() == 0)
		{
			roots.push_back(new BNode<T>(value));
			return;
		}
		BinomialHeap<T> heap;
		heap.insert(value);
		merge(heap);
	}
	template<typename T>
	void BinomialHeap<T>::printNode(BNode<T>* node)
	{
		if (!node) return;
		std::cout << node->value << " ";	
		if (node->child) std::cout << "-> {";
		printNode(node->child);
		if (node->child) std::cout << "}";
		if (node->right) std::cout << ", ";
		printNode(node->right);
	}
	template<typename T>
	void BinomialHeap<T>::print()
	{
		if (roots.size() == 0)
		{
			std::cout << "\nEmpty" << std::endl;
			return;
		}
		std::cout << "#";
		for (std::size_t i = 0; i < roots.size(); i++)
		{
			std::cout << "\n|\nV" << std::endl;
			std::cout << "B" << roots[i]->degree << ": ";
			printNode(roots[i]);	
		}
			
		std::cout << std::endl << std::endl;
	}
	template<typename T>
	BNode<T>* BinomialHeap<T>::getMin()
	{
		if (roots.size() == 0) return nullptr;
		BNode<T>* min = roots[0];
		for (std::size_t i = 1; i < roots.size(); i++)
			if (min->value > roots[i]->value) min = roots[i];
		return min;
	}
	template<typename T>
	void BinomialHeap<T>::addRoots(BNode<T>* child)
	{
		if (!child) return;
		addRoots(child->right);
		child->parent = nullptr;
		roots.push_back(child);
		child->right = nullptr;
	}
	template<typename T>
	void BinomialHeap<T>::removeRoot(BNode<T>* root)
	{
		for (std::size_t i = 0; i < roots.size(); i++)
		{
			if (root == roots[i])
			{
				roots.erase(roots.begin() + i);
				return;
			}
		}
	}
	template<typename T>
	BNode<T>* BinomialHeap<T>::extractMin()
	{
		BNode<T>* node = getMin();
		if (!node) return nullptr;
		BinomialHeap<T> heap;
		heap.addRoots(node->child);
		removeRoot(node);
		merge(heap);
		return node;
	}
	template<typename T>
	BNode<T>* BinomialHeap<T>::findInTree(BNode<T>* root, T value)
	{
		if (!root) return nullptr;
		if (root->value == value) return root;
		BNode<T>* right = findInTree(root->right,value);
		if (right) return right;
		if (root->value > value) return nullptr;
		return findInTree(root->child, value);
	}
	template<typename T>
	BNode<T>* BinomialHeap<T>::findNode(T value)
	{
		for (std::size_t i = 0; i < roots.size(); i++)
		{
			if (value >= roots[i]->value)
			{
				BNode<T>* node = findInTree(roots[i], value);
				if (node) return node;
			}
		}
		return nullptr;
	}
	template<typename T>
	void BinomialHeap<T>::setParent(BNode<T>* node, BNode<T>* parent)
	{
		if (!node) return;
		node->parent = parent;
		setParent(node->right, parent);
	}
	template<typename T>
	void BinomialHeap<T>::makeCorrect(BNode<T>* node)
	{
		if (!node || !node->parent || 
			node->value >= node->parent->value) return;
		T value = node->value;
		T pValue = node->parent->value;
		node->value = pValue;
		node->parent->value = value;
		makeCorrect(node->parent);
	}
	template<typename T>
	void BinomialHeap<T>::decrease(T value, T newValue)
	{
		if (newValue > value)
		{
			std::cerr << "Error! The new key is larger than the current one." << std::endl;
			exit(-1);
			return;
		}
		BNode<T>* node = findNode(value);
		if (!node)
		{
			std::cout << "There isn't a node with value " << value << std::endl;
			return;
		}
		node->value = newValue;
		makeCorrect(node);
	}
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
	template<typename T>
	void BinomialHeap<T>::remove(T value)
	{
		decrease(value, minValue<T>());
		BNode<T>* node = extractMin();
		delete node;
	}
	template<typename T>
	void BinomialHeap<T>::clearNode(BNode<T>* node)
	{
		if (!node) return;
		clearNode(node->right);
		clearNode(node->child);
		node->parent = nullptr;
		delete node;
	}
	template<typename T>
	BinomialHeap<T>::~BinomialHeap()
	{
		while(roots.size() > 0)
		{
			clearNode(roots[0]);
			roots.erase(roots.begin());
		}
	}
}