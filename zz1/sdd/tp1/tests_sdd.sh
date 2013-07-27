#!/bin/bash

#lecture et insertion
./agenda 1 fichier_innexistant.txt > ./tests/tests_insert1.txt;
./agenda 1 donnee0.txt > ./tests/tests_insert2.txt;
./agenda 1 donnee1.txt > ./tests/tests_insert3.txt;
./agenda 1 donnee10.txt > ./tests/tests_insert4.txt;

#recherche
./agenda 2 donnee0.txt 201342108 > ./tests/tests_rech1.txt;
./agenda 2 donnee1.txt 201305401 > ./tests/tests_rech2.txt
./agenda 2 donnee10.txt 201342108 > ./tests/tests_rech3.txt;
./agenda 2 donnee10.txt 201343210 > ./tests/tests_rech4.txt;
./agenda 2 donnee10.txt 201403517 > ./tests/tests_rech5.txt;
./agenda 2 donnee10.txt 201343209 > ./tests/tests_rech6.txt;

#suppression
./agenda 3 donnee0.txt 201342108 > ./tests/tests_supp1.txt;
./agenda 3 donnee1.txt 201305401 > ./tests/tests_supp2.txt
./agenda 3 donnee10.txt 201342108 > ./tests/tests_supp3.txt;
./agenda 3 donnee10.txt 201343208 > ./tests/tests_supp4.txt;
./agenda 3 donnee10.txt 201403517 > ./tests/tests_supp5.txt;
./agenda 3 donnee10.txt 201343209 > ./tests/tests_supp6.txt;

#listes bilatère
./agenda 5 donnee0.txt > ./tests/tests_bil1.txt;
./agenda 5 donnee1.txt > ./tests/tests_bil2.txt;
./agenda 5 donnee4.txt > ./tests/tests_bil3.txt;

#motif
./agenda 6 donnee0.txt SDD > ./tests/tests_motif1.txt;
./agenda 6 donnee10.txt Calcul > ./tests/tests_motif2.txt;
./agenda 6 donnee10.txt SDD > ./tests/tests_motif3.txt;
./agenda 6 donnee10.txt Liberte > ./tests/tests_motif4.txt;
./agenda 6 donnee10.txt truc > ./tests/tests_motif5.txt;
./agenda 6 donnee10.txt TP > ./tests/tests_motif6.txt;

#ecriture
./agenda 4 donnee0.txt donnee_e0.txt > ./tests/tests_ecr1.txt;
./agenda 4 donnee10.txt donnee_e1.txt > ./tests/tests_ecr2.txt;
