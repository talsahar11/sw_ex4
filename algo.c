#include "graph.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "algo.h"

void print_queue(pnode *queue, int size){
    pnode current ;
    printf("Printing Queue:\n_______________________________________________________\n") ;
    for(int i = 0 ; i < size ; i++){
           current = queue[i] ;
           printf("Node number: %d with key: %d\n____________________________________________\n"
                  , current->node_num, current->key) ;
    }
}

//-----Create a queue, the first element is the start_point(node) provided, and then all the other nodes in the current
//-----graph, while setting the start point key to zero, and the others key to INT_MAX(infinity)-----------------------
//-----A pointer to int represents the size of the queue will be created is passed as an argument and will be filled
//-----during the function---------------------------------------------------------------------------------------------
pnode* create_queue(pnode head, pnode start_point, int *size){
    pnode current = head ;

    //-----Calculate the size of the queue and put the value in the size pointer-----
    int i = 0  ;
    while(current != NULL){
        i++ ;
        current = current->next ;
    }
    *size = i ;

    //-----Allocate memory for the queue-----
    pnode* queue = (pnode*) malloc(sizeof(pnode)*i) ;

    //-----Push the start point to the head of the queue, and set its key to zero-----
    queue[0] = start_point ;
    start_point->key = 0 ;
    current = head ;

    //-----Push all of the others elements into the queue and set their key to INT_MAX-----
    i = 1 ;
    while(current != NULL){
        if(current != start_point) {
            current->key = INT_MAX;
            queue[i] = current;
            i++ ;
        }
        current = current->next ;
    }

    //-----Return the queue to the find_min_path method-----
    return queue ;
}

//-----Fix an element to its place in the queue, so that the natural order in the queue will be maintained-----
//-----The natural order in the queue is by the key of the nodes, from low to high-----
void fix_to_place(pnode *queue, int i){
    pnode node = queue[i] ;
    int key = node->key ;
    while(i != 0){
        if(key > queue[i-1]->key){
            break ;
        }else{
            queue[i] = queue[i-1] ;
            i-- ;
        }
    }
    queue[i] = node ;
}

//-----Find the location of a node in the queue and return the index-----
int find(pnode *queue, int size, pnode node){
    for(int i = 0 ; i < size ; i++){
        if(queue[i] == node){
            return i ;
        }
    }
    return -1 ;
}

//-----Decrease the key of a node to a given key value, then fix the node location to the right one in the queue-----
void decrease_key(pnode *queue, int size, pnode node, int key){
    node->key = key ;
    int node_index = find(queue, size, node) ;
    fix_to_place(queue, node_index) ;
}

//-----Find the min path from a start node to an end node using dijakstra algorithm-----
int find_min_path(pnode head ,pnode start, pnode end){

    //-----Create a queue and get the size of it to the variable - queueSize-----
    int queueSize = 0 ;
    pnode *queue = create_queue(head, start, &queueSize) ;

    //-----Variables initialization-----
    int i = 0 ;
    pnode dest_node = NULL ;
    int edge_weight = 0 ;

    //-----While there are still nodes that has not been polled from the queue keep running-----
    while(i < queueSize){
        pnode current = queue[i] ;
        pedge edges = current->edges ;

        //-----For each edge going out of the current node, check if the destination node key is bigger then the source
        //-----node key + the edge weight, if true, decrease the key of the destination node to the smaller value-----
        while(edges !=NULL){
            dest_node = edges->endpoint ;
            edge_weight = edges->weight ;
            if(dest_node->key > current->key + edge_weight && current->key != INT_MAX){
                decrease_key(queue, queueSize, dest_node, current->key + edge_weight) ;
            }
            edges = edges->next ;
        }
        i++ ;
    }

    //-----Get the index of the destination node of the path from the start node-----
    int end_index = find(queue, queueSize, end) ;

    //-----If there is no way to that node, the key is INT_MAX, then return -1-----
    if(queue[end_index]->key == INT_MAX){
        free(queue) ;
        return -1 ;
    }

    //-----Else return the key, it is the shortest path from start_node to end_node-----
    int shortest = queue[end_index]->key ;
    free(queue) ;
    return shortest ;
}

//-----Calculates the factorial of a number n-----
int factorial(int n){
    if(n==2){
        return n ;
    }
    return n*factorial(n-1) ;
}

//-----Swapping to elements in an array-----
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//-----Get all of the permutations of all the numbers between (start) and (end) included-----
//-----The permutations will be inserted to a two-dimensional array provided as an argument-----
int permutation_num = 0 ;
void permute(int** permutations_arr, int* arr, int start, int end) {
    if (start == end) {
        for (int i = 0; i <= end; i++) {
            permutations_arr[permutation_num][i] = arr[i] ;
        }
        permutation_num++ ;
    } else {
        for (int i = start; i <= end; i++) {
            swap(&arr[start], &arr[i]);
            permute(permutations_arr, arr, start + 1, end);
            swap(&arr[start], &arr[i]);
        }
    }
}

void print_arr(int** permutations, int rows, int cols){
    for(int i = 0 ; i < rows ; i++){
        printf("Permutation: ") ;
        for(int j = 0 ; j < cols ; j++){
            printf("%d, ", permutations[i][j]) ;
        }
        printf("\n") ;
    }
}

//-----Solve the Traveling salesman problem, getting as arguments an array of the nodes needs to be visited, the graph,
//-----and the size of the array-----
int TSP(pnode head, pnode *nodes, int size){
    //-----First create an array to be permuted, the array contains the numbers between 0 and size-1-----
    int* arr = (int*)malloc(sizeof(int)*size) ;
    for(int i = 0 ; i < size ; i++){
        arr[i] = i ;
    }

    //-----Allocate memory and create the two-dimensional array that will hold all the permutations-----
    int rows = factorial(size) ;
    int** permutations_arr = (int**) malloc(sizeof(int*) * rows) ;
    for(int i = 0 ; i < rows ; i++){
        permutations_arr[i] = (int*) malloc(sizeof(int)* size) ;
    }

    //-----Fill the two-dimensional array with the permutations-----
    permute(permutations_arr, arr, 0, size - 1) ;
    permutation_num = 0 ;

    //-----Variables initialization-----
    pnode current_start = NULL, current_end = NULL ;
    int min_path = INT_MAX, current_min_path = 0, current_path = -1 ;

    //-----For each permutation, calculate the min path between each pair of nodes and sum those values to a total
    //-----path size per permutation------
    //-----For example - for the permutation (0,1,2) find min path from nodes[0] to nodes[1], then find the min path
    //-----from nodes[1] to nodes[2] and sum the both paths to get the total path size of the trip-----
    for(int i = 0 ; i < rows ; i++){
        current_min_path = 0 ;
        for(int j = 0 ; j < size-1 ; j++){
            current_start = nodes[permutations_arr[i][j]] ;
            current_end = nodes[permutations_arr[i][j+1]] ;
            current_path = find_min_path(head, current_start, current_end) ;
            //-----If the path between two nodes does not exist, break the inner loop-----
            if(current_path == -1){
                current_min_path = INT_MAX ;
                break ;
            }
            current_min_path += current_path ;
        }
        if(current_min_path < min_path){
            min_path = current_min_path ;
        }
    }

    for(int i = 0 ; i < rows ; i++){
        free(permutations_arr[i]) ;
    }
    free(permutations_arr) ;
    free(arr) ;
    if(min_path == INT_MAX){
        return -1 ;
    }
    return min_path ;
}
