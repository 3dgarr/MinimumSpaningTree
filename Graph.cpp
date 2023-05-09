#include "./Graph.hpp"

void Graph::printGraph() const
{
	system("rm -rf in; mkdir in");
	std::ofstream input("./in/input.dot");
	if (!input.is_open())
	{
		throw std::runtime_error("Can't create inputfile");
	}

	input << "graph {\n";
	for (auto pair : graph)
	{
		input  << "\t" << pair.second.first << " -- " << pair.second.second << " [label=" << pair.first  << "]"<< std::endl; 
	}
	input << "}\n";
	input.close();
    system("dot -Tpng -O ./in/input.dot && xdg-open ./in/input.dot");
}

void	Graph::getAdjList()
{
	for (auto edge : graph)
	{
		auto	u = edge.second.first;
		auto	v = edge.second.second;
		adjancecyList[u].push_back(v);
		adjancecyList[v].push_back(u);
	}
}

bool		Graph::isConnected()
{
	getAdjList();
	auto	startIndex	= adjancecyList.begin()->first;
	std::unordered_set<int>	visitedVerteces;
	std::queue<int>			waitlist;
	waitlist.push(startIndex);
    while (!waitlist.empty()) 
	{
        int vertex = waitlist.front();
        waitlist.pop();
        visitedVerteces.insert(vertex);
        for (int neighbor : adjancecyList[vertex]) 
		{
            if (visitedVerteces.find(neighbor) == visitedVerteces.end()) 
			{
                waitlist.push(neighbor);
            }
        }
	}
	return (visitedVerteces.size() == adjancecyList.size());
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
				throw std::runtime_error("Bad input file\n");
			}
            graph.emplace_back(weight, std::make_pair(u, v));
			verteces.insert(u);
			verteces.insert(v);
			numberOfEdges++;
        }
		numberOfVerteces = verteces.size();
    }
	else 
	{
		throw	(std::runtime_error("Error opening file\n"));
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
	if (!isConnected())
		throw	std::runtime_error("Graph is not connected\n");

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
	system("rm -rf out; mkdir out");
	std::ofstream output("./out/output.dot");
	if (!output.is_open())
	{
		throw std::runtime_error("Can't create outputfile");
	}

	output << "graph {\n";
	for (auto pair : mst)
	{
		output  << "\t" << pair.second.first << " -- " << pair.second.second << " [label=" << pair.first  << "]"<< std::endl; 
	}
	output << "}";
	output.close();
    system("dot -Tpng -O ./out/output.dot && xdg-open ./out/output.dot");
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