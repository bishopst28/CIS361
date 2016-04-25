#!/bin/bash
if [ ! -f $* ] || [ $# -ne 1 ]
	then
		echo "shiftLines Usage: bash shift.sh [FileName]"
		exit 1
fi
while read -r line
	do
		set $line
		head=""
			for w in $line 
				do
					head="$head $1"
					shift
					echo $* $head
			done
done < $*