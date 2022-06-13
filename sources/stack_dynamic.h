#define t_elem int

typedef struct stack_node {
  t_elem value;
  struct stack_node *next;
} stack_node;

typedef struct stack {
  stack_node *head;
  int maxsize;
  int count;
} stack;

stack* stack_new(int maxsize);

void stack_free(stack* s);

int stack_getsize(stack* s);

int stack_getmaxsize(stack* s);

void push(stack* s, t_elem elem);

t_elem pop(stack* s);

t_elem top(stack* s);

int stack_isempty(stack* s);

int stack_isfull(stack* s);

void stack_destroy(stack* s, void elem_free(t_elem));