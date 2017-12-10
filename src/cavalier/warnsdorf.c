#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "warnsdorf.h"
#include "../graphes/graphes.h"
#include "../graphes/graphes.c"

//global values for Squirrel's tie breaking rules
int zeroModHuit[5][8] = {{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,1,8,6,7,3,4,2},{5,1,3,4,2,6,7,8},{2,1,4,3,5,6,7,8}};
int unModHuit[4][8] = {{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,1,3,2,4,6,7,8},{3,2,4,8,1,7,6,5}};
int deuxModHuit[6][8] = {{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,4,1,3,2,6,7,8},{5,2,4,3,1,6,7,8},{8,5,6,4,7,1,2,3},{1,5,7,4,6,8,2,3}};
int troisModHuit[6][8] = {{3,4,6,2,5,7,1,8},{4,2,6,8,1,3,5,7},{8,6,5,1,2,3,4,7},{5,1,8,6,7,3,4,2},{6,1,8,2,5,4,3,7},{7,1,6,4,2,5,3,8}};
int quatreModHuit[6][8] = {{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,1,8,6,7,3,4,2},{5,1,3,4,2,6,7,8},{8,6,7,5,3,4,2,1},{7,8,5,6,3,4,2,1}};
int cinqModHuit[4][8] = {{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,1,3,2,4,6,7,8},{1,5,2,3,4,6,7,8}};
int sixModHuit[6][8] = {{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,4,1,3,2,6,7,8},{5,2,4,3,1,6,7,8},{8,5,6,4,7,1,2,3},{1,2,4,5,3,6,7,8}};
int septModHuit[6][8] ={{3,4,6,2,5,7,1,8},{4,2,6,8,1,3,5,7},{8,6,5,1,2,3,4,7},{5,1,8,6,7,3,4,2},{6,1,8,2,5,4,3,7},{6,1,3,5,7,2,8,4}};

void CreerBoard(int m, GRAPHE* monGraphe);
void DiminuerPoidVoisins(SOMMET* monSommet);
int DeterminerSuivant(SOMMET* monSommet);
bool parcoursCorrect(SOMMET* monSommet,int* parcours, size_t increment,int m);
bool TestSquirrel(int* A, int* B, int m);

void warnsdorffClassique(int m)
{
    GRAPHE* monGraphe;
    int* parcours;
    //create the grpahe representing the board and the legal moves
    monGraphe = malloc(m*m*sizeof(GRAPHE));
    CreerBoard(m, monGraphe);
    //creating the structure that will hold the tour
    parcours = malloc(m*m*sizeof(int));
    for(int i=0; i<(m*m); i++){
        parcours[i] = -1;}
    size_t increment = 0; //variable d'increment pour savoir combien de cases ont été visitées
    size_t visite = 0; //indice de la case visitée.
    SOMMET* monSommet = monGraphe->premierSommet;
    bool correct = false;
    while (!correct && increment < ((m*m)-1))
    {
        parcours[visite] = increment;//give the order in which the knight parcours the board
        monSommet->info = 0;
        DiminuerPoidVoisins(monSommet);
        visite = DeterminerSuivant(monSommet);
        SOMMET* tmpPointer = monGraphe->premierSommet;
        //changement de pointeur au nouveau sommet
        while(tmpPointer != NULL)
        {
            if (tmpPointer->label == visite)
            {
                monSommet = tmpPointer;
                break;
            }       
            tmpPointer = tmpPointer->suivant;
        }
        if (tmpPointer == NULL)
        {
            printf("Erreur de determination du sommet suivant\n");
            return;
        }
        increment++;

        correct = parcoursCorrect(monSommet, parcours, increment, m);
        //printf("passage numero : %zu\n", increment);
    }
    for(int i=0; i < m*m; i++)
    {
        if(parcours[i] == -1)
        {
            parcours[i] = m*m - 1;
            break;
        }
    }
    if (correct)
        printf("tout est bien \n");
    else
        printf("Rien ne va plus\n");
    //impression du parcours
    /*int tmp = 0;
    for(int i=0; i<m; i++)
    {       
        for(int j=0; j<m; j++)
        {
            printf(" ----");
        }
        printf("\n");
        for(int j=0; j<m; j++)
        {
            printf("| %02d ",parcours[tmp]);
            tmp++;
        }
        printf("|\n");
    }
    for(int j=0; j<m; j++)
    {
        printf(" ----");
    }
    printf("\n");*/
}
bool parcoursCorrect(SOMMET* monSommet,int* parcours, size_t increment,int m)
{
    ELTADJ* adj = monSommet->adj;
    int accessible = 0;
    while(adj != NULL)
    {
        if (adj->cible->info > 0)
            accessible++;
        adj = adj->suivant;
    }
    if (increment < (m*m - 1))
        return false;
    else if(increment == (m*m - 1) && accessible > 0)
        return false;
    else return true;
}

