#include <assert.h>
#include "path.h"

/**
 * Estructura para representar un nodo en el camino.
 */

struct snode {
	bool balance;
	uint name;
};


/**
 * Estructura que representa un camino con su flujo.
 */

struct path {
	uint flow;
	uint n_nodes;
	snode *nodes;
};

/**
 * Crea un nuevo camino.
 * @returns El nuevo camino creado.
 */

path path_new() {
	path path = NULL;

	path = malloc(sizeof(struct path));
	path->n_nodes = 0;
	path->nodes = NULL;
	
	assert(path != NULL);

	return path;
}

/**
 * Destruye un camino, liberando la memoria usada.
 * @param p El camino a destruir.
 */

void path_destroy(path p){
	uint i;

	assert(p != NULL);

	for (i = 0; i < p->n_nodes; i++)
		free(p->nodes[i]);

	free(p->nodes);
	free(p);
}

/**
 * Agrega un nodo al camino con balance b.
 * @param p El camino.
 * @param i El ID del nodo a agregar.
 * @param b Balance del nodo, true si es forward, 
 * false si es backward.
 */

void path_add_node (path p, uint i, bool b) {
	assert(p != NULL);
	
	p->nodes = realloc(p->nodes, 
					   (p->n_nodes+1)
					   * sizeof(snode));
	p->nodes[p->n_nodes] = malloc(sizeof(struct snode));
	p->nodes[p->n_nodes]->balance = b;
	p->nodes[p->n_nodes]->name = i;
	p->n_nodes++;
}

/**
 * Devuelve la longitud del camino.
 * @param p El camino.
 * @returns La longitud del camino.
 */

uint path_length(path p) {
	assert(p != NULL);
	
	return p->n_nodes;
}

/**
 * Devuelve el flujo que pasa a traves del camino.
 * @param p El camino.
 * @returns El flujo a traves del camino.
 */

uint path_flow(path p) {
	assert(p != NULL);
	
	return p->flow;
}

/**
 * Modifica el flujo del camino.
 * @param p El camino.
 * @param flow El nuevo valor del flujo del camino.
 */

void path_update_flow(path p, uint flow) {
	assert(p != NULL);
	
	p->flow = flow;
}

/**
 * Devuelve el ID del nodo i-esimo en el camino.
 * @param p El camino.
 * @param i La posicion del nodo en el camino cuyo ID queremos obtener.
 * @warning La longitud del camino debe ser mayor a i.
 * @returns El id del nodo en la posicion i.
 */

uint path_nth_name(path p, uint i) {
	assert(p != NULL);
	assert(i < path_length(p));
	
	return p->nodes[i]->name;
}

/**
 * Devuelve el balance del i-esimo nodo del camino.
 * @param p El camino.
 * @param i La posicion del nodo.
 * @warning La longitud del camino debe ser mayor a i.
 * @returns True si el i-esimo nodo del camino es forward, False si
 * el nodo es backward.
 */

bool path_nth_balance(path p, uint i) {
	assert(p != NULL);
	assert(i < path_length(p));

	return p->nodes[i]->balance;
}
