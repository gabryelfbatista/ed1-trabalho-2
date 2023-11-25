#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdbool.h>

/**
 * Estrutura Heap de valores mínimos
*/

typedef void *data_type;
typedef struct Heap Heap;

// Cria uma heap vazia
Heap *heap_construct();

// Insere um elemento na heap 
void heap_push(Heap *h, void *data, int priority);

// Retorna true se a heap estiver vazia
bool heap_empty(Heap *h);

// Remove o primeiro elemento da heap e retorna o seu conteúdo
void *heap_pop(Heap *h);

// Libera da memória o espaço da Heap
void heap_destroy(Heap *h);

#endif