#include "includes/libft_malloc.h"

int	main()
{
	int	i;

	i = 0;
	while (i < 1024) {
		ft_malloc(1);
		i++;
	}
	return (0);
}
