#include <iostream>
#include <conio.h>
#include "splay_tree.h"


using namespace st;
using namespace wm;

void findMenu(SplayTree<Event>& tree)
{
    while (true)
    {
        std::string line = "0";
        std::cout << "\nEnter name of Event to find Event in tree "
            << "or enter 0 to exit: ";
        std::cin >> line;
        if (line == "0") return;
        TreeNode<Event>* node = tree.search(Event(line));
        if (!node)
        {
            std::cout << "\nEntered Event wasn't found!" << std::endl;
            
        }
        else std::cout << "\n" << node->value << " was found!" << std::endl;
        return;
    }
}
void addMenu(SplayTree<Event>& tree)
{
    while (true)
    {
        std::string line = "0";
        std::cout << "\nEnter name of Event to add Event to tree "
            << "or enter 0 to exit: ";
        std::cin >> line;
        if (line == "0") return;
        tree.insert(Event(line));
        std::cout << "\n" << line << " was added!" << std::endl;
        return;
    }
}
void removeMenu(SplayTree<Event>& tree)
{
    while (true)
    {
        std::string line = "0";
        std::cout << "\nEnter name of Event to remove Event from tree "
            << "or enter 0 to exit: ";
        std::cin >> line;
        if (line == "0") return;
        tree.remove(Event(line));
        std::cout << "\nEvent was removed or not" << std::endl;
        return;
    }
}
void addeventsToTree(SplayTree<Event>& tree, std::string path)
{
    Book map = readdays(path);
    for (std::size_t i = 0; i < map.days.size(); i++)
    {
        for (std::size_t j = 0; j < map.days[i].events.size(); j++)
        {
            tree.insert(map.days[i].events[j]);
        }
    }
    std::cout << "\nevents was read from file!" << std::endl;
}
void menu()
{
    SplayTree<Event> tree;
    std::string path = "input.txt";
    while (true)
    {
        std::cout << "\nMenu:\n1)Add events from file '" << path << "' to tree.\n" <<
            "2)Add Event to tree.\n3)Remove Event from tree.\n4)Find Event by name.\n" <<            
            "5)Print tree.\n0)Back." << std::endl;
        switch (_getch())
        {
        case '0': return;
            break;
        case '1': addeventsToTree(tree, path);
            break;
        case '2': addMenu(tree);
            break;
        case '3': removeMenu(tree);
            break;
        case '4': findMenu(tree);
            break;
        case '5': tree.print();
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
