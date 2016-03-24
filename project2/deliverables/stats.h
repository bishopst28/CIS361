#include <stdio.h>
#include <stdlib.h>

#define INTERVAL 480; 

struct _totals { 
	int totalCustomers;
	int sumWait;
	int sumLength;
};
typedef struct _totals totals;

struct _maximums {
	int maxTime;
	int maxLength;
};
typedef struct _maximums maximums;

struct _stats {

	totals t;
	maximums m;

};
typedef struct _stats stats;

void initializes(stats *s);
void setMaxTime(int time, stats *s);
void setMaxLength(int length, stats *s);
int getMaxTime(stats *s);
int getMaxLength(stats *s);
void addCustomer(stats *s);
void addWait(int wait, stats *s);
void addLength(int length, stats *s);
float getAvgWait(stats *s);
float getAvgLength(stats *s);
int getTotalCustomers(stats *s);