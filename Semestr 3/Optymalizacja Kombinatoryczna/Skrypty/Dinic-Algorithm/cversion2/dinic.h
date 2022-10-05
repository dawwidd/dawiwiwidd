#ifndef _DINIC_H_
#define _DINIC_H_

#include "utils.h"
#include "network.h"
#include "output.h"

/**
 * Lee los datos del network desde stdin
 * y los guarda en un Net. Opcionalmente lee los datos
 * de un archivo pasado como parametro. 
 * @see net_add_nodes, net_add_edges, nodes_realloc, edges_realloc,
 * net_get_nodes, net_get_edges, net_destroy,
 * EDGES_RESERVED, NODES_RESERVED
 * @param file_name (Opcional)El nombre del archivo desde donde se lee
 * el network, si es NULL los datos se leen desde stdin.
 * @returns Un nuevo Net que contiene los datos del network.
 todos los datos leidos.
 **/

Net read_data(char *file_name);



/**
* Revisa los argumentos pasados al programa
* si es que se paso alguno y devuelve las opciones
* codificadas en un entero. En caso de error termina
* la ejecucion del programa.
* @param argc Cantidad de argumentos del programa.
* @param argv Vector con los argumentos del programa.
* @returns Un entero cuyo valor codifica las opciones.
*/

int check_options(int argc, char **argv);



/**
 * Corre el algoritmo de Dinic sobre el network.
 * Los resultados del algoritmo son guardados en 
 * la estructura output.
 * @param net El network.
 * @param out_p La estructura donde guardamos los datos
 * de la ejecucion del algoritmo.
 * @param flags Opciones del programa, permite imprimir los
 * caminos encontrados.
 * @see net_aux_new, advance, augment, residual_capacity
 */

void dinic(Net net, output * out_p, int flags);


#endif
