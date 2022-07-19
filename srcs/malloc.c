#include "libft_malloc.h"

t_header	*heap_addr[3];

/*
Function to create block with space for user.
*/
void	*create_block(t_header *head, size_t size, int zone)
{
	void		*last_addr = NULL;
	t_block		*alloc = (void *)head + sizeof(t_header);

	while (alloc->next && (void *)alloc->next < (void *)(head + head->size_total - (sizeof(t_block) + size)))
	{
		last_addr = alloc;
		alloc = alloc->next;
	}
	if ((void *)alloc + sizeof(t_block) + size > (void *)head + head->size_total) {
		printf("last chunk in area\n");
		alloc->next = NULL;
	} else {
		alloc->next = (void *)alloc + sizeof(t_block) + size;
	}
	alloc->data_size = size;
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
	size_header = find_good_size(size, zone);
	printf("size malloc = %zu \n", size_header);
	if ((head = mmap(NULL, size_header, (PROT_READ | PROT_WRITE), (MAP_PRIVATE | MAP_ANONYMOUS), 0, 0)) == MAP_FAILED) {
		perror("mmap");
		return (NULL);
	}
	head->size_total = size_header;
	head->next = NULL;
	if (addr_prev) {
		head_tmp = addr_prev;
		head_tmp->next = head;
	}
	if (!heap_addr[zone])
		heap_addr[zone] = head;
	return (head);
}

/*
Check if header alredy exist with some place
*/
t_header	*find_header(size_t size, int zone)
{
	t_header	*head;
	t_block		*chunk;
	int		i = 0;

	head = heap_addr[zone];
	while (head)
	{
		chunk = (void *)head + sizeof(t_header);
		while (chunk->next) {
			chunk = chunk->next;
		}
		if ( (void *)head + head->size_total > (void *)chunk + size)
			return (head);
		head = head->next;
	}
	return (NULL);
}

/*
Start by find or create header with space
Then put chunk with  block header and zone for user.
*/
void	*find_space(size_t size, int zone)
{
	t_header	*head = NULL;
	
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
	
	//request_addr = mmap(NULL, size, (PROT_READ | PROT_WRITE), (MAP_PRIVATE | MAP_ANON), -1, 0);
	//return (NULL);
}
