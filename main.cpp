#include "./Graph.hpp"

int main(void)
{
	try
	{
		Graph	my_graph("input.txt");
		
		my_graph.printGraph();
		my_graph.Kruskal();
		my_graph.printMST();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


}

