#include "includes/libft_malloc.h"

int	main(void)
{
	void	*addr;


	ft_free(addr);
	addr = ft_malloc(10);
	ft_malloc(20);
	ft_malloc(30);
	ft_malloc(40);
	return (0);
}
