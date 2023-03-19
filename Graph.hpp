#pragma once

# include	<iostream>
# include	<fstream>
# include	<algorithm>
# include	<vector>
# include	<set>
# include	<utility> // for std::pair
# include	<exception>


using	Edges			= std::pair<int, int>;
using	AdjacencyList	= std::vector<std::pair<int, Edges>>;

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
		// void	DFS(int v, std::vector<bool>& visited);
		// bool	isConnected();




	private:
		AdjacencyList		graph;
    	AdjacencyList		mst;
		int*				parent;

		size_t				numberOfVerteces;
		size_t				numberOfEdges;
	


	
	public:
		class FileNotOpened : public std::exception
		{
			public:
				const char *what() const throw();	
		};
};

