#ifndef _PATH_H_
#define _PATH_H_

#include "problem.h"
#include "vector.h"

//aloca na memoria o vetor de caminhos com tamanho = quantidade de nós
Vector *paths_construct(int size);

//desaloca o vetor de caminhos e seu conteudo
void paths_destroy(Vector *p);

//printa os caminhos 
void paths_print(Vector *paths);

#endif