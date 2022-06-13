#include <stdio.h>
#include <stdlib.h>

#include "stack_dynamic.h"

stack* stack_new(int maxsize) {
  stack *s = (stack*)malloc(sizeof(stack));
  s->head = NULL;
  s->maxsize = maxsize;
  s->count = 0;
  return s;
}

void stack_free(stack* s) {
  stack_node *aux;
  while (s->head!=NULL){
    aux = s->head->next;
    free(s->head);
  }
  free(s);
}

int stack_getsize(stack* s) {
  return s->count;
}

int stack_getmaxsize(stack* s) {
  return s->maxsize;
}

int stack_isempty(stack* s) {
  if (s->count == 0) return 1;
  else return 0;
}

int stack_isfull(stack* s) {
  if (s->count == s->maxsize) return 1;
  else return 0;
}

void push(stack* s, t_elem elem) {
  stack_node *aux = (stack_node*)malloc(sizeof(stack_node));
  if (aux != NULL){
    aux->value = elem;
    aux->next = s->head;
    s->head = aux;
  }
  s->count++;
}

t_elem pop(stack* s) {
  t_elem value;
  if (s->head!=NULL){
    stack_node *aux = s->head;
    value = aux->value;
    s->head = s->head->next;
    free(aux);
    s->count--;
  }
  return value;
}

t_elem top(stack* s) {
  return s->head->value;
}

void stack_destroy(stack* s, void elem_free(t_elem)){
  /*COMPLETAR*/
}