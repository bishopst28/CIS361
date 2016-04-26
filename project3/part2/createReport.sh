#!/bin/bash
numOut=0
numIn=0
inputFile="test.dat"
rm -f tempOut.txt
touch tempOut.txt
if [ $# -ne 1 ]
	then 
		echo "Insufficient Args"
		echo "Usage: bash createReport [FileName]"
		exit 1
fi
if [ ! -f $inputFile ]
	then
		echo "Could not find input file!"
		echo "Make sure your input file is named test.dat"
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
done < $inputFile
cat tempOut.txt | sort -u > outfile.out
echo "The number of lines in the input file: " $numIn >> outfile.out
echo "The number of lines in the output file: " $numOut >> outfile.out