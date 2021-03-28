#include "AdjMatrix.h"

AdjMatrix::AdjMatrix(char* input) {
	cout << "Construction AdjMatrix" << endl;
	EdgeList elist(input);
	n = elist.n;
	e = elist.e;


	unsigned long i, u, v;
	cout << "Allocation en cours" << endl;
	try {
		mat.resize(n, vector<bool>(n));
	}
	catch (...){
		cout << "Echec." << endl;
		return;
	}
	cout << "Construction de la matrice" << endl;
	for (i = 0; i < e; i++) {
		u = elist.edges[i].s;
		v = elist.edges[i].t;
		mat[u][v] = true;
		mat[v][u] = true;
	}
}