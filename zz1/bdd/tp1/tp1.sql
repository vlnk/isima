/*Question 1*/
SELECT DISTINCT Categorie
FROM CLIENTS;

/* Résultat :
C
-

B
A
C
E
*/

/*Q2*/
SELECT nomclt
FROM CLIENTS
WHERE categorie = 'A';

/* Résultat :
NOMCLT
--------------------
Dupont
Girard
Alfred
*/

/*Q3*/
SELECT COUNT (numproduit)
FROM PRODUITS;

/* Résultat :
COUNT(NUMPRODUIT)
-----------------
               12
*/

/*Q4*/
SELECT COUNT (numproduit)
FROM LIVRAISONS
WHERE numclt = '1';

/* Résultat :
COUNT(NUMPRODUIT)
-----------------
                2
*/

/*Q5*/
SELECT numclt
FROM LIVRAISONS
WHERE numproduit = '6' AND quantite > 2;

/* Résultat :
    NUMCLT
----------
         5
         7
*/

/*Q6*/
SELECT max(prixbrut)
FROM PRODUITS;

/* Résultat :
MAX(PRIXBRUT)
-------------
          350
*/

/*Q7*/
SELECT numproduit,libelle
FROM PRODUITS
WHERE prixbrut = (SELECT max(prixbrut)
                  FROM PRODUITS);

/* Résultat :
NUMPRODUIT LIBELLE
---------- --------------------
        23 Cage
*/

/*Q8*/
SELECT nomclt
FROM CLIENTS
WHERE nomclt LIKE 'Du%';

 /* Résultat :
NOMCLT
--------------------
Dupond
Dupont
Dupont
*/

/*Q9*/
SELECT numclt
FROM LIVRAISONS
WHERE numproduit = '1' OR numproduit = '6';

/* Résultat :
    NUMCLT
----------
         1
         4
         1
         2
         3
         4
         5
         7
*/

/*Q10*/
SELECT numclt
FROM LIVRAISONS
WHERE numproduit = '1'
INTERSECT
SELECT numclt
FROM LIVRAISONS
WHERE numproduit = '6';

/* Résultat :
    NUMCLT
----------
         1
         4
*/

/*Q11*/
SELECT nomclt, categORie
FROM CLIENTS
WHERE numclt IN (SELECT numclt
                 FROM LIVRAISONS);

/* Résultat :
NOMCLT               C
-------------------- -
Tintin               B
Dupond               E
Dupont               E
Haddock              B
Tournesol            B
Dupont               A
*/

/*Q12*/
SELECT P.numproduit
FROM PRODUITS P, CLIENTS C, LIVRAISONS L
WHERE prixbrut < '55'
    AND P.numproduit = L.numproduit
    AND L.numclt = C.numclt
    AND C.categORie = 'A';

/* Résultat :
NUMPRODUIT
----------
         6
*/

/*Q13*/
SELECT libelle
FROM PRODUITS P, CLIENTS C, LIVRAISONS L
WHERE L.numproduit = P.numproduit
    AND L.numClt = C.numClt
    AND C.nomclt = 'Haddock'
MINUS
SELECT libelle
FROM PRODUITS P, CLIENTS C, LIVRAISONS L
WHERE L.numproduit = P.numproduit
    AND L.numClt = C.numClt
    AND C.nomclt NOT LIKE 'Haddock';

/* Résultat :
LIBELLE
--------------------
Compote
Farine
Oeuf
Pate
Pomme
Sucre
Tarte aux pommes
*/

/*Q14*/
SELECT libelle
FROM PRODUITS P, CLIENTS C, LIVRAISONS L
WHERE L.numproduit = P.numproduit
    AND L.numclt = '3'
INTERSECT
SELECT libelle
FROM PRODUITS P, CLIENTS C, LIVRAISONS L
WHERE L.numproduit = P.numproduit
    AND L.numclt = '5';

/* Résultat :
LIBELLE
--------------------
Cacahuetes
*/

/*Q15*/
SELECT numproduit, COUNT(*) "Nombre de livraison"
FROM LIVRAISONS
GROUP BY numproduit;

/* Résultat :
NUMPRODUIT Nombre de livraison
---------- -------------------
         1                   2
         6                   6
        18                   2
        23                   2
        33                   3
        40                   1
        41                   1
        42                   1
        43                   1
        44                   1
        45                   1
        46                   1
*/

