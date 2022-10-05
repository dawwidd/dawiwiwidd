#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "edge.h"

/**
 *  La estructura edge representa un lado.
 */

struct edge{
	uint x;
	uint y;
	uint c;
	uint f;
};


/**
 * La estructura edges representa una lista de lados. Los lados
 * estan indexados por la suma de los indices de sus nodos.
 * Como una tabla de hash, donde el hash seria x+y.
 */

struct edges {
	uint n_edges; /* numero de entradas en la tabla de hash */
	uint size; /* capacidad de la tabla de hash */
	edge *edges_list; /* Hash table */
	usint * n_xplusy; /* Cantidad de lados por hash */
};

/**
 * Crea una nueva lista de lados.
 * @param n Numero de entradas en la tabla de hash a reservar.
 * @returns Una nueva lista de lados.
 */

edges_list edges_new(uint n) {
	edges_list e = NULL;

	e = calloc(1, sizeof(struct edges));
	e->edges_list = calloc(n, sizeof(edge));
	e->n_xplusy = calloc(n, sizeof(usint));
	e->n_edges = 0;
	e->size = n;

	assert(e != NULL);

	return e;
}

/**
 * Agrega un lado a la lista de lados.
 * @warning c debe ser mayor o igual a f
 * @param e La lista de lados.
 * @param x Primer nodo del lado.
 * @param y Segundo nodo del lado.
 * @param c Capacidad del lado.
 * @param f Flujo del lado.
 */

void  edges_add(edges_list e, uint x, uint y, 
				uint c, uint f) {
	uint pos, size;

	assert(e != NULL);
	assert(c >= f);

	pos = e->n_xplusy[x+y];
	size = ++e->n_xplusy[x+y];

	e->edges_list[x+y] = realloc(e->edges_list[x+y],
								 sizeof(struct edge)
								 * size);
	memset(&e->edges_list[x+y][pos], 0, 
		   sizeof(struct edge));
	e->edges_list[x+y][pos].x = x;
	e->edges_list[x+y][pos].y = y;
	e->edges_list[x+y][pos].f = f;
	e->edges_list[x+y][pos].c = c;
	e->n_edges++;
	
	assert(e != NULL);
}

/**
 * Destruye la lista de lados, libera la memoria usada.
 * @param e La lista de lados.
 */

void edges_destroy(edges_list e) {
	uint i;

	for (i = 0; i < e->size; i++) {
		free(e->edges_list[i]);
	}
	free(e->edges_list);
	free(e->n_xplusy);
	free(e);
}


/**
 * Devuelve True si la lista de lados lleno su capacidad.
 * @param e La lista de lados.
 */

bool edges_is_full(edges_list e) {
	assert(e != NULL);
	
	return (e->size == e->n_edges);
}

/**
 * Devuelve el flujo del lado cuyos nodos primero y segundo son
 * respectivamente x y y.
 * @param e La lista de lados.
 * @param x El primer nodo del lado.
 * @param y El segundo nodo del lado.
 * @returns El flujo del lado si este existe, sino devuelve cero.
 */

uint edges_flow(edges_list e, uint x, uint y) {
	uint flow = 0, i;
	
	assert(e != NULL);

	for (i = 0; i < e->n_xplusy[x+y]; i++) {
		if (e->edges_list[x+y][i].x == x 
			&& e->edges_list[x+y][i].y == y) {
			flow = e->edges_list[x+y][i].f;
			break;
		}
	}
	return flow;
}


/**
 * Devuelve la capacidad del lado cuyos nodos primero y segundo son
 * respectivamente x y y.
 * @param e La lista de lados.
 * @param x El primer nodo del lado.
 * @param y El segundo nodo del lado.
 * @returns La capacidad del lado si esta existe, sino devuelve cero.
 */

uint edges_capacity(edges_list e, uint x, uint y) {
	uint cap = 0, i;

	assert(e != NULL);

	for (i = 0; i < e->n_xplusy[x+y]; i++) {
		if (e->edges_list[x+y][i].x == x 
			&& e->edges_list[x+y][i].y == y)
			cap = e->edges_list[x+y][i].c;
	}

	return cap;
}

/**
 * Aumenta la capacidad de la lista de lados a size lados.
 * @param e La lista de lados.
 * @param size La nueva capacidad de la lista.
 */

void edges_realloc(edges_list e, uint size) {
	assert(e != NULL);

	e->edges_list = realloc(e->edges_list, size * sizeof(edge));
	memset(&e->edges_list[e->size], 0, (size - e->size) 
		   * sizeof(edge));
	e->n_xplusy = realloc(e->n_xplusy, size * sizeof(usint));
	memset(&e->n_xplusy[e->size],0, (size - e->size) * sizeof(usint));
	e->size = size;
}


/**
 * Modifica el flujo del lado cuyos nodos primero y segundo 
 * son x y y respectivamente.
 * @param e La lista de lados.
 * @param x Primer nodo del lado.
 * @param y Segundo nodo del lado.
 * @param f Nuevo flujo del lado.
 */

void edges_update_flow(edges_list e, uint x, uint y, 
					   uint f) {
	usint max, i;

	assert(e != NULL);

	max = e->n_xplusy[x+y];

	for (i = 0; i < max; i++) {
		if (e->edges_list[x+y][i].x == x
			|| e->edges_list[x+y][i].x == y) {
			e->edges_list[x+y][i].f = f;
		}
	}

}
