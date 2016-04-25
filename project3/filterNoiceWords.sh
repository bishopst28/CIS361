#!/bin/bash
if [ ! -f $* ]
	then
		echo "filterNoiceWords Usage: bash filterNoiceWords [FileName]"
		exit 1
	else
		noiceFile=${*: -1} 
fi

while read -r line
	do
		set $line
		if [ ! grep -Fxq $1 $noiceFile ]
			then
				echo $line
		fi 
done

