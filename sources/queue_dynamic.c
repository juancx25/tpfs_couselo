#include <stdio.h>
#include <stdlib.h>
#include "queue_dynamic.h"

queue* queue_new (int maxsize) {
  queue* q = malloc(sizeof(queue));

  q->head = NULL;
  q->tail = NULL;
  q->maxsize = maxsize;
  q->count = 0;

  return q;
}

void queue_free (queue* q) {
  queue_node *aux;
  while (q->head!=NULL){
    aux = q->head->next;
    free(q->head);
  }
}

int queue_getsize (queue* q) {
  return q->count;
}

int queue_getmaxsize (queue* q) {
  return q->maxsize;
}

int queue_isfull (queue* q) {
    if (q->count == q->maxsize) return 1;
  else return 0;
}

int queue_isempty (queue* q) {
  if (q->count == 0) return 1;
  else return 0;
}

void enqueue (queue* q, t_elem elem) {
  if (!queue_isfull(q)){
    queue_node *new = (queue_node*)malloc(sizeof(queue_node));
    if (new!=NULL){
      new->value = elem;
      new->next = q->head;
      q->head = new;
      if (q->tail == NULL) q->tail = new;
      q->count++;
    }
  }
}

t_elem dequeue (queue* q) {
  t_elem value;
  if (!queue_isempty(q)){
    queue_node *aux = q->head;
    while ((aux != NULL) && (aux->next != q->tail)){
      aux = aux->next;
    }
    value = q->tail->value;
    free(q->tail);
    q->tail = aux;
    if (aux != NULL){
      q->tail->next = NULL;
    }
    else{
      q->tail = NULL;
      q->head = NULL;
    }
    q->count--;
  }
  return value;
}

t_elem peek (queue* q) {
  /*COMPLETAR*/
}