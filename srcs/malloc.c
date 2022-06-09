#include "libft_malloc.h"

void    *heap_addr;

void	*request_space(size_t size)
{
	void		*addr = NULL;
	int 		sizePage = 0;
	t_header	*heap;

	sizePage = getpagesize();
	if ((addr = mmap(NULL, sizePage, (PROT_READ | PROT_WRITE), (MAP_PRIVATE | MAP_ANONYMOUS), 0, 0)) == MAP_FAILED) {
		perror("mmap");
		return (NULL);
	}
	heap = addr;
	heap->prev = NULL;
	heap->next = NULL;
	heap->size_total = sizePage;
	printf("heap addr = %p heap struct size = %zu\n\n", addr, sizeof(t_header));
	return (addr);
}

void	*find_bloc(size_t size)
{
	t_header	*heap = heap_addr;
	t_block		*alloc = heap_addr + sizeof(t_header);
	void		*last_addr = NULL;

	while (alloc->next)
	{
		last_addr = alloc;
		alloc = alloc->next;
	}
	alloc->prev = last_addr;
	alloc->next = (void *)alloc + sizeof(t_block) + size;
	alloc->data_size = size;
	alloc->free = 0;
	printf("last = %p | next = %p\n", alloc->prev, alloc->next);
	printf("|%p|header 0x20|Addr return %p, data size = %zu|\n\n", alloc, (void *)alloc + sizeof(t_block),size);
	return ((void *)alloc + sizeof(t_block));
}

void	*ft_malloc(size_t size)
{
	void	*request_addr = NULL;

	if (size <= 0)
    		return NULL;
	if (!heap_addr && (heap_addr = request_space(size)) == 0)
		printf("Fail");

	request_addr = find_bloc(size);
	
	return (request_addr);
}
