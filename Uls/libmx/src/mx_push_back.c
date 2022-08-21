#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data) {
    if (!*list) {
        *list = mx_create_node(data);
        return;
    }
    t_list *tmp = *list;
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = mx_create_node(data);
}

