#include "libft_malloc.h"

#define META_SIZE sizeof(struct block_meta)	//test


//find_bloc


void	*request_space(size_t size, int sizePage)
{
	void	*addr;

	if ((addr = mmap(NULL, sizePage, (PROT_READ | PROT_WRITE), (MAP_PRIVATE | MAP_ANONYMOUS), 0, 0)) == MAP_FAILED) {
		perror("mmap");
		return (NULL);
	}

	return (addr);
}

void	*ft_malloc(size_t size)
{
	int 	sizePage = getpagesize();
	void	*addr = 0;

	if (size <= 0)
    		return NULL;

	printf("size = %zu\nPage = %d\nSize header = %zu\n", size, sizePage, META_SIZE);
	if ((addr = request_space(size, sizePage)) == 0)
		printf("Fail");
	printf("addr = %p\n", addr);
	return (NULL);
}
