#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);

int	main()
{
	char 	*ret;
	int		cnt = 10;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	while (cnt--)
	{
		ret = get_next_line(fd);
		printf("part : %s\n", ret);
		free(ret);
	}
	close(fd);
	system("leaks a.out");
	return (0);
}