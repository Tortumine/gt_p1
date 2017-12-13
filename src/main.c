#include <stdio.h>
#include <stdlib.h>
#include "graphes/graphes.h"
#include "cavalier/cavalier.h"

#define m 6 //number of columns
#define n 6 //number of lines
int main() {
    /*--------------------------------
    **THEOREME DE SHWENK POUR L'INITIALISATION**
    ----------------------------------*/
    //ajout de tous les points
    GRAPHE* monGraphe;
    monGraphe = malloc(m*n*sizeof(GRAPHE));
    initialiserGraphe(monGraphe);
    int problemSize = m*n;

    //Mouvement possibles du cavalier
    int X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    //Variable temporaire initialisation des mouvements
    int tmpX = 0;
    int tmpY = 0;

    //Initialisation des noeuds
    for(int i=0;i < problemSize;i++)
    {
        ajouterSommet(monGraphe, 0);
    }
    //add arc representing legal moves of the night on the board.
    //not oriented graph, because knight can move in every direction

    for(int y = 0;y<n;y++)
    {
        for (int x = 0; x < m; x++)
        {
            for(int i=0;i<8;i++)
            {
                //calcul des liens
                tmpX=x+X[i];
                tmpY=y+Y[i];
                if(tmpX >= 0 && tmpY >= 0 && tmpX < m && tmpY < n)
                {
                    //ajout d'un lien si la case calculée est dans les limites de l'échequier
                    ajouterArc(monGraphe,x+m*y,tmpX+m*tmpY, 0);
                }
            }
        }
    }

    afficherGraphe(monGraphe);
    BruteForceChemins(m,n,monGraphe);
    return 0;
}