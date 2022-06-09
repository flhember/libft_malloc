#ifndef LIBFT_MALLOC
# define LIBFT_MALLOC

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/mman.h>

//header of chunk
typedef struct	s_header {
	struct	s_header *prev;
	struct	s_header *next;
	size_t	size_total;
	size_t	count_block;
} t_header;

//data of block for witch malloc call
typedef struct	s_block {
	struct	s_block *prev;
	struct	s_block *next;
	size_t	data_size;
	int	free;
} t_block;

//Global Variable, -> addr heap if is set.
extern void    *heap_addr;

void	*ft_malloc(size_t size);
void 	ft_free(void *ptr);

#endif
