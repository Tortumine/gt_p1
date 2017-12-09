#include <stdio.h>
#include <stdlib.h>
#include "warnsdorf.h"
#include "../graphes/graphes.h"

void CreerBoard(int m, GRAPHE* monGraphe);
void DiminuerPoidVoisins(SOMMET* monSommet);
int DeterminerSuivant(SOMMET* monSommet);


void WarnsdorfClassique(int m)
{
    GRAPHE* monGraphe;
    int* parcours;
    //create the grpahe representing the board and the legal moves
    monGraphe = malloc(m*m*sizeof(GRAPHE));
    CreerBoard(m, monGraphe);
    //creating the structure that will hold the tour
    parcours = malloc(m*m*sizeof(int));
    for(int i=0; i<(m*m); i++)
    {
        parcours[i] = -1
    }
    size_t increment = 0; //variable d'increment pour savoir combien de cases ont été visitées
    size_t visite = 0; //indice de la case visitée.
    SOMMET* monSommet = monGraphe->premierSommet;
    while ((!parcoursCorrect()) && (increment < (m*m)))
    {
        parcours[visite] = increment;
        monSommet->infos = 0;
        DiminuerPoidsVoisins(monSommet);
        visite = DeterminerSuivant(monSommet);
        increment++;
    }
}
void DiminuerPoidVoisins(SOMMET* monSommet)
{
    ELTADJ *adj;
    adj = monSommet->adj;
    /* on cherche le sommet donné*/
    while (adj != NULL)
    {
        if (adj->cible->infos != 0)
            adj->cible->infos--;
        adj = adj->suivant;
    }
}
int DeterminerSuivant(SOMMET* monSommet)
{
    ELTADJ *adj;
    adj = monSommet->adj;
    SOMMET* potentiels[8] = NULL;//contient les candidats pour avancer
    int tmp = 0;
    int choix = 9;//plus petits poids des sommets potentiels
    
    //creation de la liste avec tous les voisins
    while (adj != NULL)
    {
        if (adj->cible->infos != 0)
            potentiels[tmp] = adj->cible->infos;
        adj = adj->suivant;
        tmp++;
    }
    for(int i=0; i<tmp; i++)
    {
        //Every candidate with a weight higher than the lowest determined is rejected
        //If a candidate has a lower weight, "choix" is changed and previous candidates are reexamined
        if (potentiels[i].cible->infos > choix)
            potentiels[i] = NULL;
        else if (potentiels[i].cible->infos < choix)
        {
            choix = potentiels[i].cible->infos
            for(int j=0; j < i-1; j++)
            {
                if (potentiels[j].cible->infos > choix)
                    potentiels[i] = NULL;
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
    if (nombreCandidats == 1)
    {
        for(int i=0; i<tmp; i++)
        {
            if (potentiels[i] != NULL)
                sommetChoisi = potentiels[i].cible->label;//valeur du sommet choisi
                monSommet = potentiels[i];//le pointeur de sommet pointe vers le nouveau sommet choisi
        }
    }
    //si il y a plusieurs candidats, il faut les départager
    else if (nombreCandidats > 1)
    {
        SOMMET* candidats;
        int parcours = 0;
        candidats = malloc(tmp*sizeof(SOMMET));
        //tous les candidats sont concentrés dans un vecteur
        for(int i=0; i<tmp; i++)
        {
            if (potentiels[i] != NULL)
            {
                candidats[parcours] = potentiels[i];
                parcours++;
            }
        }
        //l'indice d'un candidat dans le vecteur est pris au hasard
        srand(time(NULL));
        sommetChoisi = candidats[rand()%parcours].label;
        monSommet = candidats[sommetChoisi];
    }
    free(candidats);
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
            ajouterArc(monGraphe, i, i + 1 - 2*n, 0);  
            connexions++;}    
        //Left position up :
        if(!((i%m) <= 1) && !((i/m) == 0)){
            ajouterArc(monGraphe, i, i - 2 - n, 0);
            connexions++;} 
        //Left position down :
        if(!((i%m) <= 1) && !((i/m) == n-1)){
            ajouterArc(monGraphe, i, i - 2 + n, 0); 
            connexions++;}
        //Lower position right :
        if(!((i/m) >= n-2) && !((i%m) == m-1)){
            ajouterArc(monGraphe, i, i + 1 + 2*n, 0); 
            connexions++;}
        //Lower position left :
        if(!((i/m) >= n-2) && !((i%m) == 0)){
            ajouterArc(monGraphe, i,  i - 1 + 2*n, 0); 
            connexions++;}
        //Right position down :
        if(!((i%m) >= m - 2) && !((i/m) == n-1)){
            ajouterArc(monGraphe, i, i + 2 + n, 0);
            connexions++;}
        //Right position up :
        if(!((i%m) >= m - 2) && !((i/m) == 0)){
            ajouterArc(monGraphe, i, i + 2 - n, 0);
            connexions++;}
        //Upper position left :
        if(!((i/m) < 2) && !((i%m) == 0)){
            ajouterArc(monGraphe, i, i - 1 - 2*n, 0);  
            connexions++;}     
        changerInfoSommet (monGraphe, i, connexions);
    }
}