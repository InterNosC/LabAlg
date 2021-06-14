#include <iostream>
#include <conio.h>
#include "johnsons_algorithm.h"

using namespace wm;
using namespace ja;

void addMenu(Graph<Event, int>& graph)
{
    while (true)
    {
        std::string line = "0";
        std::cout << "\nEnter name of Event to add Event to graph "
            << "or enter 0 to exit: ";
        std::cin >> line;
        if (line == "0") return;
        graph.addVertex(Event(line));
        std::cout << "\n" << line << " was added!" << std::endl;
        return;
    }
}
void addeventsToHeap(Graph<Event, int>& graph, std::string path)
{
    Book map = readdays(path);
    for (std::size_t i = 0; i < map.days.size(); i++)
    {
        for (std::size_t j = 0; j < map.days[i].events.size(); j++)
        {
            graph.addVertex(map.days[i].events[j]);
        }
    }
    for (std::size_t i = 0; i < graph.getNumberOfVertices(); i++)
        for (std::size_t j = 0; j < graph.getNumberOfVertices(); j++)
            if(i != j) graph.addEdge(i, j, (graph.getVertexValue(i).getKey() + graph.getVertexValue(j).getKey())%10000);
    std::cout << "\nevents was read from file!" << std::endl;
}
void menu()
{
    Graph<Event, int> graph(true);
    std::string path = "input.txt";
    while (true)
    {
        std::cout << "\nMenu:\n1)Add events from file '" << path << "' to graph.\n" <<
            "2)Find distances.\n" <<
            "3)Print graph.\n0)Back." << std::endl;
        switch (_getch())
        {
        case '0': return;
            break;
        case '1': addeventsToHeap(graph, path);
            break;
        case '2': graph.printPathes();
            break;
        case '3': std::cout << graph.getTextRepresentation() << std::endl;
            break;
        default:
            std::cout << "\nEnter correct key!" << std::endl;
            break;
        }
    }
}
int main()
{
    menu();
    return 0;
}