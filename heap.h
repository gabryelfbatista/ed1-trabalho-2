#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdbool.h>

typedef void *data_type;
typedef struct Heap Heap;

Heap *heap_construct();

void heap_push(Heap *h, void *data, int priority);

bool heap_empty(Heap *h);

void *heap_pop(Heap *h);

void heap_destroy(Heap *h);

#endif