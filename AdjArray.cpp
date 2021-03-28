#include "AdjArray.h"
#include "updatable_priority_queue.h"
#include <queue>


AdjArray::AdjArray(const char* input) {
	cout << "Construction AdjArray" << endl;
	EdgeList elist(input);
	n = elist.n;
	e = elist.e;


	unsigned long i, u, v;
	cout << "Allocation en cours" << endl;
	try {
		adj.resize(2*e);
		cd.resize(n + 1);
	}
	catch (...) {
		cout << "Echec." << endl;
		return;
	}
	cout << "Construction de la matrice" << endl;
	vector<unsigned long> d(n);
	for (i = 0; i < e; i++) {
		d[elist.edges[i].s]++;
		d[elist.edges[i].t]++;
	}

	cd[0] = 0;
	for (i = 1; i < n + 1; i++) {
		cd[i] = cd[i - 1] + d[i - 1];
		d[i - 1] = 0;
	}

	for (i = 0; i < e; i++) {
		u = elist.edges[i].s;
		v = elist.edges[i].t;
		adj[cd[u] + d[u]++] = v;
		adj[cd[v] + d[v]++] = u;
	}
}


unsigned long AdjArray::BFS(unsigned long s) {

	std::queue<unsigned long> FIFO;
	std::vector<unsigned long> Mark = vector<unsigned long>(n, false);
	unsigned long u = 0;
	unsigned long i = 0;
	FIFO.push(s);
	Mark[s] = true;
	while (FIFO.size() != 0) {
		u = FIFO.front();
		FIFO.pop();
		i = Mark[u]+1;
		for (int j = cd[u]; j < cd[u+1]; j++) {
			if (!Mark[adj[j]]) {
				FIFO.push(adj[j]);
				Mark[adj[j]] = i;
			}
		}
	}
	return(i-2);
}

unsigned long AdjArray::Diametre() {

	unsigned long max = 0;
	unsigned long l = 0;
	for (unsigned long i = 0; i < n; i++) {
		//cout << "sommet : " << i << endl;
		l = this->BFS(i);
		//cout << "l : " << l << endl;
		if (l > max) {
			max = l;
		}
	}
	return(max);
}

int AdjArray::BFS2(unsigned long &s) {

	std::queue<unsigned long> FIFO;
	std::vector<bool> Mark = vector<bool>(n, false);
	std::vector<int> Dist = vector<int>(n, 0);
	unsigned long u = 0;
	unsigned long i = 0;
	FIFO.push(s);
	Mark[s] = true;
	while (FIFO.size() != 0) {
		u = FIFO.front();
		FIFO.pop();
		i++;
		for (int j = cd[u]; j < cd[u+1]; j++) {
			if (!Mark[adj[j]]) {
				FIFO.push(adj[j]);
				Mark[adj[j]] = true;
				Dist[adj[j]] = Dist[u] + 1;
			}
		}
	}
	int dist = 0;
	for (int j = 0; j < n; j++) {
		if (Dist[j] > dist) {
			dist = Dist[j];
			s = j;
		}
	}
	return dist;
}

int AdjArray::BorneDist(unsigned long s) {
	int dist_max = 0;
	int dist = 0;
	for (int i = 0; i < 5; i++) {
		dist = BFS2(s);
		if (dist > dist_max) {
			dist_max = dist;
		}
	}
	return dist_max;
} // borne sup = quand tous les sommets ont ete marques, on prend le "i" qui correspond dans BFS ?

