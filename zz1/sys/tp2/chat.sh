#!/bin/sh
if ! [ -f "$HOME/pseudo.cat" ]; then
    echo "Votre pseudo n\'est pas trouve.\n"
    touch "$HOME/pseudo.cat"
    echo "Veuillez saisir votre pseudo : "
    read PSEUDO
    echo "$PSEUDO" >> "$HOME/pseudo.cat"
fi

if ! [ -f "/tmp/conv11.cat" ]; then
    touch "/tmp/conv11.cat"
    chmod 666 "/tmp/conv11.cat"
fi

if ! [ -f "$HOME/online.cat" ]; then
    touch "$HOME/online.cat"
    chmod a+rx "$HOME/online.cat"
fi

PSEUDO=`more $HOME/pseudo.cat`
echo "$PSEUDO vient de se connecter !" >> "/tmp/conv.cat"
tail -f "/tmp/conv11.cat"

