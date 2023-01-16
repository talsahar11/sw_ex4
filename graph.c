#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "algo.h"

//-----Construct a new edge by its weight, next edge, and endpoint-----
pedge new_edge(pnode *head, int weight, pedge next, pnode endpoint){
    //-----allocate memory for the edge
    pedge e = (pedge) malloc(sizeof(edge)) ;

    //-----Check if the allocation succeed-----
    if(e == NULL){
        printf("Failed to allocate memory for the new edge.\n") ;
        exit(-1) ;
    }
    //-----Set the edge properties-----
    e->weight = weight ;

    e->next = next ;

    e->endpoint = endpoint ;

    return e ;
}

//-----Construct a new node by a given node-number and the next node-----
pnode new_node(int node_number, pnode next){
    //-----allocate memory for the node
    pnode n = (pnode)malloc(sizeof(node)) ;

    //-----Check if the allocation succeed-----
    if(n == NULL){
        printf("Failed to allocate memory for the new node.\n") ;
        exit(-1) ;
    }

    //-----Set the node properties-----
    n->next = next ;
    n->edges = NULL ;
    n->node_num = node_number ;
    return n ;
}

//-----Print a given edge by its properties-----
void print_edge(pedge e){
    printf("Edge weight: %d, End point: %d\n", e->weight, e->endpoint->node_num) ;
}

//-----Print a given node by its properties and recursively its edges-----
void print_node(pnode n){
    pedge curr_edge = n->edges ;
    while(curr_edge != NULL){
        print_edge(curr_edge) ;
        curr_edge = curr_edge->next ;
    }
}

//-----Print a given graph by recursively printing each node, and for each node, its edges-----
void print_graph(pnode graph_head){
    if(graph_head == NULL){
        return ;
    }
    while(graph_head !=NULL){
        print_node(graph_head) ;
        graph_head = graph_head->next ;
    }
}

//-----Create a new edge, then add it to a given node-----
void addEdge(pnode *head, pnode node, pnode dest, int weight){
//    printf("Adding edge from: %d to %d, with weight: %d\n", node->node_num, dest->node_num, weight) ;
    pedge newEdge = new_edge(head, weight, node->edges, dest) ;
    node->edges = newEdge ;
}

//-----Delete a given edge - remove it from the edges list, and free its memory-----
void deleteEdge(pedge parent, pedge edge){
    parent->next = edge->next ;
    free(edge) ;
}

//-----Finding a node in the graph by its index-----
pnode find_node(pnode head, int num){
    while(head != NULL){
        if(head->node_num == num){
            return head ;
        }
        head = head->next ;
    }
    return NULL ;
}

//-----Delete all of the edges of a given node-----
void deleteEdges(pnode node){
    pedge temp, current = node->edges ;
    while(current != NULL){
        temp = current->next ;
        free(current) ;
        current = temp ;
    }
    node->edges = NULL ;
}

//-----Delete all of the edges of a given node with a specific endpoint-----
void delete_edge_by_endpoint(pnode node, int endpoint){
    pedge edge = node->edges, parent = NULL, temp = NULL ;
    while(edge != NULL){
        if(edge->endpoint->node_num == endpoint){
            temp = edge ;
            if(parent == NULL){
                node->edges = edge->next ;
                edge = edge->next ;
            }else{
                parent->next = edge->next ;
                edge = parent->next ;
            }
            free(temp) ;
        }else {
            parent = edge;
            edge = edge->next;
        }
    }
}

//-----Delete a given node - delete first all the edges to that node, then delete all the edges from the node and
//-----remove the node from the list(change the parent node and the next node pointers)-----
void deleteNode(pnode *head, int nodeNum){
    pnode parent = NULL, current_node = *head ;

    //-----Delete all of the edges to the node-----
    while(current_node != NULL){
        if(current_node->node_num != nodeNum) {
            delete_edge_by_endpoint(current_node, nodeNum) ;
        }
        current_node = current_node->next ;
    }

    //-----Delete all of the node edges, and the node itself-----
    current_node = *head ;
    while(current_node != NULL){
        if(current_node->node_num == nodeNum){
            deleteEdges(current_node) ;
            if(parent == NULL) {
                *head = current_node->next ;
            }else{
                parent->next = current_node->next ;
            }
            free(current_node) ;
            break ;
        }
        parent = current_node ;
        current_node = current_node->next ;
    }
}

//-----Build a new abstract graph with abstract number of nodes, the number is being scanned from the user------
//-----In case a graph is already exists, delete it and create a new one------
//-----* Activated by the command 'A' -----
void build_graph_cmd(pnode *head){
    *head = NULL ;
    int num_of_nodes = -1 ;
    scanf("%d", &num_of_nodes) ;
    for(int i = 0 ; i < num_of_nodes ; i++){
        pnode newNode = new_node(i, *head) ;
        (*head) = newNode ;
    }
}

//-----Insert new node to a given graph, the node properties are being scanned from the user, at the next order:
//-----A. a number specifying the node number.
//-----B. an edge endpoint index, and its weight.
void insert_node_cmd(pnode *head){
    int res = 2 ;
    int curr_node_num = - 1, weight = - 1, dest_num = - 1 ;
    pnode current ,dest = NULL ;

    //-----Get the node number and create the node, if the node is already exist, just erase all of its edges-----
    scanf("%d", &curr_node_num) ;
    current = find_node(*head, curr_node_num) ;
    if(current != NULL){
        deleteEdges(current) ;
    }else{
        current= new_node(curr_node_num, *head) ;
        (*head) = current ;
    }

    //-----Each time a pair of numbers is being scanned, create new edge-----
    while(res == 2){
        res = scanf("%d %d", &dest_num, &weight) ;
        if(res == 2) {
            dest = find_node(*head, dest_num);

            addEdge(head, current, dest, weight);
        }
    }
}

//-----Scan a node index, find the node by the index, delete it and remove it from the graph-----
void delete_node_cmd(pnode *head){
    int node_num = -1 ;
    scanf("%d", &node_num) ;
    deleteNode(head, node_num) ;
}

//-----Delete recursively the whole graph, first delete all its edges, then delete all its nodes.
void deleteGraph_cmd(pnode *head){
    pnode current = *head, temp = NULL ;
    while(current != NULL){
        deleteEdges(current) ;
        temp = current->next ;
        free(current) ;
        current = temp ;
    }
//    free(head) ;
//    *head = NULL ;

}

//-----Find the shortest path between two nodes, the node numbers are being scanned from the user-----
void shortsPath_cmd(pnode head){
    int start_index = 0 ;
    int end_index = 0 ;
    scanf("%d %d", &start_index, &end_index) ;
    pnode start_node = find_node(head, start_index) ;
    pnode end_node = find_node(head, end_index) ;
    printf("Dijsktra shortest path: %d \n",find_min_path(head, start_node, end_node)) ;
}

//-----Find the shortest path between a group of nodes, the node numbers are being scanned from the user-----
void TSP_cmd(pnode head){
    int k = -1 ;
    scanf("%d", &k) ;

    //-----Creating an array containing the nodes included in the tsp problem-----
    pnode* nodes = (pnode*)malloc(sizeof(pnode) * k) ;
    int node_index = -1 ;
    for(int i = 0 ; i < k ; i++){
        scanf("%d", &node_index) ;
        nodes[i] = find_node(head, node_index) ;
    }

    //-----Calling TSP function of algo.c-----
    int min_path = TSP(head, nodes, k) ;
    printf("TSP shortest path: %d \n", min_path) ;
    free(nodes) ;
}

