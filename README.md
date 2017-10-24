# Graph Theory Project 1

## Ennoncé

### 19. Construction d'un graphe réel de collaborations. 
Pouvoir interroger une base de données comme [http://www.ams.org/mathscinet/](http://www.ams.org/mathscinet/) ou
[orbi.ulg.ac.be](orbi.ulg.ac.be) pour construire un graphe (pondéé non orienté)
dont les sommets sont les auteurs et une arête existe entre deux auteurs
s'ils ont une publication commune. Le poids d'une arête est fourni
par le nombre de publications communes. En interrogeant ces bases
de données, l'utilisateur pourra fournir certains critères (pour ne pas
obtenir un graphe trop gros) comme une liste de noms, certaines dates,
etc. ou construire tous les sommets à distance au plus d d'un sommet
donné.

### Quelques conseils :
- Pensez à l'utilisateur qui teste votre programme : préparer un makefile,
donner des conseils sur l'utilisation (fournir quelques fichiers de test),
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

* [MathSciNet Distance](https://mathscinet.ams.org/mathscinet/freeTools.html?version=2)
* [Vis.js](http://visjs.org/)
    * [Examples](http://visjs.org/network_examples.html)
    * [Docs](http://visjs.org/docs/network/)
    * [Download](http://visjs.org/index.html#download_install)
* [Curl](https://curl.haxx.se/libcurl/c/sepheaders.html)
