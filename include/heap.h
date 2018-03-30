#ifndef __HEAP_H__
#define __HEAP_H__

typedef int (*heapCmpFunc)(void* a, void* b);
typedef struct heap * HEAP;
             
HEAP initHeap(int size, heapCmpFunc func);
int insertHeap(HEAP h, void* elem);


#endif