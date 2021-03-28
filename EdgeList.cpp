#include "EdgeList.h"
#include <algorithm>
//reading the EdgeList from file
EdgeList::EdgeList(const char* input) {
	cout << "Construction de EdgeList" << endl;
	unsigned long e1 = NLINKS;
	ifstream file(input);

	n = 0;
	e = 0;
	cout << "Allocation en cours" << endl;
	try {
		edges = vector<Edge>(NLINKS);
	}
	catch (...) {
		cout << "Echec" << endl;
		return;
	}

	//edges.resize(e1);// = malloc(e1 * sizeof(edge));//allocate some RAM to store edges
	cout << "Construction des arretes" << endl;
	char test[256];
	file.getline(test, 256);
	file.getline(test, 256);
	file.getline(test, 256);
	file.getline(test, 256);


	unsigned long s, t;
	while (file >> s >> t) {

		edges[e].s = s;
		edges[e].t = t;

		n = max3(n, s, t);
		if (++e == e1) {//increase allocated RAM if needed
			e1 += NLINKS;
			edges.resize(e1);
		}
	}
	

	n++;

	edges.resize(e);

}


vector<float > EdgeList::PowerIteration(float alpha,unsigned int t) {
	// NB : ici on utilise le fait que les edges sont lus de façon orientée : si on lui passe un graphe orienté ca marchera
	
	// Construction de la matrice de transitions (avec le cas des noeuds isolés,
	// Il serait interessant d'essayer de les supprimer en amont
	vector<float> T(e, 0.);
	vector<unsigned long> dout(n, 0);
	for (unsigned long i = 0; i < e; i++) {
		dout[edges[i].s]++;
	}
	for (unsigned long i = 0; i < e; i++) {
		unsigned long u = edges[i].s;
		T[i] = (dout[u] == 0) ? 1. / n : 1. / dout[u];
	}
	
	vector<float> P(n, 1 / n);
	for (unsigned int i = 0; i < t; i++) {

		vector<float> buff(n, 0);

		// Produit matrice-vecteur T*P
		for (unsigned long edg = 0; edg < e; edg++) {
			buff[edges[edg].t] += T[edg] * P[edges[edg].s];
		}
		for (unsigned long j = 0; j < n; j++) {
			P[j] = (1 - alpha) * buff[j] + alpha/n; // Verifier qu'ici il faut bien diviser par n
		}
		// calcule la norme de P
		float norm = 0.;
		for (unsigned long j = 0; j < n; j++) {
			norm += abs(P[j]);
		}
		//normalise P
		for (unsigned long j = 0; j < n; j++) {
			P[j] += (1 - norm) / n;
		}
	}
	return P;
}

void TestPowerIt() {
	EdgeList g("D:\\Graphes_RDM\\alr21--dirLinks--enwiki-20071018.txt");

	std::cout << "Number of nodes:\n" << g.n << endl;
	std::cout << "Number of edges:\n" << g.e << endl;

	vector<float> P = g.PowerIteration(0.15, 10);
	vector<unsigned long> ind(g.n);
	for (int i = 0; i < g.n; i++) {
		ind[i] = i;// On suppose que la numérotation part bien de 1
	}
	sort(ind.begin(), ind.end(), [&](const int& a, const int& b) {return P[a] < P[b]; });
	// lire le fichier avec le noms de page

	ifstream file("D:\\Graphes_RDM\\alr21--pageNum2Name--enwiki-20071018.txt");
	char test[256];
	file.getline(test, 256);
	file.getline(test, 256);
	file.getline(test, 256);
	file.getline(test, 256);
	unsigned long s;
	string getter;
	string line;
	string buff;
	vector<string> names(g.n, "");
	while (file.getline(test, 256)) {
		line = string(test);
		buff = "";
		getter = "";
		//lecture de la ligne:

		while (line[0] != '\t') {
			buff += line[0];
			line.erase(0, 1);
		}
		s = strtoul(buff.c_str(), NULL, 0);
		//std::cout << s << endl;
		buff = "";
		while (line[0] == ' ') {
			line.erase(0, 1);
		}
		names[s] = line;
	}


	// Trouver les 5 meilleurs et les 5 pires:
	std::cout << "****Pires pages*****" << endl;
	unsigned int num_found = 0;
	for (unsigned long i = 0; i < g.n; i++) {
		if (names[ind[i]] != "") {
			std::cout << i << " : " << names[ind[i]] << " -  val : " << P[ind[i]] << endl;
			num_found++;
		}
		if (num_found == 5) break;
	}

	// Trouver les 5 meilleurs et les 5 pires:
	std::cout << "****Meilleures pages*****" << endl;
	num_found = 0;
	for (unsigned long i = g.n - 1; i >= 1; i--) {
		if (names[ind[i]] != "") {
			std::cout << ind[i] << " : " << names[ind[i]] << " -  val : " << P[ind[i]] << endl;
			num_found++;
		}
		if (num_found == 5) break;
	}

}



void PrintDataPowerIt() {
	EdgeList g("D:\\Graphes_RDM\\alr21--dirLinks--enwiki-20071018.txt");

	std::cout << "Number of nodes:\n" << g.n << endl;
	std::cout << "Number of edges:\n" << g.e << endl;
	cout << "0.15" << endl;
	vector<float> P = g.PowerIteration(0.15, 10);
	cout << "0.1" << endl;
	vector<float> P1 = g.PowerIteration(0.1, 10);
	cout << "0.2" << endl;
	vector<float> P2 = g.PowerIteration(0.2, 10);
	cout << "0.5" << endl;
	vector<float> P5 = g.PowerIteration(0.5, 10);
	cout << "0.9" << endl;
	vector<float> P9 = g.PowerIteration(0.9, 10);


	vector<unsigned int> InDegree(g.n, 0);
	vector<unsigned int> OutDegree(g.n, 0);
	cout << "degrees" << endl;

	for (int i = 0; i < g.e; i++) {
		InDegree[g.edges[i].t]++;
		OutDegree[g.edges[i].s]++;
	}
	cout << "Writting" << endl;

	ofstream outFile("D:\\Graphes_RDM\\Res_PageRank_Cor.txt");
	for (int i = 0; i < g.n; i++) {
		outFile << P[i] << " ";
	}
	outFile << endl;
	for (int i = 0; i < g.n; i++) {
		outFile << P1[i] << " ";
	}
	outFile << endl;
	for (int i = 0; i < g.n; i++) {
		outFile << P2[i] << " ";
	}
	outFile << endl;
	for (int i = 0; i < g.n; i++) {
		outFile << P5[i] << " ";
	}
	outFile << endl;
	for (int i = 0; i < g.n; i++) {
		outFile << P9[i] << " ";
	}
	outFile << endl;
	for (int i = 0; i < g.n; i++) {
		outFile << InDegree[i] << " ";
	}
	outFile << endl;
	for (int i = 0; i < g.n; i++) {
		outFile << OutDegree[i] << " ";
	}
	outFile << endl;
	cout << "end" << endl;
}