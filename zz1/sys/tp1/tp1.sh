#!/bin/sh
echo "Kenavo les ZZ !"

#Q2
more ~/systeme/tel.dat
cut -d ";" -f 1 "$PWD/tel.dat" | tr -s ' ' | cut -d" " -f 1

#Q3
LISTE=`ls ~`
for i in $LISTE; do
    if [ -f $i ]; then
        ls -l $i | tr -s " " | cut -d " " -f 1,5
    fi
done

#Q4
echo "Veuillez saisir votre recherche : "
read RECH_NOM
echo "\n"
grep $RECH_NOM "$PWD/tel.dat" | tr -s " " | uniq | sort

#Q5
echo "Recherche par arguments :"
while [ $# -ne 0 ]; do
    grep $1 "$PWD/tel.dat" | tr -s " " | uniq | sort
    shift
done

echo "Recherche par arguments :"
for i in $*; do
    grep $i "$PWD/tel.dat" | tr -s " " | uniq | sort
done

#Q6
TMP="/tmp"
if [ $# -ne 1 ]; then
    echo "USAGE : <MODE>"
    echo "MODE : 1) Ajout"
    echo "       2) Modification"
else
    cp "$PWD/tel.dat" $TMP
    MODE=$1
    case "$MODE" in
        1)  echo "Veuillez saisir la valeur à ajouter : "
            read NOM
            echo "$NOM" >> "$TMP/tel.dat"
            ;;

        2)  echo "Veuillez saisir la valeur à modifier : "
            read OLDVAL
            echo "Veuillez saisir la nouvelle valeur : "
            read NEWVAL
            sed -e "s/"$OLDVAL"/"$NEWVAL"/g" "$PWD/tel.dat" > "$TMP/tel.dat"
            ;;

        *) echo "Cas non prevu"
    esac
    mv "$TMP/tel.dat" "$PWD/"
fi
