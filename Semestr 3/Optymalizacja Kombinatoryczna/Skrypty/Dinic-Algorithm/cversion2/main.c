#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "dinic.h"

/**
 * @file main.c
 *
 * Modulo principal del programa.
 */


/**
 * @mainpage Implementacion del algoritmo de Dinic para el problema 
de maxflow-mincut.

 * @section usage Usage
 * dinic [options]
 * @subsection args Options
 *   - -f --flujo      Imprime tabla con los valores del flujo.
 *   - -v --verbose    Imprime los caminos en cada network auxiliar.
 *   - -c --corte      Imprime el corte minimal encontrado.
 *
 *
 * @subsection input Entrada
 * Lee los lados de la entrada estandar para para generar el network.
 *
 * Formato de lados:
 *     A B C
 * Donde A es el primer nodo del lado, B es el segundo y C es su 
 * capacidad.
 * El input debe contener un lado por linea.
 * El programa lee el input hasta que se viola el formato.
 * 
 * A, B y C son enteros sin signo.
 * 
 * El nodo fuente (Source) debe ser representado por 0.
 * El nodo destino (Target) debe ser representado por 1. 
 *
 * @section authors Autor
 *  - Marcio Diaz
 *
 */


int main(int argc, char *argv[]) {

	Net network = NULL;
	int flags = 0;
	output out = NULL;
	char * file_name = NULL;

	flags = check_options(argc, argv);

	network = read_data(file_name);

	out = out_new();

	dinic(network, &out, flags);

	out_print(out,flags);

	out_destroy(out);
	net_destroy(network);

	return 0;
}
