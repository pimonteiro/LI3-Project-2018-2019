#include "heap.h"

#include <stdlib.h>

#define PARENT(i) (i-1)/2
#define LEFT(i) 2*i + 1
#define RIGHT(i) 2*i + 2

struct heap{
    int   size; // Tamanho
    int   load;  // Load da HEAP
    void** array; // Elementos
    heapCmpFunc cmp; // Function pointers
};

HEAP initHeap(int size, heapCmpFunc func) {
    HEAP h = malloc(sizeof(struct heap));
    if(h != NULL) {
        h->size = size;
        h->load = 0;
        h->array=malloc(size*sizeof(void*));
        h->cmp = func;
    }
    return h;
}

void free_heap(void* h){
    if(h == NULL) return;
    HEAP heap = (HEAP)h;

    free(heap->array);
    free(heap);
}

static void swap(HEAP h, int a, int b) {
    void* tmp = h->array[a];
    h->array[a] = h->array[b];
    h->array[b] = tmp;
}


static void bubbleUp(HEAP h, int i) {
    while (i != 0 && (h->cmp(h->array[i], h->array[PARENT(i)]) >= 1) )  { // enquanto actual > pai
        swap(h, i, PARENT(i));
        i = PARENT(i);
    }
}


int insertHeap(HEAP h, void* elem) {
    if (h->load == h->size) {
        h->array= realloc(h->array, 2*(h->size)*sizeof(void*));
        h->size *= 2;
    }
    if(h->array != NULL){
        h->array[h->load] = elem;
        bubbleUp(h, h->load);
        ++(h->load);
        return 0;
    }
    return 1;
}
