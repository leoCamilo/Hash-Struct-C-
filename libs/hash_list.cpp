#include <iostream>
#include "hash_list.h"
#include "word_list.h"
#include "hash.h"	// has the hash calc functions 

using std::cout;

// types
// 0 - raw data
// 1 - list of data

struct data {
	bool type = 0;
	void* content;
};

hash_list::hash_list() {
	vector = new Data*[size];

	while (size--)
		vector[size] = NULL;

	size = 10000;
}

hash_list::hash_list(int size) {
	this->size = size;
	vector = new Data*[size];

	while (size--)
		vector[size] = NULL;
}

void hash_list::add(char * word) {
	int index = calc(word, size);
	Data* temp_data;

	if (!(temp_data = vector[index])) {
		Data* new_data = new Data;
		new_data->content = (void*) word;
		vector[index] = new_data;
	} else {
		if (!temp_data->type) {
			word_list* list = new word_list();
			list->add((char*)temp_data->content);
			list->add(word);
			temp_data->content = list;
			temp_data->type = 1;
		} else {
			word_list* list = (word_list*)temp_data->content;
			list->add(word);
		}
	}
}

char* hash_list::get(char * word) {
	Data* temp_data = vector[calc(word, size)];

	if (!temp_data)
		return NULL;

	if (!temp_data->type)
		return (char*)temp_data->content;

	word_list* list = (word_list*)temp_data->content;
	return list->get(word);
}

void hash_list::remove(char * word) {
	int index = calc(word, size);
	Data* temp_data = vector[index];

	if (!temp_data)
		return;

	if (!temp_data->type) {
		//delete temp_data->content;
		delete temp_data;
		vector[index] = NULL;
		return;
	}

	word_list* list = (word_list*)temp_data->content;
	list->remove(word);

	if (!list->lenght()) {
		delete list;			// test if when u remove all elements the program don't break
		vector[index] = NULL;
	}
}

void hash_list::print() {
	for (int i = 0; i < size; i++)
		cout << "\n-" << vector[i];
}