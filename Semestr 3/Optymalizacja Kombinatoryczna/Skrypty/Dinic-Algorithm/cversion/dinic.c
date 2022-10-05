#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include "edge.h"
#include "parser.h"
#include "path.h"
#include "auxiliar_network.h"


void reset_edges(edges_list edges) {
  guint i = 0, edges_length = 0;
  edge e = NULL;
  GList * edge_data = NULL;
  
  edges_length = queue_length(edges);
  edge_data = edges->head;
  for (i = 0; i < edges_length; i++, edge_data=edge_data->next) {
    e = edge_data->data;
    edge_set_used(e, false);
  }
}


GSList * get_corte(aux_net an) {
  GSList * corte = NULL;
  guint s = 0, i = 0;
  GHashTableIter iter;
  gpointer key, value;
  vertex v = NULL;
  GList * vertex_list = NULL;
  queue q = NULL;

  g_hash_table_iter_init(&iter, an);
  corte = g_slist_prepend(corte, make_vertex(s, true));
  
  while (g_hash_table_iter_next(&iter, &key, &value)) {
    q = value;
    vertex_list = q->head;
    for (i = 0; i < queue_length(value); i++, vertex_list=vertex_list->next) {
      v = vertex_list->data;
      corte = g_slist_prepend(corte, v);
    }
  }

  return corte;
}

int calculate_maxflow(edges_list edges) {
  guint maxflow = 0, i = 0, s = 0, length=0;
  GList * edge_data = NULL;
  edge e = NULL;

  length = queue_length(edges);
  edge_data = edges->head;
  for (i = 0; i < length; i++, edge_data=edge_data->next) {
    e = edge_data->data;
    if (edge_first(e) == s) {
      maxflow += edge_flow(e);
    }
  }

  return maxflow;
}


int main(int argc, char ** argv) {
  edges_list edges = NULL;
  aux_net an = NULL;
  bool an_complete = false, path_complete = false;
  guint minflow = 0, maxflow = 0;
  path p = NULL;
  GSList * corte = NULL;

  /*  open_file("../pyversion/tests/networks/complex5000.txt"); */
  open_file("../pyversion/tests/networks/net02.txt");

  edges = read_edges();

  while (true) {
    reset_edges(edges);
    an = make_auxiliar_network(edges, &an_complete);

    if (!an_complete) break;
    while (true) {

      p = get_path(an, edges, &minflow, 
		   &path_complete);
      if (path_complete) {
	print_path(p); 
	printf("minflow: %u\n", minflow);
	augment(an, edges, p, minflow);
      } else {
	break;
      }
    }
  }
  corte = get_corte(an);
  maxflow = calculate_maxflow(edges);
  printf("MaxFlow: %d\n", maxflow);
  destroy_edges(edges);

  return 0;
}
