#pragma once
#include <iostream>
#include "book.h"

namespace st//splay tree
{
	template<typename T>
	class TreeNode
	{
	public:
		T value;
		TreeNode<T>* parent;
		TreeNode<T>* left;
		TreeNode<T>* right;
		TreeNode(T value = T(),TreeNode<T>* parent = nullptr, 
			TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr);
	};

	template<typename T>
	class SplayTree
	{
	private:
		TreeNode<T>* root;

		void splay(TreeNode<T>* node);//moves the node to top of tree
        void printNode(TreeNode<T>* node);//writes a value of node to display
        TreeNode<T>* getMax(TreeNode<T>* node);//returns max mode
        TreeNode<T>* getMin(TreeNode<T>* node);//returns min node
        void merge(SplayTree<T>& tree1, SplayTree<T>& tree2);//merges two trees to this tree
        void clearNode(TreeNode<T>* node);//removes the node and children from tree
        void leftRotate(TreeNode<T>* node);//rotates a node to left
        void rightRotate(TreeNode<T>* node);//rotates a node to right
	public:
		SplayTree(TreeNode<T>* root = nullptr);
		TreeNode<T>* search(T value);//returns node by value
		void insert(T value);//adds a value to tree
		void remove(T value);//removes a node from tree
		void print();//writes a tree to display
        ~SplayTree();
	};
}
namespace st
{
    template<typename T>
    TreeNode<T>::TreeNode(T value,TreeNode<T>* parent, 
        TreeNode<T>* left, TreeNode<T>* right) :
        value{ value }, parent{ parent }, left{ left }, right{ right }{}
    template<typename T>
    void SplayTree<T>::leftRotate(TreeNode<T>* node)
    {
        TreeNode<T>* current = node->right;
        node->right = current->left;
        if (current->left) current->left->parent = node;
        current->parent = node->parent;
        if (!node->parent) this->root = current;
        else if (node == node->parent->left) node->parent->left = current;
        else node->parent->right = current;
        current->left = node;
        node->parent = current;
    }
    template<typename T>
    void SplayTree<T>::rightRotate(TreeNode<T>* node)
    {
        TreeNode<T>* current = node->left;
        node->left = current->right;
        if (current->right) current->right->parent = node;       
        current->parent = node->parent;
        if (!node->parent) this->root = current;       
        else if (node == node->parent->right) node->parent->right = current;       
        else node->parent->left = current;        
        current->right = node;
        node->parent = current;
    }
    template<typename T>
    void SplayTree<T>::splay(TreeNode<T>* node)
    {
        if (!node) return;
        while (node->parent) 
        {
            if (!node->parent->parent) 
            {
                if (node == node->parent->left) rightRotate(node->parent);                
                else leftRotate(node->parent);
            }
            else if (node == node->parent->left && 
                node->parent == node->parent->parent->left) 
            {
                rightRotate(node->parent->parent);
                rightRotate(node->parent);
            }
            else if (node == node->parent->right && 
                node->parent == node->parent->parent->right) 
            {
                leftRotate(node->parent->parent);
                leftRotate(node->parent);
            }
            else if (node == node->parent->right && 
                node->parent == node->parent->parent->left) 
            {
                leftRotate(node->parent);
                rightRotate(node->parent);
            }
            else 
            {
                rightRotate(node->parent);
                leftRotate(node->parent);
            }
        }
    }
    template<typename T>
    SplayTree<T>::SplayTree(TreeNode<T>* root): root{root}{}
    template<typename T>
    void SplayTree<T>::printNode(TreeNode<T>* node)
    {
        if (!node) return;
        //if (node->parent) std::cout << node->parent->value << ":";
        std::cout << node->value << " ";
        if (node->left || node->right) std::cout << "-> {";
        printNode(node->left);
        if (node->left && node->right) std::cout << ", ";
        printNode(node->right);
        if (node->left || node->right) std::cout << "} ";
    }
    template<typename T>
    void SplayTree<T>::print()
    {
        if (!root) std::cout << "\nTree is empty!";
        std::cout << std::endl;
        printNode(root);
        std::cout << std::endl;
    }
    template<typename T>
    void SplayTree<T>::insert(T value)
    {
        auto newNode = new TreeNode<T>(value);
        if (!root)
        {
            root = newNode;
            return;
        }
        TreeNode<T>* current = root;
        while (current)
        {
            if (value < current->value)
            {
                if (!current->left)
                {                 
                    current->left = newNode;
                    newNode->parent = current;
                    splay(newNode);
                    return;
                }
                else current = current->left;
            }
            else if (value > current->value)
            {
                if (!current->right)
                {
                    current->right = newNode;
                    newNode->parent = current;
                    splay(newNode);
                    return;
                }
                else current = current->right;
            }
            else
            {
                splay(current);
                return;
            }
        }
    }
    template<typename T>
    void SplayTree<T>::merge(SplayTree<T>& tree1, SplayTree<T>& tree2)
    {
        if (tree1.root)
        {
            tree1.splay(getMax(tree1.root));
            tree1.root->right = tree2.root;
            if (tree2.root) tree2.root->parent = tree1.root;
            this->root = tree1.root;
        }
        else this->root = tree2.root;
        tree1.root = nullptr;
        tree2.root = nullptr;
    }
    template<typename T>
    TreeNode<T>* SplayTree<T>::search(T value)
    {
        TreeNode<T>* res = nullptr;
        TreeNode<T>* current = root,* prev = nullptr;
        while (current)
        {
            prev = current;
            if (value < current->value) current = current->left;
            else if (value > current->value) current = current->right;
            else
            {
                res = current;
                break;
            }
        }
        if (res) splay(res);
        else if (prev) splay(prev);
        return res;
    }
    template<typename T>
    TreeNode<T>* SplayTree<T>::getMax(TreeNode<T>* node)
    {
        if (!node) return nullptr;
        TreeNode<T>* current = node;
        while (current->right) current = current->right;
        return current;
    }
    template<typename T>
    TreeNode<T>* SplayTree<T>::getMin(TreeNode<T>* node)
    {
        if (!node) return nullptr;
        TreeNode<T>* current = node;
        while (current->left) current = current->left;
        return current;
    }
    template<typename T>
    void SplayTree<T>::remove(T value)
    {
        TreeNode<T>* node = search(value);
        if (!node) return;
        this->splay(node);
        TreeNode<T>* leftSub = node->left, *rightSub = node->right;
        if (leftSub)
            leftSub->parent = nullptr;
        if (rightSub)
            rightSub->parent = nullptr;
        SplayTree<T> sub1{ leftSub }, sub2{ rightSub };
        merge(sub1, sub2);
        delete node;
    }
    template<typename T>
    void SplayTree<T>::clearNode(TreeNode<T>* node)
    {
        if (!node) return;
        clearNode(node->left);
        clearNode(node->right);
        delete node;
    }
    template<typename T>
    SplayTree<T>::~SplayTree()
    {
        clearNode(root);
        root = nullptr;
    }   
}