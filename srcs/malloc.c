#include "libft_malloc.h"

t_header	*heap_addr[3];

/* -------------------- */
/*	Debug ft	*/
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

/* -------------------- */



/*
Return first header.
*/
t_header	*find_first_header(t_header *head)
{
	while (head->prev)
		head = head->prev;
	return (head);
}

/*
Function to create block with space for user.
*/
void	*create_block(t_header *head, size_t size, int zone)
{
	void		*last_addr = NULL;
	t_block		*alloc = (void *)head + sizeof(t_header);

	print_header_zone(zone);
	while (alloc->next && (void *)alloc->next < (void *)(head + head->size_total - (sizeof(t_block) + size)))
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
Need multiple of getpagesize for size of area.
*/
size_t	find_multiple_page_size(size_t size)
{
	int size_page = getpagesize();

	while (size_page < size)
		size_page += getpagesize();
	return (size_page);
}

/*
Find size of area
*/
size_t	find_good_size(size_t size, int zone)
{
	if (zone == 0)
		return (find_multiple_page_size(((TINY_MAX + sizeof(t_block)) * 100) + sizeof(t_header)));
	else if (zone == 1)
		return (find_multiple_page_size(((SMALL_MAX + sizeof(t_block)) * 100) + sizeof(t_header)));
	else
		return (find_multiple_page_size(size + sizeof(t_block) + sizeof(t_header)));
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
	printf("SIZE = %zu\n", size_header);
	printf("SIZE GET PAGE = %d\n", getpagesize());
	printf("SIZE bloc = %zu, size header = %zu\n", sizeof(t_block), sizeof(t_header));
	//size_header = getpagesize() * (zone + 1); // size a fix
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
		if ((void *)(head->size_total) > (void *)(chunk->next + size))
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
	if (size <= TINY_MAX)
		return (0);
	else if (size <= SMALL_MAX)
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
