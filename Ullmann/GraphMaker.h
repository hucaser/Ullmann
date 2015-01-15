#pragma once
#include <vector>

struct Edge
{
int from; // p-th vertex
int to; // q-th vertex
int elabel; // has label 
int id;
};

class Vertex
{
public:
		std::vector<Edge> edge;	// all edges connect with this vertex
		int label;
		typedef std::vector<Edge>::iterator edge_iterator;
		void push (int from, int to, int elabel)
		{
				//why not use edge.push_back()
				// Because if we use push_back, first we need to define a Edge e
				// then push_back(e) will call Edge's copy constructor, it cost more time
				edge.resize(edge.size()+1);
				edge[edge.size()-1].from = from;
				edge[edge.size()-1].to = to;
				edge[edge.size()-1].elabel = elabel;
				return;
		}
};

class Graph : public std::vector<Vertex>
{
		int edge_size;
public:
		// generate a unique id for each edges in this graph
		void buildEdge();
		void read(std::ifstream &in);
};

class GraphMaker
{
public:
		GraphMaker(void);
		~GraphMaker(void);
		void readFile(std::ifstream& in);
		std::vector<Graph> graphDatabase;
};

