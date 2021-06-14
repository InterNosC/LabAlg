#pragma once
#include "my_graph_matrix.h"
#include "fibonacci_heap.h"
#include "my_pair.h"

using namespace mp;

namespace ja//johnson's algorithm
{

	template<typename T, typename U>
	class Graph: public gm::GraphMatrix<T,U>
	{
	private:
		bool algorithmBellmanFord(std::size_t index, std::vector<U>& path);//algorithm of Bellman Ford
		void algorithmDijkstra(std::size_t index, std::vector<U>& path);//algorithm of Dijkstra
		bool algorithmJohnson(std::size_t index, std::vector<U>& path);//algorithm of Johnson
	public:
		Graph(bool orientation = false);
		void printPathes();
	};
}
namespace ja
{
	template<typename T,typename U>
	Graph<T,U>::Graph(bool orientation):gm::GraphMatrix<T,U>(orientation){}
	template<typename T, typename U>
	bool Graph<T, U>::algorithmBellmanFord(std::size_t index, std::vector<U>& path)
	{
		for (std::size_t i = 0; i < this->numberOfVertices; i++)
			path[i] = fh::maxValue<U>();
		path[index] = U();
		for (std::size_t k = 0; k < this->numberOfVertices - 1; k++)
			for (std::size_t i = 0; i < this->numberOfVertices; i++)
				for (std::size_t j = 0; j < this->numberOfVertices; j++)
					if (this->matrix[i][j].contiguity)
						if (path[j] > path[i] + this->matrix[i][j].value)
							path[j] = path[i] + this->matrix[i][j].value;
		for (std::size_t i = 0; i < this->numberOfVertices; i++)
			for (std::size_t j = 0; j < this->numberOfVertices; j++)
				if (this->matrix[i][j].contiguity)
					if (path[j] > path[i] + this->matrix[i][j].value)
						return false;
		return true;
	}
	template<typename T, typename U>
	void Graph<T, U>::algorithmDijkstra(std::size_t index, std::vector<U>& path)
	{
		for (std::size_t i = 0; i < this->numberOfVertices; i++)
			path[i] = fh::maxValue<U>();
		path[index] = U();
		fh::FibonacciHeap<Pair<U, std::size_t>> heap;
		std::size_t heapSize = 1;
		Pair<U, std::size_t> value1(path[index], index);
		heap.insert(value1);
		while (heapSize != 0)
		{
			auto item = heap.extractMin();
			heapSize--;
			if (!item) break;
			auto vertex = item->value.second;
			for (std::size_t i = 0; i < this->numberOfVertices; i++)
			{
				if (this->matrix[vertex][i].contiguity)
				{
					if (path[i] > path[vertex] + this->matrix[vertex][i].value)
					{
						path[i] = path[vertex] + this->matrix[vertex][i].value;
						Pair<U, std::size_t> value (path[i], i);
						heap.insert(value);
						heapSize++;
					}
				}
			}
		}
	}
	template<typename T, typename U>
	bool Graph<T, U>::algorithmJohnson(std::size_t index, std::vector<U>& path)
	{
		std::vector<U> functionH(this->numberOfVertices);
		if (!algorithmBellmanFord(index, functionH)) return false;
		for (std::size_t i = 0; i < this->numberOfVertices; i++)
			for (std::size_t j = 0; j < this->numberOfVertices; j++)
				if (this->matrix[i][j].contiguity)
					this->matrix[i][j].value += functionH[i] - functionH[j];
		algorithmDijkstra(index, path);
		for (std::size_t i = 0; i < this->numberOfVertices; i++)
		{
			for (std::size_t j = 0; j < this->numberOfVertices; j++)
				if (this->matrix[i][j].contiguity)
					this->matrix[i][j].value += functionH[j] - functionH[i];				
			path[i]+= functionH[index] - functionH[i];
		}
					
		return true;
	}
	template<typename T, typename U>
	void Graph<T, U>::printPathes()
	{
		std::cout << std::endl;
		for (std::size_t index = 0; index < this->numberOfVertices; index++)
		{
			std::vector<U> path(this->numberOfVertices);
			algorithmDijkstra(index, path);
			for (std::size_t i = 0; i < this->numberOfVertices; i++)
			{
				std::cout << "Distance from " << this->vertices[index] << " to "
					<< this->vertices[i] << " is ";
				if (path[i] == fh::maxValue<U>()) std::cout << "-";
				else std::cout << path[i];
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}
}