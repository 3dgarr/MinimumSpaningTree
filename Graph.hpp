#pragma once

# include	<iostream>
# include	<fstream>
# include	<algorithm>
# include	<vector>
# include	<set>
# include	<utility> // for std::pair
# include	<exception>
# include	<sstream>
# include	<unordered_map>
# include	<unordered_set>
# include	<queue>


using	Edges			= std::pair<int, int>;
using	Weight			= int;
using	ListOfEdges		= std::vector<std::pair<Weight, Edges>>;
using	AdjacencyList	= std::unordered_map<int, std::vector<int>>;
using	Verteces		= std::set<int>;


class Graph
{
    public:
		Graph(const char* filename);
		~Graph();
	
	public:
		void	readGraphFromFile(const char *);
		void	printGraph() const;
		void	printMST()	const;
		int		FindSet(int i);
		void	UnionSet(int u, int v);
		void	Kruskal();
		bool	isConnected();
		void	getAdjList();
		

	private:
		ListOfEdges			graph;
    	ListOfEdges			mst;
		int*				parent;
		Verteces			verteces;
		size_t				numberOfVerteces;
		size_t				numberOfEdges;
		AdjacencyList		adjancecyList;	

};