vector<vector<unsigned long>> AdjArray::triangle(){


	vector<vector<unsigned long>> listTriangle(0);// = vector<vector<unsigned long>>(0);
	vector<unsigned long> tslu(0);
	// on recherche les degrés de chacun des sommets
	vector<unsigned long> deg(n);
	for (int i = 0; i < n; i++) {
		deg[i] = cd[i + 1] - cd[i];
	}

	// on crée la liste des indices de sommet
	vector<unsigned long> indice(n);
	for (unsigned long i = 0; i < n; i++) {
		indice[i] = i;
	}

	// on trie les indices de sommets en fonction des degrés
	//cout << "Tri des sommets selon les degrés" << endl;

	sort(indice.begin(), indice.end(), [&](const int& a, const int& b) {return(deg[a] > deg[b]);});

	// on crée la relation d'ordre
	//cout << "création de la relation d'ordre" << endl;

	vector<unsigned long> ordre(n);
	for (int i = 0; i < n; i++) {
		ordre[indice[i]] = i;
		//cout << "sommet :" << indice[i] << ", indice : " << i << endl;
	}


	// on crée, trie et tronque tsl[u] pour chacun des sommets
	//cout << "creation de tsl pour chacun des sommets" << endl;
	cout << n << endl;
	vector<vector<unsigned long>> tsl(n);
	for (int i = 0; i < n; i++) {
		//cout << "Sommet " << i << endl;

		// on crée tsl[u]
		tslu.resize(cd[i + 1] - cd[i]);
		for (int j = 0; j < cd[i + 1] - cd[i]; j++) {

			tslu[j] = adj[j + cd[i]];
		}
		//cout << "size " << tslu.size() << endl;
		//cout << "tri" << endl;

		// on trie  tsl[u], en fonction des degrés
		sort(tslu.begin(), tslu.end(), [&](const int& a, const int& b) {return(ordre[a] < ordre[b]);});
		//cout << "tslu" << endl;
		//for (int z = 0; z < tslu.size(); z++) {
		//	cout << tslu[z] << endl;
		//}
		//cout << "tronque" << endl;
		// on tronque tsl[u] pour tout les sommet voisins de degré supérieur à u 
		unsigned long a = 0;
		for (unsigned long j = 0; j < tslu.size(); j++) {
			if (ordre[tslu[j]] < ordre[i]) {
				a = j + 1;
			}	
		}
		//cout << "a : " <<  a << endl;
		tslu.erase(tslu.begin(), tslu.begin() + a);

		
		//cout << "tslu" << endl;
		//for (int z = 0; z < tslu.size(); z++) {
		//	cout << tslu[z] << endl;
		//}
		//cout << "ajout" << endl;
		// on ajoute tsl[u] à tsl
		for (int z = 0; z < tslu.size();z++) {
			tsl[i].push_back(tslu[z]);
		}
	}

	// on recherche les triangles
	// on parcours les u
	cout << "Recherche des triangles" << endl;

	for (unsigned long i = 0; i < n - 1; i++) {
		//cout << "sommet 1: " << i << endl;
		// on parcours les v voisins de u
		for (unsigned long k = 0; k < tsl[i].size(); k++) {
			//cout << "sommet 2: " << tsl[i][k] << endl;
			// on regarde l'intersection de tslu et tslv
			int l = 0;
			int m = 0;

			vector<unsigned long> W(0);
			while ((l < tsl[i].size()) && (m < tsl[tsl[i][k]].size())) {
				
				if (tsl[i][l] == tsl[tsl[i][k]][m]) {
					W.push_back(tsl[i][l]);
					m = m + 1;
					l = l + 1;
				}
				else if (ordre[tsl[i][l]] > ordre[tsl[tsl[i][k]][m]]) {

					m = m + 1;
				}
				else {

					l = l + 1;
				}
			}
			for (unsigned long z = 0; z < W.size(); z++) {
				//cout << "sommet 3 :" << W[z] << endl;
				vector<unsigned long> tri(3);// = vector<unsigned long>(3);
				tri[0] = i;
				tri[1] = tsl[i][k];
				tri[2] = W[z];
				listTriangle.push_back(tri);
			}
		}
	}
	return listTriangle;
}

vector<vector<unsigned long>> AdjArray::triangle(){

	vector<vector<unsigned long>> listTriangle(0);// = vector<vector<unsigned long>>(0);
	vector<unsigned long> tri(3);// = vector<unsigned long>(3);
	for (int i = 0; i < n; i++) {
		for (int k = cd[i]; k < cd[i + 1]; k++) {
			for (int l = k + 1; l < cd[i + 1]; l++) {
				for (int n = cd[adj[k]]; n < cd[adj[k] + 1]; n++) {
					if (adj[n] == adj[l]) {
						tri[0] = i;
						tri[1] = adj[k];
						tri[2] = adj[l];
						listTriangle.push_back(tri);
					}
				}
			}
		}
	}
	return listTriangle;
}


