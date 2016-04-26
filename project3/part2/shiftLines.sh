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
		body=""
		newLine=""
			for w in $line 
				do
					head="$head $w"
					shift
					body="$*"
					echo "${body} ${head}"
			done
done < $*

