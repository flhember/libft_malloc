#ifndef LIBFT_MALLOC
# define LIBFT_MALLOC

#define TINY_MAX	1024
#define SMALL_MAX	4096

//#define TINY_MAX	32
//#define SMALL_MAX	64

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/mman.h>

//header of chunk
typedef struct	s_header {
	struct	s_header *next;
	size_t	size_total;
}	t_header;

//data of block for all malloc call
typedef struct	s_block {
	struct	s_block *next;
	size_t	data_size;
}	t_block;

//Global Variable, -> addr heap if is set.
extern	t_header	*heap_addr[3];

void	*ft_malloc(size_t size);
void 	ft_free(void *ptr);
void	show_alloc_mem(void);

//malloc utils
int		find_good_zone(size_t size);
size_t		find_good_size(size_t size, int zone);
size_t		find_multiple_page_size(size_t size);
t_header	*find_first_header(t_header *head);

#endif
