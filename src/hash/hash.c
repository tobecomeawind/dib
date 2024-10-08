#include "hash.h"

#include <math.h>
#include <string.h>


long int hash(char* val)
{
	long int hashval = 0;
	int len_s   = strlen(val);
	
	for(int i = 0; i < len_s; i++)
		hashval += (long) pow(SEED, len_s - (i+1)) * val[i];
	
	return hashval;	
}


/*
int hash_index(long int hash_number, int size)
{
	return (int)(hash_number % size);	
}


int main()
{
	int size = 5;	
	long int hash_set[size];	

	hash_set[hash_index(hash("Petya", SEED), size)] = hash("Petya", SEED);
	hash_set[hash_index(hash("Masha", SEED), size)] = hash("Masha", SEED);
	hash_set[hash_index(hash("Dasha", SEED), size)] = hash("Dasha", SEED);
	hash_set[hash_index(hash("KFJSF", SEED), size)] = hash("KFJSF", SEED);
	hash_set[hash_index(hash("GGGGG", SEED), size)] = hash("GGGGG", SEED);
	
	return 0;
}
*/
