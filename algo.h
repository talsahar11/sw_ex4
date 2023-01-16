
#ifndef LAB6_ALGO_H
#define LAB6_ALGO_H
#include "graph.h"

pnode* create_queue(pnode head, pnode start_point, int *size);
//void decrease_key(pnode queue[], pnode node, int key) ;
//int find_min_path(pnode *head ,pnode start, pnode end) ;
void decrease_key(pnode *queue, int size, pnode node, int key) ;
int find_min_path(pnode head ,pnode start, pnode end) ;
int TSP(pnode start, pnode *nodes, int size);

#endif //LAB6_ALGO_H
