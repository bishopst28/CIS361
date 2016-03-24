#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "stats.h"
#include "queue.h"


#define AVG_SERVICE 2.0
#define WORKING_DAY 480 

//Struct that keeps track of whether a teller is 
//occupied and how long until they are done servicing 
//their customer
struct _teller {
	int occupied; // zero for unoccupied, 1 for occupied
	double serviceTime; //counts down each interval 
};

typedef struct _teller teller;

//gives a value for how long it will take for a given 
//customer to be serviced by a teller after making it
//out of the line
double expdist (double mean) {

	double r = rand();
	r /= RAND_MAX;
	return -mean * log(r);

}

//calculates the number of arrivals for the current interval
int getNumArrivals(int const pcts[]) {
	int numArrived;
	//picks a number between 1 and 100
	double randomNum = (rand() % 100) + 1;

	//if the number generated is less than the number stored at the
	//the current index, we use that index as the number of customers 
	//that have arrived. We can do this because we aggregated the 
	//percentages whithin the array in an earlier function.
	for(numArrived = 0; numArrived < 5; numArrived++) {
		if(randomNum < pcts[numArrived]) {
			return numArrived;
		}
	}

	//in this case, the random num was not less than the lowerbound of 
	//the maximum number of customer arrivals which is 4. So in that case
	//we just return the max number of customers that can arrive. 
	return numArrived - 1;
}

int getServiceTime() {
	return 0;
}

//stores the percentage value of each line within the dat file in each
//index. I make the assumption that the number of customers arriving 
//will always be a number between 0-4 inclusive.
void readDatFile(int pcts[], char fname[]) {
	FILE *fin;
	int *p;
	p = pcts;
	int num, percentage;
	int i;

	fin = fopen(fname, "r");

	i = fscanf(fin, "%d %d", &num, &percentage);

	while ( i != EOF) {
		
		if (i == 2) {
			*p = percentage;
			p++;
		}



		i = fscanf(fin, "%d %d", &num, &percentage);
	}

	fclose(fin);

}

//This function takes the array that stores the percentages
//from the dat file and then adds the value of each previous
//index to the current index in series. What that does is make 
//it so each index (representing a possible number of arriving 
//customers) holds the upper bound of it's range of possible values
// so for the given set of input data, 
//[0] = 15 (15 % chance)
//[1] = 35 (20 % chance)
//[2] = 60 (25 % chance)
//[3] = 70 (10 % chance)
//[4] = 100 (30 % chance)
void aggregatePcts(int pcts[]) {
	int i;
	
	for(i = 1; i < 5; i++) {
		pcts[i] += pcts[i-1];
	}

}

//simulation method called by the main method
//the fname array is the file that we want to use
//for the dat file. By default it's the example given
//in the project description if no filename is given 
//as an argument at the command line
void simulation (int numOfTellers, char fname[]) {

	// and array of tellers the size we specified in main()
	teller tellers[numOfTellers];

	//seeds the random number generator with the current clock time
	time_t seed;
	srand((unsigned) time(&seed));

	double t;
	int currentTime = 0; //the current time interval
	int cID = 0;//customer identifier
	int waitTime;//holds the difference between arrival time and time when leaving the line 
	queue q;
	stats s;
	data customer;//when a customer arrives, we use this object to put them in the queue one by one
	initializeq(&q); 
	initializes(&s);

	int intervalPct[5];//our spread of chance for an arrival of customers
	int numArrived, i;

	readDatFile(intervalPct, fname);//gets percentages from dat file
	aggregatePcts(intervalPct);//adds the perecentages in series

	//initializing the tellers array to unoccupied and no time for service
	for(i = 0; i< numOfTellers; i++) {
		tellers[i].occupied = 0;
		tellers[i].serviceTime = 0;
	}

	//the primary loop of the simulation, runs until a day is complete
	while(currentTime < WORKING_DAY) {
	
		//generates a random number and then and then
		//returns the first index whose associated value is greater than 
		//the random number. This index returned is number of customers arriving                                                            
		numArrived = getNumArrivals(intervalPct);
		
		//we enqueue the data of each customer
		//giving them a unique ID and recording the time they arrive
		for(i = 0; i <= numArrived; i++){
			customer.c = cID;
			customer.t = currentTime;

			enqueue(customer, &q);
			cID++;
		}

		//now that the customers are line we want to make sure that a teller's
		//time and occupancy are updated before we check to 
		//see if any of the customers can go straight from the lne to a teller 
		for( i = 0; i< numOfTellers; i++) {
			//1 means occupied so we decremnt time and adjust occurdingly
			if(tellers[i].occupied == 1) {

				//decrement service time if their occupied
				tellers[i].serviceTime--;

				//if time is less than one interval after decrement than that
				//means the teller is done servicing that customer so we can
				//add the customer to the total and set the occupancy to vacant
				if(tellers[i].serviceTime < 1) {
					tellers[i].occupied = 0;
					addCustomer(&s);
				}
			}

			//now that this teller is up to date we can check to see
			//if there are any customers that can be dequeued.
			//If so, we get the total time they waited, add it to the running total for the average
			//and then check if that wait time was the maximum so far 
			if((tellers[i].occupied == 0) && !empty(&q))	{
				customer = dequeue(&q);
				waitTime = currentTime - (customer.t);
				setMaxTime(waitTime, &s);
				addWait(waitTime, &s);
				
				//we also set the tellers occupancy to 1 to indicate they are busy
				//and we get the amount of time that this given service will take
				tellers[i].occupied = 1;
				tellers[i].serviceTime = expdist (AVG_SERVICE); 
			}
		}

		//after we have enqueued all the customers that have arrived during this interval and 
		//then placed them with a teller if any were availible, we then get the length of the line 
		//for this interval, add it to the running total for the average and then check to see if 
		//the line is longer than the current maximum 
		addLength(q.cnt, &s);
		setMaxLength(q.cnt, &s);
		currentTime++;
	              

	}

	//once the loop above has exited, we've completed an entire day and we can print out stats to the screen
	printf("\nSimulation: %d Tellers\n", numOfTellers);
	printf("Total Served: %d Customers\n", getTotalCustomers(&s));
	printf("Average Wait In Line: %f Minutes\n", getAvgWait(&s));
	printf("Max Time Spent Waiting: %d Minutes\n", getMaxTime(&s));
	printf("Average Line Length: %f Customers\n", getAvgLength(&s));
	printf("Max Line Length: %d Customers\n\n", getMaxLength(&s));
} 

//Main function just checks to see if a dat file parameter was given 
//and then either uses the default file or the file given as a parameter 
//for the simulation data.   
int main (int argc, char* argv[]) {

	char fname[] = "proj2.dat";
	
	if(argc == 2){
		simulation(7, argv[1]);
		simulation(6, argv[1]);
		simulation(5, argv[1]);
		simulation(4, argv[1]);
	}              
    else {
    	simulation(7, fname);
  	 	simulation(6, fname);
    	simulation(5, fname);
    	simulation(4, fname);
    }
}



