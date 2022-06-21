#ifndef LIBFT_MALLOC
# define LIBFT_MALLOC

#define TINY_MAX	1024
#define SMALL_MAX	4096

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/mman.h>

//header of chunk
typedef struct	s_header {
	struct	s_header *prev;
	struct	s_header *next;
	size_t	size_total;
}	t_header;

//data of block for all malloc call
typedef struct	s_block {
	struct	s_block *prev;
	struct	s_block *next;
	size_t	data_size;
	int	free;
	int	last;
}	t_block;

//Global Variable, -> addr heap if is set.
extern	t_header	*heap_addr[3];

void	*ft_malloc(size_t size);
void 	ft_free(void *ptr);

#endif
