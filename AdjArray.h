#pragma once

#include "Edge.h"
#include "EdgeList.h"

class AdjArray
{
public:
	unsigned long n;//number of nodes
	unsigned long e;//number of edges
	vector<unsigned long> cd; //degrés cumulés
	vector<unsigned long> adj; //listes concaténées de voisins de tous les noeuds
	AdjArray() { n = 0; e = 0; cd = vector<unsigned long>(0); adj = vector<unsigned long>(0); }
	AdjArray(const char* input);
	unsigned long BFS(unsigned long s);
	int BFS2(unsigned long &s);
	int BorneDist(unsigned long s);
	unsigned long Diametre();
	vector<vector<unsigned long>> triangle();
	unsigned long kcore_decomposition();
	unsigned long kcore_decomposition_prefixed();
	void label_propagation();

};

void mainTriangle(const char* input);
void mainKCorePref(const char* input);
void mainLabelProp(const char* input);
void mainBornesDia(const char* input);
