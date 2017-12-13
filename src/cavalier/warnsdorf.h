//created by antoine sadzot
#include <stdbool.h>
#include "../graphes/graphes.h"

//Retranscription de l'algorithme de Douglas Squirrel, inspiré de l'heurisitque de Warnsdorff
//Pour un échiquier carré de taille m*m, génère un chemin hamiltonien 
//Correspondant au problème du cavalier
//Le départage entre des cases de même poids est déterminé selon la dimension de l'échiquier
//Renvoie vrai si le chemin généré est valide. Renvoie faux sinon
bool Squirrel (int m);

//Génération de chemin hamiltonnien représentant les mouvements du cavalier sur un échiquier carré
//Graphe stocké sous forme de matrice
//Basé sur l'heurisitque de Warnsdorff
//départage aléatoire
//m = taille d'un côté de l'échiquier
//Renvoie vrai si le chemin généré est valide. Renvoie faux sinon
bool WarnsdorffClassique(int m);

//Génération de chemin hamiltonnien représentant les mouvements du cavalier sur un échiquier rectangulaire
//Graphe stocké sous forme de matrice
//n = nombre de lignes de l'échiquier
//m = nombre de colonnes de l'échiquier
//A = matrice contenant l'ordre de parcours
//Renvoie vrai si le chemin généré est valide. Renvoie faux sinon
bool WarnsdorffNFoisM(int*A,int n,int m);

//Utilisation de l'algorithme de Shun-Shii Lin et Chung-Liang Wei
//Dans le cas où l'échiquier comporte trois lignes et m colonnes
//Renvoie vrai si le chemin généré est valide. Renvoie faux sinon
bool ArbitraireTroisFoisM(int m);