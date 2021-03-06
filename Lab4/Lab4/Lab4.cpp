#include <iostream>
#include <conio.h>
#include "optimal_binary_tree.h"
#include "binary_tree.h"

using namespace obt;
using namespace wm;
OptimalTree<Event>* findMenu(OptimalTree<Event>* tree)
{
    if (!tree) return tree;
    while (true)
    {
        std::string line = "0";
        std::cout << "\nEnter name of Event to find Event in tree "
            << "or enter 0 to exit: ";
        std::cin >> line;
        if (line == "0") return tree;
        Node<Event>* node = tree->search(Event(line));
        if (!node)
        {
            std::cout << "\nEntered Event wasn't found!" << std::endl;

        }
        else {
            std::vector<Event> values;
            for (std::size_t i = 1; i < tree->values.size(); i++)
            {
                values.push_back(tree->values[i]);
            }
            std::vector<int> probabilitiesP(values.size(), 1),
                probabilitiesQ(values.size() + 1, 1);
            
            for (std::size_t i = 0; i < tree->probabilitiesQ.size(); i++)
            {
                probabilitiesQ[i] = tree->probabilitiesQ[i];
            }
            for (std::size_t i = 1; i < tree->probabilitiesP.size(); i++)
            {
                probabilitiesP[i - 1] = tree->probabilitiesP[i];
            }
            
            for (int i = 0; i < tree->values.size(); i++) {
                if (node->value.getName() == tree->values[i].getName()) {
                    int j = -1;
                    for (int k = 0; k < tree->values.size(); k++) {
                        if (tree->probabilitiesP[k] > 10 && k != i) {
                            j = k;
                            break;
                        }
                    }
                    probabilitiesQ[i] =  tree->probabilitiesQ[i] + 10;
                    probabilitiesP[j - 1] = tree->probabilitiesP[j] - 10;
                    tree = new OptimalTree<Event>(values, probabilitiesP, probabilitiesQ);
                    break;
                }
            }
            std::cout << "\n" << line << " was found!" << std::endl;
        }
        return tree;
    }
}
OptimalTree<Event>* addeventsToTree(std::string path)
{
    OptimalTree<Event>* tree = nullptr;
    Book map = readdays(path);
    std::vector<Event> values;
    for (std::size_t i = 0; i < map.days.size(); i++)
    {
        for (std::size_t j = 0; j < map.days[i].events.size(); j++)
        {
            values.push_back(map.days[i].events[j]);
        }
    }
    std::vector<int> probabilitiesP(values.size(), 1), 
        probabilitiesQ(values.size() + 1, 1);
    int sum = 100 - probabilitiesP.size() - probabilitiesQ.size();
    for (std::size_t i = 0; i < probabilitiesP.size(); i++)
    {
        auto size = std::to_string(values[i]).size();
        if (sum >= size)
        {
            probabilitiesP[i] += size;
            sum -= size;
        }
        else
        {
            probabilitiesP[i] += sum;
            sum = 0;
            break;
        }
    }
    auto part = sum / probabilitiesP.size();
    for (std::size_t i = 0; i < probabilitiesP.size(); i++)
    {
        probabilitiesP[i] += part;
        sum -= part;
        if (sum < part) break;
    }
    probabilitiesQ[0] += sum/2;
    sum -= sum / 2;
    probabilitiesQ[probabilitiesQ.size() - 1] += sum;
    tree = new OptimalTree<Event>(values, probabilitiesP, probabilitiesQ);
    std::cout << "\nevents was read from file!" << std::endl;
    return tree;
}
void menu()
{
    OptimalTree<Event>* tree = nullptr;
    std::string path = "input.txt";
    while (true)
    {
        std::cout << "\nMenu:\n1)Add events from file '" << path << "' to tree.\n" <<
            "2)Find Event by name.\n" <<
            "3)Print tree.\n0)Back." << std::endl;
        switch (_getch())
        {
        case '0': 
        {
            if (tree) delete tree;
            return;
        }
            break;
        case '1': tree = addeventsToTree(path);
            break;
        case '2': tree = findMenu(tree);
            break;
        case '3': if (tree)
        {
            std::cout << "\nTree:" << std::endl;
            tree->print();
            std::cout << "\nCost table:\n" << tree->getCostTable().str() << std::endl;
            std::cout << "Root table:\n" << tree->getRootTable().str() << std::endl;
        }
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
