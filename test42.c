#include "includes/libft_malloc.h"

int	main()
{
	int	i;
	char	*addr;

	i = 0;
	while (i < 1024) {
		addr = (char *)ft_malloc(1024);
		addr[0] = 42;
		i++;
	}
	show_alloc_mem();
	return (0);
}
