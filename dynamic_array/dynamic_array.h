#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

typedef struct dynamic_array {
	int capacity;
	int size;
	int *data;
} dynamic_array;

dynamic_array *new_dynamic_array();
void push(int item, dynamic_array *d_array);
int pop(dynamic_array *d_array);
int get(int index, dynamic_array *d_array);
void resize(dynamic_array *d_array);

#endif
