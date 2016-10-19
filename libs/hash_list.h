#pragma once

#ifndef HASH_list_H
#define HASH_list_H

struct data typedef Data;

class hash_list {
	int size = 10000;
	Data** vector;

public:
	hash_list();
	hash_list(int size);

	void add(char* word);
	char* get(char* word);
	void remove(char* word);	// returns the element and remove from the hash struct

	void print();
};

#endif