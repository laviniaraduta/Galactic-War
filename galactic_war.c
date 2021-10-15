/* Copyright 2021 Raduta Lavinia-Maria 313CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CircularDoublyLinkedList.h"
#include "functions.h"

int main() {
    doubly_linked_list_t *galaxy;
    char direction, command[MAX_STRING_SIZE];
    unsigned int number_of_commands, pos, shield_pos, val;

    /*
     * The galaxy is practically a dll, with nodes'
     * information of type struct planet.
    */
    galaxy = dll_create(sizeof(planet_t));

    scanf("%d", &number_of_commands);
    while (number_of_commands) {
        scanf("%s", command);
        if (strcmp(command, "ADD") == 0){
            add_function(galaxy);
        }
        if (strcmp(command, "BLH") == 0){
            scanf("%d", &pos);
            remove_function(galaxy, pos, 0);
        }
        if (strcmp(command, "UPG") == 0){
            scanf("%d %d %d", &pos, &shield_pos, &val);
            upgrade_function(galaxy, pos, shield_pos, val);
        }
        if (strcmp(command, "EXP") == 0){
            scanf("%d %d", &pos, &val);
            add_shield_function(galaxy, pos, val);
        }
        if (strcmp(command, "RMV") == 0){
            scanf("%d %d", &pos, &shield_pos);
            remove_shield_function(galaxy, pos, shield_pos);
        }
        if (strcmp(command, "ROT") == 0){
            scanf("%d", &pos);
            scanf(" %c", &direction);
            scanf("%d", &val);
            rotate_function(galaxy, pos, direction, val);
        }
        if (strcmp(command, "COL") == 0){
            scanf("%d %d", &pos, &shield_pos);
            collision_function(galaxy, pos, shield_pos);
        }
        if (strcmp(command, "SHW") == 0){
            scanf("%d", &pos);
            show_function(galaxy, pos);
        }
        number_of_commands--;
    }
    free_galaxy(&galaxy);
    return 0;
}
