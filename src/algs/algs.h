#ifndef ALGS_H
#define ALGS_H

#include "types.h"

int binsearch(void* *buf, int size,
		      void *target,
			  vtypes type);

int compare(void* target, void* buffer, int index, vtypes type);

#endif
