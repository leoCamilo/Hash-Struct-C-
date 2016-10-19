#include "hash.h"

int calc(char * word, int limit) {
	int e = 1;
	BFN total = 0;

	while (*word)
		total += *word++ * e++;

	return (total + ((e - 1) * e)) % limit;
}

int calc_variant(char * word, int limit, int variant) {
	int e = 1;
	BFN total = 0;

	//variant %= 10;
	//!variant ? variant = 1 : variant;

	// try not use division operation, heavy instruction

	while (*word)
		total += (*word++ + variant) * (e++ + variant);

	return (total + ((e - 1) * variant)) % limit;
}