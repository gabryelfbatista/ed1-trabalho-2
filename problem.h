#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#include "vector.h"

typedef struct ProblemNode
{
    int source_node;
    int node_value;
    int path_cost;
    int origin_cost;
} ProblemNode;


typedef struct Problem 
{
    Vector *nodes;
    int size;
} Problem;


// Le o arquivo de entrada e preenche o vetor de nós
Problem *problem_data_read(FILE *arq);

// Libera da memória a estrutura Problem assim como os nós problema
void problem_destroy(Problem *p);

// Cria um nó problema já preenchendo as informações
ProblemNode *problem_node_construct(int source, int value, int cost);

// Libera a memória de um nó problema
void problem_node_destroy(ProblemNode *p);


#endif