#include "Graph.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "The right way is in this format: ./mst <inputFile>" << std::endl;
		return (1);
	}
	try
	{
		Graph	my_graph(argv[1]);
		my_graph.printGraph();
		my_graph.Kruskal();
		my_graph.printMST();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


}

