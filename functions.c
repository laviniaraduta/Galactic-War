/* Copyright 2021 Raduta Lavinia-Maria 313CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CircularDoublyLinkedList.h"
#include "functions.h"
#include "utils.h"


/*
 * Function used to add a planet in the galaxy. The data stored is of type
 * struct. Every planet has inside another circular dll, so i have to create
 * every shield-list for every planet (node of the galaxy-list).
*/
void add_function(doubly_linked_list_t *galaxy)
{
    char name[MAX_STRING_SIZE];
    unsigned int pos, shields_number, val = 1;
    scanf("%s", name);
    scanf("%d %d", &pos, &shields_number);
    if (pos > galaxy->size) {
        printf("Planet out of bounds!\n");
    } else {
        planet_t *planet = (planet_t *)malloc(sizeof(planet_t));
        DIE(!planet, "malloc failed!");
        snprintf(planet->name, strlen(name) + 1, "%s", name);
        planet->destroyed_planets = 0;
        planet->shields = NULL;
        dll_add_nth_node(galaxy, pos, planet);
        free(planet);
        dll_node_t *curr = dll_get_nth_node(galaxy, pos);
        ((planet_t *)(curr->data))->shields = dll_create(sizeof(unsigned int));
        for (unsigned int i = 0; i < shields_number; i++) {
            dll_add_nth_node(((planet_t *)(curr->data))->shields, i, &val);
        }
        printf("The planet %s has joined the galaxy.\n", name);
    }
}

/*
 * Function used to remove a planet from the galaxy. The parameter "imploded"
 * makes difference between the case in which the planet is removed because
 * it imploded (= 1) -in this case the mesge is not displayed- or it is wanted
 * out of the galaxy by the caller (= 0). Attention to freeing memory!
 * (the memory for the shield list has to be freed separately).
*/
void remove_function(doubly_linked_list_t *galaxy,
unsigned int pos, unsigned int imploded)
{
    dll_node_t *to_remove;
    planet_t *planet;
    if (pos >= galaxy->size) {
        printf("Planet out of bounds!\n");
    } else {
        to_remove = dll_remove_nth_node(galaxy, pos);
        planet = (planet_t *)(to_remove->data);
        if (!imploded) {
            printf("The planet %s has been eaten by the vortex.\n",
            planet->name);
        }
        dll_free(&(planet->shields));
        free(planet);
        free(to_remove);
    }
}

/*
 * Function used to upgrade the value of a single shield (on the position
 * shield_pos) of the planet on the position planet_pos in the galaxy. The
 * value sent by the parameter "val" is added to the shield.
*/
void upgrade_function(doubly_linked_list_t *galaxy,
unsigned int planet_pos, unsigned int shield_pos, int val)
{
    dll_node_t *planet_to_upgrade, *shield_to_upgrade;
    if (planet_pos >= galaxy->size) {
        printf("Planet out of bounds!\n");
    } else {
        planet_to_upgrade = dll_get_nth_node(galaxy, planet_pos);
        unsigned int n_shields =
        ((planet_t *)(planet_to_upgrade->data))->shields->size;
        if (shield_pos >= n_shields) {
            printf("Shield out of bounds!\n");
        } else {
            shield_to_upgrade = dll_get_nth_node(
                ((planet_t *)(planet_to_upgrade->data))->shields, shield_pos);
            *((unsigned int *)(shield_to_upgrade->data)) += val;
        }
    }
}

/*
 * Function used to add a single shield (at the end of the shield list) of the
 * planet on the position planet_pos in the galaxy. The value of the new
 * shield is sent by the parameter "val".
*/
void add_shield_function(doubly_linked_list_t *galaxy,
unsigned int planet_pos, unsigned int val)
{
    dll_node_t *planet_where_add;
    doubly_linked_list_t *shield_where_add;
    if (planet_pos >= galaxy->size) {
        printf("Planet out of bounds!\n");
    } else {
        planet_where_add = dll_get_nth_node(galaxy, planet_pos);
        shield_where_add = ((planet_t *)(planet_where_add->data))->shields;
        unsigned int n_shields = shield_where_add->size;
        dll_add_nth_node(shield_where_add, n_shields, &val);
    }
}

/*
 * Function used to remove a specific shield (on the position shield_pos)
 * from the shield circular dll of the planet on the position planet_pos.
 * Attention to freeing the memory used for the freshly removed shield.
*/
void remove_shield_function(doubly_linked_list_t *galaxy,
unsigned int planet_pos, unsigned int shield_pos)
{
    doubly_linked_list_t *curr_shields;
    dll_node_t *curr_planet, *to_remove;
    if (planet_pos >= galaxy->size) {
        printf("Planet out of bounds!\n");
    } else {
        curr_planet = dll_get_nth_node(galaxy, planet_pos);
        curr_shields = ((planet_t *)(curr_planet->data))->shields;
        if (shield_pos >= curr_shields->size) {
                printf("Shield out of bounds!\n");
        } else {
            if (curr_shields->size == 4) {
            printf("A planet cannot have less than 4 shields!\n");
            } else {
                to_remove = dll_remove_nth_node(curr_shields, shield_pos);
                free(to_remove->data);
                free(to_remove);
            }
        }
    }
}

