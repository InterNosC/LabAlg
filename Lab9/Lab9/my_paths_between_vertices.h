#pragma once
#include <iostream>
/**
* Namespace for PathsBetweenVertices
*/
namespace pbv//path between vetices
{
    /**
    * \brief The struct for storing paths
    *
    * Stores paths between vertices in graph (gm::GraphMatrix or gs::GraphStructure) 
    * and prints their to console.
    */
    template<typename T>
    struct PathsBetweenVertices
    {
        T* distance; /**< The array with paths from vertex with 'beginIndex' to all vertices */
        bool* isMax; /**<If isMax[i], i = (0, 'size' - 1) then path from vertex with 'beginIndex' to vertex with 'i' does not exist*/
        std::size_t size;/**<Number of vetices in the graph*/
        std::size_t beginIndex;/**<The index of vertex*/
        /**
        * Default constructor
        */
        PathsBetweenVertices();
        /**
        * \brief The constructor
        * 
        * Creates empty arrays 'distance' and 'isMax' with size = 'size'
        */
        PathsBetweenVertices(std::size_t size, std::size_t beginIndex);
        /**
        * Parameterized constructor
        */
        PathsBetweenVertices(T* distance, bool* isMax, std::size_t size, std::size_t beginIndex);
        /**
        * Move constructor
        */
        PathsBetweenVertices(PathsBetweenVertices&& paths)
            noexcept;
        /**
        * \brief Destructor
        * 
        * Deletes 'distance' and 'isMax'
        */
        ~PathsBetweenVertices();
        /**
        * \brief Printing the paths
        * 
        * Print the distance from vertex with beginIndex to all vertices
        * \param show can will be true to show message of the result of the function call
        */
        void print(bool show = false);
    };
}
namespace pbv
{
    template<typename T>
    PathsBetweenVertices<T>::PathsBetweenVertices() : distance(nullptr), isMax(nullptr), size(0), beginIndex(0) {}
    template<typename T>
    PathsBetweenVertices<T>::PathsBetweenVertices(std::size_t size, std::size_t beginIndex)
    {
        this->size = size;
        this->beginIndex = beginIndex;
        distance = new T[size];
        isMax = new bool[size];
    }
    template<typename T>
    PathsBetweenVertices<T>::PathsBetweenVertices(T* distance, bool* isMax, std::size_t size, std::size_t beginIndex)
        : distance(distance), isMax(isMax), beginIndex(beginIndex), size(size){}
    template<typename T>
    PathsBetweenVertices<T>::PathsBetweenVertices(PathsBetweenVertices&& paths)
        noexcept
    {
        distance = paths.distance;
        paths.distance = nullptr;
        isMax = paths.isMax;
        paths.isMax = nullptr;
        size = paths.size;
        paths.size = 0;
        beginIndex = paths.beginIndex;
        paths.beginIndex = 0;
    }
    template<typename T>
    PathsBetweenVertices<T>::~PathsBetweenVertices()
    {
        if (distance)
        {
            delete[]distance;
            distance = nullptr;
        }
        if (isMax)
        {
            delete[]isMax;
            isMax = nullptr;
        }            
        size = 0;
        beginIndex = 0;
    }
    template<typename T>
    void PathsBetweenVertices<T>::print(bool show)
    {
        if (!distance || !isMax)
        {
            std::cout << "\nThere aren't paths between vertices!" << std::endl;
            return;
        }
        for (std::size_t i = 0; i < size; i++)
        {
            if (isMax[i])
            {
                if (show) std::cout << "\nThe graph is poorly oriented so it cannot be reached from " << beginIndex
                    << " to " << i << "." << std::endl;
            }
            else
            {
                if (show) std::cout << "\nThe smallest distance from " << beginIndex
                    << " to " << i << " = {" << distance[i] << "}." << std::endl;
            }
        }
    }
}