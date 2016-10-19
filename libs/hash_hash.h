#pragma once

#ifndef HASH_hash_H
#define HASH_hash_H

struct data typedef Data;

class hash_hash {
	int size = 10000;
	Data** vector;
	int variant = 1;
	int qtd = 0;
	int level = 0;
	static int TESTE;
	static int LAST_LVL;

public:
	hash_hash();
	//~hash_hash();
	hash_hash(int size);
	hash_hash(int size, int variant);

	void add(char* word);
	char* get(char* word);
	void remove(char* word);	// returns the element and remove from the hash struct
	int lenght();
	void print();

	void clean();
	int getTest();
	void setLevel(int lvl);
	int getLevel();
};

#endif