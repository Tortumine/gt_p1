#include <stdio.h>
#include "graphes.h"

#define m 5; //number of columns
#define n 5; //number of lines
bool canMove(int, pos1, int pos2)
{

}
int main() {
    printf("Hello, World!\n");

    //ajout de tous les points
    GRAPHE* monGraphe;
    initialiserGraphe(monGraphe);
    size_t problemSize = m*n;
    for(int i=0;i < problemSize;i++)
    {
        ajouterSommet(monGraphe, 0);
    }
    int testPos = 0;
    for(int i=0;i < problemSize;i++)
    {
        //Upper position left :

        if(((i/m) >= 2) && ((i%m) > 0))
        testPos = i - 1 - 2*n;
        if(isInTheGraph(testPos))
            ajouterArc(monGraphe, i, testPos, 0);
        //Upper position right :
        testPos = i + 1 - 2*n;
        if(isInTheGraph(testPos))
            ajouterArc(monGraphe, i, testPos, 0);
        //Lower position left :
        testPos = i - 1 + 2*n;
        if(isInTheGraph(testPos))
            ajouterArc(monGraphe, i, testPos, 0);
        //Lower position right :
        testPos = i + 1 + 2*n;
        if(isInTheGraph(testPos))
            ajouterArc(monGraphe, i, testPos, 0);
        //Left position up :
        testPos = i - 2 - n;
        if(isInTheGraph(testPos))
            ajouterArc(monGraphe, i, testPos, 0);
        //Left position down :
        testPos = i - 2 + n;
        if(isInTheGraph(testPos))
            ajouterArc(monGraphe, i, testPos, 0);
        //Right position up :
        testPos = i + 2 - n;
        if(isInTheGraph(testPos))
            ajouterArc(monGraphe, i, testPos, 0);
        //Right position down :
        testPos = i + 2 + n;
        if(isInTheGraph(testPos))
            ajouterArc(monGraphe, i, testPos, 0);
    }

    return 0;
}