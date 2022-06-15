#include "libft_malloc.h"

/*void	find_block(void *ptr)
{
	t_header        *heap = heap_addr;
	t_block         *alloc = heap_addr + sizeof(t_header);

	while (alloc->next || alloc->prev)
	{
		if (ptr == ((void *)alloc + sizeof(t_block)) && alloc->free == 0)
		{
			printf("find at bloc %p\n", alloc);
			alloc->free = 1;
		}
		alloc = alloc->next;
	}
}*/

void 	ft_free(void *ptr)
{
	printf("heap start  %p\n", heap_addr);
	printf("addr a free %p\n", ptr);
	if (!ptr || !heap_addr)
		return ;
//	find_block(ptr);
}
