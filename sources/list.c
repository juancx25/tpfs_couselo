#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list *list_new(int maxsize) {
  list *L = (list*)malloc(sizeof(list));
  L->head = NULL;
  L->count = 0;
  L->maxsize = maxsize;
  return L;
}

bool list_isempty(list *L) {
  int aux;
  if (L->count = 0) aux = true;
  else aux = false;
  return aux;
}

bool list_isfull(list *L) {
  int aux;
  if (L->count = L->maxsize) aux = true;
  else aux = false;
  return aux;
}

int list_length(list *L) {
  return L->count;
}

t_elem list_get(list *L, int index) {
  list_node *item = L->head;
  for (int j = 0;j<index;j++)
  {
    item = item->next;
  }
  t_elem aux = item->value;
  return aux;
}

int list_search(list *L, t_elem elem,int cmp(t_elem,t_elem)) {          // FUNCION CMP AGREGADA POSTERIORMENTE AL .H PROPUESTO
  int result = -2;
  if (L) {
    list_node* aux = L->head;
    result = -1;
    int index = 0;
    while ((aux) && (cmp(aux->value,elem) != 0)){
      aux = aux->next;
      index++;
    }
    if (aux) result = index;
}

  }

void list_insert(list *L, int index, t_elem elem) {
  list_node** aux = &(L->head);
  if (index == L->maxsize){
    L->maxsize <<= 1; // multiplies by 2
  }
  while (*aux) {                                                       // not fully tested!!
    aux = &(*aux)->next;
  }
  *aux = (list_node*)malloc(sizeof(list_node));
  (*aux)->value = elem;
  (*aux)->next = NULL;
  L->count++; 
  return;
}

void list_delete(list *L, int index) {
  int result = 0;
  int j = 0;
  list_node** aux = &(L->head);
  while (*aux != NULL && j != index) {
    aux = &(*aux)->next;
    j++;
  }
  if (*aux != NULL) {
    list_node* node_to_remove = *aux;
    *aux = (*aux)->next;
    node_to_remove->next = NULL;
    free(node_to_remove);
    result = 1;
  }
  if (result == 1) L->count--;
}

void list_traverse(list *L, bool look(t_elem elem, int index, void *ctx), void *ctx) {
  list_node *node = L->head;
  int index = 0;

  while (node != NULL && look(node->value, index, ctx)) {
    node = node->next;
    index++;
  }
}

void _list_print(list_node *head, void (*print)(t_elem*)){
    if (head) {
      print(head->value);
      _list_print(head->next,(void*)print);
    }
    printf("\n");
}

void list_print(list *L, void (*print)(void*)){
    if(L) {
      _list_print(L->head,(void*)print);
    }
}

