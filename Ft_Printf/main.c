int	ft_printf(const char *args, ...);

#include <stdio.h>
int main()
{
	char *str = NULL;

	printf("cnt : %d\n",   ft_printf("%s\n", str));
	printf("cnt : %d\n",   printf("%s\n", str));
}