void DiminuerPoidVoisins(SOMMET* monSommet)
{
    ELTADJ *adj;
    adj = monSommet->adj;
    /* on cherche le sommet donné*/
    while (adj != NULL)
    {
        if (adj->cible->info != 0)
            adj->cible->info--;
        adj = adj->suivant;
    }
}
int DeterminerSuivant(SOMMET* monSommet)
{
    ELTADJ *adj;
    adj = monSommet->adj;
    SOMMET* potentiels[8];//contient les candidats pour avancer
    int tmp = 0;
    int choix = 9;//plus petits poids des sommets potentiels
    //creation de la liste avec tous les voisins
    while (adj != NULL)
    {
        if (adj->cible->info != 0)
        {
            potentiels[tmp] = adj->cible;
        }
        else
        {
            potentiels[tmp] = NULL;
        }
        adj = adj->suivant;
        tmp++;
    }
    for(int i=0; i<tmp; i++)
    {
        //Every candidate with a weight higher than the lowest determined is rejected
        //If a candidate has a lower weight, "choix" is changed and previous candidates are reexamined
        if(potentiels[i] != NULL)
        {
            if (potentiels[i]->info > choix)
                potentiels[i] = NULL;
            else if (potentiels[i]->info < choix)
            {
                choix = potentiels[i]->info;
                for(int j=0; j < i; j++)
                {
                    if(potentiels[j] != NULL)
                    {
                        if (potentiels[j]->info > choix)
                            potentiels[j] = NULL;
                    }
                        
                }
            }
        }
        
    }
    int nombreCandidats=0;
    int sommetChoisi;
    //determine le nombre de candidats restants
    for(int i=0; i<tmp; i++)
    {
        if (potentiels[i] != NULL)
            nombreCandidats++;
    }
    //si il y a un seul candidat, le choix est évident
    SOMMET* candidats;
    if (nombreCandidats == 1)
    {
        for(int i=0; i<tmp; i++)
        {
            if (potentiels[i] != NULL)
                sommetChoisi = potentiels[i]->label;//valeur du sommet choisi              
        }
    }
    //si il y a plusieurs candidats, il faut les départager
    else if (nombreCandidats > 1)
    {   
        int parcours = 0;
        candidats = malloc(tmp*sizeof(SOMMET));
        if(candidats == NULL)
            printf("erreur d'allocation\n");
        //tous les candidats sont concentrés dans un vecteur
        for(int i=0; i<tmp; i++)
        {
            if (potentiels[i] != NULL)
            {
                candidats[parcours] = *potentiels[i];
                parcours++;
            }
        }
        //l'indice d'un candidat dans le vecteur est pris au hasard
        srand(time(NULL));
        sommetChoisi = candidats[rand()%parcours].label;
    }
    //free(candidats);
   return sommetChoisi;
}

