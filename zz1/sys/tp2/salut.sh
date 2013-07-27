#!/bin/sh
LISTE_FAV=`more ~/sys/favoris.cat`
PSEUDO=`more ~/pseudo.cat`
FIC="/tmp/conv.cat"

while [ -f "$HOME/online.cat" ]; do
    CHAT=`~/sys/quiestla.sh`

    for I in $CHAT; do
        MATCH_USER=`echo "$LISTE_FAV" | grep "$I"`

        if ! [ -z $MATCH_USER ]; then
            MATCH_LOG=`echo "$LISTE_LOG" | grep "$I"`

            if [ -z $MATCH_LOG ]; then
                DATE=`date +%H:%M`
                echo -e "($DATE) $PSEUDO dit Salut $I!" >> "$FIC"
                LISTE_LOG="$LISTE_LOG""$I"
            fi
        fi
    done
done