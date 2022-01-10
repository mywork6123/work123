#include <stdio.h>
#include "graph.h"

int main(){
   pnode f = NULL;
   pnode *p = &f;
   char choice = '\0';
   while (scanf("%c", &choice) != EOF){
      if (choice == 'A'){
         build_graph_cmd(p);
      }
      else if (choice == 'B'){
         insert_node_cmd(p);
      }
      else if (choice == 'D'){
         delete_node_cmd(p);
      }
      else if (choice == 'S'){
         int src = -1, dest = -1;
         scanf("%d %d", &src, &dest);
         int res = shortsPath_cmd(p, src, dest);
         printf("Dijsktra shortest path: %d \n", res);
      }
      else if (choice == 'T') {
         int res2 = TSP_cmd(*p);
         printf("TSP shortest path: %d \n", res2);
      }
   }
   return 0;
}