#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define FULL 10000

typedef unsigned int cid;
typedef unsigned int arrivalTime;

typedef enum{false, true} boolean;

//a customer represented as data in an element
struct _data {
	cid c;
	arrivalTime t;
};
typedef struct _data data;

//an element in the queue
struct _elem {
	data d;
	struct elem *next;
};
typedef struct _elem elem;

struct _queue {
	int cnt;	//num elements in queue
	elem *front; //ptr to the front element 
	elem *rear; //ptr to the back element 
};
typedef struct _queue queue;

void initializeq(queue *q);
void enqueue(data d, queue *q);
data dequeue(queue *q);
data front(const queue *q);
boolean empty(const queue *q);
boolean full(const queue *q);