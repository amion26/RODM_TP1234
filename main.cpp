// RODM_TP1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.


#include <iostream>
#include "EdgeList.h"
#include "AdjMatrix.h"
#include "AdjArray.h"

int main(int argc, char** argv)
{
	// mainTriangle("D:\\Graphes_RDM\\graphe1.txt");// Attention : corriger le chemin vers le graphe
	// TestPowerIt(); // Attention : liens en dur dans EdgeList.cpp
	// PrintDataPowerIt(); // Attention encore lien en dur dans EdgeList.cpp
	// mainKCorePref("D:\\Graphes_RDM\\graphe1.txt");//Lien à modifier
	mainLabelProp("D:\\Graphes_RDM\\graphe1.txt");// Lien a modifier



	return 0;
}