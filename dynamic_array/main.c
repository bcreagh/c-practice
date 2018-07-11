#include <stdio.h>
#include "dynamic_array.h"


int main(int argc, char *argv[]) {

	dynamic_array *my_array = new_dynamic_array();
	printf("old size: %d\n", my_array->size);
	printf("old capacity: %d\n", my_array->capacity);
	push(23, my_array);
	push(234, my_array);
	push(345, my_array);
	push(122, my_array);
	push(9999, my_array);
	printf("new size: %d\n", my_array->size);
	printf("new capacity: %d\n", my_array->capacity);
	printf("index 2: %d\n", get(2, my_array));
	printf("index 4: %d\n", get(4, my_array));
	printf("pop1: %d\n", pop(my_array));
	printf("pop2: %d\n", pop(my_array));
	printf("pop3: %d\n", pop(my_array));
	printf("new size: %d\n", my_array->size);
	printf("new capacity: %d\n", my_array->capacity);
	printf("pop4: %d\n", pop(my_array));
	printf("new size: %d\n", my_array->size);
	printf("new capacity: %d\n", my_array->capacity);
	printf("pop5: %d\n", pop(my_array));
	
	
	
	return 0;
}