void mainTriangle(const char* input) {

	time_t t1, t2;
	AdjArray g1(input);
	t1 = time(NULL);
	cout << "Number of nodes:\n" << g1.n << endl;
	cout << "Number of edges:\n" << g1.e << endl;
	cout << "Calcul des triangles" << endl;
	vector<vector<unsigned long>> sol1 = g1.triangle();
	unsigned int nt1 = sol1.size();
	cout << "Nombre de triangles : " << nt1 << endl;
	t2 = time(NULL);
	cout << "- Overall time =" << endl;
	cout << (t2 - t1) / 3600 << "h " << ((t2 - t1) % 3600) / 60 << "mn " << ((t2 - t1) % 60) << "s " << endl;
	return ;
}


unsigned long AdjArray::kcore_decomposition(){
	unsigned long c = 0;
	unsigned long i = n;
	unsigned long vi = 0, vdeg = 0;
	vector<unsigned long> marquage(n);
	vector<unsigned long> deg(n);
	better_priority_queue::updatable_priority_queue<unsigned long, unsigned long> VG;
	for (int it = 0; it<n; it++)
	{VG.push(it,n - (cd[it+1]-cd[it]));
	deg[it] = n - (cd[it+1]-cd[it]);
	}
	for (int cpt = 0; cpt < n  ; cpt++)
	{
		auto v = VG.pop_value();
		vdeg = v.priority;
		vi = v.key;
		c = max(c,n - vdeg);
		marquage[vi] = c;
		for (int j = cd[vi]; j< cd[vi + 1]; j++)
		{
			if (deg[adj[j]] != 0)
			{
				VG.update(adj[j],deg[adj[j]] + 1);
				deg[adj[j]] = deg[adj[j]] + 1;
			}
		}
		VG.push(vi, 0);
		deg[vi] = 0;
	}

	return c;
}


unsigned long AdjArray::kcore_decomposition_prefixed(){
	unsigned long c = 0;
	unsigned long i = n;
	unsigned long vi = 0, vdeg = 0;
	vector<unsigned long> marquage(n);
	vector<unsigned long> deg(n);
	vector<double> prefix(n+1);

	better_priority_queue::updatable_priority_queue<unsigned long, unsigned long> VG;
	for (int it = 0; it<n; it++)
	{VG.push(it,n - (cd[it+1]-cd[it]));
	deg[it] = n - (cd[it+1]-cd[it]);
	prefix[it+1] = 0;
	}
	prefix[0] = (double) cd[n]/(2*n);
	for (int cpt = 0; cpt < n  ; cpt++)
	{
		auto v = VG.pop_value();
		vdeg = v.priority;
		vi = v.key;
		if (cpt != n-1){
		prefix[cpt+1] = (prefix[cpt]*(n-cpt) - (n-deg[vi])) / (double) (n-cpt-1.);
		}
		c = max(c,n - vdeg);
		marquage[vi] = c;
		for (int j = cd[vi]; j< cd[vi + 1]; j++)
		{
			if (deg[adj[j]] != 0)
			{
				VG.update(adj[j],deg[adj[j]] + 1);
				deg[adj[j]] = deg[adj[j]] + 1;
			}
		}
		VG.push(vi, 0);
		deg[vi] = 0;

	}
	long int max_index = max_element(prefix.begin(),prefix.end()) - prefix.begin();
	double avg_deg_dens = *max_element(prefix.begin(),prefix.end());
	cout << "average_degree_density_densest_prefix =" << avg_deg_dens << endl;
	cout << "size_densest_prefix = " << n-max_index << endl;
	cout << "edge density =" << avg_deg_dens*(n-max_index)/(double) ((n-max_index+1)*(n-max_index+1)) << endl;

	/// Partie plot de l'exercice 2
	/// On trace le graphe sous MATLAB
	///ofstream fout("test.txt");
	///fout << n << endl;
	///for (int i = 0;i<n;i++)
	///{
	///	fout << i << " " << cd[i+1]-cd[i] << " " << marquage[i] << endl;
	///}

	return c;
}


