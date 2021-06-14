#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include "book.h"
#include "binary_tree.h"

using namespace bt;
namespace obt//optimal binary tree
{
	template<typename T>
	class OptimalTree
	{
	private:
		std::vector<std::vector<int>> tableE;
        std::vector<std::vector<int>> tableW;
		std::vector<std::vector<int>> tableRoot;
        std::vector<T> values;
		std::vector<int> probabilitiesP;
        std::vector<int> probabilitiesQ;
        std::size_t size;
        void makeOptimal();//makes optimal binary tree
        template<typename U>
        std::stringstream tableToStream(const std::vector<std::vector<U>>& table);//translates table to sstream
        std::size_t countMaxLength();//returns max string length of items in tables
        template<typename U>
        std::size_t countItemLength(const std::vector<std::vector<U>>& table);//returns max string length of items in the table
        template<typename U>
        std::string addEmpty(U value, std::size_t max);//returns empty strings
        bool isCorrect(const std::vector<T>& values, const std::vector<int>& probabilitiesP,
            const std::vector<int>& probabilitiesQ);//returns true if data is correct
        void addNodesToTree(std::size_t i, std::size_t j);//adds nodes to tree

        BinaryTree<T> bTree;
	public:
		OptimalTree(const std::vector<T>& values, const std::vector<int>& probabilitiesP,
            const std::vector<int>& probabilitiesQ);
		std::stringstream getCostTable();//returns cost table in sstream
        std::stringstream getRootTable();//returns root table in sstream
        Node<T>* search(T value);//returns the node with value
        void print();//writes tree to console
	};

}
namespace obt
{
    template<typename T>
    Node<T>* OptimalTree<T>::search(T value)
    {
        return bTree.search(value);
    }
    template<typename T>
    void OptimalTree<T>::print()
    {
        bTree.print();
    }
    template<typename T>
    void OptimalTree<T>::addNodesToTree(std::size_t i, std::size_t j)
    {
        if (j < i) return;
        bTree.insert(values[tableRoot[i][j]]);
        addNodesToTree(i, tableRoot[i][j] - 1);
        addNodesToTree(tableRoot[i][j] + 1, j);
    }
    template<typename T>
    bool OptimalTree<T>::isCorrect(const std::vector<T>& values, const std::vector<int>& probabilitiesP,
        const std::vector<int>& probabilitiesQ)
    {
        if (values.size() != probabilitiesP.size()) return false;
        if (values.size() + 1 != probabilitiesQ.size()) return false;
        int one = 0;
        for (auto item : probabilitiesP) one += item;
        for (auto item : probabilitiesQ) one += item;
        if (one != 100) return false;
        return true;
    }
    template<typename T>
    OptimalTree<T>::OptimalTree(const std::vector<T>& values, const std::vector<int>& probabilitiesP,
        const std::vector<int>& probabilitiesQ)
        :values{ values }, probabilitiesP{probabilitiesP}, 
        probabilitiesQ{ probabilitiesQ }, size(0)
    {
        if (isCorrect(values, probabilitiesP, probabilitiesQ))
        {
            size = probabilitiesP.size();
            this->probabilitiesP.insert(this->probabilitiesP.begin(), 0);
            this->values.insert(this->values.begin(), T());
            tableE = std::vector<std::vector<int>>(size + 2,
                std::vector<int>(size + 1));
            tableW = tableE;
            tableRoot = std::vector<std::vector<int>>(size + 1,
                std::vector<int>(size + 1));
            makeOptimal();
            addNodesToTree(1, size);
        }
        else std::cout << "\nData are incorrect!" << std::endl;
    }
    template<typename T>
    void OptimalTree<T>::makeOptimal() 
    {
        for (std::size_t i = 1; i <= size + 1; i++)
        {
            tableE[i][i - 1] = probabilitiesQ[i - 1];
            tableW[i][i - 1] = probabilitiesQ[i - 1];
        }
        for (std::size_t l = 1; l <= size + 1; l++)
        {
            for (std::size_t i = 1; i <= size - l + 1; i++)
            {
                auto j = i + l - 1;
                tableE[i][j] = INT_MAX;
                tableW[i][j] = tableW[i][j - 1]
                    + probabilitiesP[j] + probabilitiesQ[j];
                for (auto r = i; r <= j; r++)
                {
                    auto t = tableE[i][r - 1] + tableE[r + 1][j] + tableW[i][j];
                    if (t < tableE[i][j])
                    {
                        tableE[i][j] = t;
                        tableRoot[i][j] = r;
                    }
                }
            }
        }
    }

    template<typename T> 
    std::stringstream OptimalTree<T>::getCostTable()
    {
        return tableToStream(tableE);
    }
    template<typename T>
    std::stringstream OptimalTree<T>::getRootTable()
    {
        return tableToStream(tableRoot);
    }
    template<typename T>
    template<typename U>
    std::size_t OptimalTree<T>::countItemLength(const std::vector<std::vector<U>>& table)
    {
        std::size_t max = 0;
        for (std::size_t i = 0; i < table.size(); i++)
        {
            for (std::size_t j = 0; j < table[i].size(); j++)
            {
                auto size = std::to_string(table[i][j]).size();
                if (size > max) max = size;
            }
        }
        return max;
    }
    template<typename T>
    std::size_t OptimalTree<T>::countMaxLength()
    {
        std::size_t max = 
            countItemLength(tableRoot) > countItemLength(tableE)
            ? countItemLength(tableRoot): countItemLength(tableE);
        
        return max;
    }
    template<typename T>
    template<typename U>
    std::string OptimalTree<T>::addEmpty(U value, std::size_t max)
    {
        std::string res = " ";
        for (std::size_t i = 0; i < max - std::to_string(value).size(); i++)
            res += " ";
        return res;
        
    }
    template<typename T>
    template<typename U>
    std::stringstream OptimalTree<T>::tableToStream(const std::vector<std::vector<U>>& table)
    {
        std::stringstream out;
        auto size = countMaxLength();
        for (std::size_t i = 0; i < table.size(); i++)
        {
            for (std::size_t j = 0; j < table[i].size(); j++)
            {
                out << table[i][j];
                out << addEmpty(table[i][j], size);
            }
            out << std::endl;
        }
        return out;
    }
}