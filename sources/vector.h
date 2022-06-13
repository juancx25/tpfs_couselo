#ifndef _VECTOR
#define _VECTOR

typedef struct{
   void** a;
   int size;
   int max_size;
} vector;

vector* vector_new(int ini_size);
// Crea el vector vacío reservando el espacio en memoria. Tamaño = 0, Tamaño
// Máximo = ini_size.

void vector_free(vector* v);
// Eliminar el vector

int vector_size(vector* v);
// Permite obtener el tamaño actual del vector

int vector_isfull(vector* v);
// Devuelve 0 si no está lleno y 1 si está lleno.

int vector_isempty(vector* v);
// Devuelve 0 si no está vacío y 1 si está vacío.

void* vector_get(vector* v, int index);
// Permite obtener el valor de una posición del vector

void* vector_set(vector* v, int index, void* value);
// Permite reemplazar el valor de una posición del vector

int vector_add(vector* v, void* value);
// Permite agregar un elemento al final

int vector_insert(vector* v, int index, void* value);
// Permite agregar un elemento en una posición determinada.

void* vector_remove(vector* v, int index);
// Permite eliminar un elemento del vector

void vector_print(vector* v, void (*print)(void*));
// Permite imprimir un vector
#endif
