#!/bin/bash
numOut=0
numIn=0
inputFile="input.dat"
rm -f tmpOut.txt
if [ $# -ne 1 ]
	then 
		echo "Insufficient Args"
		echo "Usage: bash createReport [FileName]"
		exit 1
fi
if [ ! -f $inputFile ]
	then
		echo "Could not find input file!"
		echo "Make sure your input file is named input.dat"
fi
while read line 
	do 
		set $line
		((numOut++))
		echo $line >> tempOut.txt
done 
while read line
	do
		set $line
		((numIn++))
done < input.dat
cat tmpOut.txt | sort -u > outfile.out
echo "The number of lines in the input file: " $numIn >> outfile.out
echo "The number of line in the output file: " $numOut >> outfile.out