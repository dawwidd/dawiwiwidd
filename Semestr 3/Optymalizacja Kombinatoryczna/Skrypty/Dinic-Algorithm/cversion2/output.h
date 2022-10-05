#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include "network.h"
#include "utils.h"

typedef struct output * output;

/**
 * Crea una nueva estructura para guardar los datos de impresion.
 * @returns La nueva estructura output creada.
 */

output out_new();


/**
 * Destruye la estructura output y libera la memoria asignada.
 * @param out La estructura a destruir.
 */

void out_destroy(output out);



/**
 * Destruye la lista de caminos que guarda la estructura output.
 * @param out La estructura output.
 */

void out_path_destroy(output out);



/**
 * Devuelve el flujo guardado en la estructura.
 * @param out La estructura de impresion.
 * @returns El flujo guardado.
 */

uint out_get_flow(output out);

/**
 * Imprime el valor del flujo, dependiendo de los flags imprime 
 * tambien el flujo de los lados y/o el corte.
 * @param out Salida.
 * @param flags Opciones de impresion.
 */

void out_print(output out, int flags); 

/**
 * Imprime los caminos del network auxiliar junto al flujo 
 * que transportan.
 * @param out Salida.
 * @param na Numero del network auxiliar.
 */

void out_print_paths(output out, int na);

/**
 * Guarda un puntero al network dentro de out.
 * @param out La estructura de salida.
 * @param net El network.
 */

void out_set_net(output out, Net net);

/**
 * Agrega el camino a los datos de salida.
 * @param out Salida.
 * @param p Camino.
 */

void out_add_path(output out, path p);

/**
 * Guarda el flujo en la estructura out.
 * @param out La estructura de impresion.
 * @param flow El flujo a guardar.
 */

void out_set_flow(output out, uint flow);



#endif 
