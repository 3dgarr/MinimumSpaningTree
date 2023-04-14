#include "./Graph.hpp"

const char*	Graph::FileNotOpened::what(void) const throw()
{
	return ("Error opening file" );
}

const char*	Graph::BadInput::what(void) const throw()
{
	return ("Bad Input" );
}

void Graph::printGraph() const
{
    std::cout << "Edges:" << std::endl;
    for (const auto& edge : graph) 
	{
        std::cout << edge.second.first << " - " << edge.second.second << " (" << edge.first << ")" << std::endl;
    }
}

void	Graph::readGraphFromFile(const char* filename)
{
    std::ifstream file(filename);
	numberOfEdges = 0;
	numberOfVerteces = 0;

    if (file.is_open())
	{
		int u, v, weight;
		std::string	line;
		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			if (!(iss >> u >> v >> weight))
			{
				throw BadInput();
			}
            graph.emplace_back(weight, std::make_pair(u, v));
			verteces.insert(u);
			verteces.insert(v);
			numberOfEdges++;
        }
		numberOfVerteces = verteces.size();
		std::cout << "Number of Edges    = " << numberOfEdges << std::endl;
		std::cout << "Number of Verteces = " << numberOfVerteces<< std::endl;
    }
	else 
	{
		throw	(FileNotOpened());
    }
	file.close();
}

int	Graph::FindSet(int i)
{
	if (i == parent[i])
		return i;
	else
		return FindSet(parent[i]);
}

void Graph::UnionSet(int u, int v) 
{
	parent[u] = parent[v];
}

void Graph::Kruskal() 
{
	size_t	i;
	int		u, v;
	
	parent = new int[numberOfVerteces];
	for (size_t i = 0; i < numberOfVerteces; i++)
		parent[i] = i;	
	std::sort(graph.begin(), graph.end());  // increasing weight
	for (i = 0; i < graph.size(); i++) 
	{
		u = FindSet(graph[i].second.first);
		v = FindSet(graph[i].second.second);
		if (u != v) 
		{
			mst.push_back(graph[i]);
			UnionSet(u, v);
		}
  	}
}

void	Graph::printMST()	const
{
	std::cout << "< Edges > -- [weight]" << std::endl;
	for (size_t i = 0; i < mst.size(); i++)
	{
		std::cout <<"< " << mst[i].second.first << " - " << mst[i].second.second << " > -- [" << mst[i].first << "]" << std::endl; 
	}
}

Graph::Graph(const char *filename)
{
	graph.clear();
	mst.clear();		
	readGraphFromFile(filename);
}


Graph::~Graph()
{
	delete [] parent;
}