#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphes/graphes.h"
#include "bruteforce/bruteforce.h"

int main(int argc, char* argv[]) {

    int mode=1; //1:open, 2: close
    int m=5;
    int n=5;
    int def = 5;

    if(argc>=2)
    {
        if(strcmp(argv[1], "-o") == 0)
        {
            mode = 1;
        } else if(strcmp(argv[1], "-c") == 0) {
            mode = 2;
        } else
        {
            mode = 1;
            printf("Erreur de selection de mode, mode par defaut: OPEN\n");
        }
        if(argc==3)
        {
            int inputSize=0;

            if(sscanf (argv[2], "%d", &inputSize) != 1)
            {
                inputSize=def;
                printf("Erreur de selection de taille, valeurs par defaut: %d \n",inputSize);
            }
            m=n=inputSize;
        }
        else if(argc==4)
        {
            int inputSize=0;
            if(sscanf (argv[2], "%d", &inputSize) != 1)
            {
                inputSize=def;
                printf("Size arg1 incorrect , default value %d will be used.\n",inputSize);
            }
            m=inputSize;
            if(sscanf (argv[3], "%d", &inputSize) != 1)
            {
                inputSize=m;
                printf("Size arg2 incorrect , same value as arg1 %d will be used.\n",inputSize);
            }
            n=inputSize;
        }
        else
        {
            printf("No size args, default size values: %d %d\n",m,n);
        }
    }
    else
    {
        printf("No args, default values: -o %d %d\n",m,n);
    }

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


    if(mode==1)BruteForceChemins(m,n,monGraphe);
    else if(mode==2)BruteForceCircuits(m,n,monGraphe);
    return 0;
}
