#ifndef _PATH_H_
#define _PATH_H_

#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

typedef struct path * path;
typedef struct snode * snode;

/**
 * Crea un nuevo camino.
 * @returns El nuevo camino creado.
 */
path path_new();

/**
 * Destruye un camino, liberando la memoria usada.
 * @param p El camino a destruir.
 */

void path_destroy(path p);

/**
 * Devuelve la longitud del camino.
 * @param p El camino.
 * @returns La longitud del camino.
 */

uint path_length(path p);

/**
 * Devuelve el flujo que pasa a traves del camino.
 * @param p El camino.
 * @returns El flujo a traves del camino.
 */

uint path_flow(path p);

/**
 * Devuelve el ID del nodo i-esimo en el camino.
 * @param p El camino.
 * @param i La posicion del nodo en el camino cuyo ID queremos obtener.
 * @warning La longitud del camino debe ser mayor a i.
 * @returns El id del nodo en la posicion i.
 */

uint path_nth_name(path p, uint i);


/**
 * Devuelve el balance del i-esimo nodo del camino.
 * @param p El camino.
 * @param i La posicion del nodo.
 * @warning La longitud del camino debe ser mayor a i.
 * @returns True si el i-esimo nodo del camino es forward, False si
 * el nodo es backward.
 */

bool path_nth_balance(path p, uint i);


/**
 * Agrega un nodo al camino con balance b.
 * @param p El camino.
 * @param i El ID del nodo a agregar.
 * @param b Balance del nodo, true si es forward, 
 * false si es backward.
 */

void path_add_node (path p, uint i, bool b);

/**
 * Modifica el flujo del camino.
 * @param p El camino.
 * @param flow El nuevo valor del flujo del camino.
 */

void path_update_flow(path p, uint flow);

#endif
