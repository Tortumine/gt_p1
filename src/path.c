#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "Generateur/Generateur.h"

#define iterMax 100

int main() {
    srand(time(NULL));
    int choix;
    int m,n;
    int iterations;
    int* A;
    int imprim = 1;
    int continuer = 111;
    bool reussi = true;
    double iterTest;
    int j;
    //circuit
    /*A=malloc(8*8*sizeof(int));
    do{

        WarnsdorffNFoisM(A,8,8);
    }while(!TestValideCircuit(A,8,8));
    PrintBoard(A,8,8);
    //chemin
    Squirrel(A,8);
    PrintBoard(A,8,8);
    //3*m
    A=malloc(3*16*sizeof(int));
    ArbitraireTroisFoisM(A,16);
    PrintBoard(A,3,16);
    free(A);

    return 0;*/
    while(continuer == 111 || continuer == 79)
    {
    printf("Programme de résolution du probleme du cavalier\n\n");
    do{
        choix=0;
        printf("Voici les différents choix possibles\n\n");
        printf("1. Trouver un chemin hamiltonnien avec l'heuristique de warnsdorff\n");
        printf("2. Trouver un circuit hamiltonnien avec l'heuristique de warnsdorff\n");
        printf("3. Trouver un chemin hamiltonnien avec l'algorithme de Squirrel\n");
        printf("4. Trouver un chemin hamiltonien sur un échiquier de taille 3*m\n");
        printf("\n");
        printf("Votre choix : ");
        do
            choix = getchar();
        while(isspace(choix));
    }while(choix > '6' || choix < '1');
    printf("\n");
    switch (choix)
    {
        case '1' : 
            printf("Algorithme base sur l'heuristique de Warnsdorff avec departage aleatoire\n");
            printf("Cet algorithme ne garantit pas de trouver un chemin a coup sur\n");
            printf("\n");
            do{
                printf("Nombre de lignes : ");
                do
                    scanf("%d",&n);
                while(isspace(n));
                printf("Nombre de colonnes : ");
                do
                    scanf("%d",&m);
                while(isspace(m));
            }while(n < 1 && m < 1);
            A = malloc(m*n*sizeof(int));
            iterations=0;
            do
            {
                WarnsdorffNFoisM(A,n,m);
                iterations++;
            }while(iterations < iterMax && !TestValideChemin(A,n,m));
            if(iterations == iterMax)
                printf("Aucun chemin n'a ete trouve apres 100 iterations\n");
            else
                printf("Un chemin a ete trouve apres %d iteration(s)\n",iterations);
        break;
        case '2' : 
            printf("Algorithme base sur l'heuristique de Warnsdorff avec departage aleatoire\n");
            printf("Cet algorithme ne garantit pas de trouver un circuit a coup sur\n");
            printf("\n");
            do{
                printf("Nombre de lignes : ");
                 do
                    scanf("%d",&n);
                while(isspace(n));
                printf("Nombre de colonnes : ");
                do
                    scanf("%d",&m);
                while(isspace(m));
            }while(n < 1 && m < 1);
            A = malloc(m*n*sizeof(int));
            iterations=0;
            do
            {
                WarnsdorffNFoisM(A,n,m);
                iterations++;
            }while(iterations < 100000 && !TestValideCircuit(A,n,m));
            if(iterations == 100000)
                printf("Aucun circuit n'a ete trouve apres %d iterations\n",iterations);
            else
                printf("Un circuit a ete trouve apres %d iteration(s)\n",iterations);
        break;
        case '3' : 
            printf("Algorithme base sur les travaux de D. Squirrel\n");
            printf("Cet algorithme garantit de trouver un chemin pour un echiquier valide\n");
            printf("\n");
            do{
                printf("Nombre de lignes : ");
                do
                    scanf("%d",&n);
                while(isspace(choix));
                if(n < 5)
                    printf("Valeur trop petite, aucun chemin ne peut etre trouve\n");
            }while(n < 5);
            A = malloc(n*n*sizeof(int));
            iterations=0;
            m = n;
            do
            {
                Squirrel(A,n);
                iterations++;
            }while(iterations < iterMax && !TestValideChemin(A,n,n));
            if(iterations == iterMax)
                printf("Aucun chemin n'a ete trouve apres 100 iterations\n");
            else
                printf("Un chemin a ete trouve apres %d iteration(s)\n",iterations);
        break;
        case '4' :
            printf("Algorithme base sur les travaux de Shun-Shii Lin\n");
            printf("Cet algorithme garantit de trouver un chemin pour un echiquier valide\n");
            printf("\n");
            do{
                printf("Nombre de colonnes : ");
                do
                    scanf("%d",&m);
                while(isspace(choix));
            }while(m < 1);
            n=3;
            A = malloc(n*m*sizeof(int));
            iterations=0;
            if(m<4 || m==5 || m==6)
            {
                printf("Il est impossible de trouver un chemin hamiltonnien dans ce graphe\n");
                imprim = 0;
                break;
            }
            do
            {
                reussi = ArbitraireTroisFoisM(A, m);
                iterations++;
            }while(iterations < iterMax && !TestValideChemin(A,n,m));
            if(reussi == false)
                printf("Aucun chemin n'a pu etre trouve\n");
            else if(iterations == iterMax)
                printf("Aucun chemin n'a ete trouve apres 100 iterations\n");
            else
                printf("Un chemin a ete trouve apres %d iteration(s)\n",iterations);
        break;
    }
    if(imprim == 1)
        do{ 
            printf("\nVoulez vous imprimer le résultat dans le fichier Resultat.txt? (o/n) : ");
            do
                imprim = getchar();
            while(isspace(imprim));
        }while(imprim != 111 && imprim != 79 && imprim != 110 && imprim != 78);
    if(imprim == 111 || imprim == 79 && imprim == 1)
    {
        PrintBoard(A,n, m);
    }
    free(A);
    do{
        printf("\nVoulez vous recommencer? (o/n) : ");
         do
            continuer = getchar();
        while(isspace(continuer));
    }while(continuer != 111 && continuer != 79 && continuer != 110 && continuer != 78);
} 
}
