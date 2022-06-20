#include "libft_malloc.h"

t_header	*heap_addr[3];

/*void	*request_space(size_t size)
{
	void		*addr = NULL;
	int 		sizePage = 0;
	t_header	*heap;

	sizePage = getpagesize();
	printf("size pag = %d\n", sizePage);
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
}*/

/*void	*find_bloc(size_t size)
{
	t_header	*heap = heap_addr;
	t_block		*alloc = heap_addr + sizeof(t_header);
	void		*last_addr = NULL;

	while (alloc->next && (void *)alloc->next < (void *)(heap_addr + heap->size_total) - ((void *)sizeof(t_block) + size))
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
*/
//-----------------------------------------------------------------------------------//

void		print_header_content(t_header *head)
{
	t_block		*alloc = (void *)head + sizeof(t_header);
	while (alloc)
	{
		printf("+------------------------------------------+\n");
		printf("+--------------%p--------------+\n", alloc);
		printf("+prev %14p | next %14p +\n", alloc->prev, alloc->next);
		printf("+------------------------------------------+\n");
		printf("\t\tsize = %zu \n", alloc->data_size);
		printf("+------------------------------------------+\n\n");
		alloc = alloc->next;
	}
}

void		print_header_zone(int zone)
{
	t_header	*head = heap_addr[zone];

	while (head)
	{
		printf("|------------------------------------------|\n");
		printf("|--------------%p--------------|\n", head);
		printf("|prev %14p | next %14p |\n", head->prev, head->next);
		printf("|------------------------------------------|\n\n");
		head = head->next;
	}
}

t_header	*find_first_header(t_header *head)
{
	while (head->prev)
		head = head->prev;
	return (head);
}

/*
Now we have a header with some space, so create block
with space for user
*/
void	*create_block(t_header *head, size_t size, int zone)
{
	void		*last_addr = NULL;
	t_block		*alloc = (void *)head + sizeof(t_header);

	print_header_zone(zone);
	while (alloc->next && (void *)alloc->next < (void *)(head + head->size_total) - ((void *)sizeof(t_block) + size))
	{
		last_addr = alloc;
		alloc = alloc->next;
	}
	alloc->prev = last_addr;
	alloc->next = (void *)alloc + sizeof(t_block) + size;
	alloc->data_size = size;
	alloc->free = 0;
	print_header_content(head);
	return ((void *)alloc + sizeof(t_block));
}


/*
Create header if actualy not space available.
*/
void	*create_space(size_t size, int zone)
{
	size_t		size_header;
	t_header	*head = NULL;
	t_header	*head_tmp = NULL;
	void		*addr_prev = NULL;
	
	head = heap_addr[zone];
	while (head) {
		addr_prev = head;
		head = head->next;
	}
	size_header = getpagesize() * 2; // size a fix
	if ((head = mmap(NULL, size_header, (PROT_READ | PROT_WRITE), (MAP_PRIVATE | MAP_ANONYMOUS), 0, 0)) == MAP_FAILED) {
		perror("mmap");
		return (NULL);
	}
	head->size_total = size_header;
	head->prev = addr_prev;
	head->next = NULL;
	if (addr_prev) {
		head_tmp = addr_prev;
		head_tmp->next = head;
	}
	heap_addr[zone] = find_first_header(head);
	return (head);
}

/*
Check if header alredy exist with some place
*/
t_header	*find_header(size_t size, int zone)
{
	t_header	*head;
	t_block		*chunk;

	head = heap_addr[zone];
	while (head)
	{
		chunk = (void *)head + sizeof(t_header);
		while (chunk->next)
			chunk = chunk->next;
		if (head->size_total > chunk->next + size)
			return (head);
		head = head->next;
	}
	return (NULL);
}

/*
Find good zone:
0 = Tiny
1 = Small
2 = Large
Global Variable = Header_tab[Tiny, Small, Large]. Each on point to his first header.
*/
int	find_good_zone(size_t size)
{
	if (size < TINY)
		return (0);
	else if (size < SMALL)
		return (1);
	else	
		return (2);
}

/*
Start by find or create header with space
Then put chunk with  block header and zone for user.
*/
void	*find_space(size_t size, int zone)
{
	t_header	*head = NULL;
	
	printf("zone = %d\n", zone);
	if (!(head = find_header(size, zone)))
		head = create_space(size, zone);
	return (create_block(head, size, zone));
}

/* 
Main funtion, if size malloc null return NULL.
Else return address of alloc zone.
*/
void	*ft_malloc(size_t size)
{
	int	zone = 0;
	void	*request_addr = NULL;

	if (size <= 0)
    		return NULL;
	request_addr = find_space(size, find_good_zone(size));
	return (request_addr);
}
