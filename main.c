#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
int main(){
    pnode *graph_head = (pnode*) malloc(sizeof(pnode*)) ;
    *graph_head = NULL ;
    char option = 0 ;
    while(scanf("%c", &option) != EOF){
        switch (option) {

            //-----If option = 'A' - delete the previous graph and create a new one-----
            case 'A':
                deleteGraph_cmd(graph_head) ;
                build_graph_cmd(graph_head) ;

                break;

            //-----If option = 'B' - insert new node into the graph from cmd-----
            case 'B':
                insert_node_cmd(graph_head) ;
                break ;

            //-----If option = 'D' - delete a node by a number scanned from the cmd-----
            case 'D':
                delete_node_cmd(graph_head) ;
                break ;

            //-----If option = 'S' - print the shortest path between the nodes scanned from the cmd-----
            case 'S':
                //Print shortest path between 2 nodes
                shortsPath_cmd(*graph_head) ;
                break ;

            //-----If option = 'T' - print the shortest path between a group of nodes scanned from the cmd-----
            case 'T':
                TSP_cmd(*graph_head) ;
                break ;

            //-----If option = 'n' - insert new node into the graph from cmd-----
            case 'n':
                insert_node_cmd(graph_head) ;
                break ;
            case '\n':
                break ;
            case ' ':
                break ;
            case '\t':
                break ;
            default:
                printf("The char received is not valid.") ;
        }
    }

    //-----If eof reached, delete the existing graph and free all the allocated memory-----
    deleteGraph_cmd(graph_head) ;
    free(graph_head) ;
}