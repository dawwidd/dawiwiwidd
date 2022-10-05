#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "glib.h"
#include "auxiliar_network.h"
#include "vertex.h"
#include "edge.h"
#include "path.h"


edge get_edge(edges_list edges, guint first, guint last) {
  guint i = 0, edge_length=0;
  edge e = NULL;
  GList * edge_data = NULL;
  
  edge_length = queue_length(edges);
  edge_data = edges->head;
  for (i = 0; i < edge_length; i++, edge_data=edge_data->next) {
    e = edge_data->data;
    if (edge_first(e) == first 
	&& edge_last(e) == last){
      return e;
    }
  }
  return NULL;
}

guint get_residual_capacity(guint father, vertex child, 
			  edges_list edges) {
  edge e = NULL;
  guint r = 0;
  assert(edges != NULL);

  if (vertex_direction(child) == true) { /* Fordward */
    e = get_edge(edges, father, vertex_id(child));
    assert(e != NULL);
    r = edge_capacity(e) - edge_flow(e);
  } else  {
    e = get_edge(edges, vertex_id(child), father);
    assert(e != NULL);
    r = edge_flow(e);
  }
  
  return r;
}



path get_path(aux_net an, edges_list edges, 
	      guint * minflow, bool * complete) {
  
  path p = NULL;
  guint s = 0, t = 1, r = 0;
  vertex n = NULL;
  guint key = 0; /* s node */
  
  *minflow = G_MAXUINT;
  *complete = false;
  n = make_vertex(s, true); /* Source Node (s)*/
  p = queue_new();
  queue_push_tail(p, n);

  while (true) {

    n = an_get_child(an, key);
    if (n != NULL) {
      queue_push_tail(p, n);
    } else if (key == s) {
      break;
    } else if (key == t) {
      *complete = true;
      break;
    } else {
      queue_pop_tail(p);
      n = queue_peek_tail(p);
      an_remove_edges_entering(an, key);
      key = vertex_id(n);
      continue;
    }
    r = get_residual_capacity(key, n, edges);
    if (r < *minflow) {
      *minflow = r;
    }
    key = vertex_id(n);
  }

  return p;
}


void augment_and_delete(aux_net an, edges_list edges,
			vertex v, guint first, guint last, 
			guint mincost) {
  edge e = NULL;

  assert(v != NULL);
 
  if (vertex_direction(v) == true) {
    e = get_edge(edges, first, last);
    update_flow(e, edge_flow(e)+mincost);
    if (edge_capacity(e)-edge_flow(e) == 0) {
      an_remove_edge(an, edge_first(e), edge_last(e));
    }
  } else {
    e = get_edge(edges, last, first);
    update_flow(e, edge_flow(e)-mincost);
    if (edge_flow(e) == 0) {
      an_remove_edge(an, edge_last(e), edge_first(e));
    }
  }

}


void augment(aux_net an, edges_list edges, 
	     path p, guint mincost) {
  
  guint first = 0; /* s is the first node in the path */
  guint last = 0;
  vertex v = NULL;

  assert(an != NULL);
  assert(edges != NULL);
  assert(p != NULL);

  queue_pop_head(p); /* remove vertex s */

  while (!queue_is_empty(p)) {
    v = queue_pop_head(p);
    last = vertex_id(v);
    augment_and_delete(an, edges, v, first, last, 
		       mincost);
    first = last;
  }
  
}


void print_path(path p) {
  guint i = 0, length = 0;
  vertex v = NULL;
  GList * vertex_list = NULL;

  length = queue_length(p);
  vertex_list = p->head;
  for (i = 0; i < length; i++, 
	 vertex_list=vertex_list->next) {
    v = vertex_list->data;
    printf("%u ", vertex_id(v));
  }
  printf("\n");
}
