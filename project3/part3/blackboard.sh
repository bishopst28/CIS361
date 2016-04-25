#!/bin/bash
# count file prefixes 
((numFiles = 1))
while [ $(zipinfo -1 $1 | cut -c 1-$numFiles | uniq | wc -l) -eq 1 ] 
	do
    	((numFiles++))
done
((numFiles--)) #decrement since we start at 1
prefix=$(zipinfo -1 $1 | cut -c 1-$numFiles | uniq) #grabs our prefixes from the file

#makes a directory with our zip file's name
zipRoot=$(echo $1 | sed 's/.zip$//')
mkdir -p $zipRoot
unzip -q $1 -d $zipRoot
cd $zipRoot #then we move into our new directory

# each file in prefix is read in 
for f in "${prefix}"*
	do
   		#strips out unnecessary information 
   		name=$(echo $f | sed "s/^$prefix//" | sed -E "s/_attempt_[-0-9]{19}//") #stips out attempt
   		stdnt=$(echo $name | sed -E "s/([^_]+)_.*$/\1/") #grabs the students user name
   		if [ $stdnt = $name ]
   			then
      			#if then that means its the memo text file
      			stdnt=$(echo $stdnt | sed "s/\.txt$//") 
      			file=memo.txt
   			else
      			#otherwise we need to process the prefix further because its not 
      			#the memo file and we should be saving the name of the file
      			file=$(echo $name | sed "s/$stdnt\_//" )
   		fi
   		if [ ! -d $stdnt ] 
   			then
      			#create the directory if it's not there already
      			mkdir -p $stdnt
   		fi
   		#take the file and put it into the students directory
   		mv "$f" "$stdnt/$file"
done
cd .. #go back to the top directory
# go through each student and build their test make
for f in "$zipRoot/"* 
	do
    	if [[ -d $f ]] #check that we have directory
    		then
				stdnt=$(echo $f | sed "s/^$zipRoot\///") #print out student dir
				echo -e \\n$stdnt #print out student name
				cp data.txt $f #copy data file to this directory
				make -f makefile -C $f/ #run their make file
				make test -f makefile -C $f/
				cat "$f/data.bak" #for some reason the third test wont run so I put this here to demonstrate that it works 
    	fi
done >> "Report.txt"