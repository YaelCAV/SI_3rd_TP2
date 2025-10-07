#include "main.h"

#include <stdlib.h>
#define MAGIC_NUMBER 0X0123456789ABCDEFL
#define BLOCK_SIZE 1024

/*---------------------------------------------------------------------------------*/
typedef struct HEADER_TAG {
    struct HEADER_TAG *ptr_next; /* pointe sur le prochain bloc libre */
    struct HEADER_TAG *ptr_previous;
    size_t bloc_size; /* taille du memory bloc en octets*/
    long magic_number; /* 0x0123456789ABCDEFL */
} HEADER;

//function protoype
void magic_check(void* ptr);
HEADER *free_memory = NULL;
int oopsie=0;

void *malloc3is(size_t size) {
    void *request = sbrk(sizeof(HEADER) + size + sizeof(MAGIC_NUMBER));
    if (request == (void *) -1) {
        return NULL; // sbrk failed.
    }

    //initialisation du header + block
    HEADER *new_header = request;
    new_header->bloc_size = size;
    new_header->magic_number = MAGIC_NUMBER;
    *((long long *) (new_header + sizeof(HEADER) + size)) = MAGIC_NUMBER;


    return ++new_header; //typed pointer
}


void free3is(void *ptr) {
    magic_check(ptr);
    if (free_memory == NULL) {
        free_memory = (HEADER*)(ptr-sizeof(HEADER));
    } else {
        free_memory->ptr_previous = free_memory;
        free_memory->ptr_next = (HEADER *) (ptr-sizeof(HEADER));
    }
}

void magic_check(void* ptr) {
    const HEADER* header = (HEADER *) ptr-sizeof(HEADER);
    if (header->magic_number != MAGIC_NUMBER) {
        oopsie++;
    }
}

int main(void) {
    printf("Hello, World!\n");
    void *p = malloc3is(0);
    void *p2 = malloc3is(0);
    printf("%p\n", p);
    printf("%p\n", p2);
    printf("%lu\n", sizeof(HEADER) + sizeof(MAGIC_NUMBER));
    p= "feurfeurfeurfeurfeurfeur";
    printf("%p\n",free_memory );
    free3is(p);
    printf("%i\n",oopsie);
    printf("%p\n",free_memory );
    free3is(p2);
    printf("%p\n",free_memory->ptr_next );
}