/*Q16*/
SELECT numclt
FROM LIVRAISONS
GROUP BY numclt
HAVING COUNT(*) = (SELECT COUNT(DISTINCT numproduit)
                   FROM PRODUITS);

SELECT numclt
FROM LIVRAISONS
GROUP BY numclt
HAVING COUNT(DISTINCT numproduit) = (SELECT COUNT(DISTINCT numproduit)
                                     FROM PRODUITS);

/* Résultat :
    NUMCLT
----------
         4
*/

/*Q17*/
SELECT numclt
FROM LIVRAISONS
GROUP BY numclt
HAVING COUNT(DISTINCT numproduit) >= (SELECT COUNT(*)
                                      FROM PRODUITS
                                      WHERE prixbrut < '50');

/* Résultat :
    NUMCLT
----------
         4
*/

/*Q18*/
SELECT numproduit, avg(quantite) "Quantite moyenne"
FROM LIVRAISONS
GROUP BY numproduit
HAVING COUNT(*) > '2'
ORDER BY numproduit DESC;

/* Résultat :
NUMPRODUIT Quantite moyenne
---------- ----------------
        33       21.6666667
         6       3.16666667
*/

/*Q19*/
SELECT libelle, COUNT(*) "Nombre de LIVRAISONS"
FROM PRODUITS P, LIVRAISONS L
WHERE P.numproduit = L.numproduit
GROUP BY libelle
HAVING COUNT(L.numproduit) = (SELECT max(COUNT(*))
                              FROM LIVRAISONS
                              GROUP BY numproduit);

/* Résultat :
LIBELLE              Nombre de LIVRAISONS
-------------------- --------------------
Cacahuetes                              6
*/

/*Q20*/
SELECT P.numproduit, SUM(quantite*prixbrut) "Chiffre d'affaire Brut"
FROM PRODUITS P, LIVRAISONS L
WHERE P.numproduit = L.numproduit
GROUP BY P.numproduit;

/* Résultat :
NUMPRODUNUMPRODUIT Chiffre d'affaire
---------- -----------------
         1            112500
         6               475
        18               980
        23              1050
        33             16250
        40              4500
        41               180
        42                50
        43                70
        44                 5
        45               130
        46               168
*/

/*Q21*/
SELECT C.numclt, nomclt, libelle, quantite
FROM CLIENTS C, PRODUITS P, LIVRAISONS L
WHERE C.numclt = L.numclt
    AND L.numproduit = P.numproduit
UNION
SELECT C.numclt, nomclt, NULL, NULL
FROM CLIENTS C
WHERE NOT EXISTS (SELECT *
                  FROM LIVRAISONS L
                  WHERE C.numclt = L.numclt);

/* Résultat :
    NUMCLT NOMCLT               LIBELLE                QUANTITE
---------- -------------------- -------------------- ----------
         1 Tintin               Cacahuetes                    2
         1 Tintin               Foie                        500
         2 Dupond               Cacahuetes                    1
         2 Dupond               Cacahuettes                  25
         2 Dupond               Peinture                      5
         3 Dupont               Cacahuetes                    2
         3 Dupont               Peinture                      5
         4 Haddock              Cacahuetes                    1
         4 Haddock              Cacahuettes                   3
         4 Haddock              Cage                          1
         4 Haddock              Compote                      14
         4 Haddock              Farine                       35
         4 Haddock              Foie                        250
         4 Haddock              Oeuf                          5
         4 Haddock              Pate                         10
         4 Haddock              Peinture                     55
         4 Haddock              Pomme                        25
         4 Haddock              Sucre                        13
         4 Haddock              Tarte aux pommes            100
         5 Tournesol            Cacahuetes                   10
         6 Milou
         7 Dupont               Cacahuetes                    3
         7 Dupont               Cage                          2
      1715 Muller
      1716 girard
      1717 Alfred
      1718 Toto
      1720 Rastapopoulos
      1721 Girard
      1723 Girard
      1724 Girard
      1725 Girard
      1726 Nathalie
      1730 Pedrono
     17211 Girard
*/

/*Q22*/
SELECT level, numprocomposant, quantite
FROM COMPOSITION
connect by priOR numprocompose = numprocomposant;
START WITH numprocompose = '40'
ORDER BY level DESC;

/* Résultat :
     LEVEL NUMPROCOMPOSANT   QUANTITE
---------- --------------- ----------
         1              41          1
         1              42          5
         1              43          1
         2              41          1
         1              44          2
         2              41          1
         1              45         .1
         1              45        .25
         2              41          1
         1              46          1
*/