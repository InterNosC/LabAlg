#include "Johnson's_algorithm.h"
#include "Roy_Floyd_algorithm.h"
#include <conio.h>

using namespace std;

void menu()
{
	fstream output_file;
	fstream input_file;

    while (true)
    {
        std::cout << "\nMenu:\n1) Generate ten new random directed graphs\n" <<
            "2) Find all-pairs shortest paths using Johnson's algorithm\n" <<
            "3) Find all-pairs shortest paths using Johnson's algorithm for a user defined graph\n" << 
            "4) Make a comparation between Johnson's algorithm and Roy-Floyd's algorithm\n" <<
            "0) Back." << std::endl;

        switch (_getch())
        {
		case '1':
		{
			write_random_graph(output_file);
			break;
		}

		case '2':
		{
			//delete everything from output file
			output_file.open("output_Johnson.txt", ios::trunc | ios::out);
			output_file.close();

			input_file.open("input.txt", ios::in);


			for (int i = 0; i < 10; i++)
			{

				vector<Edge> edges;
				int N, E;

				input_file >> N >> E;

				for (int i = 0; i < E; i++)
				{
					Edge e;
					input_file >> e.src;
					input_file >> e.dest;
					input_file >> e.weight;
					edges.push_back(e);
				}

				Graph new_graph(edges, N);


				Johnson_algorithm(new_graph, i, output_file);

			}

			input_file.close();


			break;
		}

		case '3':
		{
			output_file.open("output_Johnson.txt", ios::trunc | ios::out);
			output_file.close();

			vector<Edge> edges;
			int N, E;
			cout << "Number of vertices in graph :" << endl;
			cin >> N;
			cout << "Number of edges in graph : maxim V*(V-1)" << endl;
			cin >> E;

			cout << "Enter the edges : (u, v, w)" << endl;
			for (int i = 0; i < E; i++)
			{
				Edge e;
				cin >> e.src;
				cin >> e.dest;
				cin >> e.weight;
				edges.push_back(e);
			}

			Graph new_graph(edges, N);

			cout << "User's graph : " << endl;
			print_graph(new_graph);

			Johnson_algorithm(new_graph, 0, output_file);

			break;
		}

		case '4':
		{
			output_file.open("output_Johnson.txt", ios::trunc | ios::out);
			output_file.close();

			output_file.open("output_Roy_Floyd.txt", ios::trunc | ios::out);
			output_file.close();

			input_file.open("input.txt", ios::in);


			for (int i = 0; i < 10; i++)
			{

				vector<Edge> edges;
				int N, E;

				input_file >> N >> E;

				for (int i = 0; i < E; i++)
				{
					Edge e;
					input_file >> e.src;
					input_file >> e.dest;
					input_file >> e.weight;
					edges.push_back(e);
				}

				Graph new_graph(edges, N);

				Johnson_algorithm(new_graph, i, output_file);

				floydWarshall(new_graph, i, output_file);
			}

			input_file.close();

			break;
		}


		case '0':
		{
			return;
		}

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