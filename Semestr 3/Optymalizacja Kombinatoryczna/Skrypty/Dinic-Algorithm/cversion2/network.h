#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "queue_bfs.h"
#include "node.h"
#include "edge.h"
#include "utils.h"

typedef struct net * Net;

/**
 * Crea un nuevo network. Reserva memoria
 * para cierta cantidad predeterminado de lados
 * y nodos.
 * @see EDGES_RESERVED, NODES_RESERVED
 * @returns El network creado.
 */

Net net_new(); 

/**
 * Libera la memoria usada por el network.
 * @param net El network.
 */

void net_destroy(Net net);


/**
 * Crea un network auxiliar corriendo BFS sobre el network.
 * @param net EL network.
 */

void net_aux_new(Net net); 

/**
 * Crea una cola con suficiente espacio para guardar todos los nodos
 * del network y coloca el nodo s en ella.
 * @param net El network.
 * @returns La cola creada.
 */

queue_bfs net_queue_bfs_new(Net net);

/**
 * Obtiene la lista de nodos del network.
 * @param net El network.
 * @returns La lista de nodos.
 */

nodes_list net_get_nodes(Net net);

/**
 * Obtiene la lista de lados del network.
 * @param net El network.
 * @returns La lista de lados.
 */

edges_list net_get_edges(Net net);


/**
 * Devuelve el indice de un vecino forward de x que aun no ha sido
 * agregado al network auxiliar y por el cual podemos aumentar mandar
 * flujo.
 * @param net El network.
 * @param x El indice del nodo cuyo vecino queremos encontrar.
 * @returns El indice del vecino del nodo si este existe, sino
 * devuelve cero.
 */

uint net_neighb_forw(Net net, uint x); 


/**
 * Devuelve el indice de un vecino backward de x que aun no ha sido
 * agregado al network auxiliar y por el cual podemos aumentar mandar
 * flujo.
 * @param net El network.
 * @param x El indice del nodo cuyo vecino queremos encontrar.
 * @returns El indice del vecino del nodo si este existe, sino
 * devuelve cero.
 */

uint net_neighb_back(Net net, uint x);

/**
 * Imprime una tabla con los lados del network, sus flujos 
 * y capacidades.
 * @param net El network.
 */
void net_print_flow_table(Net net);


/**
 * Agrega un nodo al network.
 * @param net El network.
 * @param id Id del nodo a agregar.
 * @returns Devolvemos la posicion donde fue agregado el nodo
 */

uint net_add_node(Net network, uint n); 

/**
 * Agrega los nodos pasados como parametros.
 * @param net El network.
 * @param x Puntero al id del nodo x a agregar.
 * @param y Puntero al id del nodo y a agregar.
 * @returns x Puntero a la posicion donde 
 * fue agregado el nodo x.
 * @returns y Puntero a la posicion donde 
 * fue agregado el nodo y.
 */

void net_add_nodes(Net network, uint *x, uint *y);

/**
 * Agrega un lado al network.
 * @param network El network donde guardamos el lado.
 * @param x El primer nodo del lado.
 * @param y El segundo nodo del lado.
 * @param C La capacidad del lado.
 */

void net_add_edge(Net network, uint x,uint y, uint C);
/**
 * Agrega los vecinos de in a la cola y al network auxiliar.
 * @param net El network.
 * @param Qq Puntero a la cola donde agregamos los vecinos.
 * @param in Indice del nodo cuyos vecinos queremos agregar.
 */

void net_queue_bfs_add_neighbs(Net net, queue_bfs *Qq, uint in);


#endif