void CreerBoard(int m, GRAPHE* monGraphe)
{    
    int problemSize = m*m;
    int connexions = 0;

    initialiserGraphe(monGraphe);
    for(int i=0;i < problemSize;i++)
    {
        ajouterSommet(monGraphe, 0);
    }
    //add arcs representing legal moves of the night on the board.
    //not oriented graph, because knight can move in every direction
    //The order in which the arcs are created is important for the squirrel method.
    for(int i=0;i < problemSize;i++)
    {
        connexions = 0;
        //Upper position right :
        if(!((i/m) < 2) && !((i%m) == m-1)){
            ajouterArc(monGraphe, i, i + 1 - 2*m, 0);  
            connexions++;}    
        //Left position up :
        if(!((i%m) <= 1) && !((i/m) == 0)){
            ajouterArc(monGraphe, i, i - 2 - m, 0);
            connexions++;} 
        //Left position down :
        if(!((i%m) <= 1) && !((i/m) == m-1)){
            ajouterArc(monGraphe, i, i - 2 + m, 0); 
            connexions++;}
        //Lower position right :
        if(!((i/m) >= m-2) && !((i%m) == m-1)){
            ajouterArc(monGraphe, i, i + 1 + 2*m, 0); 
            connexions++;}
        //Lower position left :
        if(!((i/m) >= m-2) && !((i%m) == 0)){
            ajouterArc(monGraphe, i,  i - 1 + 2*m, 0); 
            connexions++;}
        //Right position down :
        if(!((i%m) >= m - 2) && !((i/m) == m-1)){
            ajouterArc(monGraphe, i, i + 2 + m, 0);
            connexions++;}
        //Right position up :
        if(!((i%m) >= m - 2) && !((i/m) == 0)){
            ajouterArc(monGraphe, i, i + 2 - m, 0);
            connexions++;}
        //Upper position left :
        if(!((i/m) < 2) && !((i%m) == 0)){
            ajouterArc(monGraphe, i, i - 1 - 2*m, 0);  
            connexions++;}     
        changerInfoSommet (monGraphe, i, connexions);
    }
}
//Retranscription of the algorithm presented by Squirrel.
void WarnsdorffSquirrel (int m)
{
    //Retranscription de l'alogrithme pésenté par Squirrel dans
    //A Warnsdorff-Rule Algorithm for Knight's Tours on Square ChessBoards de 1996
    //Permet de trouver un CHEMIN hamiltonien pour le parcours du cavalier
    //Avec détermination de la prochaine case en cas d'égalité.

    //A = matrice contenant le chemin hamiltonien
    //B = matrice contenant le poids de chaque case
    //K = Tous les mouvements possibles
    //T = vecteur contenant l'ordre actuel de déplacement en cas d'égalité
    //i = variable de parcours des lignes du tableau
    //j = variable de parcours colonnes du tableau
    //k = variable de parcours de K et T
    //t = variable de parcours des permutations.
    //z = condition de fin de parcours
    //c = ordre dans lequel chaque case est visitée
    //uv = coordonnees de condition de changement de permutation
    //xy = coordonnées pour visiter les matrices A et B
    //xyP = coordonnées temporaires pour interagir avec la matrice B
    //xyPP = coordonnées temporaires pour determiner la futur case à visiter
    //uv* = tableau contenant la condition de permutation pour chaque valeur de mod8
    int *A, *B;
    int K[8][2] = { {-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1} };
    int T[8];
    int c;
    int i, j, k, t, z;
    int uv[2], xy[2], xyP[2], xyPP[2];
    int uvZero[5][2], uvUn[4][2], uvDeux[6][2], uvTrois[6][2];
    int uvQuatre[6][2], uvCinq[4][2], uvSix[6][2], uvSept[6][2];

    //initialisation des variables 
    A = malloc(m*m*sizeof(int));
    B = malloc(m*m*sizeof(int));
    for(int i=0;i<m*m;i++){
        A[i]=-1;
        B[i]=0;
    }
    c=-1;
    t=0;
    uv[0]=0;uv[1]=0;
    xy[0]=0;xy[1]=0;

    //initialisation des tableaux contenant les conditions de permutations
    //code érit de manière compacte pour ne pas prendre trop de place
    uvZero[0][0]=m-1;uvZero[0][1]=m-2; uvZero[1][0]=2;uvZero[1][1]=2; uvZero[2][0]=m-8;uvZero[2][1]=1; uvZero[3][0]=7;uvZero[3][1]=m-3; uvZero[4][0]=-1;uvZero[4][1]=-1;
    uvUn[0][0]=m-1;uvUn[0][1]=m-2; uvUn[1][0]=2;uvUn[1][1]=2; uvUn[2][0]=m-6;uvUn[2][1]=((m-1)/2) + 5; uvUn[3][0]=-1;uvUn[3][1]=-1;
    uvDeux[0][0]=6;uvDeux[0][1]=1; uvDeux[1][0]=3;uvDeux[1][1]=1; uvDeux[2][0]=m-15;uvDeux[2][1]=4; uvDeux[3][0]=10;uvDeux[3][1]=m-2; uvDeux[4][0]=5;uvDeux[4][1]=(m/2)-3; uvDeux[5][0]=-1;uvDeux[5][1]=-1;
    uvTrois[0][0]=m-1;uvTrois[0][1]=m-2; uvTrois[1][0]=m-6;uvTrois[1][1]=m; uvTrois[2][0]=2;uvTrois[2][1]=5; uvTrois[3][0]=m-10;uvTrois[3][1]=3; uvTrois[4][0]=((m-1)/2)+1;uvTrois[4][1]=m-2; uvTrois[5][0]=-1;uvTrois[5][1]=-1;
    uvQuatre[0][0]=m-1;uvQuatre[0][1]=m-2; uvQuatre[1][0]=2;uvQuatre[1][1]=2; uvQuatre[2][0]=m-8;uvQuatre[2][1]=1; uvQuatre[3][0]=10;uvQuatre[3][1]=m-5; uvQuatre[4][0]=13;uvQuatre[4][1]=(m/2)+1; uvQuatre[5][0]=-1;uvQuatre[5][1]=-1;
    uvCinq[0][0]=m-1;uvCinq[0][1]=m-2; uvCinq[1][0]=2;uvCinq[1][1]=2; uvCinq[3][0]=-1;uvCinq[3][1]=-1;
    if(m == 5%16)
    {
        uvCinq[2][0]=m-2;uvCinq[2][1]=((m-1)/2)-2;
    }
    else
    {
        uvCinq[2][0]=m-2;uvCinq[2][1]=((m-1)/2)-6;
    }
    uvSix[0][0]=6;uvSix[0][1]=1; uvSix[1][0]=3;uvSix[1][1]=1; uvSix[2][0]=m-10;uvSix[2][1]=1; uvSix[3][0]=10;uvSix[3][1]=m-2; uvSix[4][0]=3;uvSix[4][1]=(m/2)+4; uvSix[5][0]=-1;uvSix[5][1]=-1;
    uvSept[0][0]=m-1;uvSept[0][1]=m-2; uvSept[1][0]=m-6;uvSept[1][1]=m; uvSept[2][0]=2;uvSept[2][1]=5; uvSept[3][0]=m-6;uvSept[3][1]=3; uvSept[4][0]=((m-1)/2)+1;uvSept[4][1]=m-2; uvSept[5][0]=-1;uvSept[5][1]=-1;
    //initialisation de la matrice B
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
        {
             for(int k=0;k<8;k++)
            {
                xyP[0] = i + K[k][0];
                xyP[1] = j + K[k][1];  
                if(xyP[0] >= 0 && xyP[0] < m && xyP[1] >= 0 && xyP[1] < m)
                {
                    B[i*m+j] += 1;
                }
            }
            
        }
    //Boucle principale
    while(true)
    {
        A[xy[0]*m + xy[1]] = c;
        c = c + 1;
        z = 8;
        k = 0;

        //change move ordering if (x,y) == (u,v)
        if (xy[0] == uv[0] && xy[1] == uv[1])
        {
            switch(m%8)
            {
                case 0:
                for(int i=0;i<8;i++)
                    T[i] = zeroModHuit[t][i];
                uv[0]=uvZero[t][0];
                uv[1]=uvZero[t][1];
                break;
                case 1:
                for(int i=0;i<8;i++)
                    T[i] = unModHuit[t][i];
                uv[0]=uvUn[t][0];
                uv[1]=uvUn[t][1];
                break;
                case 2:
                for(int i=0;i<8;i++)
                    T[i] = deuxModHuit[t][i];
                uv[0]=uvDeux[t][0];
                uv[1]=uvDeux[t][1];
                break;
                case 3:
                for(int i=0;i<8;i++)
                    T[i] = troisModHuit[t][i];
                uv[0]=uvTrois[t][0];
                uv[1]=uvTrois[t][1];
                break;
                case 4:
                for(int i=0;i<8;i++)
                    T[i] = quatreModHuit[t][i];
                uv[0]=uvQuatre[t][0];
                uv[1]=uvQuatre[t][1];
                break;
                case 5:
                for(int i=0;i<8;i++)
                    T[i] = cinqModHuit[t][i];
                uv[0]=uvCinq[t][0];
                uv[1]=uvCinq[t][1];
                break;
                case 6:
                for(int i=0;i<8;i++)
                    T[i] = sixModHuit[t][i];
                uv[0]=uvSix[t][0];
                uv[1]=uvSix[t][1];
                break;
                case 7:
                for(int i=0;i<8;i++)
                    T[i] = septModHuit[t][i];
                uv[0]=uvSept[t][0];
                uv[1]=uvSept[t][1];
                break;
            }        
            t++;
        }
        //On parcours les huit directions possibles pour le cavalier. On determine la direction
        //qui soit a le poids le plus faible et qui est la première dans dans l'ordre déterminé.
        while(k<8)
        {
            //Attention que les valeurs dans T sont comptées à partir de 1. Il faut donc diminuer de 1 pour avoir les vlaeurs justes
            xyP[0] = xy[0] + K[T[k]-1][0];
            xyP[1] = xy[1] + K[T[k]-1][1];
            if(xyP[0] >= 0 && xyP[0] < m && xyP[1] >= 0 && xyP[1] < m && A[xyP[0]*m + xyP[1]] == -1)
            {
                B[xyP[0]*m + xyP[1]] -= 1;
                if(B[xyP[0]*m + xyP[1]] < z)
                {
                    xyPP[0] = xyP[0];
                    xyPP[1] = xyP[1];
                    z = B[xyP[0]*m + xyP[1]];
                }
            }
            k++; 
        }
        //next square
        if(z == 8)
            break;
        else
        {
            xy[0] = xyPP[0];
            xy[1] = xyPP[1];
        }
        /*printf("valeur de c : %d\n",c);
        printf("valeur de la case : %d\n",xy[0]*m+xy[1]);*/
    }
    if(TestSquirrel(A, B, m))
        printf("Chemin Trouve");
    else
        printf("Erreur");
    printf("\nSquirell termine\n");
}
bool TestSquirrel(int* A, int* B, int m)
{
    int K[8][2]={{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
    int parcouru = A[0];
    int recherche = 0;
    int tmpRecherche = 0;
    bool trouve;
    int k = 0;
    int x,y;

    for(int i=0; i < m*m ;i++)
    {
        B[i] = 0;
    }
    //on parcours tout le tableau A, dans l'ordre de passage du cavalier
    //Si on trouve la case suivante et qu'elle n'a pas encore été visitée, on marque dans B que la case actuelle a été visitée
    //Et on va à la case suivante.
    while(parcouru < m*m - 2)
    {
        printf("Verifparcouru : %d\n",parcouru);
        trouve = false;
        tmpRecherche = recherche;
        k=0;
        while(!trouve && k < 8)
        {
            tmpRecherche += K[k][0]*m;
            tmpRecherche += K[k][1];
            x = tmpRecherche/m + K[k][0]*m;
            y = tmpRecherche%m + K[k][1];
            if(x >= 0 && x/m < m && y >= 0 && y%m < m)
            {
                printf("dans la cond x : %d, y : %d\n",x,y);

            printf("tmprecherche : %d\n",tmpRecherche);
                printf("A : %d\n",A[tmpRecherche]);
                if (A[tmpRecherche] == parcouru+1)
                {
                    trouve = true;
                    recherche=tmpRecherche;
                    //B[tmpRecherche] = 1;
                }
            }
           
            k++;
        }
        if(!trouve)
            return false;
        parcouru++;
    }
    return true;
}