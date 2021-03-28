#pragma once
#include "EdgeList.h"
class AdjMatrix
{
public:
	unsigned long n;//number of nodes
	unsigned long e;//number of edges
	vector<vector<bool>> mat;
	AdjMatrix() { n = 0; e = 0; mat = vector<vector<bool>>(0); }
	AdjMatrix(char* input);
};