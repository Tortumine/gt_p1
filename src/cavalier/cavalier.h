//
// Created by tortumine on 8/12/17.
//
#include <stdlib.h>
#include <stdio.h>
#include "../graphes/graphes.h"

void bruteforceChemin(int n, int m,GRAPHE* graph_possible, u_int origine);
u_int bruteforceCheminsRec(u_int origine,u_int position, GRAPHE* graphe_possible,short* tableau_visites, u_int hauteur_actuelle, u_int hauteur_max, u_int nombre_chemins);