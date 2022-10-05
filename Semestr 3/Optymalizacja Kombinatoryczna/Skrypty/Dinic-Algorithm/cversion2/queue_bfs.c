#include <assert.h>
#include "queue_bfs.h"

typedef struct bfs_elem bfs_elem;

/**
 * Estructura que representa un nodo en la cola bfs.
 */

struct bfs_elem{
	uint id;
};


/**
 * Cola enteros sin signo de tamaño fijo.
 */

struct queue_bfs{
	unsigned size;
	unsigned end;
	unsigned start;
	bfs_elem *tail;
};


/**
 * Crea una nueva cola con capacidad para n nodos.
 * @param n La maxima cantidad de nodos que se guardaran en la cola.
 * @returns La cola creada.
 */

queue_bfs queue_bfs_new(uint n) {
	queue_bfs q = NULL;

	q = malloc(sizeof(struct queue_bfs));
	q->tail = calloc(n, sizeof(struct bfs_elem));
	q->start = 0;
	q->end = 0;
	q->size = n;
	
	assert(q != NULL);

	return q;
}

/**
 * Agrega el nodo n a la cola.
 * @warning La cola NO debe estar llena.
 * @param q La cola donde agregamos el nodo.
 */

void queue_bfs_push(queue_bfs q, uint n) {
	assert(q != NULL);
	assert(!queue_bfs_is_full(q));

	q->tail[q->end].id = n;
	q->end++;
}


/**
 * Destruye la cola, libera la memoria usada.
 * @param q La cola a destruir.
 */

void queue_bfs_destroy(queue_bfs q){
	assert(q != NULL);
	free(q->tail);
	free(q);
}

/**
 * Devuelve true si la cola esta vacia.
 * @param q La cola.
 */

bool queue_bfs_is_empty(queue_bfs q) {
	assert(q != NULL);
	return (q->start == q->end);
}

/**
 * Borra y devuelve el primer elemento de la cola.
 * @warning La cola NO debe estar vacia.
 * @param q La cola.
 * @returns El primer elemento de la cola.
 */

uint queue_bfs_pop(queue_bfs q) {
	uint r = 0;
	
	assert(q != NULL);
	assert(!queue_bfs_is_empty(q));
	
	r = q->tail[q->start].id;
	q->start++;
	return r;
}


/**
 * Devuelve true si la cola esta llena y no se pueden agregar 
 * elementos.
 * @param q La cola.
 * @returns True si la cola esta llena, de lo contrario False.
 */

bool queue_bfs_is_full(queue_bfs q) {
	assert(q != NULL);
	
	return ((q->end - q->start) == q->size);
}

/**
 * Vacia la cola, no libera memoria.
 * @param La cola a vaciar.
 */

void queue_bfs_clear(queue_bfs q) {
	assert(q != NULL);
	
	q->start = 0;
	q->end = 0;
}
