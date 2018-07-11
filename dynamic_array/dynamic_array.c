#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

static const int no_resize_required = 0;
static const int upsize_required = 1;
static const int downsize_required = 2;

static void resize(dynamic_array *d_array);
static int determine_resize_type(dynamic_array *d_array);
static void upsize(dynamic_array *d_array);
static void downsize(dynamic_array *d_array);


dynamic_array *new_dynamic_array() {
	dynamic_array *new_d_array = malloc(sizeof(dynamic_array));
	new_d_array->capacity = 4;
	new_d_array->size = 0;
	new_d_array->data = (int *)malloc(sizeof(int) * 4);

	return new_d_array;
}

int get(int index, dynamic_array *d_array){
	if(index >= (d_array->size)) {
		exit(EXIT_FAILURE);	
	}

	return d_array->data[index];
}

void push(int item, dynamic_array *d_array) {
	int resize_type = determine_resize_type(d_array);

	if(resize_type == upsize_required) {
		resize(d_array);
	}

	d_array->data[d_array->size] = item;
	d_array->size += 1;
}

int pop(dynamic_array *d_array) {
	int last_item;
	int resize_type;

	if(d_array->size <= 0) {
		fprintf(stderr, "ERROR: Tried to pop from a dynamic_array with a size of %d\n", d_array->size);
		exit(EXIT_FAILURE);
	}
	last_item = d_array->data[d_array->size -1];
	d_array->size -= 1;

	resize_type = determine_resize_type(d_array);
	if(resize_type == downsize_required) {
		resize(d_array);
	}

	return last_item;
}

void resize(dynamic_array *d_array) {

	int resize_type = determine_resize_type(d_array);
	
	if(resize_type == upsize_required) {
		upsize(d_array);
	} else if(resize_type == downsize_required) {
		downsize(d_array);
	} else {
		exit(EXIT_FAILURE);
	}
}

static int determine_resize_type(dynamic_array *d_array) {
	if(d_array->size == d_array->capacity) {
		return upsize_required;
	} else if (d_array->size <= (d_array->capacity / 4)) {
		return downsize_required;
	}
	return no_resize_required;
}

static void upsize(dynamic_array *d_array) {

	int new_capacity = d_array->capacity * 2;
	d_array->capacity = new_capacity;
	
	int *new_data = (int*)malloc(sizeof(int) * new_capacity);
	
	for(int i = 0; i < d_array->size; i++) {
		new_data[i] = d_array->data[i];
	}
	
	free(d_array->data);
	d_array->data = new_data;
}

static void downsize(dynamic_array *d_array) {
	int new_capacity = d_array->capacity / 4;

	if(new_capacity < d_array->size) {
		exit(EXIT_FAILURE);
	}

	d_array->capacity = new_capacity;
	
	int *new_data = (int*)malloc(sizeof(int) * new_capacity);
	
	for(int i = 0; i < d_array->size; i++) {
		new_data[i] = d_array->data[i];
	}
	
	free(d_array->data);
	d_array->data = new_data;
}


