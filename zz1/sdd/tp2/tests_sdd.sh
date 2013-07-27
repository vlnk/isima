#!/bin/bash

# Malrin Vincent
# Laurent Valentin
# Script shell de tests : tests_sdd.sh

#inversion
#1)chaine vide
./inversion/inversion > ./tests/tests_inversion1.txt;
#2)un caractere
./inversion/inversion a > ./tests/tests_inversion2.txt;
#3)cas general
./inversion/inversion dcba > ./tests/tests_inversion3.txt;

#validite des arguments
#1) validite du fichier
./dico/dico inconnu.txt > ./tests/tests_finvalide.txt;
#2) validite de lecriture parenthese
./dico/dico dico/abr_err1.txt > ./tests/tests_err1.txt
./dico/dico dico/abr_err2.txt > ./tests/tests_err2.txt
./dico/dico dico/abr_err3.txt > ./tests/tests_err3.txt
./dico/dico dico/abr_err4.txt > ./tests/tests_err4.txt
./dico/dico dico/abr_err5.txt > ./tests/tests_err5.txt
#3) validite des chaines a inserrer
./dico/dico dico/abr_vide.txt rien arbre7 @rbre arbré > ./tests/tests_err6.txt

#lecture et affichage
#1)arbre vide
./dico/dico dico/abr_vide.txt > ./tests/tests_aff0.txt;
#2)arbre atomique
./dico/dico dico/abr_atome.txt > ./tests/tests_aff1.txt;
#3)cas general
./dico/dico dico/abr_verbe.txt > ./tests/tests_aff2.txt;

#insersion
#arbre vide
./dico/dico dico/abr_vide.txt rien > ./tests/tests_vide.txt;

#arbre atomique
#1) insertion frere avant
./dico/dico dico/abr_atome.txt ah > ./tests/tests_atome1.txt;
#2) insertion frere apres
./dico/dico dico/abr_atome.txt oh > ./tests/tests_atome2.txt
#3) insertion fils
./dico/dico dico/abr_atome.txt eh > ./tests/tests_atome3.txt

#cas general
#1) insertion avant les freres
./dico/dico dico/abr_verbe.txt chanta > ./tests/tests_insert1.txt;
#1bis) insertion avant les freres (sans fils)
./dico/dico dico/abr_verbe.txt chantea > ./tests/tests_insert1bis.txt;
#2) insertion entre les freres
./dico/dico dico/abr_verbe.txt chantier > ./tests/tests_insert2.txt;
#2bis) insertion entre les freres (sans fils)
./dico/dico dico/abr_verbe.txt chanter > ./tests/tests_insert2bis.txt;
#3) insertion apres les freres
./dico/dico dico/abr_verbe.txt chans > ./tests/tests_insert3.txt;
#3bis) insertion apres les freres (sans fils)
./dico/dico dico/abr_verbe.txt chantez > ./tests/tests_insert3bis.txt;
#4) insertion en fils
./dico/dico dico/abr_verbe.txt chanson > ./tests/tests_insert4.txt;
#5) insertion d'un mot inclu
./dico/dico dico/abr_verbe.txt chant > ./tests/tests_insert5.txt;
#6) insertion d'un mot deja ecrit
./dico/dico dico/abr_verbe.txt chante > ./tests/tests_insert6.txt;
#7) insertion sur une cellule sans frere (apres)
./dico/dico dico/abr_verbe.txt chartes > ./tests/tests_insert7.txt;
#8) insertion sur une cellule sans frere (avant)
./dico/dico dico/abr_verbe.txt charles > ./tests/tests_insert8.txt;
#9) insertion avant racine
./dico/dico dico/abr_verbe.txt bavarde > ./tests/tests_insert9.txt;
#10) insertion apres racine
./dico/dico dico/abr_verbe.txt discute > ./tests/tests_insert10.txt;
#11) insertion fils racine
./dico/dico dico/abr_verbe.txt calvitie > ./tests/tests_insert11.txt;

#liberation memoire
#1)dico sans argument
valgrind ./dico/dico 2> ./tests/tests_free0.txt
#2)dico
valgrind ./dico/dico dico/abr_verbe.txt zorro 2> ./tests/tests_free1.txt
#3)inversion
valgrind ./inversion/inversion dcba 2> ./tests/tests_free2.txt

