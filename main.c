#include "main.h"

#include <stdlib.h>
#define MAGIC_NUMBER 0X0123456789ABCDEFL
#define BLOCK_SIZE 1024

/*---------------------------------------------------------------------------------*/
typedef struct HEADER_TAG {
    struct HEADER_TAG *ptr_next; /* pointe sur le prochain bloc libre */
    size_t bloc_size; /* taille du memory bloc en octets*/
    long magic_number; /* 0x0123456789ABCDEFL */
} HEADER;


HEADER *free_memory = NULL;

void *malloc3is(size_t size) {
    void *p = sbrk(0);
    void *request = sbrk(sizeof(HEADER) + size + sizeof(MAGIC_NUMBER));
    if (request == (void *) -1) {
            return NULL; // sbrk failed.
        }

    //initialisation du header + block
    HEADER *new_header = (HEADER *) request;
    new_header->bloc_size = size;
    new_header->magic_number = MAGIC_NUMBER;
    *((long long *) (new_header + sizeof(HEADER) + size)) = MAGIC_NUMBER;


    assert(p == new_header);
    return new_header;
}


void  free3is(void *ptr) {

}

int main(void) {
    printf("Hello, World!\n");
    void *p = malloc3is(0);
    void *p2 = malloc3is(0);
    printf("%p\n", p);
    printf("%p\n", p2);
    printf("%i\n", sizeof(HEADER) + sizeof(MAGIC_NUMBER));
}
