#include "hash.h"

#include <math.h>
#include <string.h>
#include <stdio.h>

uint64_t hash(char* val)
{
	uint64_t hashval = 0;
	uint8_t  len_s   = strlen(val);
	
	for(uint8_t i = 0; i < len_s; i++)
		hashval += (uint64_t) pow(SEED, len_s - (i+1)) * val[i];
	
	return hashval;	
}



uint8_t hash_index(uint64_t hash_number, int size)
{
	printf("\nHash index for %li = %i\n", hash_number, hash_number % size);	
	return (uint8_t)(hash_number % size);	
}


int main()
{
	int size = 4;	
	char* hash_set[size];	

	uint64_t Petya = hash("Petya");
	uint64_t Masha = hash("Masha");
	uint64_t Vasya = hash("Vasya");
	uint64_t Oleg  = hash("Oleg");

	hash_set[hash_index(Petya, size)] = "Petya";
	hash_set[hash_index(Masha, size)] = "Masha";
	hash_set[hash_index(Vasya, size)] = "Olegg";
	hash_set[hash_index(Oleg,  size)] = "Olegg";

	if (hash_set[hash_index(Petya, size)] == "Olegg") {
		printf("\nAll good\n");	
	}		

	return 0;
}

