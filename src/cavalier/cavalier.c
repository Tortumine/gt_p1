//
// Created by tortumine on 8/12/17.
//
#include <printf.h>
#include "cavalier.h"


void BruteForceChemins(int m,int n,GRAPHE* monGraphe)
{
    int i=0;
    int tmp=0;
    int* result;

    result=malloc(n*m*(sizeof(int)));
    printf("-------------------\nBrute Force Chemins\n-------------------\n",m,n,tmp);

    for(i=0;i<m*n;i++)
    {
        result[i]=bruteforceChemin(n,m,monGraphe,i);
        tmp=tmp+result[i];
        printf("%d/%d\n",i+1,n*m);
    }


    printf("\nNombre de chemins trouvés dans une grille %d x %d : %d\n",m,n,tmp);
    printf("Détail du resultats: chemins possibles en fonction de la case de départ.\n\n");
    for(int j = 0;j<n;j++)
    {
        printf("\t");
        for (int k = 0; k < m; k++)
        {
            printf("%05d\t",result[k+m*j]);
        }
        printf("\n");
    }
}
void BruteForceCircuits(int m,int n,GRAPHE* monGraphe)
{
    int i=0;
    int tmp=0;
    int* result=malloc(n*m*(sizeof(int)));
        for(i=0;i<m*n;i++)
    {
        result[i] = bruteforceCircuit(n,m,monGraphe,i);
        tmp=tmp+result[i];
        printf("%d/%d\n",i+1,n*m);
    }

    printf("Nombre de circuits trouvés dans une grille %d x %d : %d\n",m,n,tmp);
    printf("Détail du resultats: circuits possibles en fonction de la case de départ.\n\n");
    for(int j = 0;j<n;j++)
    {
        printf("\t");
        for (int k = 0; k < m; k++)
        {
            printf("%05d\t",result[k+m*j]);
        }
        printf("\n");
    }
}


//----------------------------------------------------------
//             Fonctions d'appel de recurcion
//----------------------------------------------------------

//Fonction de lancement de l'exploration d'arbre
// en cherchant des chemins euleriens

int bruteforceChemin(int m, int n,GRAPHE* graph_possible, int origine)
{
    //printf("------------------------\n");
    //printf("   Brute Force Chemins\n");
    //printf("------------------------\n");

    short* tableau_visites={0};
    int hauteur_actuele = 0;
    int nombre_chemins = 0;
    int  hauteur_max = (int)(m * n - 1);
    tableau_visites = malloc(m * n * sizeof(short));

    nombre_chemins=bruteforceCheminsRec(origine,origine,graph_possible,tableau_visites,
                         hauteur_actuele,hauteur_max,nombre_chemins);

    //printf("------------------------\n");
    //printf("Nombre chemins: %d\n",nombre_chemins);
    return nombre_chemins;
}

//Fonction de lancement de l'exploration d'arbre
// en cherchant des circuits euleriens
int bruteforceCircuit(int m, int n,GRAPHE* graph_possible,int origine)
{
    //printf("------------------------\n");
    //printf("   Brute Force CIrcuits\n");
    //printf("------------------------\n");

    short* tableau_visites={0};
    int hauteur_actuele = 0;
    int nombre_circuits = 0;
    int  hauteur_max = (int)(m * n - 1);
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

int bruteforceCheminsRec(int origine,int position, GRAPHE* graphe_possible,
                           short* tableau_visites, int hauteur_actuelle,
                           int hauteur_max, int nombre_chemins)
{
    tableau_visites[position]=1;
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

int bruteforceCircuitsRec(int origine,int position, GRAPHE* graphe_possible,
                            short* tableau_visites, int hauteur_actuelle,
                            int hauteur_max, int nombre_circuit)
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
                break;
            }
            test = test->suivant;
        }
    }
    tableau_visites[position]=0;
    return nombre_circuit;
}