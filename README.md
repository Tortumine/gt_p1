# Graph Theory Project 1

## Ennoncé

### 5. Enumération de circuits hamiltoniens - le parcours du cavalier. 
Etant donné un échiquier de dimension m*n, énumérer tous les circuits hamiltoniens réalisés en utilisant uniquement les mouvements du cavalierdans le jeu d'échecs. Même question, mais en énumérant le nombre de chemins hamiltoniens "ouverts" (origine et destination différentes).

### Quelques conseils :
- Pensez à l'utilisateur qui teste votre programme : préparer un makefile,
donner des conseils sur l'utilisation (fournir quelques fichiers de test),
quelles entrées fournir, quelles sorties attendues ? Décrivez un exemple
typique d'utilisation.
- Préparez une petite bibliographie, citer les sources utilisées (même les
pages Wikipedia !). Si vous avez exploiter une source, un autre cours,
mentionnez-le explicitement !
- Avez-vous tester votre programme sur de gros graphes ? De quelles
tailles ? Eventuellement produire un petit tableau de "benchmarking"
indiquant, sur une machine donnée, le temps de calcul en fonction des
tailles de graphes testés.
- Relisez (et relisez encore) votre rapport ! Faites attention à l'orthographe
(accords, conjugaison), au style.
- Si vous développez des heuristiques, avez-vous des exemples de graphes
(ou de familles de graphes) qui se comportent mal par rapport à cette
heuristique ?

## Liens utilies

* [Wikipedia (fr)](https://fr.wikipedia.org/wiki/Probl%C3%A8me_du_cavalier)
* [Algorithmique iii - Le problème du cavalier](http://zanotti.univ-tln.fr/ALGO/I51/Cavalier.html)
* [Problème du cavalier](http://bayledes.free.fr/carres_magiques/Cavaliers.html)
* [Graphs and Graph Algorithms](http://interactivepython.org/runestone/static/pythonds/Graphs/toctree.html)
* [Knight’s Tour Analysis](http://interactivepython.org/runestone/static/pythonds/Graphs/KnightsTourAnalysis.html)
* [Warnsdorff’s algorithm for Knight’s tour problem](http://www.geeksforgeeks.org/warnsdorffs-algorithm-knights-tour-problem/)
* [Warnsdorff's algorithm study](http://math.oregonstate.edu/~math_reu/proceedings/REU_Proceedings/Proceedings1996/1996Squirrel.pdf)
* [Graphes et représentation de graphe](https://zestedesavoir.com/tutoriels/681/a-la-decouverte-des-algorithmes-de-graphe/727_bases-de-la-theorie-des-graphes/3352_graphes-et-representation-de-graphe/)

# Algorithmes
## Parcourt du cavalier
### Circuits
      FONCTION int Parcourt (case_origine, case_actuelle, possible_graph, 
                        pile_visites, hauteur_actuelle, hauteur_max, nombre_chemins)
      DEBUT
         PUSH case_actuelle INTO pile_visites 
         SI hauteur_actuelle < hauteur_max
         DEBUT
            POURCHAQUE case_suivante dans possible_graph
            DEBUT
               SI case_suivante EST_PRESENTE_DANS pile_visites
               ALORS
                  nombre_chemins = Parcourt(case_origine, casecase_suivante, possible_graph, 
                           pile_visites, hauteur_actuelle++, hauteur_max, nombre_chemins)
            FIN
         FIN
         
         SINONSI case_origine EST_PRESENTE_DANS possible_graph
            ALORS nombre_chemins++;
         PULL case_actuelle FROM pile_visites
         RETURN nombre_chemins
      FIN
      
 ### Chemins
 
      FONCTION int Parcourt (case_origine, case_actuelle, possible_graph, 
                        pile_visites, hauteur_actuelle, hauteur_max, nombre_chemins)
      DEBUT
         PUSH case_actuelle INTO pile_visites 
         SI hauteur_actuelle < hauteur_max
         DEBUT
            POURCHAQUE case_suivante dans possible_graph
            DEBUT
               SI case_suivante EST_PRESENTE_DANS pile_visites
               ALORS
                  nombre_chemins = Parcourt(case_origine, casecase_suivante, possible_graph, 
                           pile_visites, hauteur_actuelle++, hauteur_max, nombre_chemins)
            FIN
         FIN
         
         SINON
            ALORS nombre_chemins++;
         PULL case_actuelle FROM pile_visites
         RETURN nombre_chemins
      FIN
