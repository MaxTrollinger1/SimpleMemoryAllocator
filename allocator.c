// allocator.c
// A simple memory allocator by Max Trollinger to learn basic memory allocation techniques.
#include <stddef.h>
#include <unistd.h>
#include <pthread.h>

header_t *head, *tail;
pthread_mutex_t global_malloc_lock;


void *malloc(size_t size)
{
    size_t total_size;
    void *block;
    header_t *header;

    if (!size)
        return NULL;

    pthread_mutex_lock(&global_malloc_lock); // lock mutex
    header = get_free_block(size);

    if (header) { // found free block
        header->s.is_free = 0; // not free anymore
        pthread_mutex_unlock(&global_malloc_lock); // unlock mutex
        return (void*)(header + 1); // return ptr to data
    }

    total_size = sizeof(header_t) + size;
    block = sbrk(total_size); // extend heap

    if (block == (void*) - 1) { // sbrk failed to allocate memory
        pthread_mutex_unlock(&global_malloc_lock); // unlock mutex
        return NULL;
    }

    header = block;
    header->s.size = size;
    header->s.is_free = 0;
    header->s.next = NULL;
    if (!head)
        head = header; // set head of free list
    if (tail)
        tail->s.next = header;

    tail = header;
    pthread_mutex_unlock(&global_malloc_lock); // unlock mutex

    return (void*)(header + 1); // pointer to usable memory
}

void free(void *block)
{
    header_t *header, *tmp;
    void *program_break;

    if (!block)
        return;

    pthread_mutex_lock(&global_malloc_lock); // lock mutex
    header = (header_t*)block - 1; // get header

    programbreak = sbrk(0);

    if ((char*)block + header->s.size == programbreak) { // block is at the end of the heap
		if (head == tail) {
			head = tail = NULL;
		} else {
			tmp = head;
			while (tmp) {
				if(tmp->s.next == tail) {
					tmp->s.next = NULL;
					tail = tmp;
				}
				tmp = tmp->s.next;
			}
		}
		sbrk(0 - sizeof(header_t) - header->s.size); // shrink heap
		pthread_mutex_unlock(&global_malloc_lock);
		return;
	}

    // not at the end of the heap, mark as free and hope to reuse later
    header->s.is_free = 1;
    pthread_mutex_unlock(&global_malloc_lock); // unlock mutex
}

void *calloc(size_t num, size_t nsize)
{
    size_t size;
    void *block 

    if (!num || !nsize)
        return NULL;

    size = num * nsize;

    // check for overflow
    if (nsize != size / num)
        return NULL; // overflow
    
    block = malloc(size);
    if (!block)
        return NULL;

    memset(block, 0, size); // set allocated memory to zero
    return block;
}

// changes the size of the memory block
void *realloc(void *block, size_t nsize)
{
    header_t *header;
	void *ret;

    // if block is null
	if (!block || !size)
		return malloc(size);

	header = (header_t*)block - 1;
	if (header->s.size >= size)
		return block;

	ret = malloc(size);
	if (ret) { // malloc succeeded
		memcpy(ret, block, header->s.size); // copy old data to new block
		free(block);
	}
	return ret;
}

// traverses the linked list and see if there already exist a block of memory that is marked as free and can accomodate the given size
header_t *get_free_block(size_t size)
{
    header_t *curr = head;

	while(curr) {
		if (curr->s.is_free && curr->s.size >= size) // found a free block with enough size
			return curr;
		curr = curr->s.next;
	}

	return NULL;
}

typedef char ALIGN[16];

union header
{
    struct header_t {
        size_t size;
        unsigned is_free;
        struct header_t *next;
    } s;
    ALIGN stub;
};
typedef union header header_t;
