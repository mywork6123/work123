#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
int TSP_res = 10000;
int TSP_numOfNodes;
pnode TSP_graph;


void build_graph_cmd(pnode *head){
   int NumOfNodes;
   scanf("%d", &NumOfNodes); // after we collected 'A' we want to get the number of nodes in the new graph.
   deleteGraph_cmd(head); // delete the current graph to built the new one.
   for(int i = 0; i < NumOfNodes; i++){
      char n;
      scanf(" %c", &n); // collect the 'n's ignore spaces.
      insert_node_cmd(head); // the next char in the input is the id of the new node, collect it in this function and add it.
   }
}

void printGraph_cmd(pnode head)
{
    pnode nodeIndex = head;
    while (nodeIndex != NULL)
    {
        printf("Node %d: ", nodeIndex->node_num);
        pedge edgeIndex = nodeIndex->edges;
        while (edgeIndex != NULL)
        {
            printf("dest %d: weight %d, ", edgeIndex->endpoint->node_num, edgeIndex->weight);
            edgeIndex = edgeIndex->next;
        }
        printf("\n");
        nodeIndex = nodeIndex->next;
    }
}

void insert_node_cmd(pnode *head){
   int node_id;
   scanf(" %d", &node_id); // collect the new node id, ignore spaces.
   pnode i = *head;
   while(i != NULL){ // check if the node already exist using the inputted node id.
      if((*i).node_num == node_id){
         break;
      }
      else{
         i = (*i).next;
      }
   }
   if(i != NULL){ // if the node already exists 
      pedge j = (*i).edges;
      while(j != NULL){ // free all the existing node edges to collect the new ones.
         pedge k = (*j).next;
         free(j);
         j = k;
      }
      (*i).edges = NULL;
   }
   else{ // the node does not exists so we will built a new one
      i = (pnode)malloc(sizeof(node));
      (*i).edges = NULL;
      (*i).node_num = node_id;
      (*i).next = *head;
      *head = i;
   }
   //either way we need to insert the new edges:
   pedge* pe = &((*i).edges);
   int d;
   while(scanf("%d", &d) != 0){ // while the number of inputted values by the scanf = 0 (when we get an 'n').
      int w;
      pnode x = *head;
      while(x != NULL){ // again, check if the node already exist using the inputted node id.
         if((*x).node_num == d){
            break;
         }
         else{
            x = (*x).next;
         }
      }
      if(x == NULL){ // node does not exists and we need to build it.
         x = (pnode)malloc(sizeof(node));
         (*x).edges = NULL;
         (*x).node_num = d;
         (*x).next = *head;
         *head = x;
      }
      scanf("%d", &w);
      *pe = (pedge)malloc(sizeof(edge));
      (*pe)->endpoint = x;
      (*pe)->weight = w;
      (*pe)->next = NULL;
      pe = &((*pe)->next);
   }   
}

void delete_node_cmd(pnode *head){
   int id;
   scanf("%d", &id); // get the removed node i.
   pnode i = *head;
   pnode prev = NULL;
   pnode *first = NULL;
   if((*i).node_num == id){
      first = head;
   }
   while(i != NULL){
      if((*i).next != NULL){
         if((*i).next->node_num == id){
            prev = i;
         }
      }
      if((*i).edges != NULL){
         if((*i).edges->endpoint->node_num == id){
            pedge x = (*i).edges;
            (*i).edges = (*i).edges->next;
            free(x);
            i = (*i).next;
            continue;
         }
      }
      pedge e = (*i).edges;
      if(e != NULL){
         while((*e).next != NULL){
            if((*e).next->endpoint->node_num == id){
               pedge x = (*e).next;
               (*e).next = (*x).next;
               free(x);
            }
            else{
               e = (*e).next;
            }
         }
      }
      i = (*i).next;
   }
   if(first != NULL){
      pedge e = (*first)->edges;
      while(e != NULL){
         pedge x = e;
         e = (*e).next;
         free(x);
      }
      pnode x = *first;
      *first = (*x).next;
      free(x);
   }
   else if(prev != NULL){
      pnode remove = (*prev).next;
      pedge e = (*remove).edges;
      while(e != NULL){
         pedge x = e;
         e = (*e).next;
         free(x);
      }
      (*prev).next = (*remove).next;
      free(remove);
   }
}

