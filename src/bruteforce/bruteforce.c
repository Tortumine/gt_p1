//
// Created by tortumine on 8/12/17.
//



/***
 * Created by tortumine on 8/12/17.
 *
 *      ____             _       _____
 *     | __ ) _ __ _   _| |_ ___|  ___|__  _ __ ___ ___
 *     |  _ \| '__| | | | __/ _ \ |_ / _ \| '__/ __/ _ \
 *     | |_) | |  | |_| | ||  __/  _| (_) | | | (_|  __/
 *     |____/|_|   \__,_|\__\___|_|  \___/|_|  \___\___|
 *
 *
 *     Trois types de fonction sont présentes ici:
 *          -Parcours récurcif   (bf_close_rec, bf_open_rec)
 *          -Initilisation de la recurcuion  (bf_open_rec, bf_close_rec)
 *          -Wrappers qui renvoient à l'utilisateur une sortie structurée    (BruteForceChemins, BruteForceCircuits)
 *     
 *     
 */



#include <printf.h>
#include <omp.h>
#include "bruteforce.h"

/***
 * Wrapper de calcul des chemins hamiltoniens (cavalier)
 *
 * Cette fonction appelle le parcours récurcif de l'échequier
 * pour chaque case de départ possible. Afin d'optimiser les
 * temps de calcul OpenMP est utilisé pour le multithreading.
 *
 * L'évolution du calcul est affichée en temps réel dans le terminal.
 *
 * @param m nombre de colonnes
 * @param n nombre de lignes
 * @param monGraphe graphe des cases accessibles
 */
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

/***
 * initilaisation du multithreading
 */
#pragma omp parallel
    {
        thread_id = omp_get_thread_num();

        /***
         * Quelques infos pour l'utilisateur
         */
        if ( thread_id == 0 ) {
            nb_threads = omp_get_num_threads();
            printf("Le calcul se fait sur %d threads\n",nb_threads);
            printf("Progression: % 2d/%d\t\tSolutions: %d",progress,grid,tmp);
            fflush(stdout);
        }

/***
* Boucle parallelisée
*/
#pragma omp for
        for(i=0;i<m*n;i++)
        {
            result[i]= bf_open_init(n, m, monGraphe, i);
            tmp=tmp+result[i];

            /***
             * Mise à jour des infos (progression du calcul)
             */
            progress=progress+(1/(grid));
            progress++;
            printf("\rProgression: % 2d/%d\t\tSolutions: %d",progress,grid,tmp);
            fflush(stdout);
        }
    }

    /***
     * Affichage du résultat
     */
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


/***
 * Wrapper de calcul des circuits hamiltoniens (cavalier)
 *
 * Cette fonction appelle le parcours récurcif de l'échequier
 * pour chaque case de départ possible. Afin d'optimiser les
 * temps de calcul OpenMP est utilisé pour le multithreading.
 *
 * L'évolution du calcul est affichée en temps réel dans le terminal.
 *
 * @param m nombre de colonnes
 * @param n nombre de lignes
 * @param monGraphe graphe des cases accessibles
 */
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

/***
 * initilaisation du multithreading
 */
#pragma omp parallel
    {
        thread_id = omp_get_thread_num();

        /***
        * Quelques infos pour l'utilisateur
        */
        if (thread_id == 1) {
            nb_threads = omp_get_num_threads();
            printf("Le calcul se fait sur %d threads\n", nb_threads);
            printf("Progression: % 2d/%d\t\tSolutions: %d", progress, grid, tmp);
            fflush(stdout);
        }

/***
* Boucle parallelisée
*/
#pragma omp for
        for (i = 0; i < m * n; i++) {
            result[i] = bf_close_init(n, m, monGraphe, i);
            tmp = tmp + result[i];

            /***
             * Mise à jour des infos (progression du calcul)
             */
            progress = progress + (1 / (grid));
            progress++;
            printf("\rProgression: % 2d/%d\t\tSolutions: %d", progress, grid, tmp);
            fflush(stdout);
        }
    }
    /***
    * Affichage du résultat
    */
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


/***
 * ----------------------------------------------------------
 *                 Fonctions d'appel de recurcion
 * ----------------------------------------------------------
 */

