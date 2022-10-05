Implementacion del algoritmo de Dinic para resolver el problema
de maxflow-mincut.

Autor: Marcio Diaz.
Email: marcio.diaz@gmail.com.

Compilacion:

> make

Ejemplos Ejecucion:

> cat networks/net01_33.txt | ./dinic
Valor del Flujo: 33

> cat networks/net01_33.txt | ./dinic -f -c

Flujo Maximal:

0	  2  	8 (8)
0	  4		7 (7)
0	  6		6 (10)
0	  7		12 (12)
2	  8		0 (4)
2	  9		1 (3)
2	  11  	7 (8)
4	  9	  	1 (2)
4	  10  	1 (3)
4	  12  	5 (5)
6	  8	  	4 (4)
6	  9	  	2 (2)
7	  8	  	3 (3)
7	  9	  	6 (6)
7	  10  	3 (4)
8	  1	  	7 (7)
9	  1	  	6 (6)
9	  3	  	4 (4)
11	  1	  	9 (9)
3	  11  	2 (2)
3	  12  	2 (2)
12	  1	  	7 (15)
10	  1	  	4 (4)

Valor del Flujo: 33
Corte: {0, 6}

> cat networks/net02_512.txt | ./dinic -c
Valor del Flujo: 512
Corte: {0}
