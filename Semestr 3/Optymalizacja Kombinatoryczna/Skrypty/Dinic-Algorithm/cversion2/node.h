#ifndef _NODE_H_
#define _NODE_H_

#include <stdbool.h>
#include "path.h"
#include "utils.h"

typedef struct node * node;
typedef struct nodes * nodes_list;


/**
 * Crea una nueva lista de nodos.
 * @param size La capacidad de nodos de la lista.
 * @returns La nueva lista de nodos.
 */

nodes_list nodes_new(uint size);

/**
 * Destruye la lista de nodos, liberando la memoria.
 * @param n La lista de nodos.
 */

void nodes_destroy(nodes_list nodes);


/**
 * Aumenta la capacidad del la lista de nodos a size nodos.
 * @param n Lista de nodos.
 * @param size Nueva capacidad de la lista.
 * @warning La nueva capacidad debe ser mayor a la capacidad anterior.
 */

void nodes_realloc(nodes_list nodes, uint size);


/**
 * Devuelve el layer en el que esta el nodo en el network auxiliar.
 * @param n Un nodo del network.
 * @returns El nivel del nodo en el network auxiliar.
 */

uint node_get_level(node n);

/**
 * Devuelve el balance del nodo.
 * @param n El nodo.
 * @returns True si el balance del nodo es forward, False de lo 
 * contrario.
 */

bool node_get_balance(node n);


/**
 * Devuelve el i-esimo nodo de la lista.
 * @param nodes Lista de nodos.
 * @param i Indice del nodo que queremos obtener.
 * @returns Nodo i-esimo. 
 * @warning El nodo debe existir en la lista.
 */

node nodes_get_node(nodes_list nodes, uint i);

/**
 * Devuelve la cantidad del nodos en la lista.
 * @param nodes La lista de nodos.
 * @returns La cantidad de nodos en la lista.
 */

uint nodes_get_length(nodes_list nodes);


/**
 * Devuelve el antecesor del i-esimo nodo.
 * @param nodes Lista de nodos.
 * @param i Indice del nodo.
 * @returns El indice del ancestro de i.
 */

uint nodes_get_ancestor(nodes_list nodes, uint n);

/**
 * Devuelve el nivel del i-esimo nodo de la lista.
 * @param nodes La lista de nodos.
 * @param i Indice del nodo.
 * @returns El nivel del i-esimo nodo.
 */

uint nodes_get_level(nodes_list nodes, uint x);


/**
 * Devuelve el balance del i-esimo nodo de la lista.
 * @param nodes La lista de nodos.
 * @param Indice del nodo.
 * @returns True si el balance es forward, false de lo contrario.
 */

bool nodes_get_balance(nodes_list nodes, uint n);

/**
 * Obtiene el Nombre del nodo cuyo indice es i.
 * @param nodes Lista de nodos.
 * @param i Indice del nodo.
 * @returns Nombre del nodo.
 */

uint nodes_get_id(nodes_list nodes, uint n);

/**
 * Devuelve el indice de la lista de vecinos forward.
 * @param n La lista de nodos.
 * @param x Nodo.
 * @returns Indice al primer vecino forward.
 */

uint nodes_forw_get_start(nodes_list n, uint x);

/**
 * Devuelve el indice de la lista de vecinos backward.
 * @param n La lista de nodos.
 * @param x Nodo.
 * @returns Indice al primer vecino backward.
 */

uint nodes_back_get_start(nodes_list n, uint x);



/**
 * Devuelve la cantidad de vecinos forward que tiene el nodo.
 * @param nodes Lista de nodos.
 * @param n El nodo cuya cantidad de vecinos forward queremos obtener.
 * @returns La cantidad de vecinos forward del nodo.
 */

uint nodes_forw_get_length(nodes_list nodes, uint n);

/**
 * Devuelve la cantidad de vecinos backward que tiene el nodo.
 * @param nodes Lista de nodos.
 * @param n El nodo cuya cantidad de vecinos backward queremos obtener.
 * @returns La cantidad de vecinos backward del nodo.
 */

uint nodes_back_get_length(nodes_list nodes, uint n);


/**
 * Devuelve un vecino forward del nodo.
 * @param n Lista de nodos.
 * @param x El indice del nodo.
 * @returns El indice de un vecino forward del nodo, si existe alguno,
 * sino cero.
 */

uint nodes_forw_neighb(nodes_list nodes, uint x);

/**
 * Devuelve un vecino backward del nodo.
 * @param n Lista de nodos.
 * @param x El indice del nodo.
 * @returns El indice de un vecino backward del nodo, si existe alguno,
 * sino cero.
 */

uint nodes_back_neighb(nodes_list nodes, uint x);


/**
 * Modifica el balance del i-esimo nodo de la lista.
 * @param nodes La lista de nodos.
 * @param i El indice del nodo cuyo balance queremos modificar.
 * @param balance True si queremos que tenga balance forward, False
 * de lo contrario.
 */

