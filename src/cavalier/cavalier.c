//
// Created by tortumine on 8/12/17.
//
#include <printf.h>
#include "cavalier.h"

//----------------------------------------------------------
//             Fonctions d'appel de recurcion
//----------------------------------------------------------

//Fonction de lancement de l'exploration d'arbre
// en cherchant des chemins euleriens
void bruteforceChemin(int n, int m,GRAPHE* graph_possible, u_int origine)
{
    short* tableau_visites;
    u_int position_actuelle = 0;
    u_int hauteur_actuele = 0;
    u_int nombre_chemins = 0;
    u_int  hauteur_max = (u_int)(m * n - 1);
    tableau_visites = malloc(m * n * sizeof(short));

    bruteforceCheminsRec(origine,position_actuelle,graph_possible,tableau_visites,
                         hauteur_actuele,hauteur_max,nombre_chemins);

}

//Fonction de lancement de l'exploration d'arbre
// en cherchant des circuits euleriens
void bruteforceCircuit(int n, int m,GRAPHE* graph_possible,u_int origine)
{
    short* tableau_visites;
    u_int hauteur_actuele=0;
    u_int nombre_circuits;
    u_int  hauteur_max = (u_int)(m * n - 1);
    tableau_visites = malloc(m * n * sizeof(short));

}
//----------------------------------------------------------
//   Fonctions récurcives pour l'exploiration de l'arbre
//----------------------------------------------------------

u_int bruteforceCheminsRec(u_int origine,u_int position, GRAPHE* graphe_possible,
                           short* tableau_visites, u_int hauteur_actuelle,
                           u_int hauteur_max, u_int nombre_chemins)
{
    tableau_visites[position]=1;
    if(hauteur_actuelle < hauteur_max)
    {
        int i=0;
        ELTADJ* test = graphe_possible->premierSommet->adj;

        for(i; i< position;i++)
        {
            test = test->suivant;
        }
        i=0;
        while(test != NULL )
        {
            printf("test %d_%d_%d\n",i,test->info,test->dest);
            position++;
            i++;
            test = test->suivant;
        }
    }
    return nombre_chemins;
}

u_int bruteforceCircuitsRec(u_int origine,u_int position, GRAPHE* graphe_possible,
                            short* tableau_visites, u_int hauteur_actuelle,
                            u_int hauteur_max, u_int nombre_chemins)
{

}