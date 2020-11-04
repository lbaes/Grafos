/* Lucas Franchini Baes */

/*
  notes:

  functions that modify the list should be used like this:

  node_t *head;
  head = insert_at_head(head, i);
  head = remove_node(head, find_node(head, 10));

  insert_in_order() only works in already sorted lists
*/

#ifndef LISTA_H
#define LISTA_H

// singly linked list node
typedef struct node_t {
    int n;
    struct node_t *next;
} node_t;

void insert_after(node_t *node, int num);
node_t *insert_at_head(node_t *head, int num);
node_t *remove_node(node_t *head, node_t *node);
node_t *list_at(node_t *head, int index);
node_t *find_node(node_t *head, int num);
node_t *delete_list(node_t *head);
int list_size(node_t *head);
void print_list(node_t *head);
node_t *insert_in_order(node_t *head, int num);
//int list_pop(node_t *head);

#endif