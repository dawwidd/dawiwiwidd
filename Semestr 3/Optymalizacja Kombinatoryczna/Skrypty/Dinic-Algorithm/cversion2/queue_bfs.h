#ifndef _QUEUE_BFS_H_
#define _QUEUE_BFS_H_

#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

typedef struct queue_bfs *queue_bfs; 


/**
 * Crea una nueva cola con capacidad para n nodos.
 * @param n La maxima cantidad de nodos que se guardaran en la cola.
 * @returns La cola creada.
 */

queue_bfs queue_bfs_new(uint n);

/**
 * Destruye la cola, libera la memoria usada.
 * @param q La cola a destruir.
 */

void queue_bfs_destroy(queue_bfs queue);

/**
 * Devuelve true si la cola esta llena y no se pueden agregar 
 * elementos.
 * @param q La cola.
 * @returns True si la cola esta llena, de lo contrario False.
 */

bool queue_bfs_is_full(queue_bfs q);

/**
 * Devuelve true si la cola esta vacia.
 * @param q La cola.
 */

bool queue_bfs_is_empty(queue_bfs q);

/**
 * Borra y devuelve el primer elemento de la cola.
 * @warning La cola NO debe estar vacia.
 * @param q La cola.
 * @returns El primer elemento de la cola.
 */

uint queue_bfs_pop(queue_bfs q);

/**
 * Vacia la cola, no libera memoria.
 * @param La cola a vaciar.
 */

void queue_bfs_clear(queue_bfs q);


/**
 * Agrega el nodo n a la cola.
 * @warning La cola NO debe estar llena.
 * @param q La cola donde agregamos el nodo.
 */

void queue_bfs_push(queue_bfs q, uint n);

#endif
