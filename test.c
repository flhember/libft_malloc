#include "includes/libft_malloc.h"

int	main(void)
{
	ft_malloc(10);
	ft_malloc(10);
	ft_malloc(10);
	ft_malloc(10);
	ft_malloc(4096);
	ft_malloc(10);
	//ft_malloc(7000);
	//ft_malloc(100000);
	show_alloc_mem();
	return (0);
}
