#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "queue_bfs.h"
#include "node.h"


/**
 * Estructura que representa un nodo con sus vecinos.
 */

struct node{
	uint level; 
	uint ancestor;
	bool balance; 
	uint n_neighbs_forw;
	uint n_neighbs_back;
	uint n_start_forw; 
	uint n_start_back;
	uint *neighbs_forw; 
	uint *neighbs_back; 
};

/**
 * Lista de nodos.
 */

struct nodes {
	uint n_nodes;
	uint size;
	uint *ids;
	node * nodes_list;
};


/**
 * Devuelve el layer en el que esta el nodo en el network auxiliar.
 * @param n Un nodo del network.
 * @returns El nivel del nodo en el network auxiliar.
 */

uint node_get_level(node n) {
	return n->level;
}

/**
 * Devuelve el balance del nodo.
 * @param n El nodo.
 * @returns True si el balance del nodo es forward, False de lo 
 * contrario.
 */

bool node_get_balance(node n) {
	assert(n != NULL);
	
	return n->balance;
}

/**
 * Devuelve el i-esimo nodo de la lista.
 * @param nodes Lista de nodos.
 * @param i Indice del nodo que queremos obtener.
 * @returns Nodo i-esimo. 
 * @warning El nodo debe existir en la lista.
 */

node nodes_get_node(nodes_list nodes, uint i) {
	assert(nodes != NULL);
	assert(nodes->n_nodes > i);
	
	return nodes->nodes_list[i];
}

/**
 * Devuelve la cantidad de vecinos forward que tiene el nodo.
 * @param nodes Lista de nodos.
 * @param n El nodo cuya cantidad de vecinos forward queremos obtener.
 * @returns La cantidad de vecinos forward del nodo.
 */

uint nodes_forw_get_length(nodes_list nodes, uint i) {
	assert(nodes != NULL);
	assert(nodes->n_nodes > i);
	
	return nodes->nodes_list[i]->n_neighbs_forw;
}


/**
 * Devuelve la cantidad de vecinos backward que tiene el nodo.
 * @param nodes Lista de nodos.
 * @param n El nodo cuya cantidad de vecinos backward queremos obtener.
 * @returns La cantidad de vecinos backward del nodo.
 */

uint nodes_back_get_length(nodes_list nodes, uint i) {
	assert(nodes != NULL);
	assert(nodes->n_nodes > i);
	
	return nodes->nodes_list[i]->n_neighbs_back;
}

/**
 * Obtiene el Nombre del nodo cuyo indice es i.
 * @param nodes Lista de nodos.
 * @param i Indice del nodo.
 * @returns Nombre del nodo.
 */

uint nodes_get_id(nodes_list nodes, uint i) {
	assert(nodes != NULL);
	assert(nodes->n_nodes > i);	

	return nodes->ids[i];
}

/**
 * Modifica el nombre del i-esimo nodo de la lista a id.
 * @param nodes Lista de nodos.
 * @param i Indice del nodo en la lista.
 * @param id Nuevo nombre del nodo.
 */

void nodes_set_id(nodes_list nodes, uint i, uint id) {
	assert(nodes != NULL);
	assert(nodes->n_nodes > i);
	
	nodes->ids[i] = id;
}

/**
 * Devuelve la cantidad del nodos en la lista.
 * @param nodes La lista de nodos.
 * @returns La cantidad de nodos en la lista.
 */

uint nodes_get_length(nodes_list nodes) {
	assert(nodes != NULL);
	
	return nodes->n_nodes;
}

/**
 * Modifica el balance del i-esimo nodo de la lista.
 * @param nodes La lista de nodos.
 * @param i El indice del nodo cuyo balance queremos modificar.
 * @param balance True si queremos que tenga balance forward, False
 * de lo contrario.
 */

void nodes_set_balance(nodes_list nodes, uint i, 
					   bool balance) {
	assert(nodes != NULL);
	assert(nodes_get_length(nodes) > i);
	
	nodes->nodes_list[i]->balance = balance;
}

/**
 * Devuelve el balance del i-esimo nodo de la lista.
 * @param nodes La lista de nodos.
 * @param Indice del nodo.
 * @returns True si el balance es forward, false de lo contrario.
 */

