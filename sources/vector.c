#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

/**
 * @brief Crea el vector vacío reservando el espacio en memoria. Tamaño = 0, Tamaño Máximo = ini_size.
 * 
 * @param ini_size 
 * @return vector* 
 */
vector* vector_new(int ini_size){
   vector *v = NULL;
   v = (vector *)malloc(sizeof(vector));
   v->a = (void *)malloc(sizeof(void *) * ini_size);
   v->size = 0;
   v->max_size = ini_size;
   return v;
}

/**
 * @brief Eliminar el vector
 * 
 * @param v 
 */
void vector_free(vector* v){
   free(v->a);
   free(v);
   return;
} 

/**
 * @brief Permite obtener el tamaño actual del vector
 * 
 * @param v 
 * @return int 
 */
int vector_size(vector* v){
   return v->size;
}

/**
 * @brief Devuelve 0 si no está lleno y 1 si está lleno. 
 * 
 * @param v 
 * @return int 
 */
int vector_isfull(vector* v) {
   if (v->size == v->max_size) return 1;
   return 0;
}

/**
 * @brief Devuelve 0 si no está vacío y 1 si está vacío. 
 * 
 * @param v 
 * @return int 
 */
int vector_isempty(vector* v){
   if (v->size == 0) return 1;
   return 0;
}


/**
 * @brief Permite obtener el valor de una posición del vector
 * 
 * @param v 
 * @param index 
 * @return void* 
 */
void* vector_get(vector* v, int index){
   return v->a[index];
}  


/**
 * @brief Permite reemplazar el valor de una posición del vector
 * 
 * @param v 
 * @param index 
 * @return void* 
 */
void* vector_set(vector* v, int index, void* value){
   void* aux = NULL;
   if (v->size < v->max_size){
      aux = v->a[index];
      v->a[index] = value;
      v->size++;
   }
   return aux;
}

/**
 * @brief Permite agregar un elemento al final
 * 
 * @param v 
 * @param value 
 */
int vector_add(vector* v, void* value){
   if (vector_isfull(v) == 1) return 1;
   v->a[v->size] = value;
   v->size++;
   return 0;
}


/**
 * @brief Permite agregar un elemento en una posición determinada.
 * 
 * @param v 
 * @param index 
 * @param value 
 */
int vector_insert(vector* v, int index, void* value){
   if (vector_isfull(v) == 1) return 1;
   v->a = (void *)realloc(v->a,v->size*sizeof(void *));
   for (int i=index;i<v->size-1;i++)
   {
      v->a[i+1] = v->a[i];
   }
   v->a[index] = value;
      v->size++;
   return 0;
}


/**
 * @brief Permite eliminar un elemento del vector
 * 
 * @param v 
 * @param index 
 */
void* vector_remove(vector* v, int index){
   void* value;
   
   value = v->a[index];
   for (int i=index;i<v->size;i++)
   {
      v->a[i] = v->a[i+1];
   }
   v->size--;
   return value;
}

/**
 * @brief print the vector
 * 
 */
void vector_print(vector* v, void (*print)(void*)){
   for (int i=0;i<v->size;i++)
   {
      print(v->a[i]);
   }
   printf("\n");
}