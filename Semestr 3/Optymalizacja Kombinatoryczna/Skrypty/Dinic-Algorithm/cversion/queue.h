#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "glib.h"
#include <stdbool.h>


typedef GQueue * queue;

queue queue_new();
guint queue_length(queue q);
bool queue_is_empty(queue q);
void queue_push_head(queue q, gpointer data);
void queue_push_tail(queue q, gpointer data);
gpointer queue_pop_head(queue q);
gpointer queue_pop_tail(queue q);
gpointer queue_peek_head(queue q);
gpointer queue_peek_tail(queue q);
bool queue_has_node(queue q, guint vertex_id);
void queue_delete_vertex(queue q, guint vertex_id);
void queue_free(queue q, void (*free_data) (gpointer));
void queue_clear(queue q);

#endif
