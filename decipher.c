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

	i = fscanf(fin, "%c %f", &ch, &fl);

	while ( i != EOF )
	{
		if(i == 2)
		{
			*p = fl; 
			printf("%f\n",*p);
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

	for(i = 0; i < 26; i++)
	{
		found[i] = 0;
	}

	while(fscanf(fin, "%c", &ch) != EOF)
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

	while(numRotations < 26)
	{
		letterNum = 0;
		difference = 0;

		while(letterNum < 26)
		{
			difference += pow(found[(numRotations+letterNum)%26] - given[letterNum], 2);

			letterNum++;
		}
		
		difference = difference/26;

		if(difference < min)
		{
			min = difference;
			key = numRotations;
		}

		numRotations++;
	}

	return key;
}

// Decrypt the encoded text in the input file using the key and display the decoded text
void decrypt(int key, char fname[])
{
	FILE *fin;
	key = -key;
	char ch;

	fin = fopen(fname, "r");

	
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

void decryptToFile(int key, char finame[], char foutname[])
{
	FILE *fin, *fout;
	key = -key;
	char ch;

	fin = fopen(finame, "r");
	fout = fopen(foutname, "w");

	fprintf(fout, "%c", encrypt(ch, key));
	
	while ( fscanf(fin, "%c", &ch) != EOF )
	{
		if(isalpha(ch))
		{
			printf("%c", rotate(ch, key));
			fprintf(fout, "%c", rotate(ch, key));
		}
		else
		{
			printf("%c", ch);
			fprintf(fout, "%c", ch);
		}
	}

	fclose(fin);

}

int main(int argc, char* argv[])
{  
	
	float given[26], found[26];

	int key; 

	if (argc != 4)
	{
		printf ("Usage: cipher infile, outfile, data file\n");
		exit(1);
	}



	readFreq(given, argv[3]);



	calcFreq(found, argv[1]);



	key = findKey(given, found);



	decrypt(key, argv[1]); //should only print to screen at this time.




	return 0;
}