/*
 * Function used to show the info for the planet on the position pos in the
 * galaxy.
*/
void show_function(doubly_linked_list_t *galaxy, unsigned int pos)
{
    dll_node_t *curr_planet;
    if (galaxy->size == 0 || pos >= galaxy->size) {
        printf("Planet out of bounds!\n");
    } else {
        curr_planet = dll_get_nth_node(galaxy, pos);
        printf("NAME: %s\n", ((planet_t *)(curr_planet->data))->name);
        if (galaxy->size == 1) {
            printf("CLOSEST: none\n");
        } else {
            if (galaxy->size == 2) {
                printf("CLOSEST: %s\n",
                ((planet_t *)(curr_planet->next->data))->name);
            } else {
                printf("CLOSEST: %s and %s\n",
                ((planet_t *)(curr_planet->prev->data))->name,
                ((planet_t *)(curr_planet->next->data))->name);
            }
        }
        printf("SHIELDS: ");
        dll_print_int_list(((planet_t *)(curr_planet->data))->shields);
        printf("KILLED: %d\n",
        ((planet_t *)(curr_planet->data))->destroyed_planets);
    }
}



/*
 * Function used to rotate the shield of the planet on the position planet_pos
 * in the galaxy. Because the shield is a circular dll the rotation means just
 * updating the head of the list.
*/
void rotate_function(doubly_linked_list_t *galaxy,
unsigned int planet_pos, char direction, unsigned int units)
{
    doubly_linked_list_t *curr_shields;
    dll_node_t *curr_planet, *new_head;
    if (planet_pos >= galaxy->size) {
        printf("Planet out of bounds!\n");
    } else {
        if (direction != 'c' && direction != 't') {
            printf("Not a valid direction!\n");
        } else {
            curr_planet = dll_get_nth_node(galaxy, planet_pos);
            curr_shields = ((planet_t *)(curr_planet->data))->shields;
            if (direction == 't') {
                units = units % curr_shields->size;
            } else {
                units = curr_shields->size - units % curr_shields->size;
            }
            new_head = dll_get_nth_node(curr_shields, units);
            curr_shields->head = new_head;
        }
    }
}

/*
 * Function used to simulate the collision between two consecutive planets
 * (on positions planet1_pos and planet2_pos). It is guarantated that the 2
 * positions are consecutive.
*/
void collision_function(doubly_linked_list_t *galaxy,
unsigned int planet1_pos,  unsigned int planet2_pos)
{
    doubly_linked_list_t *shields1, *shields2;
    dll_node_t *planet1, *planet2, *col_shield1, *col_shield2;
    int n1, n2, alive1, alive2;
    /* alive1 and 2 are used to verify if the planet is alive */

    if (planet1_pos >= galaxy->size || planet2_pos >= galaxy->size) {
        printf("Planet out of bounds!\n");
    } else {
        planet1 = dll_get_nth_node(galaxy, planet1_pos);
        planet2 = dll_get_nth_node(galaxy, planet2_pos);
        shields1 = ((planet_t *)(planet1->data))->shields;
        shields2 = ((planet_t *)(planet2->data))->shields;
        /*
         * n1, n2 - the positions of the collision shields in the
         * 2 circular dll-shields of the each planet
        */ 
        n1 = (shields1->size) /4;
        n2 = ((shields2->size) /4) * 3;

        /*
         * The collision shields from each planet
        */
        col_shield1 = dll_get_nth_node(shields1, n1);
        col_shield2 = dll_get_nth_node(shields2, n2);
        alive1 = alive2 = 1;
        if (*((unsigned int *)(col_shield1->data)) == 0) {
            printf("The planet %s has imploded.\n",
            ((planet_t *)(planet1->data))->name);
            alive1 = 0;
        }
        if (*((unsigned int *)(col_shield2->data)) == 0) {
            printf("The planet %s has imploded.\n",
            ((planet_t *)(planet2->data))->name);
            alive2 = 0;
        }
        if (!alive1 && alive2) {
            ((planet_t *)(planet2->data))->destroyed_planets++;
            upgrade_function(galaxy, planet2_pos, n2, -1);
            remove_function(galaxy, planet1_pos, 1);
        }
        if (alive1 && !alive2) {
            ((planet_t *)(planet1->data))->destroyed_planets++;
            upgrade_function(galaxy, planet1_pos, n1, -1);
            remove_function(galaxy, planet2_pos, 1);
        }
        if (alive1 && alive2) {
            upgrade_function(galaxy, planet1_pos, n1, -1);
            upgrade_function(galaxy, planet2_pos, n2, -1);
        }
        if (!alive1 && !alive2) {
            remove_function(galaxy, planet1_pos, 1);
            remove_function(galaxy, planet1_pos, 1);
        }
    }
}

/*
 * Function used to free the memory allocated for the circular dll galaxy.
 * The memory allocated for the circular dll-shields has to be deallocated
 * first (using the functons from the library). Next it is safely to aply the
 * same function to deallocate every planet from the galaxy.
*/
void free_galaxy(doubly_linked_list_t **galaxy)
{
    dll_node_t *curr = (*galaxy)->head;
    planet_t *planet;
    unsigned int i = 0;
    while (i < (*galaxy)->size) {
        planet = ((planet_t *)(curr->data));
        dll_free(&(planet->shields));
        curr = curr->next;
        i++;
    }
    dll_free(galaxy);
}
