#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "network.h"
#include "output.h"


/**
 * Estructura donde guardamos los caminos para despues imprimirlos.
 */

struct output{
	path *paths;
	uint n_paths;
	uint flow;
	Net net;
};



/**
 * Devuelve el numero de caminos en out.
 * @param out La salida.
 * @returns El numero de caminos.
 */

uint out_num_paths(output out) {
	assert(out != NULL);
	
	return out->n_paths;
}

/**
 * Devuelve el i-esimo camino guardado en out.
 * @param out Salida.
 * @param i Indice del camino.
 * @returns El i-esimo camino.
 */

path out_get_path(output out, uint i) {
	assert(out != NULL);
	assert(out->n_paths > i);
	
	return out->paths[i];
}

/**
 * Imprime los caminos del network auxiliar junto al flujo 
 * que transportan.
 * @param out Salida.
 * @param na Numero del network auxiliar.
 */

void out_print_paths(output out, int na) {
	uint i;
	uint flow = 0;
	uint tot_flow = 0;

	assert(out != NULL);

	printf("N.A. %d:\n", na);
	for(i=0; i<out->n_paths; i++){
		nodes_print_path(net_get_nodes(out->net), 
				   out->paths[i], &flow);
		tot_flow += flow;
	}
	printf("El N.A. %d aumenta el flujo en %u.\n\n", 
		   na, tot_flow);
}


/**
 * Agrega el camino a los datos de salida.
 * @param out Salida.
 * @param p Camino.
 */

void out_add_path(output out, path p){
	assert(p != NULL);
	assert(out != NULL);
	
	out->n_paths++;
	out->paths = realloc(out->paths, sizeof(path) * out->n_paths); 
	out->paths[out->n_paths-1] = p;
	out->flow += path_flow(p);
}


/**
 * Imprime el corte del network.
 * @param out La estructura de impresion.
 */

void out_print_cut(output out) {
	Net net = NULL;
	queue_bfs q =  NULL;
	uint x = 0;
	nodes_list nodes = NULL;


	assert(out != NULL);

	net = out->net;

	assert(net != NULL);

	nodes = net_get_nodes(net);
	nodes_aux_reset(nodes);

	q = net_queue_bfs_new(net);
	
	printf("Corte: {");

	do {
		x = queue_bfs_pop(q);
    
		if (x)
			printf(", %u", nodes_get_id(nodes, x));
		else
			printf("%u", nodes_get_id(nodes, x));

		net_queue_bfs_add_neighbs(net, &q, x);
    
	} while (!queue_bfs_is_empty(q));
  
	printf("}\n");

	queue_bfs_destroy(q);
}


/**
 * Imprime el valor del flujo, dependiendo de los flags imprime 
 * tambien el flujo de los lados y/o el corte.
 * @param out Salida.
 * @param flags Opciones de impresion.
 */

void out_print(output out, int flags){
	
	if ((flags&FLUJO))
		net_print_flow_table(out->net);

	printf("Valor del Flujo: %i\n", out->flow);

	if ((flags&CORTE))
		out_print_cut(out);
}

/**
 * Crea una nueva estructura para guardar los datos de impresion.
 * @returns La nueva estructura output creada.
 */

output out_new(){
	output out;
	out = calloc(1,sizeof(struct output));
	assert(out != NULL);
	
	return out;
}


/**
 * Destruye la lista de caminos que guarda la estructura output.
 * @param out La estructura output.
 */

void out_path_destroy(output out){
	uint i;

	assert(out != NULL);
	
  	for(i = 0; i < out->n_paths; i++) {
		path_destroy(out->paths[i]);
		
	}
	free(out->paths);
  	out->paths = NULL;
  	out->n_paths = 0;
}



/**
 * Destruye la estructura output y libera la memoria asignada.
 * @param out La estructura a destruir.
 */

void out_destroy(output out) {
	out_path_destroy(out);
	free(out->paths);
	free(out);
}

/**
 * Guarda un puntero al network dentro de out.
 * @param out La estructura de salida.
 * @param net El network.
 */

void out_set_net(output out, Net net) {
	out->net = net;
}

/**
 * Guarda el flujo en la estructura out.
 * @param out La estructura de impresion.
 * @param flow El flujo a guardar.
 */

void out_set_flow(output out, uint flow) {
	assert(out != NULL);
	
	out->flow = flow;
}

/**
 * Devuelve el flujo guardado en la estructura.
 * @param out La estructura de impresion.
 * @returns El flujo guardado.
 */

uint out_get_flow(output out) {
	assert(out != NULL);
	
	return out->flow;
}