void deleteGraph_cmd(pnode* head){
   pnode n = *head;
   while(n != NULL){
      pedge e = (*n).edges;
      while(e != NULL){
         pedge fr = e;
         e = (*e).next;
         free(fr);
      }
      pnode fre = n;
      n = (*n).next;
      free(fre);
   }
   *head = NULL;
}

void make_PDNode(pdnode * pd , pnode p){
   pdnode x =(pdnode) malloc(sizeof(pdnode));
   (*x).dist =1000;
   (*x).id = (*p).node_num;
   (*x).visited = 0;
   (*x).next =(*pd);
   (*pd) = x;
}
void makeList(pdnode * pd , pnode * head){
   pnode x = *head;
   *pd = NULL;
   while (x){
      make_PDNode(pd, x);
      x = (*x).next;
   }
}

pdnode DijkHelper_GetNode(pdnode p, int nodeId){
   while(p){
      if((*p).id == nodeId){
         return p;
      }
      p = (*p).next;
    }
    return NULL;
}

pnode DijkHelper_FindNode(int id, pnode head){
   while(head != NULL){
      if((*head).node_num == id){
         return head;
      }
      head = (*head).next;
    }
    return NULL;
}

pdnode DijkHelper_GetMinimum (pdnode p){
   int currmin = 1000;
    pdnode res = NULL;
    while(p){
       if((*p).visited == 0){
          if((*p).dist < currmin){
             currmin = (*p).dist;
             res = p;
            }
        }
        p = (*p).next;
    }
    return res; 
}

void dijkstra (pnode* head, int src, pdnode* p){
   pdnode s = DijkHelper_GetNode((*p), src); 
   (*s).dist = 0;
   (*s).visited = 1;
   while(s != NULL){
      pedge edg = DijkHelper_FindNode((*s).id, *head)->edges;
      while(edg){
         pdnode temp = DijkHelper_GetNode((*p), (*edg).endpoint->node_num);
         if((*temp).dist > (((*edg).weight) +  ((*s).dist))){
            (*temp).dist = (((*edg).weight) +  ((*s).dist));
         }
         edg = (*edg).next;
      }
      (*s).visited = 1;
      s = DijkHelper_GetMinimum(*p);
   }   
}

int shortsPath_cmd(pnode *head, int src, int dest){
   pdnode n = NULL;
   makeList(&n, head);
   dijkstra(head, src, &n);
   int res =((DijkHelper_GetNode(n, dest))->dist);
   if(res == 1000)
   {
      return -1;
   }
   return res;
   free(n);
}


void TSP_GetDist(int *arr){
   int tempdist = 0;
   for (int j = 0; j < TSP_numOfNodes - 1; j++){
      pnode *p;
      p = &TSP_graph;
      int dist = shortsPath_cmd(p, arr[j], arr[j + 1]);
      if (dist == -1){
         tempdist = 10000;
         return;
      }
      tempdist += dist;
   }
   if (tempdist < TSP_res){
      TSP_res = tempdist;
   }
}

void TSP_Permutation(int s, int *temp){
   if (s == TSP_numOfNodes - 1){
      TSP_GetDist(temp);
      return;
   }
   for (int i = s; i < TSP_numOfNodes; ++i){
      int *t = (int *)malloc(sizeof(int) * TSP_numOfNodes);
      for (int j = 0; j < TSP_numOfNodes; j++){
         t[j] = temp[j];
      }
      int x = t[s];
      t[s] = t[i];
      t[i] = x;
      TSP_Permutation(s + 1, t);
      free(t);
   }
}


int *TSP_GetIds(int TSP_numOfNodes){
    int *nodes = (int *)malloc(sizeof(int) *TSP_numOfNodes);
     if (nodes == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < TSP_numOfNodes; i++)
    {
        scanf("%d", &nodes[i]);
    }
    return nodes;
}


int TSP_cmd(pnode head){
   TSP_graph = head;
   TSP_res = 10000;
   scanf("%d", &TSP_numOfNodes);
   int *nodes = TSP_GetIds(TSP_numOfNodes);
   int *temp = (int *)malloc(sizeof(int) * TSP_numOfNodes);
   for (int i = 0; i < TSP_numOfNodes; i++){
      temp[i] = nodes[i];
   }
   TSP_Permutation(0, temp);
   free(nodes);
   free(temp);
   if(TSP_res == 10000){
      return -1;
   }
   return TSP_res;
}