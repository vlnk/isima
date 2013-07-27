#!/bin/bash

DIR="$HOME/sys/tp3"
MENU="$DIR/menu.dat"
REPETE=50
CHOIX=A
NO_OPT="$DIR/no_$"

#q1 -> affichage du menu
if [ -f "$MENU" ]; then
    DEB_LIGNE="  "

    #echo $(for i in $(seq 1 $REPETE); do echo '-' ; done) | tr -d ' ' > "$MENU"

    echo -e "$DEB_LIGNE""Bonjour $USER !" > "$MENU"
    echo "$DEB_LIGNE"$(for i in $(seq 1 $REPETE); do echo ' ' ; done) >> "$MENU"
    echo -e "$DEB_LIGNE""Repertoire par defaut : $PWD" >> "$MENU"
    echo "$DEB_LIGNE"`$(for i in $(seq 1 $REPETE); do echo ' ' ; done)` >> "$MENU"
    if [ -z `grep D "$NO_OPT"` ]; then
        echo -e "$DEB_LIGNE""D) afficher l'espace disque occupe" >> "$MENU"
    fi
    if [ -z `grep F "$NO_OPT"` ]; then
        echo -e "$DEB_LIGNE""F) fixer le repertoire par defaut" >> "$MENU"
    fi
    if [ -z `grep C "$NO_OPT"` ]; then
        echo -e "$DEB_LIGNE""C) creer un repertoire" >> "$MENU"
    fi
    if [ -z `grep E "$NO_OPT"` ]; then
        echo -e "$DEB_LIGNE""E) editer un texte" >> "$MENU"
    fi
    if [ -z `grep M "$NO_OPT"` ]; then
        echo -e "$DEB_LIGNE""M) envoyer un mail" >> "$MENU"
    fi
    if [ -z `grep S "$NO_OPT"` ]; then
        echo -e "$DEB_LIGNE""S) envoyer un fichier par mail" >> "$MENU"
    fi
    if [ -z `grep Q "$NO_OPT"` ]; then
        echo -e "$DEB_LIGNE""Q) se deconnecter" >> "$MENU"
    fi
    #echo $(for i in $(seq 1 $REPETE); do echo '-' ; done) | tr -d ' ' >> "$MENU"
    #echo -e "\n  Votre choix (D,F,C,E,M,S,Q) ?" >> "$MENU"
fi

more "$MENU"

#q2 -> saisie du choix
while [[ "$CHOIX" != [D,F,C,E,M,S,Q] ]]; do
    echo -e "\n  Votre choix (D,F,C,E,M,S,Q) ?"
    read CHOIX
done

case "$CHOIX" in
    D) echo `df -h`
        ;;
    F) echo "Veuillez saisir le nouveau repertoire par defaut :"
       read NEWDIR
       cp $DIR/* "$NEWDIR"
       sed -i s!'$HOME/sys/tp3'!"$NEWDIR"!g "$NEWDIR/menu.sh"
        ;;
    C) echo "Veuillez saisir le repertoire a creer :"
       read NEWDIR
       mkdir "$NEWDIR"
        ;;
    E) echo "Veuillez saisir le nom du fichier a editer :"
       read NEWFIC
       vi "$NEWFIC"
        ;;
esac


#lit reponse utilisateur
#read $CHOIX

#ligne() # $1:nombre, $2:char
#{
#    typeset -i compt
#    compt=$1
#    chaine=""

#    while [ $compt -ne 0 ]; done
#        chaine="$chaine""$2"
#        compt=$compt-1
#    done
#    echo "$chaine"
#}

