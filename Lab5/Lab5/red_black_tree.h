#pragma once
#include "book.h"
#include <memory>
#include <sstream>
#include <Windows.h>
#include <vector>

namespace rbt//red-black tree
{
	enum class Color
	{
		RED,
		BLACK
	};
	template<typename T>
	class TreeNode
	{
	public:
		T value;
		Color color;
		TreeNode<T>* left;
		TreeNode<T>* right;
        TreeNode<T>* parent;
        std::size_t numberOfParents;
		TreeNode(T value = T(), Color color = Color::BLACK, 
            TreeNode<T>* parent = nullptr, TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr);
        TreeNode(const TreeNode<T>& node);
    };
	template<typename T>
	class RedBlackTree
	{
	private:	
		TreeNode<T>* root;
        std::vector<TreeNode<T>*> roots;
        std::vector<TreeNode<T>*> marksBro;
        std::vector<TreeNode<T>*> marksPar;
		void restoration(TreeNode<T>* node);//edites tree for it will be reb-black tree after inserting
		void leftRotate(TreeNode<T>* node);//rotates a node to left
		void rightRotate(TreeNode<T>* node);//rotates a node to right	
        void printNode(TreeNode<T>* node);//writes a value of node to display
        void removeRestoration(TreeNode<T>* node);//edites tree for it will be reb-black tree after removing
        void transplantNodes(TreeNode<T>* node1, TreeNode<T>* node2);//replaces node1 to node2
        TreeNode<T>* findNode(T value);//finds node by value
        TreeNode<T>* minimum(TreeNode<T>* node);//returns a minimum of tree
        TreeNode<T>* maximum(TreeNode<T>* node);//returns a maximum of tree
        TreeNode<T>* successor(TreeNode<T>* node);//returns the next node in Inorder traversal of tree
        TreeNode<T>* predecessor(TreeNode<T>* node);//returns the prev node in Inorder traversal of tree
        void clearNode(TreeNode<T>* node);//clears the node and all childeren
        void prevRoot(TreeNode<T>* root);
	public:
		RedBlackTree(TreeNode<T>* root = nullptr);
		void insert(T value);//adds a value to tree
        void print();//writes a tree to display
        void remove(T value);//removes a node from tree
        TreeNode<T>* getMin();//returns min
        TreeNode<T>* getMax();//returns max
        TreeNode<T>* search(T value);//returns node by value
        void prev();//moves tree to prev state
        ~RedBlackTree();
    };
    void SetColor(int text, int background);//edits console color
}
namespace rbt
{
    void SetColor(int text, int background)
    {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
    }   
    template<typename T>
    TreeNode<T>::TreeNode(T value, Color color,
        TreeNode<T>* parent, TreeNode<T>* left, TreeNode<T>* right) :
        value{ value }, color{ color }, parent{ parent }, numberOfParents{ 0 }, left{ left }, right{ right }{}
    template<typename T>
    TreeNode<T>::TreeNode(const TreeNode<T>& node) : value{ node.value },
        color{ node.color }, parent{ node.parent }, numberOfParents{ node.numberOfParents },
        left{ node.left }, right{ node.right }{}
    template<typename T>
    RedBlackTree<T>::RedBlackTree(TreeNode<T>* root) : root{ root } 
    {
        roots.push_back(root); 
        marksPar.push_back(root);
        marksBro.push_back(root);
    }
    template<typename T>
    TreeNode<T>* RedBlackTree<T>::minimum(TreeNode<T>* node) 
    {
        if (!node) return nullptr;
        while (node->left) 
        {
            node = node->left;
        }
        return node;
    }
    template<typename T>
    TreeNode<T>* RedBlackTree<T>::maximum(TreeNode<T>* node) 
    {
        if (!node) return nullptr;
        while (node->right)
        {
            node = node->right;
        }
        return node;
    }
    template<typename T>
    TreeNode<T>* RedBlackTree<T>::successor(TreeNode<T>* node) 
    {
        if (node->right) return minimum(node->right);        
        TreeNode<T>* current = node->parent;
        while (current && node == current->right) 
        {
            node = current;
            current = current->parent;
        }
        return current;
    }
    template<typename T>
    TreeNode<T>* RedBlackTree<T>::predecessor(TreeNode<T>* node) 
    {
        if (node->left) return maximum(node->left);        
        TreeNode<T>* current = node->parent;
        while (current&& node == current->left) 
        {
            node = current;
            current = current->parent;
        }

        return current;
    }
    template<typename T>
    void RedBlackTree<T>::clearNode(TreeNode<T>* node)
    {
        if (!node) return;
        if (node->left) clearNode(node->left);
        if (node->right) clearNode(node->right);
        delete node;
    }
    template<typename T>
    RedBlackTree<T>::~RedBlackTree()
    {
        clearNode(root);
        root = nullptr;
    }
    template<typename T>
    void RedBlackTree<T>::prevRoot(TreeNode<T>* root)
    {
        if (!root) return;
        if (root->left)
        {
            root->left->parent = root;
            prevRoot(root->left);
        }
        if (root->right)
        {
            root->right->parent = root;
            prevRoot(root->right);
        }
    }
    template<typename T>
    void RedBlackTree<T>::prev()
    {
        if (roots.size() < 2)
        {
            std::cout << "\nThere isn't any state of tree!" << std::endl;
            return;
        }
        std::cout << "\nPrev state!" << std::endl;
        roots.erase(roots.begin() + roots.size() - 1);
        root = roots[roots.size() - 1];
        prevRoot(root);
        if (marksPar[marksPar.size() - 1]) restoration(marksPar[marksPar.size() - 1]);
        marksPar.erase(marksPar.begin() + marksPar.size() - 1);
        if (marksBro[marksBro.size() - 1]) restoration(marksBro[marksBro.size() - 1]);
        marksBro.erase(marksBro.begin() + marksBro.size() - 1);
    }
    template<typename T>
    void RedBlackTree<T>::insert(T value)
    {
        auto newNode = new TreeNode<T>(value, Color::RED);
        TreeNode<T>* node = nullptr, *nextNode = nullptr;
        TreeNode<T>* current = this->root;
        if (current) roots.push_back(new TreeNode<T>(*current));
        auto nextCurrent = roots[roots.size() - 1];
        while (current) 
        {
            node = current;
            nextNode = nextCurrent;
            if (newNode->value < current->value)
            {
                if (current->right)
                {
                    current->right->parent = nextCurrent;
                    current->right->numberOfParents++;
                }
                if (current->left)
                {
                    nextCurrent->left = new TreeNode<T>(*(current->left));
                    nextCurrent->left->parent = nextCurrent;

                }
                nextCurrent = nextCurrent->left;
                current = current->left;
            }
            else
            {
                if (current->left)
                {
                    current->left->parent = nextCurrent;
                    current->left->numberOfParents++;
                }
                if (current->right) 
                {
                    nextCurrent->right = new TreeNode<T>(*(current->right));
                    nextCurrent->right->parent = nextCurrent;
                }
                nextCurrent = nextCurrent->right;
                current = current->right;
            }
        }
        if (!nextNode)
        {
            roots.push_back(newNode);
            marksBro.push_back(nullptr);
            marksPar.push_back(nullptr);
        }
        else
        {
            if (newNode->value < node->value)
            {
                nextNode->left = newNode;
                marksBro.push_back(node->right);
            }
            else
            {
                nextNode->right = newNode;
                marksBro.push_back(node->left);
            }
            node->color = Color::RED;
            marksPar.push_back(node);
        }
        newNode->parent = nextNode;
        root = roots[roots.size() - 1];
        if (!newNode->parent) 
        {
            newNode->color = Color::BLACK;
            return;
        }
        if (!newNode->parent->parent) return;   
        restoration(newNode);
    }
    template<typename T>
    void RedBlackTree<T>::restoration(TreeNode<T>* node)
    {
        TreeNode<T>* current = nullptr;
        while (node->parent&&node->parent->color == Color::RED)
        {
            if (node->parent == node->parent->parent->right) 
            {
                current = node->parent->parent->left;
                if (current&&current->color == Color::RED)
                {
                    current->color = Color::BLACK;
                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    node = node->parent->parent;
                }
                else 
                {
                    if (node == node->parent->left) 
                    {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    leftRotate(node->parent->parent);
                }
            }
            else 
            {
                current = node->parent->parent->right;
                if (current&&current->color == Color::RED)
                {
                    current->color = Color::BLACK;
                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    node = node->parent->parent;
                }
                else 
                {
                    if (node == node->parent->right) 
                    {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    rightRotate(node->parent->parent);
                }
            }
            if (node == root) break;           
        }
        root->color = Color::BLACK;
    }
    template<typename T>
    void RedBlackTree<T>::leftRotate(TreeNode<T>* node)
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
    void RedBlackTree<T>::rightRotate(TreeNode<T>* node)
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
    void RedBlackTree<T>::removeRestoration(TreeNode<T>* node)
    {
        if (!node) return;
        TreeNode<T>* current;
        while (node != root && node->color == Color::BLACK) 
        {
            if (node == node->parent->left) 
            {
                current = node->parent->right;
                if (current->color == Color::RED)
                {
                    current->color = Color::BLACK;
                    node->parent->color = Color::RED;
                    leftRotate(node->parent);
                    current = node->parent->right;
                }
                if (current->left->color == Color::BLACK && 
                    current->right->color == Color::BLACK) 
                {
                    current->color = Color::RED;
                    node = node->parent;
                }
                else 
                {
                    if (current->right->color == Color::BLACK)
                    {
                        current->left->color = Color::BLACK;
                        current->color = Color::RED;
                        rightRotate(current);
                        current = node->parent->right;
                    }
                    current->color = node->parent->color;
                    node->parent->color = Color::BLACK;
                    current->right->color = Color::BLACK;
                    leftRotate(node->parent);
                    node = root;
                }
            }
            else 
            {
                current = node->parent->left;
                if (current->color == Color::RED)
                {
                    current->color = Color::BLACK;
                    node->parent->color = Color::RED;
                    rightRotate(node->parent);
                    current = node->parent->left;
                }
                if (current->left->color == Color::BLACK && 
                    current->right->color == Color::BLACK) 
                {
                    current->color = Color::RED;
                    node = node->parent;
                }
                else 
                {
                    if (current->left->color == Color::BLACK)
                    {
                        current->right->color = Color::BLACK;
                        current->color = Color::RED;
                        leftRotate(current);
                        current = node->parent->left;
                    }
                    current->color = node->parent->color;
                    node->parent->color = Color::BLACK;
                    current->left->color = Color::BLACK;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        node->color = Color::BLACK;
    }
    template<typename T>
    void RedBlackTree<T>::transplantNodes(TreeNode<T>* node1, TreeNode<T>* node2)
    {
        if (!node1->parent) 
        {
            root = node2;
        }
        else if (node1 == node1->parent->left) 
        {
            node1->parent->left = node2;
        }
        else 
        {
            node1->parent->right = node2;
        }
        if(node2) node2->parent = node1->parent;
    }
    template<typename T>
    TreeNode<T>* RedBlackTree<T>::findNode(T value)
    {
        TreeNode<T>* current = root;
        while (current)
        {
            if (value == current->value)
            {               
                return current;
            }
            else if (value < current->value) current = current->left;
            else current = current->right;
        }
        return nullptr;
    }
    template<typename T>
    void RedBlackTree<T>::remove(T value)
    {     
        TreeNode<T>* node = findNode(value);
        if (!node) 
        {
            std::cout << "\nThere isn't node with value " << value << std::endl;
            return;
        }
        TreeNode<T>* node1, *node2;
        node2 = node;
        Color node2Color = node2->color;
        if (!node->left) 
        {
            node1 = node->right;
            transplantNodes(node, node->right);
        }
        else if (!node->right) 
        {
            node1 = node->left;
            transplantNodes(node, node->left);
        }
        else 
        {
            node2 = minimum(node->right);
            node2Color = node2->color;
            node1 = node2->right;
            if (node2->parent == node) 
            {
                if(node1) node1->parent = node2;
            }
            else 
            {
                transplantNodes(node2, node2->right);
                node2->right = node->right;
                node2->right->parent = node2;
            }
            transplantNodes(node, node2);
            node2->left = node->left;
            node2->left->parent = node2;
            node2->color = node->color;
        }
        delete node;
        if (node2Color == Color::BLACK)
        {
            removeRestoration(node1);
        }
        std::cout << "\nThis node was removed!" << std::endl;
    }
    template<typename T>
    void RedBlackTree<T>::printNode(TreeNode<T>* node)
    {
        if (!node) return;
        if (node->color == Color::RED) SetColor(4, 7);
        else SetColor(0, 7);
        std::cout << node->value;
        SetColor(7, 0);
        std::cout << " ";
        if (node->left || node->right) std::cout << "-> {";
        //if (node->left) std::cout << node->value << ":";
        printNode(node->left);
        if (node->left && node->right) std::cout << ", ";
        //if (node->right) std::cout << node->value << ":";
        printNode(node->right);
        if (node->left || node->right) std::cout << "} ";
    }
    template<typename T>
    void RedBlackTree<T>::print()
    {
        if (!root) std::cout << "\nTree is empty!";
        std::cout << std::endl;
        printNode(root);
        std::cout << std::endl;
    }
    template<typename T>
    TreeNode<T>* RedBlackTree<T>::getMin()
    {
        return minimum(root);
    }
    template<typename T>
    TreeNode<T>* RedBlackTree<T>::getMax()
    {
        return maximum(root);
    }
    template<typename T>
    TreeNode<T>* RedBlackTree<T>::search(T value)
    {
        return findNode(value);
    }
}