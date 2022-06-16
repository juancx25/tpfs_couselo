#define t_elem__queue void*

typedef struct queue_node {
  t_elem__queue value;
  struct queue_node *next;
} queue_node;

typedef struct queue {
  queue_node *head;
  queue_node *tail;
  int maxsize;
  int count;
} queue;

queue* queue_new (int maxsize);

void queue_free (queue* q);

int queue_getsize (queue* q);

int queue_getmaxsize (queue* q);

int queue_isfull (queue* q);

int queue_isempty (queue* q);

void enqueue (queue* q, t_elem__queue elem);

t_elem__queue dequeue (queue* q);

t_elem__queue peek (queue* q);
