#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"
#include "vector.h"
#include "heap.h"
#include "problem.h"
#include "path.h"


/**
 * Função criada para construir o vetor de nós que foram visitados
 * Cada posição do vetor corresponde a um nó e ele guarda um bool
 * @param size tamanho do vetor 
*/
Vector *visited_construct(int size)
{
    Vector *visited = vector_construct();

    for (int i = 0; i < size; i++)
    {
        vector_push_back(visited, false);
    }

    return visited;
};


/**
 * Função criada para pegar os vizinhos de um determinado nó
 * que está sendo visitado, ela checa se esse vizinho já foi viitado
 * se não foi adiciona no vetor de vizinhos
 * @param nodes vetor de nós que vieram do Problem
 * @param source valor do nó de origem
*/
Vector *get_neighbors(Vector *visited, Vector *nodes, int source)
{
    Vector *neighbors = vector_construct();
    bool was_visited;
    int size = vector_size(nodes);


    for (int i = 0; i < size; i++)
    {
        ProblemNode *aux = vector_get(nodes, i);
        was_visited = vector_get(visited, aux->node_value);

        if (aux->source_node == source && was_visited == false)
        {
            vector_push_back(neighbors, aux);
        }
    }

    return neighbors;
}


/**
 * Função criada para checar se o vetor de visitados ainda
 * tem algum que não foi visitado, usada para acabar 
 * o loop principal do algoritmo
 * @param visited vetor de visitados
*/
bool visited_check(Vector *visited)
{
    int size = vector_size(visited);

    for (int i = 0; i < size; i++)
    {
        if(vector_get(visited, i) == false)
        {
            // printf("Ainda tem no sem visitar\n");
            return false;
        }
    }
    return true;
};


Vector *run_dijkstra(Problem *problem)
{
    Problem *p = problem;
    Vector *visited = visited_construct(p->size);
    Vector *paths = paths_construct(p->size);
    Heap *not_visited = heap_construct();

    ProblemNode *pn;
    ProblemNode *node_removed;
    ProblemNode *node_path;
    ProblemNode *origin = problem_node_construct(0, 0, 0); //nó de origem
    int node_removed_cost = 0;
    int node_value = 0;
    bool was_visited = true;

    heap_push(not_visited, origin, origin->origin_cost);
    
    while (heap_empty(not_visited) == false)
    {
        node_removed = heap_pop(not_visited);

        //verifica se o nó ainda nao foi visitado
        if (vector_get(visited, node_removed->node_value) == false)
        {
            node_removed_cost = node_removed->origin_cost;

            node_path = vector_get(paths, node_removed->node_value);
            node_path->source_node = node_removed->source_node;
            node_path->path_cost = node_removed->path_cost;
            node_path->origin_cost = node_removed->origin_cost;

            node_value = node_removed->node_value;   

            Vector *neighbors = get_neighbors(visited, p->nodes, node_value);

            // adiciona os vizinhos na heap somando o custo total pra origem
            for (int i = 0; i < vector_size(neighbors); i++)
            {
                pn = vector_get(neighbors, i);
                pn->origin_cost = pn->path_cost + node_removed_cost;
                heap_push(not_visited, pn, pn->origin_cost);       
            }

            vector_destroy(neighbors);

            //marca como visitado depois que adiciona os vizinhos na heap
            vector_set(visited, node_value, &was_visited); 
        }               
    };

    vector_destroy(visited);
    heap_destroy(not_visited);
    free(origin);

    return paths;
};