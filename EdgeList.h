#pragma once
#include "Edge.h"

class EdgeList
{
public:
	unsigned long n;//number of nodes
	unsigned long e;//number of edges
	vector<Edge> edges;//list of edges
	EdgeList() { n = 0; e = 0; edges = vector<Edge>(0); }
	EdgeList(const char* input);

	vector<float > PowerIteration(float alpha, unsigned int t);
};

void TestPowerIt(); // Chercher les 5 meilleures et 5 moins bonnes pages (en terme de PageRank)
void PrintDataPowerIt(); // Ecrit dans un fichier l'ensemble des tableaux qu'on veut afficher avec python