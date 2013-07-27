#!/bin/sh
PSEUDO=`more ~/pseudo.cat`

if [ -f "$HOME/online.cat" ]; then
    rm ~/online.cat
fi

echo "$PSEUDO vient de se deconnecter !" >> "/tmp/conv11.cat"

PID=`ps u | grep "/bin/sh ./sys/chat.sh" | grep -v grep | tr -s " " | cut -d" " -f2`

if ! [ -z $PID ]; then
    kill -9 $PID
fi

PID=`ps u | grep "tail" | grep -v grep | tr -s " " | cut -d" " -f2`

if ! [ -z $PID ]; then
    kill -9 $PID
fi

