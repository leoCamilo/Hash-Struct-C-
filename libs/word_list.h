#pragma once

#ifndef WORD_L_H
#define WORD_L_H

struct node typedef Node;

class word_list {
	Node* start;
	Node* end;
	Node* middle;
	
	int qtd;
	char middle_flag;	// control when advance with the middle

public:
	word_list();
	void add(char* word);		// ordered insertion
	char* get(char* word);		// returns NULL when elements are not find
	void remove(char* word);
	void print();
	int lenght();

private:
	Node* find(char* word);
	Node* find(char* word, int * after_middle);
	void add_at_end(char* word);
};

#endif