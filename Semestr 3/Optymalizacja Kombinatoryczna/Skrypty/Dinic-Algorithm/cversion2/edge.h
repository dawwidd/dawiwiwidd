#ifndef _EDGE_H_
#define _EDGE_H_

#include <stdbool.h>
#include "utils.h"

typedef struct edge *edge;
typedef struct edges * edges_list;

/**
 * Crea una nueva lista de lados.
 * @param n Numero de entradas en la tabla de hash a reservar.
 * @returns Una nueva lista de lados.
 */

edges_list edges_new(uint n);

/**
 * Destruye la lista de lados, libera la memoria usada.
 * @param e La lista de lados.
 */

void edges_destroy(edges_list e);



/**
 * Aumenta la capacidad de la lista de lados a size lados.
 * @param e La lista de lados.
 * @param size La nueva capacidad de la lista.
 */

void edges_realloc(edges_list e, uint size);

/**
 * Devuelve True si la lista de lados lleno su capacidad.
 * @param e La lista de lados.
 */

bool edges_is_full(edges_list e);


/**
 * Devuelve el flujo del lado cuyos nodos primero y segundo son
 * respectivamente x y y.
 * @param e La lista de lados.
 * @param x El primer nodo del lado.
 * @param y El segundo nodo del lado.
 * @returns El flujo del lado si este existe, sino devuelve cero.
 */

uint edges_flow(edges_list e, uint x, uint y);


/**
 * Devuelve la capacidad del lado cuyos nodos primero y segundo son
 * respectivamente x y y.
 * @param e La lista de lados.
 * @param x El primer nodo del lado.
 * @param y El segundo nodo del lado.
 * @returns La capacidad del lado si esta existe, sino devuelve cero.
 */

uint edges_capacity(edges_list e, uint x, uint y);



/**
 * Agrega un lado a la lista de lados.
 * @warning c debe ser mayor o igual a f
 * @param e La lista de lados.
 * @param x Primer nodo del lado.
 * @param y Segundo nodo del lado.
 * @param c Capacidad del lado.
 * @param f Flujo del lado.
 */

void edges_add(edges_list e, uint x, uint y, uint c, uint f);


/**
 * Modifica el flujo del lado cuyos nodos primero y segundo 
 * son x y y respectivamente.
 * @param e La lista de lados.
 * @param x Primer nodo del lado.
 * @param y Segundo nodo del lado.
 * @param f Nuevo flujo del lado.
 */

void edges_update_flow(edges_list e, uint x, uint y, uint f);

#endif
