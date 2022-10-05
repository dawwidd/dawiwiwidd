#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "auxiliar_network.h"
#include "edge.h"
#include "queue.h"
#include "utils.h"

void free_hash_row(gpointer data) {
  queue_free(data, (void (*) (gpointer)) destroy_vertex);
}


aux_net make_an() {
  return g_hash_table_new(NULL, NULL);
}


aux_net make_auxiliar_network(edges_list edges, bool *complete) {
  aux_net an = NULL;
  guint i = 0, level= 1, s=0, t=1, edges_length=0, r=0;
  edge e = NULL;
  vertex v = NULL;
  GList * edge_data = NULL;
  bool fordward = true, backward = false;
  queue f_layer = NULL;
  queue c_layer = NULL;
  queue tmp_queue = NULL;
  GHashTable * vertex_levels = NULL;
  
  assert(edges != NULL);
  
  *complete = false;
  /* Creating Data Structures */
  
  an = make_an();
  f_layer = queue_new();
  c_layer = queue_new();
  vertex_levels = g_hash_table_new(NULL, NULL);
  
  /* Initializing Data structures */

  queue_push_tail(f_layer, GUINT_TO_POINTER(s));
  g_hash_table_insert(vertex_levels, GUINT_TO_POINTER(s), 
		      GUINT_TO_POINTER(level));
  level++;
  while (!queue_is_empty(f_layer)) {

    /* Add new layer to auxiliar network */

    guint key = GPOINTER_TO_UINT(queue_pop_head(f_layer));

    edges_length = queue_length(edges); 
    edge_data = edges->head;

    for (i=0; i < edges_length && !*complete; i++, edge_data=edge_data->next) { 

      e = edge_data->data;
      if (edge_used(e)) continue;
      r = edge_capacity(e) - edge_flow(e);
      if (key == edge_first(e) && r > 0)
	v = make_vertex(edge_last(e), fordward);
      else if (key == edge_last(e) && edge_flow(e) > 0)
	v = make_vertex(edge_first(e), backward);

      else continue;

      guint id = vertex_id(v);

      if (!queue_has_node(c_layer, id)) {
	queue_push_tail(c_layer, GUINT_TO_POINTER(id));
	if (id == t) *complete = true;
      }
      
      gpointer level_tmp = g_hash_table_lookup(vertex_levels, GUINT_TO_POINTER(id));

      if (level_tmp == NULL) {
	level_tmp = GUINT_TO_POINTER(level);
	g_hash_table_insert(vertex_levels, GUINT_TO_POINTER(id), level_tmp);
      }

      if (GPOINTER_TO_UINT(level_tmp) == level) {
	an_add_edge(an, key, v);
	edge_set_used(e, true);
      }
    }
    
    if (queue_is_empty(f_layer)) {
      queue_clear(f_layer);
      tmp_queue = f_layer;
      f_layer = c_layer;
      c_layer = tmp_queue;
      level++;
    }
  }

  return an;
}



void destroy_auxiliar_network(aux_net an) {
  assert(an != NULL);
  g_hash_table_destroy(an);
}


void an_print(aux_net an) {
  GHashTableIter iter;
  guint * key = NULL, length = 0, i = 0;
  GList * children_data = NULL;
  queue children = NULL;
  vertex v = NULL;
  
  g_hash_table_iter_init(&iter, an);
  while (g_hash_table_iter_next(&iter, (gpointer) &key, (gpointer) &children)) {
    printf("key: %u\t", GPOINTER_TO_UINT(key));

    length = queue_length(children);
    children_data = children->head;
    for (i=0; i<length; i++, children_data=children_data->next) {
      v = children_data->data;
      printf("id: %u\t", vertex_id(v));
    }

    printf("\n");
  }
}


void an_add_edge(aux_net an, guint key, vertex v) {
  assert(an != NULL);
  assert(v != NULL);

  queue vertex_list = NULL;
  vertex_list = g_hash_table_lookup(an, GUINT_TO_POINTER(key));
  if (vertex_list == NULL) {
    vertex_list = queue_new();
    queue_push_tail(vertex_list, v);
    g_hash_table_insert(an, GUINT_TO_POINTER(key), vertex_list);
  } else {
    queue_push_tail(vertex_list, v);
  }
}


void an_remove_edge(aux_net an, guint key, guint id) {
  assert(an != NULL);
  
  queue vertex_list = NULL;
  vertex_list = g_hash_table_lookup(an, GUINT_TO_POINTER(key));
  assert(vertex_list != NULL);
  queue_delete_vertex(vertex_list, id);
}


vertex an_get_child(aux_net an, guint father) {
  queue children = NULL;
  vertex v = NULL;
  
  assert(an != NULL);

  children = g_hash_table_lookup(an, GUINT_TO_POINTER(father));
  
  if (children != NULL)
    v = queue_peek_head(children);

  return v;
}

void an_remove_edges_entering(aux_net an, guint key) {
  assert(an != NULL);
  
  GHashTableIter iter;
  gpointer father, children; /* key, value*/
  vertex v = NULL;

  g_hash_table_iter_init(&iter, an);
  while (g_hash_table_iter_next(&iter, &father, 
				&children)) {
    queue_delete_vertex(children, key);
  }
}