void AdjArray::label_propagation()
{
	vector<unsigned long> label(n);
	vector<long> ordre(n);
	vector<unsigned long> frequence(n);
	vector<bool> max_voisinage(n);
	int ind_min;
	int label_max;
	int cpt_false;
	int cpt_boucle = 0;
	int magic_label_max;
	for (int i = 0;i < n; i++)
	{
		label[i] = i;
		ordre[i] = i;
	}
	bool finished = true;
	while (finished)
	{
		
		random_shuffle(ordre.begin(),ordre.end());
		cpt_false = 0;
		for (int i = 0; i<n; i++)
		{
			for (int j = 0; j<n; j++)
				{frequence[j] = 0;}
			ind_min = min_element(ordre.begin(),ordre.end()) - ordre.begin();
			for (int j = cd[ind_min]; j<cd[ind_min + 1]; j++)
				{frequence[label[adj[j]]] ++;}
			magic_label_max = *max_element(frequence.begin(),frequence.end());
			deque<unsigned long> magic(1);
			for (int j = 0; j<n; j++)
			{ if (frequence[label[j]] == magic_label_max)
				{
					magic.push_back(label[j]);
				}
			}
			magic.pop_front();
			random_shuffle(magic.begin(),magic.end());
			label_max = magic.front();
			max_voisinage[ind_min] = (label[ind_min] == label_max);
			label[ind_min] = label_max;
			ordre[ind_min] = 400;
			for (int j = 0; j<n; j++)
				{ordre[j] -=1;}
		}
		for (int i = 0; i<n; i++)
		{
			if (max_voisinage[i] == false) {cpt_false++;}
		}
		finished = (cpt_false >= 1);
		cpt_boucle++;
//		cout << "iteration " << cpt_boucle << endl; 
	}


	//  Sortie dans un fichier
	ofstream fout("sortie_tp4.txt");
	for (int i = 0; i<n; i++)
	{
	//	cout << "label sommet " << i << " = " << label[i] << endl;
		fout << "label sommet " << i << " = " << label[i] << endl;
	}


}

void mainKCorePref(const char* input){
    time_t t1, t2;

	t1 = time(NULL);

	//cout << "Reading EdgeList from file\n" << argv[1] << endl;
	//EdgeList g(argv[1]);
	//cout << "Reading AdjMatrix from file\n" << argv[1] << endl;
	//AdjMatrix g(argv[1]);
	cout << "Reading AdjArray from file\n" << input<< endl;
	AdjArray g(input);

	cout << "Number of nodes:\n" << g.n << endl;
	cout << "Number of edges:\n" << g.e << endl;

	t2 = time(NULL);

	cout << "- Overall time =" << endl;
	cout << (t2 - t1) / 3600 << "h " << ((t2 - t1) % 3600) / 60 << "mn " << ((t2 - t1) % 60) << "s " << endl;;

	//unsigned long i = g.BFS(548551);
	//cout << "BFS depuis 0 : " << i << endl;
//	cout << "Calcul des triangles" << endl;
//	unsigned long nt = g.triangle().size()/3;
//	cout << "Nombre de triangles : " << nt << endl;

	cout << "Calcul de la kcore_decomposition" << endl; 
	unsigned long c = g.kcore_decomposition_prefixed() ; 
	cout << "c = " << c << endl ;
}

void mainLabelProp(const char* input){
    time_t t1, t2;

	t1 = time(NULL);

	cout << "Reading AdjArray from file\n" << argv[1] << endl;
	AdjArray g(argv[1]);

	cout << "Number of nodes:\n" << g.n << endl;
	cout << "Number of edges:\n" << g.e << endl;

	t2 = time(NULL);

	cout << "- Overall time =" << endl;
	cout << (t2 - t1) / 3600 << "h " << ((t2 - t1) % 3600) / 60 << "mn " << ((t2 - t1) % 60) << "s " << endl;;
	
	g.label_propagation();
}