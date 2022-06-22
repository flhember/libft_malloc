#include "libft_malloc.h"

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

void		print_name_zone(int zone, void *addr)
{
	if (zone == 0)
		printf("TINY : %p\n", addr);
	else if (zone == 1)
		printf("SMALL : %p\n", addr);
	else
		printf("LARGE : %p\n", addr);
}

size_t		print_zone(int zone)
{
	size_t		size_total = 0;
	t_header	*head = heap_addr[zone];
	t_block		*chunk = (void *)head + sizeof(t_header);
	
	if (head)
		print_name_zone(zone, head);
	while (head)
	{
		while (chunk->next)
		{
			printf("%p - %p : %zu octets\n", (void *)chunk + sizeof(t_block), chunk->next ,chunk->data_size);
			size_total += chunk->data_size;
			chunk = chunk->next;
		}
		head = head->next;
	}
	return (size_total);
}

void		show_alloc_mem(void)
{
	int	zone = 0;
	size_t	size_total = 0;

	while (zone < 3)
	{
		size_total += print_zone(zone);
		zone += 1;
	}
	printf("Total : %zu octets\n", size_total);
}
