#pragma once
#include "my_override_functions_and_operators.h"
#include "my_paths_between_vertices.h"
#include <ctime>

using namespace ofo;
using namespace pbv;
/**
* Namespace for GraphMatrix
*/
namespace gm//graph matrix
{
    /**
    * \brief Edge in graph (GraphMatrix)
    * 
    * This struct is used to preserve the value of graph edges
    */
    template<typename T>
    struct Edge
    {
        bool contiguity;/**< Reports whether the vertices at the ends of the edge are contiguity*/
        T value; /**< Eigenvalue, which is stored in the edge*/
        /**
        * \brief Default constructor
        * 
        * Creates empty edge between non-contiguity vertices
        */
        Edge();
        /**
        * \brief Parameterized constructor
        * 
        * Creates edge between contiguity vertices. Edge retains the value
        */
        Edge(bool contiguity, T value);
    };  
     /**
     * \brief Class for representing a graph in the form of a adjacency matrix
     * 
     * See [Adjacency Matrix](https://en.wikipedia.org/wiki/Adjacency_matrix "Information about adjacency matrix in Wikipedia")
     * 
     * The edges are stored in 'std::vector<std::vector<Edge<T>>> matrix',
     * and the vertices are stored in 'std::vector<T> vertices'. See Edge
     * 
     * This class also stores information about the number of edges and vertices,
     * the weight of the graph, and information about the orientation of the graph
     * 
     * \see gs::GraphStructure
     */
    template<typename T, typename U>
    class GraphMatrix
    {
    protected:
        std::vector<std::vector<Edge<U>>> matrix;//the two-dimensional array in which the the edges between the vertices are stored, if such an edge exists or the default value is stored in the opposite case
        std::vector<T> vertices;//the one-dimensional array in which the values of vertices are stored
        std::size_t numberOfVertices;
        std::size_t numberOfEdges;
        bool orientation;//if orientation is true then Graph is oriented, else it is no-oriented
        U totalValue;//there is the sum of all values of Edges

