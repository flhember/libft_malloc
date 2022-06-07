#ifndef LIBFT_MALLOC
# define LIBFT_MALLOC


//Include
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/mman.h>

//Stuct
struct block_meta {
  size_t size;
  struct block_meta *next;
  int free;
};

//Proto
void	*ft_malloc(size_t size);


#endif
