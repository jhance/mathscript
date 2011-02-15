#include "xmalloc.h"
#include <stdlib.h>
#include <stdio.h>

void *xmalloc(size_t size) {
    void *alloc = malloc(size);
    if(alloc != NULL) {
        return alloc;
    } else {
        fprintf(stderr, "Error: Out of memory\n");
        exit(1);
    }
}
