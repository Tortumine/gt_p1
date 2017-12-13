//Ecrit par Sadzot Antoine
//Génération de parcours hamiltoniens respectant les règles du problème du cavalier
//A programme : Warnsdorff's rule et algorithmes déterministes pour la génération de chemines
//Par convention, tous les chemins commencent dans la case en haut à gauche, la case 0

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "warnsdorf.h"
#include "../graphes/graphes.h"
#include "../graphes/graphes.c"

//fonctions propres au fichier
bool TestValideRect(int* A, int n, int m);
void PrintBoard(int* A, int n, int m);


//Génération de chemin hamiltonnien représentant les mouvements du cavalier sur un échiquier carré
//Graphe stocké sous forme de matrice
//Basé sur l'heurisitque de Warnsdorff
//algorithme inspiré de celui de Squirrel car simple et rapide. Au détriment d'un stockage par l'interface "graphe"
//départage aléatoire entre les cellules de même poids
//m = taille d'un côté de l'échiquier
//Renvoie vrai si le chemin généré est valide. Renvoie faux sinon
bool WarnsdorffClassique(int m)
{
    int *A,*B;//A contient le chemin généré. B contient le poids de chaque cellule
    int pos=0;//contient l'élément à visiter dans le vecteur A
    int iter=0;//Numero de passage du chemin des cellules stockées dans A
    int moinsDePoids;//Poids de la potentielle prochaine cellule
    int k;//parcours de la matrice K
    int x,y,xP,yP;//Transcription en coordonnées des indices des Elements A
    //Matrice contenant les mouvements du cavalier
    int K[8][2] = { {-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1} };
    int tmpPos[8];//contient les cellules candidates de même poids
    int parcoursArray = 0; //variable temporaire pour parcourir le tableau des directions possibles
    A = malloc(m*m*sizeof(int));
    B = malloc(m*m*sizeof(int));
    for(int i=0;i<m*m;i++){
        A[i]=-1;
        B[i]=0;
    }
    //initialisation de B
    for(int i=0;i<m*m;i++)
    {
        x = i/m;
        y = i%m;
        for(int k=0;k<8;k++)
        {
            xP = x + K[k][0];
            yP = y + K[k][1];  
            if(xP >= 0 && xP < m && yP >= 0 && yP < m)
            {
                B[i] += 1;
            }
        }
    } 
    //boucle principale. S'arrête quand toutes les cellules ont été visitées
    //Ou "break" quand il n'est plus possible d'avancer
    while(iter < m*m)
    {
        A[pos] = iter;
        B[pos] = 0;
        iter++;
        moinsDePoids = 9;
        k=0;
        
        //réinitialisation du vecteur temporaire des candidats
        for(int i=0; i <= parcoursArray; i++)
            tmpPos[i] = -1;   
        parcoursArray = 0;

        //Sélection des candidats dans les huit directions possibles 
        while(k<8)
        {
            //conversion des indices en coordonnées
            x = (pos/m + K[k][0])*m;
            y = pos%m + K[k][1];   
            if((x/m >= 0) && (x/m < m) && (y >= 0) && (y < m) && A[x+y] == -1)
            {
                B[x+y] -= 1;
                //stockage des cellules de même poids
                if(B[x+y] == moinsDePoids)
                {
                    parcoursArray++;
                    tmpPos[parcoursArray] = x+y;
                }
                //si une cellule a un poids plus faible, on réinitialise le vecteur
                else if(B[x+y] < moinsDePoids)
                {
                    for(int i=0; i < 8; i++)
                    {
                        tmpPos[i] = -1;                      
                    }
                    tmpPos[0] = x+y;
                    moinsDePoids=B[x+y];
                    parcoursArray=0;
                }
            }
            k++; 
        }
        //Aucun candidat possible, on quitte la boucle
        if(moinsDePoids == 9)
            break;
        //Un candidat unique, c'est la future cellule visitée
        if(parcoursArray == 0)
            pos = tmpPos[0];
        //Plusieurs candidats possibles. On les départage de aléatoirement
        else
        {
            do
            {
                pos = tmpPos[rand()%(parcoursArray+1)];
            }while(pos == -1);
        }
    }
    //On teste la validité du labyrinthe
    bool resultat = TestValideRect(A,m, m);
    
    //Bon ou mauvais, on imprime ce qu'on a
    PrintBoard(A, m, m);
    
    free(A);
    free(B);
    if(resultat)
        return true;
    else
        return false;
}
//Génération de chemin hamiltonnien représentant les mouvements du cavalier sur un échiquier rectangulaire
//Graphe stocké sous forme de matrice
//n = nombre de lignes de l'échiquier
//m = nombre de colonnes de l'échiquier
//A = matrice contenant l'ordre de parcours
//Renvoie vrai si le chemin généré est valide. Renvoie faux sinon
bool WarnsdorffNFoisM(int *A, int n,int m)
{
    int *B;//B contient le poids de chaque cellule
    int pos=0;//contient l'élément à visiter dans le vecteur A
    int iter=0;//Numero de passage du chemin des cellules stockées dans A
    int moinsDePoids;//Poids de la potentielle prochaine cellule
    int k;//parcours de la matrice K
    int x,y,xP,yP;//Transcription en coordonnées des indices des Elements A
    //Matrice contenant les mouvements du cavalier
    int K[8][2] = { {-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1} };
    int tmpPos[8];//contient les positions des candidats
    int parcoursArray = 0;//variable temporaire pour parcourir le tableau des directions possibles

    B = malloc(n*m*sizeof(int));
    for(int i=0;i<n*m;i++){
        A[i]=-1;
        B[i]=0;
    }
    //initialisation de B
    for(int i=0;i<n*m;i++)
    {
        x = i/m;
        y = i%m;
        for(int k=0;k<8;k++)
        {
            xP = x + K[k][0];
            yP = y + K[k][1];  
            if(xP >= 0 && xP < n && yP >= 0 && yP < m)
            {
                B[i] += 1;
            }
        }
    }
    //On parcourt toutes les cellules. A moins qu'un "break" ne se produise
    //Si on ne trouve plus de candidat potentiel 
    while(iter < n*m)
    {
        A[pos] = iter;
        B[pos] = 0;
        iter++;
        moinsDePoids = 9;
        k=0;

        //réinitialisation du vecteur temporaire des candidats
        for(int i=0; i <= parcoursArray; i++)
            tmpPos[i] = -1;  
        parcoursArray = 0;

        //Sélection des candidats dans les huit directions possibles 
        while(k<8)
        {
            //conversion des indices de A en coordonnées
            x = (pos/m + K[k][0])*m;
            y = pos%m + K[k][1];   
            if((x/m >= 0) && (x/m < n) && (y >= 0) && (y < m) && A[x+y] == -1)
            {
                B[x+y] -= 1;
                //On ajoute les candidats de même poids
                if(B[x+y] == moinsDePoids)
                {
                    parcoursArray++;
                    tmpPos[parcoursArray] = x+y;
                }
                //si on trouve un candidat de poids plus petit,
                //On réinitialise le vecteur 
                else if(B[x+y] < moinsDePoids)
                {
                    for(int i=0; i < 8; i++)
                    {
                        tmpPos[i] = -1;                      
                    }
                    tmpPos[0] = x+y;
                    moinsDePoids=B[x+y];
                    parcoursArray=0;
                }
            }
            k++; 
        }
        //Aucun cnadidat trouvé
        if(moinsDePoids == 9)
            break;
        //Un seul candidat trouvé
        if(parcoursArray == 0)
            pos = tmpPos[0];
        //Plusieurs candidats de même poids. On les départage aléatoirement
        else
        {
            do
            {
                pos = tmpPos[rand()%(parcoursArray+1)];
            }while(pos == -1);
        }
        
    }
    //A la fin, on teste le résultat
    bool resultat = TestValideRect(A, n, m);

    //Bon ou mauvais, on imprime ce qu'on a
    PrintBoard(A, m, m);

    free(B);
    if(resultat)
        return true;
    else
        return false;
}
//Permet de tester la validité du chemin hamiltonien
//A est la matrice contenant l'ordre de parcours
//n est le nombre de lignes
//m est le nombre de colonnes
//Renvoie vrai si le chemin soumis est correct. Renvoie faux sinon
bool TestValideRect(int* A, int n, int m)
{
    //Vecteur de déplacements possibles du cavalier
    int K[8][2]={{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
    int parcouru = A[0];//variable qui contient la valeur de la cellule de A visitée
    int recherche = 0;//variable de parcours de A. Suit le chemin
    int tmpRecherche = 0;//variable temporaire pour la recherche de la prochaine cellule
    bool trouve;//cellule suivant trouvée
    int k = 0;//parcours de K

    //on parcourt tout le tableau A, dans l'ordre de passage du cavalier
    //Si on trouve la case contenant la valeur suivante, on s'y déplace
    //Si on ne la trouve pas, le chemin n'est pas valide
    while(parcouru < n*m-1)
    {
        trouve = false;
        
        k=0;
        while(!trouve && k < 8)
        {
            tmpRecherche = recherche;
            tmpRecherche += K[k][0]*m;
            tmpRecherche += K[k][1];
            if((tmpRecherche/m >= 0) && (tmpRecherche/m < n) && (tmpRecherche%m >=0) && (tmpRecherche%m < m))
            {
                if (A[tmpRecherche] == parcouru+1)
                {
                    trouve = true;
                    recherche=tmpRecherche;
                }
            }
            k++;
        }
        if(!trouve)
        {
            return false;
        }
        parcouru++;
    }
    return true;
}
//Retranscription de l'algorithme de Douglas Squirrel, inspiré de l'heurisitque de Warnsdorff
//Pour un échiquier carré de taille m*m, génère un chemin hamiltonien 
//Correspondant au problème du cavalier
//Le départage entre des cases de même poids est déterminé selon la dimension de l'échiquier
//Renvoie vrai si le chemin généré est valide. Renvoie faux sinon
bool Squirrel (int m)
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
    //uv[][]* = matrices contenant la condition de permutation pour chaque valeur de mod8
    int *A, *B;
    int K[8][2] = { {-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1} };
    int T[8];
    int c;
    int i, j, k, t, z;
    int uv[2], xy[2], xyP[2], xyPP[2];
    int uvZero[5][2], uvUn[4][2], uvDeux[6][2], uvTrois[6][2];
    int uvQuatre[6][2], uvCinq[4][2], uvSix[6][2], uvSept[6][2];

    //Ordre de parcours des cellules pour tous les types de tableaux
    int zeroModHuit[5][8] = {{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,1,8,6,7,3,4,2},{5,1,3,4,2,6,7,8},{2,1,4,3,5,6,7,8}};
    int unModHuit[4][8] = {{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,1,3,2,4,6,7,8},{3,2,4,8,1,7,6,5}};
    int deuxModHuit[6][8] = {{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,4,1,3,2,6,7,8},{5,2,4,3,1,6,7,8},{8,5,6,4,7,1,2,3},{1,5,7,4,6,8,2,3}};
    int troisModHuit[6][8] = {{3,4,6,2,5,7,1,8},{4,2,6,8,1,3,5,7},{8,6,5,1,2,3,4,7},{5,1,8,6,7,3,4,2},{6,1,8,2,5,4,3,7},{7,1,6,4,2,5,3,8}};
    int quatreModHuit[6][8] = {{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,1,8,6,7,3,4,2},{5,1,3,4,2,6,7,8},{8,6,7,5,3,4,2,1},{7,8,5,6,3,4,2,1}};
    int cinqModHuit[4][8] = {{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,1,3,2,4,6,7,8},{1,5,2,3,4,6,7,8}};
    int sixModHuit[6][8] = {{3,4,2,6,1,5,7,8},{8,7,6,4,2,1,3,5},{5,4,1,3,2,6,7,8},{5,2,4,3,1,6,7,8},{8,5,6,4,7,1,2,3},{1,2,4,5,3,6,7,8}};
    int septModHuit[6][8] ={{3,4,6,2,5,7,1,8},{4,2,6,8,1,3,5,7},{8,6,5,1,2,3,4,7},{5,1,8,6,7,3,4,2},{6,1,8,2,5,4,3,7},{6,1,3,5,7,2,8,4}};

    //initialisation des tableaux contenant les conditions de permutations
    //code compacte pour ne pas prendre trop de place
    uvZero[0][0]=m-1;uvZero[0][1]=m-2; uvZero[1][0]=2;uvZero[1][1]=2; uvZero[2][0]=m-8;uvZero[2][1]=1; uvZero[3][0]=7;uvZero[3][1]=m-3; uvZero[4][0]=-1;uvZero[4][1]=-1;
    uvUn[0][0]=m-1;uvUn[0][1]=m-2; uvUn[1][0]=2;uvUn[1][1]=2; uvUn[2][0]=m-6;uvUn[2][1]=((m-1)/2) + 5; uvUn[3][0]=-1;uvUn[3][1]=-1;
    uvDeux[0][0]=6;uvDeux[0][1]=1; uvDeux[1][0]=3;uvDeux[1][1]=1; uvDeux[2][0]=m-15;uvDeux[2][1]=4; uvDeux[3][0]=10;uvDeux[3][1]=m-2; uvDeux[4][0]=5;uvDeux[4][1]=(m/2)-3; uvDeux[5][0]=-1;uvDeux[5][1]=-1;
    uvTrois[0][0]=m-1;uvTrois[0][1]=m-2; uvTrois[1][0]=m-6;uvTrois[1][1]=m; uvTrois[2][0]=2;uvTrois[2][1]=5; uvTrois[3][0]=m-10;uvTrois[3][1]=3; uvTrois[4][0]=((m-1)/2)+1;uvTrois[4][1]=m-2; uvTrois[5][0]=-1;uvTrois[5][1]=-1;
    uvQuatre[0][0]=m-1;uvQuatre[0][1]=m-2; uvQuatre[1][0]=2;uvQuatre[1][1]=2; uvQuatre[2][0]=m-8;uvQuatre[2][1]=1; uvQuatre[3][0]=10;uvQuatre[3][1]=m-5; uvQuatre[4][0]=13;uvQuatre[4][1]=(m/2)+1; uvQuatre[5][0]=-1;uvQuatre[5][1]=-1;
    uvCinq[0][0]=m-1;uvCinq[0][1]=m-2; uvCinq[1][0]=2;uvCinq[1][1]=2;uvCinq[2][0]=m-2;uvCinq[2][1]=((m-1)/2)-6; uvCinq[3][0]=-1;uvCinq[3][1]=-1;
    uvSix[0][0]=6;uvSix[0][1]=1; uvSix[1][0]=3;uvSix[1][1]=1; uvSix[2][0]=m-10;uvSix[2][1]=1; uvSix[3][0]=10;uvSix[3][1]=m-2; uvSix[4][0]=3;uvSix[4][1]=(m/2)+4; uvSix[5][0]=-1;uvSix[5][1]=-1;
    uvSept[0][0]=m-1;uvSept[0][1]=m-2; uvSept[1][0]=m-6;uvSept[1][1]=m; uvSept[2][0]=2;uvSept[2][1]=5; uvSept[3][0]=m-6;uvSept[3][1]=3; uvSept[4][0]=((m-1)/2)+1;uvSept[4][1]=m-2; uvSept[5][0]=-1;uvSept[5][1]=-1;
    
    //initialisation des variables 
    A = malloc(m*m*sizeof(int));
    B = malloc(m*m*sizeof(int));
    for(int i=0;i<m*m;i++)
    {
        A[i]=-1;
        B[i]=0;
    }
    c=0;
    t=0;
    uv[0]=1;uv[1]=1;
    xy[0]=0;xy[1]=0;
        
    //initialisation de la matrice B
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
        {
             for(int k=0;k<8;k++)
            {
                xyP[0] = i + K[k][0];
                xyP[1] = j + K[k][1];  
                if(xyP[0] >= 0 && xyP[0] < m && xyP[1] >= 0 && xyP[1] < m)
                    {B[i*m+j] += 1;  }
            }
        }
    //Boucle principale. Parcours de toutes les cellules si tout se passe bien
    while(true)
    {
        A[xy[0]*m + xy[1]] = c;
        B[xy[0]*m + xy[1]] = 0;
        c = c + 1;
        z = 9;
        k = 0;

        //Si la case visitée est une case particulière, on change l'ordre de parcours
        //Les valuers de xy sont augemntées de 1 car les valeurs renseignées commencent à 1 et pas 0 
        if ((xy[0] + 1 == uv[0]) && (xy[1] + 1 == uv[1]))
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
        //On parcourt les huit directions possibles pour le cavalier. On determine la direction
        //qui a le poids le plus faible et qui est la première dans dans l'ordre déterminé.
        while(k<8)
        {
            //Attention que les valeurs dans T sont comptées de 1 à 8. Il faut donc diminuer de 1 pour avoir les vlaeurs justes
            xyP[0] = xy[0] + K[T[k]-1][0];
            xyP[1] = xy[1] + K[T[k]-1][1];
            if(xyP[0] >= 0 && xyP[0] < m && xyP[1] >= 0 && xyP[1] < m && A[xyP[0]*m + xyP[1]] == -1)
            {
                B[xyP[0]*m + xyP[1]] -= 1;
                if(B[xyP[0]*m + xyP[1]] < z)
                {
                    xyPP[0] = xyP[0];
                    xyPP[1] = xyP[1];
                    z=B[xyP[0]*m + xyP[1]];
                }
            }
            k++; 
        }
        //Si aucun candidat n'a été trouvé, c'est la fin de l'algorithme
        if(z == 9)
            break;
        //parcours de la cellule suivante
        xy[0] = xyPP[0];
        xy[1] = xyPP[1];
    }
    //Valide ou non, on imprime le résultat
    PrintBoard(A, m, m);

    if(TestValideRect(A,m, m))
    {
        free(A);
        free(B);
        return true;
    }
    else
    {
        free(A);
        free(B);
        return false;
    }  
}
//Utilisation de l'algorithme de Shun-Shii Lin et Chung-Liang Wei
//Dans le cas où l'échiquier comporte trois lignes et m colonnes
//Renvoie vrai si le chemin généré est valide. Renvoie faux sinon
bool ArbitraireTroisFoisM(int m)
{
   //Algorithme pour trouver un tour du cavalier par Shun-Shii Lin
   //Implementation pour un échiquier de taille 3*m
   //Basé en partie sur la fonction WarnsdorffNFoisM

   int *A = malloc(m*3*sizeof(int));//Vecteur repésentant l'échiquier
   int iter=0;//variable utilisée pour la génération de chemin pour m<=12

   //aucun parcours n'existe pour ces dimensions d'échiquiers
   if(m<4 || m==5 || m==6)
   {
       printf("Il est impossible de trouver un chemin hamiltonnien dans ce graphe\n");
       free(A);
       return false;
   }
   //pour un échiquier plus petit que 10 et ne satisfaisant pas les conditions précédentes,
   //Le parcours est généré en une fois
   else if(m <= 12)
   {
       //plusieurs générations aléatoires peuvent être nécessaires
       //avant de trouver un chemin correct
        while(!WarnsdorffNFoisM(A, 3, m) && iter < 100)
        {iter++;} 
        free(A);
        if(iter == 100)
            return false;
        else
            return true;  
   }

   //Pour m>12, on utilise la méthode du diviser pour régner
   //Un échiquier "principal" de taille 9 =< m <= 12 et x échiquiers de taille 4.

   int k=0;//taille de l'échiquier "principal"
   int* tmp;//tableau temporaire pour l'ajout des petits échiquiers
   int echiquiers=0;//nombre d'échiquiers 3*4 à rajouter
   int x,y;//coordonnées de cases
   int zValeur;//valeur de la case de l'échiquier de droite qui démarre la connection
   //un chemin hamiltonien est codé en dur pour les petits échiquiers
   //Deux vecteurs pour deux sens de parcours différents
   int troisFoisQuatreOrd[12]= {0,3,6,9,11,8,1,4,2,5,10,7};
   int troisFoisQuatreInver[12]= {11,8,5,2,0,3,10,7,9,6,1,4};
   int intermediaire[12];

   k = ((m-9)%4)+9;//Détermination de k, au départ Compris entre 9 et 12
   echiquiers=(m-k)/4;//Echiquiers est le nombre de petits echiquiers
   tmp = malloc(3*k*sizeof(int));

   //On génére l'échiquier "principal" de taille 9<=m<=12
   iter=0;
   while(!WarnsdorffNFoisM(tmp, 3, k) && iter < 100)
        {iter++;}  
    if(iter == 100)
    {
        printf("Erreur de génération du chemin\n");
        free(A);
        free(tmp);
        return false;  
    }
   //On ajoute l'échiquier généré dans le vecteur A 
   for(int i=0; i<3*k;i++)
   {
       x=i/k;
       y=i%k;
       A[x*m+y] = tmp[i];
   }  
   //On ajoute chaque échiquier 3*4 l'un après l'autre
   for(int j=0; j < echiquiers;j++)
   {
        k+=(j*4);
        //On choisit entre deux cases précises celle qui va "précéder" dans l'ordre de parcours
        //le nouvel échiquier 3*4. La seconde case sera la case de retour
        if(A[2*m+(k-1)] > A[k-2])
        {
            zValeur=A[k-2];
            for(int i=0;i<12;i++)
            {
                intermediaire[i] = troisFoisQuatreInver[i]+zValeur+1;
            }
        }
        else
        {
            zValeur=A[2*m+(k-1)];
            for(int i=0;i<12;i++)
            {
                intermediaire[i] = troisFoisQuatreOrd[i]+zValeur+1;
            }
        } 
        //ajout de l'échiquier au tableau principal
        for(int i=0; i<12;i++)
        {
            x=i/4;
            y=i%4;
            A[x*m+(y+k)] = intermediaire[i];
        }
        //modification des valeurs de l'ordre parcours dans le grand échiquier
        for(int i=0;i<3*k;i++)
        {
            x=i/(k);
            y=i%(k);
            if(A[x*m+y] > zValeur)
                A[x*m+y] += 12; 
        }
   }
   PrintBoard(A,3,m);

   if(TestValideRect(A, 3, m))
   {
       free(A);
       free(tmp);
       return true;
   }
   else
   {
       free(A);
       free(tmp);
       return false;
   }
} 
//imprime dans un fichier "chemin.txt" un chemin valide sous la forme d'un échiquier
//dont les cases sont numérotées dans leur ordre de passage
//A contient la matrice
//n est le nombre de lignes
//m est le nombre de colonnes
void PrintBoard(int* A, int n, int m)
{
    //N'imprime pas les échiquier de plus de 9999 cellules pour une question de dimensions de cellules.
    //Le parcours commence à Zero, en haut à gauche
    FILE *fp;
    if(n*m > 9999)
    {
        printf("Echiquier de taile %d * %d trop grand pour être enregistré",n,m);
        return;
    }

    fp=fopen("Chemin.txt","w");
    if(fp == NULL)
    {
        printf("Erreur ouverture du fichier");
        return;
    }
    fprintf(fp,"Echiquier de taille %d * %d\n",n,m);
   
    int tmptest = 0;
    for(int i=0; i<3; i++)
    {       
        for(int j=0; j<m; j++)
        {
            fprintf(fp," ----");
        }
        fprintf(fp,"\n");
        for(int j=0; j<m; j++)
        {
            fprintf(fp,"|%4d",A[tmptest]);
            tmptest++;
        }
        fprintf(fp,"|\n");
    }
    for(int j=0; j<m; j++)
    {
        fprintf(fp," ----");
    }
    fprintf(fp,"\n");

    fclose(fp);
}