#ifndef PATH_H
#define PATH_H

#include "auxiliar_network.h"
#include "edge.h"

typedef queue path;



path get_path(aux_net an, edges_list edges, 
	      guint * minflow, bool * complete);
void augment(aux_net an, edges_list edges, 
	     path p, guint mincost);
void print_path(path p);

#endif
