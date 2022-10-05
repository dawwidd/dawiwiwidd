#include <stdlib.h>
#include "glib.h"
#include "utils.h"


gint compare_ints(gconstpointer n1, gconstpointer  n2) {
  return !(*((guint*)n1) == *((guint*)n2));
}


gint compare_vertex(gconstpointer v, gconstpointer id) {
  return !(vertex_id(v) == *(guint*)id);
}
