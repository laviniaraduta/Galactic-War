/* Copyright 2021 Raduta Lavinia-Maria 313CA */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "CircularDoublyLinkedList.h"
#define MAX_STRING_SIZE 21

typedef struct planets {
    char name[MAX_STRING_SIZE];
    doubly_linked_list_t *shields;
    unsigned int destroyed_planets;
} planet_t;

void add_function(doubly_linked_list_t *galaxy);

void remove_function(doubly_linked_list_t *galaxy,
unsigned int pos, unsigned int imploded);

void upgrade_function(doubly_linked_list_t *galaxy, unsigned int planet_pos,
unsigned int shield_pos, int val);

void add_shield_function(doubly_linked_list_t *galaxy,
unsigned int planet_pos, unsigned int val);

void show_function(doubly_linked_list_t *galaxy, unsigned int pos);

void free_galaxy(doubly_linked_list_t **galaxy);

void remove_shield_function(doubly_linked_list_t *galaxy,
unsigned int planet_pos, unsigned int shield_pos);

void rotate_function(doubly_linked_list_t *galaxy,
unsigned int planet_pos, char direction, unsigned int units);

void collision_function(doubly_linked_list_t *galaxy,
unsigned int planet1_pos,  unsigned int planet2_pos);

#endif  // FUNCTIONS_H_
