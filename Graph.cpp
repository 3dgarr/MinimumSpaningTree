#include "./Graph.hpp"

const char*	Graph::FileNotOpened::what(void) const throw()
{
	return ("Error opening file" );
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
    if (file.is_open())
	{
        file >> numberOfVerteces >> numberOfEdges;
        for (size_t i = 0; i < numberOfEdges; i++) 
		{
            int u, v, weight;
            file >> u >> v >> weight;
            graph.emplace_back(weight, std::make_pair(u, v));
        }
        file.close();
		std::cout << "Number of Edges    = " << numberOfEdges << std::endl;
		std::cout << "Number of Verteces = " << numberOfVerteces<< std::endl;
    }
	else 
	{
		throw	(FileNotOpened());
    }
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
// void Graph::DFS(int v, std::vector<bool>& visited) 
// {
//     visited[v] = true;
//     for (auto& neighbor : graph.second) 
// 	{
//         int u = neighbor.second.first;
//         if (!visited[u]) 
// 		{
//             DFS(u, visited);
//         }
//     }
// }

// bool Graph::isConnected() 
// {
//     std::vector<bool> visited(numberOfVerteces + 1, false);
//     DFS(1, visited);
//     for (int i = 1; i <= numberOfVerteces; ++i) 
// 	{
//         if (!visited[i]) 
// 		{
//             return false;
//         }
//     }
//     return true;
// }



Graph::Graph(const char *filename)
{
	graph.clear();
	mst.clear();		
	readGraphFromFile(filename);
	// if (isConnected())
}


Graph::~Graph()
{
	delete [] parent;
}