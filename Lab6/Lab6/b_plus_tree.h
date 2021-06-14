#pragma once
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
namespace bpt//B+ tree
{
    template<typename T>
    class Node 
    {
    public:
        bool isLeaf;
        std::size_t size;
        std::vector<T> keys;
        std::vector<Node<T>*> children;
        const static std::size_t MAX;
        Node(bool isLeaf = true);
    };
    template<typename T>
    class BPTree 
    {
    private:
        Node<T>* root;

        void insertInternal(T value, Node<T>* current, Node<T>* child);//edits tree after inserting
        Node<T>* findParent(Node<T>* current, Node<T>* child);//returns parent of child
        void printNode(Node<T>* node);//writes node and children to console
    public:
        BPTree();
        Node<T>* search(T value);//returns node with one of key = value
        void insert(T value);//adds value to tree
        void print();//writes tree to console
    };
}
namespace bpt
{
    template<typename T>
    const std::size_t Node<T>::MAX = 3;
    template<typename T>
    Node<T>::Node(bool isLeaf) : keys(std::vector<T>(MAX)),
        children(std::vector<Node<T>*>(MAX + 1, nullptr)), isLeaf(isLeaf), size(0) {}
    template<typename T>
    BPTree<T>::BPTree() : root(nullptr) {}
    template<typename T>
    Node<T>* BPTree<T>::search(T value)
    {
        if (!root) return nullptr;
        else
        {
            Node<T>* current = root;
            while (current->isLeaf == false)
            {
                for (std::size_t i = 0; i < current->size; i++)
                {
                    if (value < current->keys[i])
                    {
                        current = current->children[i];
                        break;
                    }
                    if (i == current->size - 1)
                    {
                        current = current->children[i + 1];
                        break;
                    }
                }
            }
            for (std::size_t i = 0; i < current->size; i++)
            {
                if (current->keys[i] == value)
                {
                    return current;
                }
            }
            return nullptr;
        }
    }
    template<typename T>
    void BPTree<T>::insert(T value)
    {
        if (!root)
        {
            root = new Node<T>();
            root->keys[0] = value;
            root->size = 1;
        }
        else
        {
            Node<T>* current = root;
            Node<T>* parent = nullptr;
            while (current->isLeaf == false)
            {
                parent = current;
                for (std::size_t i = 0; i < current->size; i++)
                {
                    if (value < current->keys[i])
                    {
                        current = current->children[i];
                        break;
                    }
                    if (i == current->size - 1)
                    {
                        current = current->children[i + 1];
                        break;
                    }
                }
            }
            if (current->size < Node<T>::MAX)
            {
                std::size_t i = 0;
                while (value > current->keys[i] && i < current->size)
                    i++;
                for (std::size_t j = current->size; j > i; j--)
                {
                    current->keys[j] = current->keys[j - 1];
                }
                current->keys[i] = value;
                current->size++;
                current->children[current->size] = current->children[current->size - 1];
                current->children[current->size - 1] = nullptr;
            }
            else
            {
                auto newLeaf = new Node<T>();
                std::vector<T> virtualNode(Node<T>::MAX + 1);
                for (std::size_t i = 0; i < Node<T>::MAX; i++)
                {
                    virtualNode[i] = current->keys[i];
                }
                std::size_t i = 0, j = 0;
                while (value > virtualNode[i] && i < Node<T>::MAX)
                    i++;
                for (std::size_t k = Node<T>::MAX; k > i; k--)
                {
                    virtualNode[k] = virtualNode[k - 1];
                }
                virtualNode[i] = value;
                current->size = (Node<T>::MAX + 1) / 2;
                newLeaf->size = Node<T>::MAX + 1 - (Node<T>::MAX + 1) / 2;
                current->children[current->size] = newLeaf;
                newLeaf->children[newLeaf->size] = current->children[Node<T>::MAX];
                current->children[Node<T>::MAX] = nullptr;
                for (i = 0; i < current->size; i++)
                {
                    current->keys[i] = virtualNode[i];
                }
                for (i = 0, j = current->size; i < newLeaf->size; i++, j++)
                {
                    newLeaf->keys[i] = virtualNode[j];
                }
                if (current == root)
                {
                    auto newRoot = new Node<T>(false);
                    newRoot->keys[0] = newLeaf->keys[0];
                    newRoot->children[0] = current;
                    newRoot->children[1] = newLeaf;
                    newRoot->size = 1;
                    root = newRoot;
                }
                else
                {
                    insertInternal(newLeaf->keys[0], parent, newLeaf);
                }
            }
        }
    }
    template<typename T>
    void BPTree<T>::insertInternal(T value, Node<T>* current, Node<T>* child)
    {
        if (current->size < Node<T>::MAX)
        {
            std::size_t i = 0;
            while (value > current->keys[i] && i < current->size)
                i++;
            for (std::size_t j = current->size; j > i; j--)
            {
                current->keys[j] = current->keys[j - 1];
            }
            for (std::size_t j = current->size + 1; j > i + 1; j--)
            {
                current->children[j] = current->children[j - 1];
            }
            current->keys[i] = value;
            current->size++;
            current->children[i + 1] = child;
        }
        else
        {
            auto newInternal = new Node<T>(false);
            std::vector<T> virtualKey(Node<T>::MAX + 1);
            std::vector < Node<T>*> virtualPtr(Node<T>::MAX + 2);
            for (std::size_t i = 0; i < Node<T>::MAX; i++)
            {
                virtualKey[i] = current->keys[i];
            }
            for (std::size_t i = 0; i < Node<T>::MAX + 1; i++)
            {
                virtualPtr[i] = current->children[i];
            }
            std::size_t i = 0, j = 0;
            while (value > virtualKey[i] && i < Node<T>::MAX)
                i++;
            for (std::size_t j = Node<T>::MAX; j > i; j--)
            {
                virtualKey[j] = virtualKey[j - 1];
            }
            virtualKey[i] = value;
            for (std::size_t j = Node<T>::MAX + 1; j > i + 1; j--)
            {
                virtualPtr[j] = virtualPtr[j - 1];
            }
            virtualPtr[i + 1] = child;
            current->size = (Node<T>::MAX + 1) / 2;
            newInternal->size = Node<T>::MAX - (Node<T>::MAX + 1) / 2;
            for (i = 0, j = current->size + 1; i < newInternal->size; i++, j++)
            {
                newInternal->keys[i] = virtualKey[j];
            }
            for (i = 0, j = current->size + 1; i < newInternal->size + 1; i++, j++)
            {
                newInternal->children[i] = virtualPtr[j];
            }
            if (current == root)
            {
                auto newRoot = new Node<T>(false);
                newRoot->keys[0] = current->keys[current->size];
                newRoot->children[0] = current;
                newRoot->children[1] = newInternal;
                newRoot->size = 1;
                root = newRoot;
            }
            else
            {
                insertInternal(current->keys[current->size],
                    findParent(root, current), newInternal);
            }
        }
    }
    template<typename T>
    Node<T>* BPTree<T>::findParent(Node<T>* cursor, Node<T>* child)
    {
        Node<T>* parent = nullptr;
        if (cursor->isLeaf || (cursor->children[0])->isLeaf)
        {
            return nullptr;
        }
        for (std::size_t i = 0; i < cursor->size + 1; i++)
        {
            if (cursor->children[i] == child)
            {
                parent = cursor;
                return parent;
            }
            else {
                parent = findParent(cursor->children[i], child);
                if (parent) return parent;
            }
        }
        return parent;
    }
    template<typename T>
    void BPTree<T>::printNode(Node<T>* current)
    {
        if (current)
        {
            for (std::size_t i = 0; i < current->size; i++)
            {
                std::cout << current->keys[i] << " ";
            }
            if (current->isLeaf == false)
            {
                std::cout << "{";
                for (std::size_t i = 0; i < current->size + 1; i++)
                {
                    printNode(current->children[i]);
                    if(i != current->size) std::cout << ", ";
                }
                std::cout << "}";
            }  
        }
    }
    template<typename T>
    void BPTree<T>::print()
    {
        std::cout << std::endl;
        printNode(root);
        std::cout << std::endl;
    }
}