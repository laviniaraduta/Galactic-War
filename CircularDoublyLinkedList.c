/* Copyright 2021 Raduta Lavinia-Maria 313CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

/*
 * Function used for allocating memory and initialising lists.
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
    doubly_linked_list_t* list =
    (doubly_linked_list_t *)malloc(sizeof(doubly_linked_list_t));
    DIE(!list, "malloc failed!");
    list->head = NULL;
    list->data_size = data_size;
    list->size = 0;
    return list;
}

/*
 * The function returns a pointer to the node on the nth position.
 * The first node of the list is at the position 0.
 * If n >= nr_noduri we cycle from the last node to the first.
 * If n < 0, error.
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    unsigned int i = 0;
    dll_node_t *curr = list->head;
    if (n  > list->size) {
        /* directly the wanted position, without cycling */
        n = n % list->size;
    }
    while (i < n) {
        curr = curr->next;
        i++;
    }
    return curr;
}

/*
 * Based on the data sent through the new_data pointer, a new node is created
 * and added to the nth position of the list represented by the list pointer.
 * The first node in the list is at position 0. When we index the positions
 * we do not "cycle" on the circular list as in get, but the nodes
 * are considered in the order from head to last node in the list.
 * If n >= no_nodes, then the new node is added to the end of the list.
 * If n < 0, error.
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
    dll_node_t *new_node, *curr;

    new_node = (dll_node_t*)malloc(sizeof(dll_node_t));
    DIE(!new_node, "malloc failed!");
    new_node->data = malloc(list->data_size);
    DIE(!new_node->data, "malloc failed!");
    memcpy(new_node->data, data, list->data_size);

    if (n >= list->size) {
        n = list->size;
    }
    if (!list->head) { /* adding in an empty list */
        list->head = new_node;
        new_node->next = new_node->prev = new_node;
        list->size++;
    } else {
        if (n == 0) { /* add first */
            /* last <-> new <-> head */
            new_node->next = list->head; /* new -> head */
            new_node->prev = list->head->prev; /* last <- new */
            list->head->prev->next = new_node; /* last -> new */
            list->head->prev = new_node; /*  new <- head */
            list->head = new_node; /* new_node becomes the head of list */
            list->size++;
        } else {
            curr = dll_get_nth_node(list, n - 1); /* the previous node */
            /* curr <-> new <-> curr->next */
            new_node->next = curr->next;
            new_node->prev = curr;
            curr->next->prev = new_node;
            curr->next = new_node;
            list->size++;
        }
    }
}

/*
 * Removes the node from the nth position in the list (whose pointer is sent as
 * parameter). The positions in the list are indexed from 0. The function
 * returns a pointer to the freshly removed node. If n >= no_nodes - 1, it
 * removes the node from the end of list. If n <0, error. It is the caller's
 * responsibility to free the memory of this node.
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    dll_node_t *curr, *to_delete;
    if (!list->head) { /* list is empty */
        DIE(1, "error, list is empty!");
    } else {
        if (list->size == 1) {
            to_delete = list->head;
            list->head = NULL;
            list->size--;
            return to_delete;
        }
        if (n == 0) { /* removing the first node */
            /* last <-> head->next */
            curr = list->head;
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            list->head = curr->next;
            list->size--;
            return curr;
        } else {
            if (n > list->size) {
                n = list->size - 1;
            }
            curr = dll_get_nth_node(list, n - 1); /* the previously node */
            to_delete = curr->next;
            curr->next = to_delete->next;
            to_delete->next->prev = curr;
            list->size--;
            return to_delete;
        }
    }
}

/*
 * The function returns the number of nodes of the list sent as parameter.
 */
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
    return list->size;
}

/*
 * The function frees the memory used for the nodes of the list and at the end
 * frees the memory used for the list structure.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
    unsigned int i = 0;
    dll_node_t *curr;
    while (i < (*pp_list)->size) {
        curr = (*pp_list)->head;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        (*pp_list)->head = curr->next;
        free(curr->data);
        free(curr);
        i++;
    }
    free(*pp_list);
    pp_list = NULL;
}

/*
 * THIS FUNCTION CAN ONLY BE USED FOR LISTS THAT HAVE DATA TYPE = INT.
 * It prints the nodes' data from the first to the last.
 */
void
dll_print_int_list(doubly_linked_list_t* list)
{
    dll_node_t *curr;
    if (!list->head) {
        DIE(1, "error, list is empty!");
    } else {
        printf("%d ", *((int *)(list->head->data)));
        if (list->size != 1) {
            curr = list->head->next;
            while (curr != list->head) {
                printf("%d ", *((int *)(curr->data)));
                curr = curr->next;
            }
        }
    }
    printf("\n");
}

/*
 * THIS FUNCTION CAN ONLY BE USED FOR LISTS THAT HAVE DATA TYPE = STRING.
 * It prints the nodes' data from the first to the last.
 */
void
dll_print_string_list(doubly_linked_list_t* list)
{
    dll_node_t *curr;
    if (!list->head) {
        DIE(1, "error, list is empty!");
    } else {
        printf("%s ", (char *)(list->head->data));
        curr = list->head->next;
        while (curr != list->head) {
            printf("%s ", (char *)(curr->data));
            curr = curr->next;
        }
    }
    printf("\n");
}

/*
 * THIS FUNCTION CAN ONLY BE USED FOR LISTS THAT HAVE DATA TYPE = INT.
 * It prints the nodes' data from the node sent as parameter
 * continuing at left. 
 */
void
dll_print_ints_left_circular(dll_node_t* start)
{
    dll_node_t *curr = start;
    while (curr->next != start) {
        printf("%d ", *((int *)(curr->data)));
        curr = curr->prev;
    }
    printf("\n");
}

/*
 * THIS FUNCTION CAN ONLY BE USED FOR LISTS THAT HAVE DATA TYPE = STRING.
 * It prints the nodes' data from the node sent as parameter
 * continuing at left.
 */
void
dll_print_ints_right_circular(dll_node_t* start)
{
    dll_node_t *curr = start;
    while (curr->next != start) {
        printf("%s ", (char *)(curr->data));
        curr = curr->next;
    }
    printf("\n");
}
