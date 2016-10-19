#include <iostream>
#include "hash_hash.h"
#include "hash.h"	// has the hash calc functions 

#define SUB_HASH_SIZE 150

using std::cout;

struct data {
	void* raw_content = NULL;
	void* hash_content = NULL;
};

int hash_hash::TESTE = 0;
int hash_hash::LAST_LVL = 1;

hash_hash::hash_hash() {
	vector = new Data*[size];

	while (size--)
		vector[size] = NULL;

	size = 10000;
}

/*
hash_hash::~hash_hash() {
	int len = this->size;

	while (len--)
		if (vector[len]) {
			if (vector[len]->content)
				delete vector[len]->content;

			delete vector[len];
		}

	delete[] vector;
}
*/
hash_hash::hash_hash(int size) {
	this->size = size;
	vector = new Data*[size];

	while (size--)
		vector[size] = NULL;
}

hash_hash::hash_hash(int size, int variant) {
	this->size = size;
	this->variant = variant;
	vector = new Data*[size];

	while (size--)
		vector[size] = NULL;
}

void hash_hash::add(char * word) {
	int index = calc_variant(word, size, variant);
	Data* temp_data;

	if (!(temp_data = this->vector[index])) {
		Data* new_data = new Data;
		new_data->raw_content = (void*) word;
		vector[index] = new_data;
	} else {
		if (!temp_data->hash_content) {
			hash_hash* list = new hash_hash(SUB_HASH_SIZE, variant + 1);
			int a = calc_variant((char*)temp_data->raw_content, list->size, list->variant);
			int b = calc_variant(word, list->size, list->variant);
			
			if (a == b) {
				//cout << "\nconflito raro nova hash";
				//cout << "\npalavra 1: " << a << " - " << (char*)temp_data->raw_content;
				//cout << "\npalavra 2: " << b << " - " << word << '\n';
				
				TESTE++;
				//list->clean();
				//delete list;
				//return;
			}
			
			list->setLevel(level + 1);
			list->add(word);
			temp_data->hash_content = list;
		} else {
			hash_hash* list = (hash_hash*)temp_data->hash_content;
			list->add(word);
		}
	}

	qtd++;
}

char* hash_hash::get(char * word) {
	Data* temp_data = vector[calc_variant(word, size, variant)];

	if (!temp_data)
		return NULL;

	if (!strcmp(word, (char*)temp_data->raw_content))
		return (char*)temp_data->raw_content;

	if (temp_data->hash_content) {
		hash_hash* list = (hash_hash*)temp_data->hash_content;
		return list->get(word);
	}

	return NULL;
}

void hash_hash::remove(char * word) {	// TODO - CONCERTAR LINHA ABAIXO
	int index = calc_variant(word, size, variant);
	Data* temp_data = vector[index];

	if (!temp_data)
		return;

	if (!strcmp(word, (char*)temp_data->raw_content)) {
		temp_data->raw_content = NULL;
		qtd--;
		return;
	}

	hash_hash* list = (hash_hash*)temp_data->hash_content;
	list->remove(word);
	qtd--;

	if (!list->lenght()) {
		delete list;					// test if when u remove all elements the program don't break
		temp_data->hash_content = NULL;
	}
}

int hash_hash::lenght() {
	return qtd;
}

void hash_hash::print() {
	for (int i = 0; i < size; i++)
		cout << "\n-" << vector[i];
}

void hash_hash::clean() {	// percorre the vector clean the Data references
	delete[] vector;
}

int hash_hash::getTest() {
	return TESTE;
}

void hash_hash::setLevel(int lvl) {
	LAST_LVL = (level = lvl) > LAST_LVL ? level : LAST_LVL;
}

int hash_hash::getLevel() {
	return LAST_LVL;
}