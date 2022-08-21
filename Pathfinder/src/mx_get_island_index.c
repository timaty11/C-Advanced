#include "../inc/header.h"

int mx_get_island_index(char *island_name, char *island_array[]) {
    for (int i = 0; island_array[i]; i++) {
        if (!mx_strcmp(island_name, island_array[i])) {
            return i;
        }
    }
    return 0;
}

