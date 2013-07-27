#!/bin/sh
if ! [ -f "$HOME/online.cat" ]; then
    exit 1;
fi

PSEUDO=`more ~/pseudo.cat`
DATE=`date +%H:%M`
FIC="/tmp/conv11.cat"
MSG=$*

echo -e "($DATE) $PSEUDO dit : $MSG">>"$FIC"

