//
// Created by tortumine on 8/12/17.
//
#include <printf.h>
#include <omp.h>
#include "cavalier.h"


void BruteForceChemins(int m,int n,GRAPHE* monGraphe)
{
    int i=0;
    int j=0;
    int k=0;
    int tmp=0;
    int* result;

    result=malloc(n*m*(sizeof(int)));
    printf("-------------------\nBrute Force Chemins\n-------------------\n",m,n,tmp);
    printf("En cours de calcul...\n%d cases dans la grille\n",m*n);

    omp_set_dynamic(0);
    omp_set_num_threads(4);
#pragma omp parallel
    {
#pragma omp critical
           printf("%d\n",omp_get_num_threads());

#pragma omp for
        for(i=0;i<m*n;i++)
        {
            result[i]=bruteforceChemin(n,m,monGraphe,i);
            tmp=tmp+result[i];

            printf("%d/%d\n",i+1,n*m);
        }
    }

    printf("\nNombre de chemins trouvés dans une grille %d x %d : %d\n",m,n,tmp);
    printf("Nombre de chemins possibles en fonction de la case de départ:\n\n");
    for(j = 0;j<n;j++)
    {
        printf("\t");
        for (k = 0; k < m; k++)
        {
            //affichage de la case
            printf("% 6d\t",result[k+m*j]);
        }
        printf("\n");
    }
}
void BruteForceCircuits(int m,int n,GRAPHE* monGraphe)
{
    int i=0;
    int j=0;
    int k=0;
    int tmp=0;
    int* result=malloc(n*m*(sizeof(int)));
    printf("-------------------\nBrute Force Circuits\n-------------------\n",m,n,tmp);

    for(i=0;i<m*n;i++)
    {
        result[i] = bruteforceCircuit(n,m,monGraphe,i);
        tmp=tmp+result[i];
        printf("%d/%d\n",i+1,n*m);
    }

    printf("Nombre de circuits trouvés dans une grille %d x %d : %d\n",m,n,tmp);
    printf("Nombre de circuits possibles en fonction de la case de départ:\n\n");
    for(j = 0;j<n;j++)
    {
        printf("\t");
        for (k = 0; k < m; k++)
        {
            //affichage de la case
            printf("% 6d\t",result[k+m*j]);
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
                            int hauteur_max, int nombre_circuits)
{
    tableau_visites[position]=1;

    int i=0;
    // Ces lignes permettent d'acceder au sommet / la case consernée
    // ATTENTION: ce code n'est pas optimal, l'acces à la position par &(graphe_possible->premiersommet[position]) ne marche pas
    SOMMET* sommet = graphe_possible->premierSommet;
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
                nombre_circuits = bruteforceCircuitsRec(origine,test->dest,graphe_possible,tableau_visites,hauteur_actuelle + 1 ,hauteur_max,nombre_circuits);}
            test = test->suivant;
        }
    }
    else
    {
        while(test != NULL)
        {
            if(test->dest==origine)
            {
                nombre_circuits++;
                break;
            }
            test = test->suivant;
        }
    }
    tableau_visites[position]=0;
    return nombre_circuits;
}