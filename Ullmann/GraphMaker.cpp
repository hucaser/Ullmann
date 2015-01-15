#include "StdAfx.h"
#include "GraphMaker.h"
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>

std::vector<std::string>& split(std::string& s, char delim, 
		std::vector<std::string>& elems)
{
		/* head file sstream */
		std::stringstream ss(s);
		std::string item;
		while(std::getline(ss, item, delim)){
				elems.push_back(item);
		}
		return elems;
}

GraphMaker::GraphMaker(void)
{
}


GraphMaker::~GraphMaker(void)
{
}

void GraphMaker::readFile(std::ifstream& in)
{
		Graph g;
		std::string str;
		std::vector<std::string> result;
		while(true){
				str.clear();
				/* head file is fstream*/
				if(!getline(in, str)) break;
				result.clear();
				split(str, ' ', result);
				if(result[0] == "t" && result[2] == "-1")
						break;
				else{
						std::cout << result[2] << std::endl;
						g.clear();
						g.read(in);
						graphDatabase.push_back(g);
				}
		}
}


void Graph::read(std::ifstream& in)
{
		std::string str;
		std::vector<std::string> result;
		while(true){
				std::streampos pos = in.tellg();

				str.clear();
				if(!getline(in, str)) break;
				result.clear();
				split(str, ' ', result);

				if(result.empty()){
						// this line is empty, do nothing
				} else if(result[0] == "t"){
						in.seekg(pos);
						break;
				} else if(result[0] == "v" && result.size() >=3){
						unsigned int id = atoi(result[1].c_str());
						this->resize(id+1);
						(*this)[id].label = atoi(result[2].c_str());
				} else if(result[0] == "e" && result.size() >= 4){
						int from = atoi(result[1].c_str());
						int to = atoi(result[2].c_str());
						int elabel = atoi(result[3].c_str());

						(*this)[from].push(from, to, elabel);
						(*this)[to].push(to, from, elabel);
				}
		}
		buildEdge();
}

void Graph::buildEdge()
{
		char buf[512];
		std::map<std::string, int> tmp;

		unsigned int id = 0;
		for(int from=0; from < (int)size(); from++){
				for(std::vector<Edge>::iterator it = (*this)[from].edge.begin();
						it != (*this)[from].edge.end(); ++it){
						if(from <= it->to)
								std::sprintf (buf, "%d %d %d", from, it->to, it->elabel);
						else
								std::sprintf (buf, "%d %d %d", it->to, from, it->elabel);

						// Assign unique id's for the edges.
						if(tmp.find(buf) == tmp.end()){
								it->id = id;
								tmp[buf] = id;	// add (buf,id) to map. The most frequent used way
								id++;
						} else {
								it->id = tmp[buf];
						}
				}
		}

		edge_size = id;
}