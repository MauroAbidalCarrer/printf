#include<stdio.h>
int	ft_printf(const char * s, ...);

int	main(int ac, char **av)
{
	char *ui = NULL;
	printf("%d\n", ft_printf("my = j'ai %p ans!\n", ui));

	printf("%d\n", printf("og = j'ai %p ans!\n", ui));
}
