#include <iostream>
#include <conio.h>
#include "book.h"
#include "fibonacci_heap.h"

using namespace fh;
void addMenu(FibonacciHeap<Event>& heap)
{
    while (true)
    {
        std::string line = "0";
        std::cout << "\nEnter name of Event to add Event to heap "
            << "or enter 0 to exit: ";
        std::cin >> line;
        if (line == "0") return;
        heap.insert(Event(line));
        std::cout << "\n" << line << " was added!" << std::endl;
        return;
    }
}
void removeMenu(FibonacciHeap<Event>& heap)
{
    while (true)
    {
        std::string line = "0";
        std::cout << "\nEnter name of Event to remove Event from heap "
            << "or enter 0 to exit: ";
        std::cin >> line;
        if (line == "0") return;
        heap.remove(Event(line));
        std::cout << "\nEvent was removed or not" << std::endl;
        return;
    }
}
void addeventsToHeap(FibonacciHeap<Event>& heap, std::string path)
{
    Book map = readdays(path);
    for (std::size_t i = 0; i < map.days.size(); i++)
    {
        for (std::size_t j = 0; j < map.days[i].events.size(); j++)
        {
            heap.insert(map.days[i].events[j]);
        }
    }
    std::cout << "\nevents was read from file!" << std::endl;
}
void menu()
{
    FibonacciHeap<Event> heap;
    std::string path = "input.txt";
    while (true)
    {
        std::cout << "\nMenu:\n1)Add events from file '" << path << "' to heap.\n" <<
            "2)Add Event to heap.\n3)Remove Event from heap.\n" <<
            "4)Print heap.\n0)Back." << std::endl;
        switch (_getch())
        {
        case '0': return;
            break;
        case '1': addeventsToHeap(heap, path);
            break;
        case '2': addMenu(heap);
            break;
        case '3': removeMenu(heap);
            break;
        case '4': heap.print();
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
