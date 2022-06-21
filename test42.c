#include "includes/libft_malloc.h"

int	main()
{
	int	i;
	int	j;

	i = 0;
	j = 1000;
	while (i < 100) {
		ft_malloc(j);
		i++;
		j++;
	}
	return (0);
}
