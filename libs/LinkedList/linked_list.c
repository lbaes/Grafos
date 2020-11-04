/* Lucas Franchini Baes */
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

// prints msg and crashes the program
static void crash(const char* msg){
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}

// inserts a new node after the node pointer
void insert_after(node_t *node, int num) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) crash("Memory error on insert_after()");
    new_node->n = num;
    new_node->next = node->next;
    node->next = new_node;
}

// inserts a node at head and returns the head of the list
node_t *insert_at_head(node_t *head, int num) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) crash("Memory error on insert_at_head()");
    new_node->n = num;
    new_node->next = head;
    return new_node;
}

// inserts a new node with value num in order
node_t *insert_in_order(node_t *head, int num) {
    node_t *cursor1, *cursor2;
    if (head == NULL) {
        return insert_at_head(head, num);
    }

    if (num < head->n){
      return insert_at_head(head, num);
    }

    cursor1 = head;
    cursor2 = cursor1->next;
    while (cursor2 != NULL) {
        if (num > cursor1->n && num < cursor2->n) {
            insert_after(cursor1, num);
            return head;
        }
        cursor1 = cursor2;
        cursor2 = cursor2->next;
    }

    insert_after(cursor1, num);
    return head;
    
}

// removes a node pointed by the node parameter and returns the head of the list
node_t *remove_node(node_t *head, node_t *node) {
    node_t *cursor1, *cursor2;

    if (node == head) {
        cursor1 = head->next;
        free(head);
        return cursor1;
    }

    cursor1 = cursor2 = head;
    while (cursor2 != node && cursor2 != NULL) {
        cursor1 = cursor2;
        cursor2 = cursor2->next;
    }

    if (cursor2 != NULL) {
        cursor1->next = cursor2->next;
        free(cursor2);
    }
    return head;
}

// returns the size of the list
int list_size(node_t *head) {
    int counter = 0;
    node_t *cursor = head;
    while (cursor != NULL) {
        counter++;
        cursor = cursor->next;
    }
    return counter;
}

// returns a pointer to the node at index
node_t *list_at(node_t *head, int index) {
    int counter = 0;
    node_t *cursor = head;
    while (counter < index && cursor != NULL) {
        cursor = cursor->next;
        counter++;
    }
    return cursor;
}

// returns a pointer to the first node found where node->n == num
node_t *find_node(node_t *head, int num) {
    node_t *cursor = head;
    while (cursor != NULL && cursor->n != num) {
        cursor = cursor->next;
    }
    return cursor;
}

// deletes the list and returns null;
node_t *delete_list(node_t *head) {
    node_t *cursor1, *cursor2;
    cursor1 = head;
    while (cursor1 != NULL) {
        cursor2 = cursor1;
        cursor1 = cursor1->next;
        free(cursor2);
    }
    return NULL;
}

// prints the list to stdout
void print_list(node_t *head) {
    node_t *cursor = head;
    while (cursor != NULL) {
        printf("%d->", cursor->n);
        cursor = cursor->next;
    }
    printf("null\n");
}