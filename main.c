#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "heap.h"
#include "problem.h"
#include "dijkstra.h"
#include "path.h"

int main() {

    FILE *arq = fopen("entrada.txt", "r");
    Problem *p = problem_data_read(arq);
    Vector *paths = run_dijkstra(p);
    paths_print(paths);


    fclose(arq);
    paths_destroy(paths);
    problem_destroy(p);

    return 0;
}