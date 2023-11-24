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


Problem *problem_data_read(FILE *arq);


void problem_destroy(Problem *p);


ProblemNode *problem_node_construct(int source, int value, int cost);

void problem_node_destroy(ProblemNode *p);


#endif