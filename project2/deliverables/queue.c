//author: Stanley Bishop

#include "queue.h"


//zeros out all the queue values
void initializeq(queue *q) {

	q -> cnt = 0;
	q -> front = NULL;
	q -> rear = NULL;

}

//removes an element from the queue
//takes the sets the front node to
//the node after the front
//stores the front nodes data to be
//returned and the free's the memeory 
//that was once used by the previous front node 
data dequeue(queue *q) {

	data d;
	elem *p;

	d.c = q -> front -> d.c;
	d.t = q -> front -> d.t;
	p = q -> front;
	q -> front = (elem *)q -> front -> next;
	q -> cnt--;
	free(p);
	return d;

}

//takes the given data, mallocs a new
//node with the given data, then sets the 
//value of the next node after the rear to 
//the new node and then makes that new node the
//node at the rear
void enqueue(data d, queue *q) {

	elem *p;

	p = malloc(sizeof(elem));
	p -> d.c = d.c;
	p -> d.t = d.t;
	p -> next = NULL;
	if (!empty(q)) {
		q -> rear -> next = (struct elem *)p;
		q -> rear = p;
	}
	else 
		q -> front = q -> rear = p;
	q -> cnt++;

}

//returns the data at the front node
data front(const queue *q) {
	return (q -> front -> d);
}

//indicates whether or not the queue is empty
boolean empty(const queue *q) {
	return ((boolean) (q -> cnt == EMPTY));
}

//indicates whether or not the queue is at max capacity 
boolean full(const queue *q) {
	return ((boolean)(q -> cnt == FULL));
}










