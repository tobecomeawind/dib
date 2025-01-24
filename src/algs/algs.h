#ifndef ALGS_H
#define ALGS_H

#include "types.h"
#include "stdint.h"

int8_t binsearch(void** buf, uint8_t size, void* target, bstypes type);

typedef struct queue_node_t {

	void*                data;
	struct queue_node_t* next;

} QueueNode;


typedef struct queue_t {

	uint8_t    size;
	QueueNode* head;
	QueueNode* tail;

} Queue;



QueueNode* queueNodeConstruct (void*      data);
void       queueNodeDestruct  (QueueNode* qnptr);
Queue*     queueConstruct     (void);
void       queueDestruct      (Queue* qptr);
void       queuePush          (Queue* qptr, void* data);
void*      queuePop           (Queue* qptr);


#endif
