#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    char *temp;
    unsigned long len = mx_strlen((char *)ptr);

    if (ptr == NULL) {
        ptr = mx_strnew(size);
        return ptr;
    }

    if (size == 0) {
        free(ptr);
        return NULL;
    } else if (size > len) {
        temp = mx_strnew(len);
        temp = mx_memcpy(temp, ptr, len);
        ptr = mx_strnew(size);
        ptr = mx_memcpy(ptr, temp, len);
        free(temp);
    } else if (size <= len && size > 0) {
        temp = mx_strnew(size);
        temp = mx_memcpy(temp, ptr, size);
        ptr = mx_strnew(size);
        ptr = mx_memcpy(ptr, temp, len);
        free(temp);
    }

    return ptr;
}

