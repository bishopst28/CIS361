//Author: Stanley Bishop
//decrypts caesar cipher text
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>





// Load array given with the letter frequencies for English from file LetFreq.txt
void readFreq(float given[], char fname[])
{

	FILE *fin;
	char ch;
	float *p;
	float fl;
	p = given;
	int i;

	fin = fopen(fname, "r");

	/*
	For some reason fscanf likes to scan each line twice
	The first time returns two items (the char and the float)
	The second time returns one item (just the float)
	So we scan once to begin and loop until end of file is reached
	if we have two items we store the float, if just one item we ignore
	inorder to move to the next line
	*/
	i = fscanf(fin, "%c %f", &ch, &fl);

	while ( i != EOF )
	{
		if(i == 2)
		{
			*p = fl; 
			p++;
		}

		i = fscanf(fin, "%c %f", &ch, &fl);
	}




	fclose(fin);

}

// Read the encoded text from an input file and accumulate the letter frequency                  
// data for the encoded text. Store the frequency data in array found.
void calcFreq(float found[], char fname[])
{
	FILE *fin;
	char ch;
	int i, index;
	int numChars = 1;

	fin = fopen(fname, "r");

	//initializes the array of observed frequencies to zero
	for(i = 0; i < 26; i++)
	{
		found[i] = 0;
	}

	//We loop through and scan each character until end of file
	while(fscanf(fin, "%c", &ch) != EOF)
	{
		//check if char is alpha 
		//check the case of the char
		//then grab index
		//increment index's count
		if(isalpha(ch))
		{
			if( isupper(ch))
			{
				index = ch - 'A';
			}
			else if( islower(ch))
			{
				index = ch - 'a';
			}

			found[index]++;
			numChars++;
		}
	}

	//divide each count by total number of chars
	for(i = 0; i < 26; i++)
	{
		found[i] = found[i] / numChars;
	}

	fclose(fin);

}

// Rotate the character in parameter ch down the alphabet for the number of   
// positions as given in parameter num and return the resulting character.
char rotate(char ch, int num)
{
	if ( num < 0 )
		num = num + 26;

	if ( isupper(ch) )
		return (ch - 'A' + num) % 26 + 'A';
	
	if ( islower(ch) )
		return (ch - 'a' + num) % 26 + 'a';
	
	return ch;
}

// Compare the data in array found with the frequency data in array given, looking
// for a key that will give you the best match. To do this, try each of the 26 rotations,
// and remember which gives the smallest difference between the frequencies you
// observed and the frequencies given. Return the key.
int findKey(float given[], float found[])
{
	double difference, min; 
	int numRotations, letterNum, key;

	key = 0;
	numRotations = 0;
	min = 30000; 

	//loop through each of the 26 possible rotations
	while(numRotations < 26)
	{
		letterNum = 0;
		difference = 0;

		//get the difference of each corresponding index for each rotation
		//then square each difference and add it to the total difference
		while(letterNum < 26)
		{
			difference += pow(found[(numRotations+letterNum)%26] - given[letterNum], 2);

			letterNum++;
		}
		
		//get the difference average
		difference = difference/26;

		//save the lowest observed difference average so far
		//and the corresponding number of rotations
		if(difference < min)
		{
			min = difference;
			key = numRotations;
		}

		numRotations++;
	}

	//return the number of rotations with smallest average difference
	return key;
}

//Decrypt the encoded text in the input file using the key and display the decoded text
void decrypt(int key, char fname[])
{
	FILE *fin;
	key = -key;
	char ch;

	fin = fopen(fname, "r");

	//go through each character, if it's alphabetical then we rotate according to the key we found
	while ( fscanf(fin, "%c", &ch) != EOF )
	{
		if(isalpha(ch))
		{
			printf("%c", rotate(ch, key));
		}
		else
			printf("%c", ch);
	}

	fclose(fin);

}

//Does the same thing as the function above except it outputs to a file rather than 
//to the console
void decryptToFile(int key, char finame[], char foutname[])
{
	FILE *fin, *fout;
	key = -key;
	char ch;

	fin = fopen(finame, "r");
	fout = fopen(foutname, "w");

	
	while ( fscanf(fin, "%c", &ch) != EOF )
	{
		if(isalpha(ch))
		{
			//printf("%c", rotate(ch, key));
			fprintf(fout, "%c", rotate(ch, key));
		}
		else
		{
			//printf("%c", ch);
			fprintf(fout, "%c", ch);
		}
	}

	fclose(fin);

}

//arguments to output to file(input file, output file, frequency data file)
//arguments to output to console(input file, frequency data file)
int main(int argc, char* argv[])
{  
	
	float given[26], found[26];

	int key; 

	if (argc != 4 && argc != 3)
	{
		printf ("Arguments to output to file: infile, outfile, data file\nArguments to output to console: infile, data file\n");
		exit(1);
	}

	//prints to console
	if(argc == 3)
	{
		readFreq(given, argv[2]);



		calcFreq(found, argv[1]);



		key = findKey(given, found);	



		decrypt(key, argv[1]);
	}
	else if (argc == 4) //prints to output file
	{
		readFreq(given, argv[3]);



		calcFreq(found, argv[1]);



		key = findKey(given, found);


		decryptToFile(key, argv[1], argv[2]);
	}



	return 0;
}