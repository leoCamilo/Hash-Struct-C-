#include <iostream>
#include <string.h>

#include "word_list.h"

struct node {
	char* content;
	struct node* next = NULL;
	struct node* back = NULL;
};

word_list::word_list() {
	start = NULL;
	middle = NULL;
	end = NULL;
	qtd = 1;
	middle_flag = 0;
}

void word_list::add(char * word) {
	if (!start) {
		start = new Node;
		middle = start;
		end = start;
		start->content = word;
		return;
	}

	Node* temp_node = start;
	char* temp_word = (char*) middle->content;
	int add_after_middle = 0;
	int boolean = 0;

	if ((boolean = strcmp(word, temp_word)) > 0) {
		temp_node = middle;
		add_after_middle = 1;
	}

	if (!boolean)
		temp_node = middle;

	temp_word = (char*) temp_node->content;

	while (strcmp(word, temp_word) > 0) {
		if (!temp_node->next) {
			add_at_end(word);
			return;
		}

		temp_node = temp_node->next;
		temp_word = (char*) temp_node->content;
	}

	Node* new_node = new Node;
	new_node->back = temp_node->back;
	new_node->next = temp_node;
	new_node->content = word;
	qtd++;

	if (temp_node != start) {
		temp_node->back->next = new_node;
		temp_node->back = new_node;
		return;
	}

	temp_node->back = new_node;
	start = new_node;

	if (add_after_middle) {
		if (++middle_flag == 2) {
			middle = middle->next;
			middle_flag = 0;
		}
	} else
		if (--middle_flag == -2) {
			middle = middle->back;
			middle_flag = 0;
		}
}

char * word_list::get(char * word) {
	Node* temp_node = find(word);
	return temp_node ? (char*)temp_node->content : NULL;
}

void word_list::remove(char * word) {
	int after_middle;
	Node *temp_node = find(word, &after_middle);
	Node *before, *after;

	if (temp_node) {
		qtd--;
		before = temp_node->back;
		after = temp_node->next;

		before ? before->next = after : start = after;
		after ? after->back = before : end = before;

		if (!qtd) {
			start = NULL;
			middle = NULL;
			end = NULL;
		}

		if (after_middle)
			if (--middle_flag == -2) {
				middle = middle->back;
				middle_flag = 0;
			}
		else
			if (++middle_flag == 2) {
				middle = middle->next;
				middle_flag = 0;
			}

		if (temp_node == middle)
			middle = (middle_flag > 0) ? middle->next : middle->back;

		delete temp_node;
	}
}

void word_list::print() {	// temp
	Node* temp = start;
	char* a;

	if (!temp) {
		std::cout << "empty\n";
		return;
	}

	do {
		a = (char*) temp->content;
		std::cout << a << "\n";
		// do { std::cout << *a; } while (*a++);
	} while (temp = temp->next);

	a = (char*) start->content;
	std::cout << "\nstart: " << a << '\n';

	a = (char*) middle->content;
	std::cout << "middle: " << a << '\n';

	a = (char*) end->content;
	std::cout << "end: " << a << "\nsize: " << qtd << '\n';
}

int word_list::lenght() {
	return qtd;
}

Node * word_list::find(char * word) {
	if (!start || !word)
		return NULL;

	Node* temp_node = start;
	char* temp_word = (char*)middle->content;
	int boolean = 0;

	if ((boolean = strcmp(word, temp_word)) > 0 && !boolean)
		temp_node = middle;

	temp_word = (char*)temp_node->content;

	while ((boolean = strcmp(word, temp_word)) > 0 && temp_node->next) {
		temp_node = temp_node->next;
		temp_word = (char*)temp_node->content;
	}

	if (!boolean)
		return temp_node;

	return NULL;
}

Node * word_list::find(char * word, int * after_middle) {
	if (!start || !word)
		return NULL;

	*after_middle = 0;
	Node* temp_node = start;
	char* temp_word = (char*)middle->content;
	int boolean = 0;

	if ((boolean = strcmp(word, temp_word)) > 0) {
		temp_node = middle;
		*after_middle = 1;
	}

	if (!boolean)
		return middle;

	temp_word = (char*)temp_node->content;

	while ((boolean = strcmp(word, temp_word)) > 0 && temp_node->next) {
		temp_node = temp_node->next;
		temp_word = (char*)temp_node->content;
	}

	if (!boolean)
		return temp_node;

	return NULL;
}

void word_list::add_at_end(char* word) {	// add element at the end of the list
	end->next = new Node;
	end->next->back = end;
	end = end->next;
	end->content = word;
	qtd++;

	if (++middle_flag == 2) {
		middle = middle->next;
		middle_flag = 0;
	}
}