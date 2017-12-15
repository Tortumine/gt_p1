//
// Created by tortumine on 8/12/17.
//
#include <printf.h>
#include <omp.h>
#include "bruteforce.h"


void BruteForceChemins(int m,int n,GRAPHE* monGraphe)
{
    int i=0;
    int j=0;
    int k=0;
    int tmp=0;
    int grid = m*n;
    int progress=0;
    int* result=malloc(n*m*(sizeof(int)));

    int thread_id, nb_threads;

    printf("-------------------\nBrute Force Chemins\n-------------------\n");
    printf("\n%d cases dans la grille\n",grid);

#pragma omp parallel
    {
        thread_id = omp_get_thread_num();

        if ( thread_id == 0 ) {
            nb_threads = omp_get_num_threads();
            printf("Le calcul se fait sur %d threads\n",nb_threads);
            printf("Progression: % 2d/%d\t\tSolutions: %d",progress,grid,tmp);
            fflush(stdout);
        }


#pragma omp for
        for(i=0;i<m*n;i++)
        {
            result[i]=bruteforceChemin(n,m,monGraphe,i);
            tmp=tmp+result[i];
            //statut du calcul
            progress=progress+(1/(grid));
            progress++;
            printf("\rProgression: % 2d/%d\t\tSolutions: %d",progress,grid,tmp);
            fflush(stdout);
        }
    }

    printf("\n\nNombre de chemins trouvés dans une grille %d x %d : %d\n",m,n,tmp);
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
    int grid = m*n;                         //évite des calculs rondondants
    int progress=0;                         //statut du calcul
    int* result=malloc(n*m*(sizeof(int)));

    int thread_id, nb_threads;              //multithreading

    printf("--------------------\nBrute Force Circuits\n--------------------\n");
    printf("\n%d cases dans la grille\n",grid);

#pragma omp parallel
    {
        thread_id = omp_get_thread_num();

        if (thread_id == 1) {
            nb_threads = omp_get_num_threads();
            printf("Le calcul se fait sur %d threads\n", nb_threads);
            printf("Progression: % 2d/%d\t\tSolutions: %d", progress, grid, tmp);
            fflush(stdout);
        }

#pragma omp for
        for (i = 0; i < m * n; i++) {
            result[i] = bruteforceCircuit(n, m, monGraphe, i);
            tmp = tmp + result[i];
            //statut du calcul
            progress = progress + (1 / (grid));
            progress++;
            printf("\rProgression: % 2d/%d\t\tSolutions: %d", progress, grid, tmp);
            fflush(stdout);
        }
    }
    printf("\n\nNombre de circuits trouvés dans une grille %d x %d : %d\n",m,n,tmp);
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
    short* tableau_visites={0};
    int hauteur_actuele = 0;
    int nombre_chemins = 0;
    int  hauteur_max = (m * n - 1);
    tableau_visites = malloc(m * n * sizeof(short));

    nombre_chemins=bruteforceCheminsRec(origine,origine,graph_possible,tableau_visites,
                         hauteur_actuele,hauteur_max,nombre_chemins);

    return nombre_chemins;
}

//Fonction de lancement de l'exploration d'arbre
// en cherchant des circuits euleriens
int bruteforceCircuit(int m, int n,GRAPHE* graph_possible,int origine)
{
    short* tableau_visites={0};
    int hauteur_actuele = 0;
    int nombre_circuits = 0;
    int  hauteur_max = (m * n - 1);
    tableau_visites = malloc(m * n * sizeof(short));

    nombre_circuits=bruteforceCircuitsRec(origine,origine,graph_possible,tableau_visites,
                                        hauteur_actuele,hauteur_max,nombre_circuits);

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
