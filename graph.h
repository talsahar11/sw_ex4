#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next ;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int key ;
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

pedge new_edge(pnode *head, int weight, pedge next, pnode endpoint);
pnode new_node(int node_number, pnode next) ;
void print_edge(pedge e) ;
void print_node(pnode n) ;
void print_graph(pnode graph_head) ;
pnode find_node(pnode head, int num);
void addEdge(pnode *head, pnode node, pnode dest, int weight);

void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);

#endif
