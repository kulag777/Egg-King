#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"

typedef List Queue;

Queue *queue_create() { return list_create(); }

void queue_insert(Queue *queue, void *data) { list_pushBack(queue, data); }

void *queue_remove(Queue *queue) { return list_popFront(queue); }

void *queue_front(Queue *queue) { return list_first(queue); }

void queue_clean(Queue *queue) { list_clean(queue); }

int queue_size(Queue *queue) { return list_size(queue); }

void *queue_get(Queue *queue, int index) { return list_get(queue, index); }

#endif /* QUEUE_H */