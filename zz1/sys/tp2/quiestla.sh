#!/bin/sh
LISTE=`ls ../*/online.cat | cut -d"/" -f2`

for LOG in $LISTE; do
	if [ -f "../$LOG/pseudo.cat" ]; then
		echo `more ../$LOG/pseudo.cat`
	fi
done