bool nodes_get_balance(nodes_list nodes, uint i) {
	assert(nodes != NULL);
	assert(nodes_get_length(nodes) > i);

	return nodes->nodes_list[i]->balance;
}

/**
 * Modifica el antecesor del i-esimo nodo.
 * @param nodes Lista de nodos.
 * @param i Indice del nodo en la lista.
 * @param ancestor Nuevo ancestro del nodo.
 */

void nodes_set_ancestor(nodes_list nodes, uint i, 
						uint ancestor) {
	assert(nodes != NULL);
	assert(nodes_get_length(nodes) > i);

	nodes->nodes_list[i]->ancestor = ancestor;
}

/**
 * Devuelve el antecesor del i-esimo nodo.
 * @param nodes Lista de nodos.
 * @param i Indice del nodo.
 * @returns El indice del ancestro de i.
 */

uint nodes_get_ancestor(nodes_list nodes, uint i) {
	assert(nodes != NULL);
	assert(nodes_get_length(nodes) > i);

	return nodes->nodes_list[i]->ancestor;
}

/**
 * Modifica el nivel del i-esimo nodo de la lista.
 * @param nodes Lista de nodos.
 * @param i Indice del nodo.
 * @param level Nuevo nivel del nodo.
 */

void nodes_set_level(nodes_list nodes, uint i, uint level) {
	assert(nodes != NULL);
	assert(nodes_get_length(nodes) > i);

	nodes->nodes_list[i]->level = level;
}

/**
 * Devuelve el nivel del i-esimo nodo de la lista.
 * @param nodes La lista de nodos.
 * @param i Indice del nodo.
 * @returns El nivel del i-esimo nodo.
 */

uint nodes_get_level(nodes_list nodes, uint i) {
	assert(nodes != NULL);
	assert(nodes_get_length(nodes) > i);

	return nodes->nodes_list[i]->level;
}

/**
 * Agrega un vecino forward al nodo.
 * @param n Nodo.
 * @param y El vecino forward que queremos agregar al nodo.
 */

void node_add_forw_neighb(node n, uint y) {
	uint n_forw = 0;

	assert(n != NULL);
	n_forw = ++n->n_neighbs_forw;
	n->neighbs_forw = realloc(n->neighbs_forw, n_forw * sizeof(uint));
	n->neighbs_forw[n_forw-1] = y;
}

/**
 * Agrega un vecino backward al nodo.
 * @param n Nodo.
 * @param x El vecino backward que queremos agregar al nodo.
 */

void node_add_back_neighb(node n, uint x) {
	uint n_back = 0;

	assert(n != NULL);
	n_back = ++n->n_neighbs_back;
	n->neighbs_back = realloc(n->neighbs_back, n_back * sizeof(uint));
	n->neighbs_back[n_back-1] = x;
}

/**
 * Crea una nueva lista de nodos.
 * @param size La capacidad de nodos de la lista.
 * @returns La nueva lista de nodos.
 */

nodes_list nodes_new(uint size) {
	uint i;
	nodes_list n;

	n = calloc(1, sizeof(struct nodes));
	n->nodes_list = calloc(size, sizeof(node));
	for (i = 0; i < size; i++) {
		n->nodes_list[i] = calloc(1, sizeof(struct node));
	}
	n->ids = calloc(size, sizeof(struct nodes));
	n->size = size;
	n->n_nodes = 2;
	
	assert(n != NULL);

	return n;
}

/**
 * Destruye un nodo, liberando la memoria ocupada.
 * @param n Nodo a destruir.
 */

void node_destroy(node n) {
	free(n->neighbs_forw);
	free(n->neighbs_back);
	free(n);
}

/**
 * Destruye la lista de nodos, liberando la memoria.
 * @param n La lista de nodos.
 */

void nodes_destroy(nodes_list n) {
	uint i;
	
	assert(n != NULL);
	
	for (i = 0; i < n->size; i++)
		node_destroy(n->nodes_list[i]);
	free(n->nodes_list);
	free(n->ids);
	free(n);
}

/**
 * Aumenta la capacidad del la lista de nodos a size nodos.
 * @param n Lista de nodos.
 * @param size Nueva capacidad de la lista.
 * @warning La nueva capacidad debe ser mayor a la capacidad anterior.
 */

