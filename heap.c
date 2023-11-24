#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef struct HeapNode
{
    void *data;
    int priority;
} HeapNode;


struct Heap
{
    HeapNode *nodes; 
    int size;
    int allocd;
};


const int initial_size = 10;
const int growth_step = 5;


Heap *heap_construct()
{
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->nodes = (HeapNode*)malloc(initial_size * sizeof(HeapNode));
    h->size = 0;
    h->allocd = initial_size;
    return h;
};


void heap_swap(Heap *h, int i, int j)
{
    HeapNode node_salvo = h->nodes[i];

    h->nodes[i] = h->nodes[j];
    h->nodes[j] = node_salvo;
};


void heapify_up(Heap *h)
{
    int idx, idx_pai;
    idx = h->size - 1;

    while(idx != 0)
    {
        idx_pai = (idx-1)/2;
        
        if (h->nodes[idx_pai].priority > h->nodes[idx].priority)
        {
            heap_swap(h, idx_pai, idx);
        }

        idx = idx_pai;
    }
};


void heapify_down(Heap *h)
{
    int idx, idx_left, idx_right;
    idx = 0;
    
    while(idx < h->size)
    {
        idx_left = 2*idx + 1;
        idx_right = 2*idx + 2;   

        // se o filho esquerda n existe, quer dizer que chegou no fim da arvore
        if (idx_left > h->size)
        {
            break;
        }
        else // se o filho esquerda for valido 
        {
            //confere se o filho da direita eh valido
            if (idx_right < h->size)
            {
                // se for valido e for menor que o filho esquerda
                if (h->nodes[idx_right].priority <= h->nodes[idx_left].priority)
                {
                    // se filho direita menor, troca
                    if (h->nodes[idx_right].priority <= h->nodes[idx].priority)
                    {
                        heap_swap(h, idx_right, idx);
                        idx = idx_right;
                    }
                    else // se filho direita maior pode parar
                    {
                        break;
                    }
                }
                else // esquerda eh menor que direita 
                {
                    // se filho esquerda menor troca
                    if (h->nodes[idx_left].priority <= h->nodes[idx].priority)
                    {
                        heap_swap(h, idx_left, idx);
                        idx = idx_left;
                    }
                    else // se filho esquerda maior pode parar
                    {
                        break;
                    }
                }
            }
            else //se filho direita n for valido, compara apenas com o da esquerda
            {
                //troca se for menor
                if (h->nodes[idx_left].priority <= h->nodes[idx].priority)
                {
                    heap_swap(h, idx_left, idx);
                    idx = idx_left;
                }
                else //se n for menor, pode parar
                {
                    break;
                }
            }
        }
    }
};


bool heap_empty(Heap *h)
{
    if (h->size == 0)
    {
        return true;
    }
    else return false;
};


void heap_push(Heap *h, void *data, int priority)
{
    if (h->size == h->allocd)
    {
        h->allocd *= growth_step;
        h->nodes = (HeapNode *)realloc(h->nodes, h->allocd * sizeof(HeapNode));
    }

    h->nodes[h->size].data = data;
    h->nodes[h->size].priority = priority;
    h->size++;

    if (h->size >= 1)
    {
        heapify_up(h);
    }
};


void *heap_pop(Heap *h)
{
    HeapNode node_removido = h->nodes[0];
    h->nodes[0] = h->nodes[h->size-1];
    h->size--;

    heapify_down(h);

    return node_removido.data;
};


void heap_destroy(Heap *h)
{
    free(h->nodes);
    free(h);
};