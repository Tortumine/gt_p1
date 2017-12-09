#include <stdio.h>
#include <stdlib.h>
#include "graphes/graphes.h"
#include "cavalier/cavalier.h"

#define m 5 //number of columns
#define n 5 //number of lines
int main() {
    printf("Hello, World!\n");


    /*--------------------------------
    **THEOREME DE SHWENK POUR L'INITIALISATION**
    ----------------------------------*/
    //ajout de tous les points
    GRAPHE* monGraphe;
    monGraphe = malloc(m*n*sizeof(GRAPHE));
    initialiserGraphe(monGraphe);
    int problemSize = m*n;
    for(int i=0;i < problemSize;i++)
    {
        ajouterSommet(monGraphe, 0);
    }
    //add arc representing legal moves of the night on the board.
    //not oriented graph, because knight can move in every direction
    for(int i=0;i < problemSize;i++)
    {
        //Upper position left :
        if(!((i/m) < 2) && !((i%m) == 0))
            ajouterArc(monGraphe, i, i - 1 - 2*n, 0);
        //Upper position right :
        if(!((i/m) < 2) && !((i%m) == m-1))
            ajouterArc(monGraphe, i, i + 1 - 2*n, 0);      
        //Lower position left :
         if(!((i/m) >= n-2) && !((i%m) == 0))
            ajouterArc(monGraphe, i,  i - 1 + 2*n, 0); 
        //Lower position right :
         if(!((i/m) >= n-2) && !((i%m) == m-1))
            ajouterArc(monGraphe, i, i + 1 + 2*n, 0); 
        //Left position up :
        if(!((i%m) <= 1) && !((i/m) == 0))
            ajouterArc(monGraphe, i, i - 2 - n, 0); 
        //Left position down :
        if(!((i%m) <= 1) && !((i/m) == n-1))
            ajouterArc(monGraphe, i, i - 2 + n, 0); 
        //Right position up :
        if(!((i%m) >= m - 2) && !((i/m) == 0))
            ajouterArc(monGraphe, i, i + 2 - n, 0);
        //Right position down :
        if(!((i%m) >= m - 2) && !((i/m) == n-1))
            ajouterArc(monGraphe, i, i + 2 + n, 0);
    }

    afficherGraphe(monGraphe);

    bruteforceChemin(n,m,monGraphe,0);
    return 0;
}