void nodes_set_balance(nodes_list nodes, uint n, bool balance);


/**
 * Modifica el antecesor del i-esimo nodo.
 * @param nodes Lista de nodos.
 * @param i Indice del nodo en la lista.
 * @param ancestor Nuevo ancestro del nodo.
 */

void nodes_set_ancestor(nodes_list nodes, uint n, uint ancestor);

/**
 * Modifica el nivel del i-esimo nodo de la lista.
 * @param nodes Lista de nodos.
 * @param i Indice del nodo.
 * @param level Nuevo nivel del nodo.
 */


void nodes_set_level(nodes_list nodes, uint x, uint level);

/**
 * Modifica el nombre del i-esimo nodo de la lista a id.
 * @param nodes Lista de nodos.
 * @param i Indice del nodo en la lista.
 * @param id Nuevo nombre del nodo.
 */

void nodes_set_id(nodes_list nodes, uint n, uint id);


/**
 * Imprime el camino y su flujo transportado.
 * @param nodes Lista de nodos.
 * @param p Camino a imprimir.
 * @param flowp Puntero a una variable donde devolvemos el flujo
 * del camino.
 */

void nodes_print_path(nodes_list nodes, path p, uint *flowp);

/**
 * Agrega un vecino forward al nodo.
 * @param n Nodo.
 * @param y El vecino forward que queremos agregar al nodo.
 */

void node_add_forw_neighb(node n, uint y);

/**
 * Agrega un vecino backward al nodo.
 * @param n Nodo.
 * @param x El vecino backward que queremos agregar al nodo.
 */

void node_add_back_neighb(node n, uint x);

/**
 * Agrega cada nodo como vecino del otro en la lista de nodos.
 * @param n La lista de nodos.
 * @param x El primer nodo del lado, el vecino backward.
 * @param y El segundo nodo del lado, el vecino forward.
 */

void nodes_add_neighbs(nodes_list n, uint x, uint y);


/**
 * Agrega un nodo cuyo nombre es id a la lista de nodos.
 * @param n La lista de nodos.
 * @param id El nombre del nodo que queremos agregar.
 * @returns El indice del nodo agregado.
 */

uint nodes_add(nodes_list n, uint id);


/**
 * Agrega un nodo a la cola y al network auxiliar.
 * @param nodes Lista de nodos del network.
 * @param Qq Puntero a la cola en la cual agregaremos el nodo.
 * @param i Nodo a agregar.
 * @param level Nivel del nodo en el network auxiliar.
 * @note Si el nodo ya esta en la cola no se agrega.
 */

void nodes_queue_bfs_add(nodes_list nodes, queue_bfs *Qq, uint i, 
						 uint level); 


/**
 * Incrementa el puntero a los vecinos forward del nodo.
 * @param n Lista de nodos.
 * @param x Nodo.
 * @warning Debe haber al menos un vecino forward.
 */

void nodes_del_forw(nodes_list nodes, uint x);

/**
 * Incrementa el puntero a los vecinos backward del nodo.
 * @param n Lista de nodos.
 * @param x Nodo.
 * @warning Debe haber al menos un vecino backward.
 */

void nodes_del_back(nodes_list nodes, uint x);

/**
 * Borra un vecino del nodo, dependiendo del valor del balance.
 * Si el balance es forward (true) borra un vecino forward, sino uno
 * backward.
 * @param nodes Lista de nodos.
 * @param x El nodo cuyo vecino queremos borrar.
 * @param bal Balance.
 * @see nodes_del_forw, nodes_del_back
 */

void nodes_del_neighb(nodes_list nodes, uint x, bool bal);

/**
 * Pone a cero los indices de vecinos forward y backward del nodo.
 * @param nodes Lista de nodos.
 */

void nodes_reset_start(nodes_list nodes);

/**
 * Quita los nodos del network auxiliar, poniendo un valor muy alto 
 * a sus niveles (salvo el nivel de s que siempre es cero).
 * @param nodes Lista de nodos.
 */

void nodes_aux_reset(nodes_list nodes);


/**
 * Devuelve el i-esimo vecino forward del nodo.
 * @param n Lista de nodos.
 * @param x Indice del nodo.
 * @param i Indice del vecino forward del nodo.
 * @returns Indice del  i-esimo vecino forward del nodo.
 */

uint nodes_nth_forw_neighb(nodes_list n, uint x, uint i);


/**
 * Devuelve el i-esimo vecino backward del nodo.
 * @param n Lista de nodos.
 * @param x Indice del nodo.
 * @param i Indice del vecino backward del nodo.
 * @returns Indice del  i-esimo vecino backward del nodo.
 */

uint nodes_nth_back_neighb(nodes_list n, uint x, uint i);










#endif
