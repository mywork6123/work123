#ifndef GRAPH_H
#define GRAPH_H

typedef struct Node {
    int key;
    struct Node* next; // for linked list
} Node;

typedef struct Edge {
    int src;
    int weight;
    int dest;
    struct Edge* next; // for linked list
} Edge;

typedef struct Graph {
    int nodes_num;
    int edges_num;
    struct Node* head_node; // linked list of nodes
    struct Edge* head_edge; // linked list of edges
} Graph;

void add_node(int, struct Graph*);
void remove_node(int, struct Graph*);
void connect(int, int, int, struct Graph*);
void remove_edge(int, int, struct Graph*);
void init_graph(struct Graph*, char*);
void print_graph(struct Graph*);
void delete_graph(struct Graph*);
int shortest_path(int, int, struct Graph*);
int TSP(struct Graph*, char*);
void free_graph(struct Graph*);

#endif