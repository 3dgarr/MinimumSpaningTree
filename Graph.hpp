#pragma once

# include	<iostream>
# include	<fstream>
# include	<algorithm>
# include	<vector>
# include	<set>
# include	<utility> // for std::pair
# include	<exception>
# include	<sstream>


using	Edges			= std::pair<int, int>;
using	Weight			= int;
using	AdjacencyList	= std::vector<std::pair<Weight, Edges>>;

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
		std::set<int>		verteces;
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
		class BadInput : public std::exception
		{
			public:
				const char *what() const throw();	
		};
};