/***
 * Fonction d'initialisation de la recurcion "open knight's tour"
 *
 * Cette fonction initialise la fonction récurcive qui parcours l'arbre
 * à la recherche de chemins hamiltoniens
 *
 * L'appel de fait pour une case de départ donnée
 *
 * @param m colonnes
 * @param n lignes
 * @param graph_possible graphe des cases accessibles
 * @param origine indice de la case d'origine
 * @return nombre de chemins trouvés pour à partir de la case d'origine
 */
int bf_open_init(int m, int n, GRAPHE *graph_possible, int origine)
{
    short* tableau_visites={0};
    int hauteur_actuele = 0;
    int nombre_chemins = 0;
    int  hauteur_max = (m * n - 1);
    tableau_visites = malloc(m * n * sizeof(short));

    nombre_chemins= bf_open_rec(origine, origine, graph_possible, tableau_visites,
                                hauteur_actuele, hauteur_max, nombre_chemins);

    return nombre_chemins;
}

/***
 * Fonction d'initialisation de la recurcion "closed knight's tour"
 *
 * Cette fonction initialise la fonction récurcive qui parcours l'arbre
 * à la recherche de circuits hamiltoniens
 *
 * L'appel de fait pour une case de départ donnée
 *      (les tests montrent que c'est bel et bien unutile)
 *
 * @param m colonnes
 * @param n lignes
 * @param graph_possible graphe des cases accessibles
 * @param origine indice de la case d'origine
 * @return nombre de circuits trouvés pour à partir de la case d'origine
 */
int bf_close_init(int m, int n, GRAPHE *graph_possible, int origine)
{
    short* tableau_visites={0};
    int hauteur_actuele = 0;
    int nombre_circuits = 0;
    int  hauteur_max = (m * n - 1);
    tableau_visites = malloc(m * n * sizeof(short));

    nombre_circuits= bf_close_rec(origine, origine, graph_possible, tableau_visites,
                                  hauteur_actuele, hauteur_max, nombre_circuits);

    return nombre_circuits;
}


/***
 * ----------------------------------------------------------
 *    Fonctions récurcives pour l'exploiration de l'arbre
 * ----------------------------------------------------------
 */

/***
 * Fonction de parcours récursif en profondeur
 * de "l'abre" des possibilités "open knight's tour"
 *
 * @param origine
 * @param position
 * @param graphe_possible
 * @param tableau_visites
 * @param hauteur_actuelle
 * @param hauteur_max
 * @param nombre_chemins
 * @return nombre_chemins
 */
int bf_open_rec(int origine, int position, GRAPHE *graphe_possible, short *tableau_visites, int hauteur_actuelle,int hauteur_max, int nombre_chemins)
{
    tableau_visites[position]=1;        // marquer case actuelle come visitée
    if(hauteur_actuelle < hauteur_max)  // si hauteur maximale non atteinte
    {
        int i = 0;

        // Ces lignes permettent d'acceder au sommet / la case consernée
        // ATTENTION: ce code n'est pas optimal, mais l'acces à la position par &(graphe_possible->premiersommet[position]) ne marche pas
        SOMMET *sommet = graphe_possible->premierSommet;
        for (i = 0; i < position; i++) {
            sommet = sommet->suivant;
        }
        ELTADJ *test = sommet->adj;

        // Tant que le cavalier peut acceder à des case non visitée
        // réappler recurcivement
        while (test != NULL) {
            if (tableau_visites[test->dest] == 0) {
                nombre_chemins = bf_open_rec(origine, test->dest, graphe_possible, tableau_visites,
                                             hauteur_actuelle + 1, hauteur_max, nombre_chemins);
            }
            test = test->suivant;
        }
    }
    else    // si hauteur maximale atteinte
    {
        nombre_chemins++;
    }
    tableau_visites[position]=0;    //démarquer visite case
    return nombre_chemins;
}

int bf_close_rec(int origine, int position, GRAPHE *graphe_possible,short *tableau_visites, int hauteur_actuelle,int hauteur_max, int nombre_circuits)
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
                nombre_circuits = bf_close_rec(origine, test->dest, graphe_possible, tableau_visites,
                                               hauteur_actuelle + 1, hauteur_max, nombre_circuits);}
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
