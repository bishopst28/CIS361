#! /bin/bash

helpOpt=0 #help option flag, 0 or 1 
listOpt=0 #list option flag, 0 or 1
numOpt=0 #num files and space option flag
junkDir="~/.junk" #place holder for junk directory name
mkdir -p $junkDir #make the hidden junk directory if it's not there already
#loop through the args given and turn on the flag for each proper arg chosen 
for i in $@
	do
		case $i in 
			"--help" ) helpOpt=1;;
			"-l" ) listOpt=1;;
			"-n" ) numOpt=1;;
		esac
done
if [ $helpOpt == 1 ] #help option given, tell them about how to use args and what options they have
	then
		echo "Usage: junk [options] targetFileList"
		echo
		echo "Junk moves files given by name in the targetFileList to the .junk directory. If duplicates are present, the newest version is retained"
		echo
		echo "Options: -l -n --help"
		echo "		-l : lists contents of .junk directory"
		echo "		-n : gives the number of files and space used within the .junk directory"	
		echo
fi
if [ $# == 0 ] #indicates that no args were given but we at least need a list of files to junk or the help option 
	then
		echo "You must provide at least one argument. Use 'junk --help' for more help"
		exit
fi
fileNames=${*: -1} #our list of file names given as the first argument 
if [ -f $fileNames ] #check to make sure it was actually given and is a file
	then
		while read f #while we have another line to read
			do
				if [ -f $f ] #make sure this line of text is actually a file
					then #move the file to junk and then delete it, -u option given to keep latest version
						mv -u $f $junkDir 
						rm -f $f
				fi
		done
fi
if [ $listOpt == 1 ] #run ls if the -l optional arg is given 
	then
		echo ".junk directory contents: "
		echo $(ls ~/.junk)
		echo
fi
if [ $numOpt == 1 ] #use ls and disk usage tool if the -n optional arg is given
	then
		echo "Number of Files in .junk: " $(ls~/.junk | wc -l)
		echo "Space Used: " $(du -sbh ~/.junk)
fi






