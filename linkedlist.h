#ifndef __LINKEDLIST_H_
#define __LINKEDLIST_H_

typedef struct __node_t node_t;
typedef struct __list_t list_t;

struct __node_t{
	char *ubicacion[21];
	char *nombre[30];
	int *pid;
	char estado[30];
	node_t *next;
};

struct __list_t {
	node_t *head;
};

void list_init(list_t *l);
void apply(node_t *node, char ubicacion[], char nombre[],	int pid, char estado[]);
//int list_nondup_end_insert(list_t *l, node_t *node);
//int list_insert_end(list_t *l, node_t *node);
int get_index(list_t *l, char ele[]);
int get_size(list_t *l);
void display(list_t *l);
#endif
