#!/bin/sh
LISTE=`ls ../*/online.cat | cut -d"/" -f2`
RET=""

for LOG in $LISTE; do

    if [ -f "../$LOG/pseudo.cat" ]; then
        PSEUDO=`more ../$LOG/pseudo.cat`

        if [ "$PSEUDO" = "$1" ]; then
            RET="$LOG"
        fi
    fi
done

if ! [ -z "$RET" ]; then
    echo "$RET"
else
    echo "Aucun pseudo n'est trouve!"
fi