void nodes_realloc(nodes_list n, uint size) {
	uint old_size = n->size, i;
	
	assert(n != NULL);
	assert(n->size <= size);
	
	n->nodes_list = realloc(n->nodes_list, size * sizeof(node));
	
	for (i = old_size; i < size; i++) {
		n->nodes_list[i] = calloc(1, sizeof(struct node));
	}
	
	n->ids = realloc(n->ids, size * sizeof(uint));
	memset(&n->ids[n->size], 0, (size - n->size) * sizeof(uint));
	n->size = size;
}

/**
 * Agrega un nodo cuyo nombre es id a la lista de nodos.
 * @param n La lista de nodos.
 * @param id El nombre del nodo que queremos agregar.
 * @returns El indice del nodo agregado.
 */

uint nodes_add(nodes_list n, uint id) {
	uint n_nodes = 0, pos = 0, s = SOURCE_ID, t = TARGET_ID;
	
	assert(n != NULL);

	n_nodes = n->n_nodes;
	
	if(id != s && id != t){
		pos = n_nodes;
		n->nodes_list[pos]->level = (uint)-1;
		n->n_nodes++;
	} else if(id != t){
		pos = 0;
		n->nodes_list[pos]->level = 0;
	} else {
		pos = 1;
		n->nodes_list[pos]->level = (uint)-1;
	}
	
	n->ids[pos] = id;

	return pos;
}

/**
 * Agrega cada nodo como vecino del otro en la lista de nodos.
 * @param n La lista de nodos.
 * @param x El primer nodo del lado, el vecino backward.
 * @param y El segundo nodo del lado, el vecino forward.
 */

void nodes_add_neighbs(nodes_list n, uint x, uint y) {
	assert(n != NULL);
	node_add_forw_neighb(n->nodes_list[x], y);
	node_add_back_neighb(n->nodes_list[y], x);
}

/**
 * Devuelve un vecino forward del nodo.
 * @param n Lista de nodos.
 * @param x El indice del nodo.
 * @returns El indice de un vecino forward del nodo, si existe alguno,
 * sino cero.
 */

uint nodes_forw_neighb(nodes_list n, uint x) {
	uint y = 0;
	uint n_start_forw = 0;
	
	assert(n != NULL);

	n_start_forw = n->nodes_list[x]->n_start_forw;

	if (n_start_forw < n->nodes_list[x]->n_neighbs_forw)
		y = n->nodes_list[x]->neighbs_forw[n_start_forw];
	return y;
}

/**
 * Devuelve un vecino backward del nodo.
 * @param n Lista de nodos.
 * @param x El indice del nodo.
 * @returns El indice de un vecino backward del nodo, si existe alguno,
 * sino cero.
 */

uint nodes_back_neighb(nodes_list n, uint x) {
	uint y = 0;
	uint n_start_back = 0;
	
	assert(n != NULL);

	n_start_back = n->nodes_list[x]->n_start_back;
	if (n->nodes_list[x]->n_start_back 
		< n->nodes_list[x]->n_neighbs_back)
		y = n->nodes_list[x]->neighbs_back[n_start_back];
	
	return y;
}

/**
 * Incrementa el puntero a los vecinos forward del nodo.
 * @param n Lista de nodos.
 * @param x Nodo.
 * @warning Debe haber al menos un vecino forward.
 */

void nodes_del_forw(nodes_list n, uint x) {
	assert(n != NULL);
	assert(nodes_forw_get_length(n, x) 
		   - n->nodes_list[x]->n_start_forw > 0);
	
	n->nodes_list[x]->n_start_forw++;
}


/**
 * Incrementa el puntero a los vecinos backward del nodo.
 * @param n Lista de nodos.
 * @param x Nodo.
 * @warning Debe haber al menos un vecino backward.
 */

void nodes_del_back(nodes_list n, uint x) {
	assert(n != NULL);
	assert(nodes_back_get_length(n, x) 
		   - n->nodes_list[x]->n_start_back > 0);

	n->nodes_list[x]->n_start_back++;
}

/**
 * Devuelve el indice de la lista de vecinos forward.
 * @param n La lista de nodos.
 * @param x Nodo.
 * @returns Indice al primer vecino forward.
 */

uint nodes_forw_get_start(nodes_list n, uint x) {
	assert(n != NULL);
	
	return n->nodes_list[x]->n_start_forw;
}

