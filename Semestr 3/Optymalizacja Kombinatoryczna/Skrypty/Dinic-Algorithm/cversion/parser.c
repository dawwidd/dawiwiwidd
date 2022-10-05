#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "glib.h"
#include "edge.h"
#include "parser.h"


void open_file(const char * filename) {
  FILE * f = NULL;
  f = freopen(filename, "r", stdin);
  if (f == NULL) {
    printf("Failed to open file %s.\n", filename);
    exit(1);
  }
}


