#include "glib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "edge.h"


struct sedge {
  guint first;
  guint last;
  guint capacity;
  guint flow;
  bool used;
};


edge make_edge(guint first, guint last, guint capacity, 
	       guint flow, bool used) {
  edge e = malloc(sizeof(struct sedge));
  e->first = first;
  e->last = last;
  e->capacity = capacity;
  e->flow = flow;
  e->used = used;

  return e;
}

void destroy_edge(edge e) {
  free(e);
}

guint edge_first(edge e) {
  return e->first;
}

guint edge_last(edge e) {
  return e->last;
}

guint edge_capacity(edge e) {
  return e->capacity;
}

guint edge_flow(edge e) {
  return e->flow;
}



void update_flow(edge e, guint flow) {
  e->flow = flow;
}

bool edge_used(edge e) {
  return e->used;
}

void print_edge(edge e) {
  printf("%u %u %u %u %s\n", 
	 edge_first(e), 
	 edge_last(e),
	 edge_capacity(e),
	 edge_flow(e),
	 edge_used(e)?"True":"False");
}


void edge_set_used(edge e, bool used) {
  assert(e != NULL);
  e->used = used;
}


edges_list read_edges() {
  guint first = 0, last = 0, capacity = 0;
  edge e = NULL;
  edges_list edges = NULL;

  edges = queue_new();
  while(scanf("%u %u %u\n", 
	      &first, &last, &capacity) != EOF){
    e = make_edge(first, last, capacity, 0, false);
    queue_push_tail(edges, e);
  }
  return edges;
}


void print_edges(edges_list edges) {
  guint i, length=0;
  GList *e = NULL;
  
  length = queue_length(edges);
  e = edges->head;
  for (i=0; i<length; i++, e = e->next) {
    print_edge(e->data);
  }
}

void destroy_edges(edges_list edges) {
  queue_free(edges, (free_edge_func) &destroy_edge);
}