/**
 * Devuelve el indice de la lista de vecinos backward.
 * @param n La lista de nodos.
 * @param x Nodo.
 * @returns Indice al primer vecino backward.
 */

uint nodes_back_get_start(nodes_list n, uint x) {
	assert(n != NULL);
	return n->nodes_list[x]->n_start_back;
}

/**
 * Devuelve el i-esimo vecino forward del nodo.
 * @param n Lista de nodos.
 * @param x Indice del nodo.
 * @param i Indice del vecino forward del nodo.
 * @returns Indice del  i-esimo vecino forward del nodo.
 */

uint nodes_nth_forw_neighb(nodes_list n, uint x, uint i) {
	assert(n != NULL);
	assert(n->nodes_list[x]->n_neighbs_forw > i);
	
	return n->nodes_list[x]->neighbs_forw[i];
}

/**
 * Devuelve el i-esimo vecino backward del nodo.
 * @param n Lista de nodos.
 * @param x Indice del nodo.
 * @param i Indice del vecino backward del nodo.
 * @returns Indice del  i-esimo vecino backward del nodo.
 */

uint nodes_nth_back_neighb(nodes_list n, uint x, uint i) {
	assert(n != NULL);
	assert(n->nodes_list[x]->n_neighbs_back > i);

	return n->nodes_list[x]->neighbs_back[i];
}


/**
 * Pone a cero los indices de vecinos forward y backward del nodo.
 * @param nodes Lista de nodos.
 */

void nodes_reset_start(nodes_list nodes){
	uint i;

	assert(nodes != NULL);
	
	for(i = 0; i < nodes_get_length(nodes); i++){
		nodes->nodes_list[i]->n_start_forw = 0;
		nodes->nodes_list[i]->n_start_back = 0;
	}
}

/**
 * Quita los nodos del network auxiliar, poniendo un valor muy alto 
 * a sus niveles (salvo el nivel de s que siempre es cero).
 * @param nodes Lista de nodos.
 */

void nodes_aux_reset(nodes_list nodes) {
	uint i;

	assert(nodes != NULL);
	
	for(i = 1; i < nodes_get_length(nodes); i++)
		nodes_set_level(nodes, i, UINT_MAX);
}

/**
 * Borra un vecino del nodo, dependiendo del valor del balance.
 * Si el balance es forward (true) borra un vecino forward, sino uno
 * backward.
 * @param nodes Lista de nodos.
 * @param x El nodo cuyo vecino queremos borrar.
 * @param bal Balance.
 * @see nodes_del_forw, nodes_del_back
 */

void nodes_del_neighb(nodes_list nodes, uint x, bool bal) {
	if(bal)
		nodes_del_forw(nodes, x);
	else
		nodes_del_back(nodes, x);
}


/**
 * Agrega un nodo a la cola y al network auxiliar.
 * @param nodes Lista de nodos del network.
 * @param Qq Puntero a la cola en la cual agregaremos el nodo.
 * @param i Nodo a agregar.
 * @param level Nivel del nodo en el network auxiliar.
 * @note Si el nodo ya esta en la cola no se agrega.
 */

void nodes_queue_bfs_add(nodes_list nodes, queue_bfs *Qq, uint i, 
						 uint level){
	queue_bfs Q=*Qq;
	
	assert(nodes != NULL);
	assert(Q != NULL);
	
	if (nodes_get_level(nodes, i) == UINT_MAX){
		queue_bfs_push(Q, i);
		nodes_set_level(nodes, i, level);
	}
}


/**
 * Imprime el camino y su flujo transportado.
 * @param nodes Lista de nodos.
 * @param p Camino a imprimir.
 * @param flowp Puntero a una variable donde devolvemos el flujo
 * del camino.
 */

void nodes_print_path(nodes_list nodes, path p, uint *flowp) {
	int i;
	
	assert(nodes != NULL);
	assert(p != NULL);
	assert(flowp != NULL);

	printf("0 ");
	for(i = path_length(p)-2; 0 < i ; i--){
		if(path_nth_balance(p, i)){
			printf("%u ", nodes_get_id(nodes, path_nth_name(p, i)));
		} else
			printf("<- %u ", nodes_get_id(nodes, path_nth_name(p, i)));
	}
	printf("1 (flujo transportado: %u)\n", path_flow(p));
	*flowp = path_flow(p);
}


