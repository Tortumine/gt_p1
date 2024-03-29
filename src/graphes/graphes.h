//graphe interface by M. Rigo.

#ifndef REPRESENTMATRIX_GRAPHES_H
#define REPRESENTMATRIX_GRAPHES_H

//#endif //REPRESENTMATRIX_GRAPHES_H

#define MAX 10000

struct eltadj {
    int dest;
    int info;
    struct sommet *cible;
    struct eltadj *suivant;
};

struct sommet {
    int label;
    int info;
    struct sommet *suivant;
    struct eltadj *adj;
};

struct graphe {
    int nbS;
    int nbA;
    int maxS;
    struct sommet *premierSommet;
    struct sommet *dernierSommet;
};

typedef struct graphe GRAPHE;
typedef struct sommet SOMMET;
typedef struct eltadj ELTADJ;

void initialiserGraphe(GRAPHE *);

int ajouterSommet(GRAPHE *, int info);

void changerInfoSommet (GRAPHE *g, int sommet, int infos);

int ajouterArc(GRAPHE *, int a, int b, int info);

int supprimerSommet(GRAPHE *, int label);

int supprimerArc(GRAPHE *, int a, int b);

void supprimerGraphe(GRAPHE *);

void afficherGraphe(GRAPHE *);

int lireFichier(char *nomf, GRAPHE *);

#endif