#ifndef AUXILIAR_NETWORK_
#define AUXILIAR_NETWORK_

#include "glib.h"
#include "edge.h"
#include "vertex.h"


typedef GHashTable * aux_net;

aux_net make_auxiliar_network(edges_list edges, 
			      bool *complete);
void destroy_auxiliar_network(aux_net an);
void an_add_edge(aux_net an, guint key, vertex v);
void an_remove_edge(aux_net an, guint key, guint vid);
void an_print(aux_net an);
vertex an_get_child(aux_net an, guint father);
void an_remove_edges_entering(aux_net an, guint key);

int * make_int(int n);

#endif
