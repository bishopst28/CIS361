//author: Stanley Bishop

#include "stats.h"
//This file is primarily getters and setters 
//for a stats struct that contains the running
//values for waiting and line length and total customers served
//and also the max values for each statistic 
//The only real calculations done here is for the averages.
void initializes(stats *s) {

	s -> t.totalCustomers = 0;
	s -> t.sumWait = 0;
	s -> t.sumLength = 0;

	s -> m.maxTime = 0;
	s -> m.maxLength = 0;
}

//will only set max time if the value is higher than the current max
void setMaxTime(int t, stats *s) {

	if(t > s -> m.maxTime)
		s -> m.maxTime = t;

}

//will only set max length if the value is higher than the current max
void setMaxLength(int length, stats *s) {

	if(length > s -> m.maxLength)
		s-> m.maxLength = length;

}

//getter for max time
int getMaxTime(stats *s) {
	return s -> m.maxTime;
}

//getter for max line length
int getMaxLength(stats *s) {
	return s -> m.maxLength;
}

//increments the number of customers serviced
void addCustomer(stats *s) {
	s -> t.totalCustomers++;
}

//adds a waiting time to the running total for the average
void addWait(int wait, stats *s) {
	s -> t.sumWait += wait;
}

//adds a line length to the running total for the average
void addLength(int length, stats *s) {
	s -> t.sumLength += length;
}

//calculates the average waiting time for all the serviced customers
float getAvgWait(stats *s) {
	return (float) s -> t.sumWait / s -> t.totalCustomers;
}

//calculates the average line length at the end of a one 
//minute interval across a work day
float getAvgLength(stats *s) {
	return (float) s -> t.sumLength / INTERVAL;
}

//returns the total number of customers serviced
int getTotalCustomers(stats *s) {
	return s -> t.totalCustomers;
}
