//
// Created by tortumine on 8/12/17.
//
#include <stdlib.h>
#include <stdio.h>
#include "../graphes/graphes.h"

void BruteForceChemins(int n,int m,GRAPHE* monGraphe);
void BruteForceCircuits(int n,int m,GRAPHE* monGraphe);

int bf_open_init(int n, int m, GRAPHE *graph_possible, int origine);
int bf_open_rec(int origine, int position, GRAPHE *graphe_possible, short *tableau_visites, int hauteur_actuelle,
                int hauteur_max, int nombre_chemins);

int bf_close_init(int n, int m, GRAPHE *graph_possible, int origine);
int bf_close_rec(int origine, int position, GRAPHE *graphe_possible, short *tableau_visites, int hauteur_actuelle,
                 int hauteur_max, int nombre_chemins);
