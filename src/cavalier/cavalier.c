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
u_int bruteforceChemin(int n, int m,GRAPHE* graph_possible, u_int origine)
{
    //printf("------------------------\n");
    //printf("   Brute Force Chemins\n");
    //printf("------------------------\n");

    short* tableau_visites={0};
    u_int hauteur_actuele = 0;
    u_int nombre_chemins = 0;
    u_int  hauteur_max = (u_int)(m * n - 1);
    tableau_visites = malloc(m * n * sizeof(short));

    nombre_chemins=bruteforceCheminsRec(origine,origine,graph_possible,tableau_visites,
                         hauteur_actuele,hauteur_max,nombre_chemins);

    //printf("------------------------\n");
    //printf("Nombre chemins: %d\n",nombre_chemins);
    return nombre_chemins;
}

//Fonction de lancement de l'exploration d'arbre
// en cherchant des circuits euleriens
u_int bruteforceCircuit(int n, int m,GRAPHE* graph_possible,u_int origine)
{
    //printf("------------------------\n");
    //printf("   Brute Force CIrcuits\n");
    //printf("------------------------\n");

    short* tableau_visites={0};
    u_int hauteur_actuele = 0;
    u_int nombre_circuits = 0;
    u_int  hauteur_max = (u_int)(m * n - 1);
    tableau_visites = malloc(m * n * sizeof(short));

    nombre_circuits=bruteforceCircuitsRec(origine,origine,graph_possible,tableau_visites,
                                        hauteur_actuele,hauteur_max,nombre_circuits);

    //printf("------------------------\n");
    //printf("Nombre chemins: %d\n",nombre_chemins);
    return nombre_circuits;
}
//----------------------------------------------------------
//   Fonctions récurcives pour l'exploiration de l'arbre
//----------------------------------------------------------

u_int bruteforceCheminsRec(u_int origine,u_int position, GRAPHE* graphe_possible,
                           short* tableau_visites, u_int hauteur_actuelle,
                           u_int hauteur_max, u_int nombre_chemins)
{
    tableau_visites[position]=hauteur_actuelle+1;

    if(hauteur_actuelle < hauteur_max)
    {
        int i=0;

        // Ces lignes permettent d'acceder au sommet / la case consernée
        // ATTENTION: ce code n'est pas optimal, l'acces à la position par &(graphe_possible->premiersommet[position]) ne marche pas
        SOMMET* sommet = graphe_possible->premierSommet;
        for(i=0;i<position;i++)
        {
            sommet=sommet->suivant;
        }
        ELTADJ* test = sommet->adj;


        while(test != NULL )
        {
            if(tableau_visites[test->dest]==0)
            {
                nombre_chemins = bruteforceCheminsRec(origine,test->dest,graphe_possible,tableau_visites,hauteur_actuelle + 1 ,hauteur_max,nombre_chemins);}
            test = test->suivant;
        }
    }
    else
    {
        nombre_chemins++;
    }
    tableau_visites[position]=0;
    return nombre_chemins;
}

u_int bruteforceCircuitsRec(u_int origine,u_int position, GRAPHE* graphe_possible,
                            short* tableau_visites, u_int hauteur_actuelle,
                            u_int hauteur_max, u_int nombre_circuit)
{
    int i=0;
    tableau_visites[position]=hauteur_actuelle + 1;
    SOMMET* sommet = graphe_possible->premierSommet;

    // Ces lignes permettent d'acceder au sommet / la case consernée
    // ATTENTION: ce code n'est pas optimal, l'acces à la position par &(graphe_possible->premiersommet[position]) ne marche pas
    for(i=0;i<position;i++)
    {
        sommet=sommet->suivant;
    }
    ELTADJ* test = sommet->adj;

    if(hauteur_actuelle < hauteur_max)
    {
        while(test != NULL )
        {
            if(tableau_visites[test->dest]==0)
            {
                nombre_circuit = bruteforceCircuitsRec(origine,test->dest,graphe_possible,tableau_visites,hauteur_actuelle + 1 ,hauteur_max,nombre_circuit);}
            test = test->suivant;
        }
    }
    else
    {
        while(test != NULL)
        {
            if(test->dest==origine)
            {
                nombre_circuit++;
            }
            test = test->suivant;
        }
    }
    tableau_visites[position]=0;
    return nombre_circuit;
}