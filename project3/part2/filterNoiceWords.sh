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
		grep -Fxq "$1" $noiceFile
		if [ $?=1 ]
			then
				echo $line
		fi 
done

