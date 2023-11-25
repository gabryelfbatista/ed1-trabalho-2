#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "problem.h"
#include "vector.h"

/**
 * Nessa função ao construir o nó, eu sempre inicializo
 * a valor pra origin como 0, pois isso será atualizado apenas no
 * algoritmo de dijkstra
 * @param source valor do nó de origem
 * @param value valor do nó vizinho
 * @param cost custo de ir para o vizinho 
*/
ProblemNode *problem_node_construct(int source, int value, int cost)
{
    ProblemNode *n = (ProblemNode *)calloc(1, sizeof(ProblemNode));
    n->source_node = source;
    n->node_value = value;
    n->path_cost = cost;
    n->origin_cost = 0;
    
    return n;
};


Problem *problem_construct()
{
    Problem *p = (Problem *)calloc(1, sizeof(Problem));
    p->nodes = vector_construct();
    p->size = 0;

    return p;
};

/**
 * Função responsável por ler o arquivo e preencher o 
 * vetor de nós da estrutura Problem
 * @param arq arquivo de entrada
*/
Problem *problem_data_read(FILE *arq)
{
    Problem *p = problem_construct();
    int qtd_nodes;
    int value, cost;
    char last_char;


    fscanf(arq, "%d\n", &qtd_nodes);
    p->size = qtd_nodes + 1;

    for (int i = 0; i <= qtd_nodes; i++)
    {
        while (1)
        {
            fscanf(arq, "%d%d%c", &value, &cost, &last_char);

            ProblemNode *n = problem_node_construct(i, value, cost);
            vector_push_back(p->nodes, n);

            if (last_char == '\n')
            {
                break;
            }
        }
    }
    return p;
};


void problem_destroy(Problem *p)
{
    int size = vector_size(p->nodes);

    for (int i = 0; i < size; i++)
    {
        ProblemNode *n = vector_get(p->nodes, i);
        free(n);
    }

    vector_destroy(p->nodes);
    free(p);
};

