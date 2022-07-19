#include "libft_malloc.h"

/*
Return first header.
*/
t_header	*find_first_header(t_header *head)
{
//	while (head->prev)
//		head = head->prev;
	return (head);
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
		return (find_multiple_page_size((TINY_MAX * 100)));
	else if (zone == 1)
		return (find_multiple_page_size((SMALL_MAX * 100) + sizeof(t_header)));
	else
		return (find_multiple_page_size(size + sizeof(t_block) + sizeof(t_header)));
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
