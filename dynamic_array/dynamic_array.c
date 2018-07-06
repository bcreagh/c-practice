#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"


dynamic_array *new_dynamic_array() {
	dynamic_array *new_d_array = malloc(sizeof(dynamic_array));
	new_d_array->capacity = 4;
	new_d_array->size = 0;
	new_d_array->data = (int *)malloc(sizeof(int) * 4);

	return new_d_array;
}

void push(int item, dynamic_array *d_array) {
	if(d_array->size == d_array->capacity) {
		resize(d_array);
	}
	d_array->data[d_array->size] = item;
	d_array->size += 1;
}

int get(int index, dynamic_array *d_array){
	if(index >= (d_array->size)) {
		exit(EXIT_FAILURE);	
	}

	return d_array->data[index];
}

void resize(dynamic_array *d_array) {
	int new_capacity = d_array->capacity * 2;
	d_array->capacity = new_capacity;
	
	int *new_data = (int*)malloc(sizeof(int) * new_capacity);
	
	for(int i = 0; i < d_array->size; i++) {
		new_data[i] = d_array->data[i];
	}
	
	free(d_array->data);
	d_array->data = new_data;
}