        bool isIndex(std::size_t index, bool show = false);//if vectex with index is in graph then return true, else - false
        bool doAddIndex(std::vector<std::size_t>& indexes, std::size_t index);// if index is not in indexes then function adds index to indexes
        void isConnectedRelativeToTheVertex(std::vector<std::size_t>& indexes, std::size_t index);//the function checks whether the graph is connected starting from a given index of vertex
        bool isConnected(std::vector<std::size_t>& indexes);//the function checks whether the graph is connected with respect to all vertices
        std::size_t minDistance(PathsBetweenVertices<U>& paths, bool* isChecked);//find min distance 
        void dijkstra(PathsBetweenVertices<U>& paths);// algorithm for finding the shortest paths between vertices in a graph
        bool connectedGraph(bool show = false);//if the graph isn't connected the function messeges about it
        std::vector<std::vector<std::size_t>> createSet();//creates a set consisting only of connected vertices
        void editSet(std::vector<std::vector<std::size_t>>& set, std::size_t index);//remove index from set
        bool isInIndexes(std::vector<std::size_t> indexes, std::size_t index);//checks if there is an index in the array 
        void createSpanningTree(GraphMatrix<T, U>& spanningTree, std::vector<std::size_t>& indexes, std::size_t index);//algorithm for create spanning tree from graph
        GraphMatrix<T, U> kruskal();//algorithm for create minimum spanning tree from graph
        void createRandomVertices(std::size_t numberOfVertices, const T& maxValue);//adds vertices to new graph
        void createRandomEdges(std::size_t numberOfEdges, const T& maxValue);//adds edges to new graph
        void createGraph(std::size_t numberOfVertices, std::size_t numberOfEdges, bool orientation, const T& maxValue);//create graph with numberOfVertices vertices and numberOfEdges edges
        void deleteEdges(std::size_t index);//when removes vertex need delete its edges
    public:
        /**
        * \brief Default constructor 
        * 
        * Creates a empty no-oriented graph without vertices and edges
        */
        GraphMatrix();
        /**
       * \brief Edited default constructor 
       *
       * Creates a empty no-oriented graph if orientation is false or 
       * creates a empty oriented graph if orientation is true.
       * In two cases graph will be without vertices and edges
       */
        GraphMatrix(bool orientation);
        /**
        * \brief Random Constructor
        * 
        * Creates no-oriented or oriented graph with the specified number of vertices and edges.
        * The value of the vertices and edges will not be greater than the 'maxValue'
        */
        GraphMatrix(std::size_t numberOfVertices, std::size_t numberOfEdges, bool orientation, const T& maxValue);//create random graph
        /**
        * \brief Destructor
        *
        * Clears all arrays in this class
        */
        ~GraphMatrix();
        /**
        * \brief Adding the vertex to graph
        * 
        * Adds new vertex with value to the end of 'vertices'.
        * 
        * Adds one column and one row to the 'matrix'
        * 
        * Index of vertex will be equal to 'numberOfVertices' 
        * and 'numberOfVertices' will increase by one.
        * 
        * \param value that be stored in the new vertex
        * \param show can will be true to show message of the result of the function call
        */
        void addVertex(const T& value, bool show = false);
        /**
        * \brief Adding the edge to graph
        * 
        * If the graph has vertices with indexes beginIndex and endIndex then 
        * creates new edge with value between these vertices.   
        * If this edge already exists, then nothing will happen
        * 
        * Adds the edge to 'matrix[beginIndex][endIndex]'. 
        * If the graph is no-oriented then also adds the edge to 'matrix[endIndex][beginIndex]'
        * 
        * The 'numberOfEdges' will increase by one
        * 
        * Adds to the 'totalValue' its value
        * \param beginIndex is index of first vertex
        * \param endIndex is index of second vertex
        * \param value that be stored in the new edge
        * \param show can will be true to show message of the result of the function call
        */
        void addEdge(std::size_t beginIndex, std::size_t endIndex, const U& value, bool show = false);
        /**
        * \brief Removing vertex from graph
        * 
        * If the graph has vertex with 'index' then 
        * removes index-elements from 'matrix[i][index]', i = (0, 'numberOfVertices' - 1) 
        * and clears array 'matrix[index]'. 
        * Also subtracts all the values of the edges that pass through 
        * this vertex from the 'totalValue'
        * 
        * Reduces the 'numberOfVertices' by one and reduces the 'numberOfEdges' by number of edges 
        * that pass through this vertex
        * \param index is index of this vertex
        * \param show can will be true to show message of the result of the function call
        */
        void removeVertex(std::size_t index, bool show = false);
        /**
        * \brief Removing edge from graph
        * 
        * If the graph has vertices with indexes 'beginIndex' and 'endIndex' then 
        * makes these vertices not adjacent that is removing an edge from the graph. 
        * If the graph is non-oriented then makes vertices with indexes 
        * 'endIndex' and 'beginIndex' not adjacent, too
        * 
        * Reduces the 'numberOfEdges' by one 
        * and subtracts the value of the edge from the 'totalValue'
        * \param beginIndex is index of first vertex
        * \param endIndex is index of second vertex
        * \param show can will be true to show message of the result of the function call
        */
        void removeEdge(std::size_t beginIndex, std::size_t endIndex, bool show = false);
        /**
        * \return - number of vertices in the graph
        */
        std::size_t getNumberOfVertices();
        /**
        * \return - number of edges in the graph
        */
        std::size_t getNumberOfEdges();
        /**
        * \return - 'totalValue' of the graph
        */
        U getTotalValue();
        /**
        * \param index is index of the vertex
        * \return - value of vertex with 'index' if the graph have it
        * \return - default value if the graph haven't this vertex
        */
        T getVertexValue(std::size_t index);
        /**
        * \param beginIndex is index of first vertex
        * \param endIndex is index of second vertex
        * \return - value of edge between vertices with indexes 'beginIndex' and 'endIndex'
        * if the graph have their
        * \return - default value if the graph haven't this edge
        */
        U getEdgeValue(std::size_t beginIndex, std::size_t endIndex);
        /**
        * \brief This method like function std::to_string
        * 
        * Converts a graph to a string(for example to output to the console)
        * \return - text representation of the graph
        */
        std::string getTextRepresentation();
        /**
        * \brief Checking whether the graph is connected
        * 
        * See [Connectivity of graph]( https://en.wikipedia.org/w/index.php?search=Connectivity+graph+theory&title=Special%3ASearch&fulltext=1&ns0=1 "Graph theory in Wikipedia")
        * \param show can will be true to show message of the result of the function call
        * \return - true if the graph is connected
        * \return - false if the graph isn't connected
        */
        bool checkingTheConnectivity(bool show = false);
        /**
        * \brief Algorithm for traversing graph
        * 
        * See [Depth-first search for graph](https://en.wikipedia.org/wiki/Depth-first_search "Graph theory in Wikipedia")
        * 
        * Indexes are added to the array taking into account the order of traversal of the graph
        * If the graph isn't connected then the function cannot perform a search
        * and array will be empty
        * \param show can will be true to show message of the result of the function call
        * \return - array of indexes of vertices
        */
        std::vector<std::size_t> depthFirstSearch(bool show = false);
        /**
        * \brief Finding the smallest path
        * 
        * Finds the path from 'beginIndex' to 'endIndex'. Uses dijkstra algorithm
        * 
        * If the graph isn't connected then the function cannot find the path
        * 
        * \param beginIndex is index of first vertex
        * \param endIndex is index of second vertex
        * \param show can will be true to show message of the result of the function call
        * \return - the smallest path between two vertices
        * \return - default value if the graph haven't these vertices or graph isn't connected
        */
        U getPathBetweenTwoVertices(std::size_t beginIndex, std::size_t endIndex, bool show = false);
        /**
        * \brief Finding the smallest paths
        *
        * Finds the paths from 'beginIndex' to everyone else. Uses dijkstra algorithm
        *
        * If the graph isn't connected then the function cannot find the paths
        *
        * \param beginIndex is index of the vertex
        * \param show can will be true to show message of the result of the function call
        * \return - 'struct pbv::PathsBetweenVertices' that has the smallest paths between vertices
        * \return - empty 'struct pbv::PathsBetweenVertices' if the graph haven't this vertex or graph isn't connected
        */
        PathsBetweenVertices<U> getPathsFromTheVertexToEveryoneElse(std::size_t beginIndex, bool show = false);
        /**
        * \brief Algorithm topological sorting of oriented graph only
        * 
        * The function linearly arranges the vertices of the graph.
        * If graph is non-oriented or isn't connected then array will be empty
        * 
        * See [Topological sorting](https://en.wikipedia.org/wiki/Topological_sorting "Graph theory in Wikipedia")
        * \param show can will be true to show message of the result of the function call
        * \return - array with the result of topological sorting
        */
        std::vector<std::size_t> topologicalSorting(bool show = false);
        /**
        * \brief Creating spanning tree
        * 
        * Creates spannig tree from non-oriented graph only.
        * Uses the Depth-first search algorithm
        * 
        * The resulting graph will have all vertices, but the number of edges may be smaller, 
        * resulting in less weight of the graph
        * 
        * See [Spannig tree](https://en.wikipedia.org/wiki/Spanning_tree "Graph theory in Wikipedia")
        * 
        * In fact, the spanning tree will consist of the path obtained by searching
        * 
        * If graph isn't connected then spanning tree will be empty
        * \param show can will be true to show message of the result of the function call
        * \return - created graph
        */
        GraphMatrix<T,U> getSpanningTree(bool show = false);
        /**
        * \brief Creating the smallest spanning tree
        *
        * Creates minimum spanning tree from non-oriented graph only. 
        * Uses Kruskal's algorithm
        * 
        * The resulting graph will have all vertices, but the number of edges may be smaller,
        * resulting in the smallest weight of the graph
        * 
        * See [Kruskal's algorithm](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm "Graph theory in Wikipedia")
        *
        * If graph isn't connected then spanning tree will be empty
        * \param show can will be true to show message of the result of the function call
        * \return - created graph
        */
        GraphMatrix<T,U> getTheSmallestSpanningTree(bool show = false);
    };
}
namespace gm
{
    //Edge
    template<typename T>
    Edge<T>::Edge() : contiguity(false), value(T()) {}
    template<typename T>
    Edge<T>::Edge(bool contiguity, T value) : contiguity(contiguity), value(value) {}   
    //GraphMatrix
    //private
    template<typename T,typename U>
    bool GraphMatrix<T, U>:: isIndex(std::size_t index, bool show)
    {
        if (index >= numberOfVertices)
        {
            if(show) std::cout << "\nVertex with index: " << index << " isn't in Graph!" << std::endl;
            return false;
        }

        return true;
    }
    template<typename T, typename U>
    bool GraphMatrix<T, U>::doAddIndex(std::vector<std::size_t>& indexes, std::size_t index)
    {
        for (std::size_t i = 0; i < indexes.size(); i++)
        {
            if (indexes[i] == index) return false;
        }
        indexes.push_back(index);

        return true;
    }
    template<typename T, typename U>
    void GraphMatrix<T, U>:: isConnectedRelativeToTheVertex(std::vector<std::size_t>& indexes, std::size_t index)
    {
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            if (matrix[index][i].contiguity)
            {
                doAddIndex(indexes, index);
                if (index == i) continue;
                if (doAddIndex(indexes, i))
                {
                    isConnectedRelativeToTheVertex(indexes, i);
                }
            }
        }
    }
    template<typename T, typename U>
    bool GraphMatrix<T, U>::isConnected(std::vector<std::size_t>& indexes)
    {
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            isConnectedRelativeToTheVertex(indexes, i);
            if (indexes.size() == numberOfVertices)
            {
                return true;
            }
            indexes.clear();
        }

        return false;
    }
    template<typename T, typename U>
    std::size_t GraphMatrix<T, U>::minDistance(PathsBetweenVertices<U>& paths, bool* isChecked)
    {
        U min = U();
        bool max = true;
        std::size_t index = 0;
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            if (!isChecked[i] && !paths.isMax[i] && (max || paths.distance[i] <= min))
            {
                max = false;
                min = paths.distance[i];
                index = i;
            }
        }

        return index;
    }
    template<typename T, typename U>
    void GraphMatrix<T, U>::dijkstra(PathsBetweenVertices<U>& paths)
    {
        bool* isChecked = new bool[numberOfVertices];
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            paths.isMax[i] = true;
            isChecked[i] = false;
        }
        paths.distance[paths.beginIndex] = U();
        paths.isMax[paths.beginIndex] = false;
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            std::size_t index = minDistance(paths, isChecked);
            isChecked[index] = true;
            for (std::size_t j = 0; j < numberOfVertices; j++)
            {
                if (!isChecked[j] && matrix[index][j].contiguity && !paths.isMax[index]
                    && (paths.isMax[j] || (paths.distance[index] + matrix[index][j].value < paths.distance[j])))
                {
                    paths.distance[j] = paths.distance[index] + matrix[index][j].value;
                    paths.isMax[j] = false;
                }
            }
        }
        delete[] isChecked;
    }
    template<typename T, typename U>
    bool GraphMatrix<T, U>::connectedGraph(bool show)
    {
        std::vector<std::size_t> indexes;
        if (!isConnected(indexes))
        {
            if (show) std::cout << "\nThe graph isn't connected!" << std::endl;
            return false;
        }
        return true;
    }
    template<typename T, typename U>
    std::vector<std::vector<std::size_t>> GraphMatrix<T, U>::createSet()
    {
        std::vector<std::vector<std::size_t>> set(numberOfVertices);
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            for (std::size_t j = 0; j < numberOfVertices; j++)
            {
                if (matrix[i][j].contiguity) set[j].push_back(i);
            }
        }
        return set;
    }
    template<typename T, typename U>
    void GraphMatrix<T, U>::editSet(std::vector<std::vector<std::size_t>>& set, std::size_t index)
    {
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            for (std::size_t j = 0; j < set[i].size(); j++)
            {
                if (set[i][j] == index)
                {
                    set[i].erase(set[i].begin() + j);
                    j--;
                }
            }
        }
    }
    template<typename T, typename U>
    bool GraphMatrix<T, U>::isInIndexes(std::vector<std::size_t> indexes, std::size_t index)
    {
        for (std::size_t i = 0; i < indexes.size(); i++)
        {
            if (indexes[i] == index) return true;
        }
        return false;
    }
    template<typename T, typename U>
    void GraphMatrix<T, U>::createSpanningTree(GraphMatrix<T, U>& spanningTree, std::vector<std::size_t>& indexes, std::size_t index)
    {
        if (indexes.size() == numberOfVertices) return;
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            if (matrix[index][i].contiguity)
            {
                doAddIndex(indexes, index);
                if (index == i) continue;
                if (doAddIndex(indexes, i))
                {
                    spanningTree.addEdge(index, i, matrix[index][i].value, false);
                    createSpanningTree(spanningTree, indexes, i);
                }
            }
        }
    }
    template<typename T, typename U>
    GraphMatrix<T, U> GraphMatrix<T, U>::kruskal()
    {
        GraphMatrix<T> spanningTree(false);
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            spanningTree.addVertex(vertices[i]);
        }
        std::vector<std::size_t> belongs(numberOfVertices);
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            belongs[i] = i;
        }
        std::size_t firstIndex;
        std::size_t secondIndex;
        for (std::size_t vertexIndex = 1; vertexIndex < numberOfVertices; vertexIndex++)
        {
            T min = T();
            bool isMax = true;
            for (std::size_t i = 0; i < numberOfVertices; i++)
            {
                for (std::size_t j = 0; j < numberOfVertices; j++)
                {
                    if (matrix[i][j].contiguity && (isMax || min > matrix[i][j].value)
                        && (belongs[i] != belongs[j]))
                    {
                        min = matrix[i][j].value;
                        isMax = false;
                        firstIndex = i;
                        secondIndex = j;
                    }
                }
            }
            if (belongs[firstIndex] != belongs[secondIndex])
            {
                spanningTree.addEdge(firstIndex, secondIndex, min);
                std::size_t tempIndex = belongs[secondIndex];
                belongs[secondIndex] = belongs[firstIndex];
                for (std::size_t i = 0; i < numberOfVertices; i++)
                {
                    if (belongs[i] == tempIndex)
                    {
                        belongs[i] = belongs[firstIndex];
                    }
                }
            }
        }

        return spanningTree;
    }
    template<typename T, typename U>
    void GraphMatrix<T, U>::createRandomVertices(std::size_t numberOfVertices, const T& maxValue)
    {
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            addVertex(randomValue(maxValue));
        }
    }
    template<typename T, typename U>
    void GraphMatrix<T, U>::createRandomEdges(std::size_t numberOfEdges, const T& maxValue)
    {
        if (numberOfEdges <= (numberOfVertices * (numberOfVertices + 1)) / 2)
        {
            while (this->numberOfEdges < numberOfEdges)
            {
                std::size_t i = rand() % numberOfVertices, j = rand() % numberOfVertices;
                if (!matrix[i][j].contiguity)
                {
                    addEdge(i, j, randomValue(maxValue));
                }
            }  
            return;
        }              
        std::cout << "\nThere are too many edges!" << std::endl;
    }
    template<typename T, typename U>
    void GraphMatrix<T, U>::createGraph(std::size_t numberOfVertices, std::size_t numberOfEdges, bool orientation, const T& maxValue)
    {
        srand(unsigned(time(0)));
        this->orientation = orientation;
        this->numberOfVertices = 0;
        this->numberOfEdges = 0;
        totalValue = T();
        createRandomVertices(numberOfVertices, maxValue);
        createRandomEdges(numberOfEdges, maxValue);
    }
    template<typename T, typename U>
    void GraphMatrix<T, U>::deleteEdges(std::size_t index)
    {
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            if (matrix[i][index].contiguity)
            {
                numberOfEdges--;
                totalValue = totalValue - matrix[i][index].value;
                matrix[i][index].contiguity = false;
                if (!orientation) matrix[index][i].contiguity = false;
            }
           
        }
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            if (matrix[index][i].contiguity)
            {
                numberOfEdges--;
                totalValue = totalValue - matrix[index][i].value;
                matrix[index][i].contiguity = false;
            }
        }
    }
    //public
    template<typename T, typename U>
    GraphMatrix<T, U>::GraphMatrix()
    {
        numberOfVertices = 0;
        numberOfEdges = 0;
        orientation = false;
        totalValue = U();
    }
    template<typename T, typename U>
    GraphMatrix<T, U>::GraphMatrix(bool orientation)
    {
        numberOfVertices = 0;
        numberOfEdges = 0;
        this->orientation = orientation;
        totalValue = U();
    }
    template<typename T, typename U>
    GraphMatrix<T, U>::GraphMatrix(std::size_t numberOfVertices, std::size_t numberOfEdges, bool orientation, const T& maxValue)
    {
        createGraph(numberOfVertices, numberOfEdges, orientation, maxValue);
    }
    template<typename T, typename U>
    GraphMatrix<T, U>::~GraphMatrix()
    {
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            matrix[i].clear();
        }
        matrix.clear();
        vertices.clear();
        numberOfVertices = 0;
        numberOfEdges = 0;
        orientation = false;
        totalValue = U();
    }
    template<typename T, typename U>
    void GraphMatrix<T, U>::addVertex(const T& value, bool show)
    {
        vertices.push_back(value);
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            matrix[i].push_back(Edge<U>());
        }
        numberOfVertices++;
        std::vector<Edge<U>> newLine(numberOfVertices, Edge<U>());
        matrix.push_back(newLine);
        if (show) std::cout << "\nThe vertex is added!" << std::endl;
    }
    template<typename T, typename U>
    void GraphMatrix<T, U>::addEdge(std::size_t beginIndex, std::size_t endIndex, const U& value, bool show)
    {
        if (!isIndex(beginIndex, show) || !isIndex(endIndex, show)) return;
        if (matrix[beginIndex][endIndex].contiguity)
        {
            if (show) std::cout << "\nThe edge already exists between the vertices!" << std::endl;
            return;
        }
        Edge<U> node = Edge<U>(true, value);
        matrix[beginIndex][endIndex] = node;
        if (!orientation) matrix[endIndex][beginIndex] = node;
        numberOfEdges++;
        totalValue = totalValue + value;
        if (show) std::cout << "\nThe edge added!" << std::endl;
    }
    template<typename T, typename U>
    void GraphMatrix<T, U>::removeVertex(std::size_t index, bool show)
    {
        if (!isIndex(index)) return;
        deleteEdges(index);
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            matrix[i].erase(matrix[i].begin() + index);
        }
        matrix.erase(matrix.begin() + index);
        numberOfVertices--;
        if (show) std::cout << "\nThe vertex with index " << index << " was removed!" << std::endl;
    }
    template<typename T, typename U>
    void GraphMatrix<T, U>::removeEdge(std::size_t beginIndex, std::size_t endIndex, bool show)
    {
        if (!isIndex(beginIndex) || !isIndex(endIndex)) return;
        if (matrix[beginIndex][endIndex].contiguity)
        {
            matrix[beginIndex][endIndex].contiguity = false;
            numberOfEdges--;
            totalValue = totalValue - matrix[beginIndex][endIndex].value;
            if (!orientation) matrix[endIndex][beginIndex].contiguity = false;
            if (show) std::cout << "\nThe edge between vertices "
                << beginIndex << " and " << endIndex
                << " was removed!" << std::endl;
        }
        else if (show) std::cout << "\nThere isn't the edge between vertices "
            << beginIndex << " and " << endIndex << "!" << std::endl;
    }
    template<typename T, typename U>
    std::size_t GraphMatrix<T, U>::getNumberOfVertices()
    {
        return numberOfVertices;
    }
    template<typename T, typename U>
    std::size_t GraphMatrix<T, U>::getNumberOfEdges()
    {
        return numberOfEdges;
    }
    template<typename T, typename U>
    U GraphMatrix<T, U>::getTotalValue()
    {
        return totalValue;
    }
    template<typename T, typename U>
    T GraphMatrix<T, U>::getVertexValue(std::size_t index)
    {
        if (!isIndex(index)) return T();
        return vertices[index];
    }
    template<typename T, typename U>
    U GraphMatrix<T, U>::getEdgeValue(std::size_t beginIndex, std::size_t endIndex)
    {
        if (!isIndex(beginIndex) || !isIndex(endIndex)) return T();
        return matrix[beginIndex][endIndex].value;
    }
    template<typename T, typename U>
    std::string GraphMatrix<T, U>::getTextRepresentation()
    {
        std::string result = "";
        if (numberOfVertices == 0)
        {
            return "\nThe graph is empty!\n";
        }
        result += "\nGraph:\n";
        result += "\nNumber of vertices: " + toTheString(numberOfVertices) + "\n";
        result += "Number of edges: " + toTheString(numberOfEdges) + "\n";
        result += "Total value: {" + toTheString(totalValue) + "}\n\n";
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            result += "| ";
            for (std::size_t j = 0; j < numberOfVertices; j++)
            {
                if (matrix[i][j].contiguity) result += "1 ";
                else result += "0 ";
            }
            result += "|\n";
        }
        result += "\nVertices:\n";
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            result += toTheString(i) + ")value: {" + toTheString(vertices[i]) + "}.\n";
        }
        result += "\n";

        return result;
    }
    template<typename T, typename U>
    bool GraphMatrix<T, U>::checkingTheConnectivity(bool show)
    {
        return connectedGraph(show);
    }
    template<typename T, typename U>
    std::vector<std::size_t> GraphMatrix<T, U>::depthFirstSearch(bool show)
    {
        std::vector<std::size_t> indexes;
        if (isConnected(indexes))
        {
            if (show) std::cout << "\nSearch is finished!" << std::endl;
        }
        else
        {
            if (show) std::cout << "\nThe graph isn't connected!" << std::endl;
            indexes.clear();
        }
        return indexes;
    }
    template<typename T, typename U>
    U GraphMatrix<T, U>::getPathBetweenTwoVertices(std::size_t beginIndex, std::size_t endIndex, bool show)
    {
        if (!connectedGraph(show)) return T();
        T result = T();
        PathsBetweenVertices<T> paths(numberOfVertices, beginIndex);
        dijkstra(paths);
        if (paths.isMax[endIndex])
        {
            if (show) std::cout << "\nThe graph is poorly oriented so it cannot be reached from " << beginIndex
                << " to " << endIndex << "." << std::endl;
        }
        else
        {
            result = paths.distance[endIndex];
            if (show) std::cout << "\nThe smallest distance from " << beginIndex
                << " to " << endIndex << " was found!" << std::endl;
        }

        return result;
    }
    template<typename T, typename U>
    PathsBetweenVertices<U> GraphMatrix<T, U>::getPathsFromTheVertexToEveryoneElse(std::size_t beginIndex, bool show)
    {
        if (!connectedGraph(show)) return PathsBetweenVertices<U>();
        PathsBetweenVertices<U> paths(numberOfVertices, beginIndex);
        dijkstra(paths);
        if (show) std::cout << "\nThe smallest distance from " << beginIndex
            << " to to everyone else was found!" << std::endl;

        return paths;
    }
    template<typename T, typename U>
    std::vector<std::size_t> GraphMatrix<T, U>::topologicalSorting(bool show)
    {
        std::vector<std::size_t> indexes;
        if (!orientation)
        {
            if (show) std::cout << "\nTopological sorting for directed graph only" << std::endl;
            return indexes;
        }
        if (!connectedGraph(show)) return indexes;
        std::vector<std::vector<std::size_t>> set = createSet();
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            if ((set[i].size() == 0) && !isInIndexes(indexes, i))
            {
                indexes.push_back(i);
                editSet(set, i);
                i = -1;
            }
        }
        if (indexes.size() != numberOfVertices)
        {
            if (show) std::cout << "\nThe graph has a cycle!" << std::endl;
            indexes.clear();
        }
        else if (show) std::cout << "\nTopological sorting is finished!" << std::endl;
        return indexes;
    }
    template<typename T, typename U>
    GraphMatrix<T, U> GraphMatrix<T, U>::getSpanningTree(bool show)
    {
        if (orientation)
        {
            if (show) std::cout << "\nSpanning tree for undirected graph only" << std::endl;
            return GraphMatrix();
        }
        GraphMatrix<T> spanningTree(false);
        for (std::size_t i = 0; i < numberOfVertices; i++)
        {
            spanningTree.addVertex(vertices[i], false);
        }
        std::vector<std::size_t> indexes;
        createSpanningTree(spanningTree, indexes, 0);
        if (indexes.size() != numberOfVertices)
        {
            if (show) std::cout << "\nThe graph isn't connected!" << std::endl;
            return GraphMatrix();
        }
        if (show) std::cout << "\nThe spanning tree is created!" << std::endl;       

        return spanningTree;
    }
    template<typename T, typename U>
    GraphMatrix<T,U> GraphMatrix<T,U>::getTheSmallestSpanningTree(bool show)
    {
        if (orientation)
        {
            if (show) std::cout << "\nSpanning tree for undirected graph only" << std::endl;
            return GraphMatrix<T>();
        }
        if (!connectedGraph(show)) return GraphMatrix<T>();
        GraphMatrix<T> spanningTree = kruskal();
        if (show) std::cout << "\nThe smallest spanning tree is created!" << std::endl;

        return spanningTree;
    }   
}