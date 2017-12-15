//created by antoine sadzot
#include <stdbool.h>

//Retranscription de l'algorithme de Douglas Squirrel, inspiré de l'heurisitque de Warnsdorff
//Pour un échiquier carré de taille m*m, génère un chemin hamiltonien 
//Correspondant au problème du cavalier
//Le départage entre des cases de même poids est déterminé selon la dimension de l'échiquier
void Squirrel (int* A, int m);

//Génération de chemin hamiltonnien représentant les mouvements du cavalier sur un échiquier carré
//Graphe stocké sous forme de matrice
//Basé sur l'heurisitque de Warnsdorff
//départage aléatoire
//m = taille d'un côté de l'échiquier
void WarnsdorffClassique(int* A, int m);

//Génération de chemin hamiltonnien représentant les mouvements du cavalier sur un échiquier rectangulaire
//Graphe stocké sous forme de matrice
//n = nombre de lignes de l'échiquier
//m = nombre de colonnes de l'échiquier
//A = matrice contenant l'ordre de parcours
void WarnsdorffNFoisM(int*A,int n,int m);

//Utilisation de l'algorithme de Shun-Shii Lin et Chung-Liang Wei
//Dans le cas où l'échiquier comporte trois lignes et m colonnes
//Renvoie vrai si le chemin généré est valide. Renvoie faux sinon
bool ArbitraireTroisFoisM(int* A, int m);

//Permet de tester la validité d'un circuit hamiltonien
//A est la matrice contenant l'ordre de parcours
//n est le nombre de lignes
//m est le nombre de colonnes
//Renvoie vrai si le circuit soumis est correct. Renvoie faux sinon
bool TestValideCircuit(int* A, int n, int m);

//Permet de tester la validité d'un chemin hamiltonien
//A est la matrice contenant l'ordre de parcours
//n est le nombre de lignes
//m est le nombre de colonnes
//Renvoie vrai si le chemin soumis est correct. Renvoie faux sinon
bool TestValideChemin(int* A, int n, int m);

//imprime dans un fichier "chemin.txt" un chemin valide sous la forme d'un échiquier
//dont les cases sont numérotées dans leur ordre de passage
//A contient la matrice
//n est le nombre de lignes
//m est le nombre de colonnes
void PrintBoard(int* A, int n, int m);
