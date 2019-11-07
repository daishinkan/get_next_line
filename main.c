#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int ac, char **av)
{
	(void)ac;
	int fd;
	int ret;
	char *line;

	fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			return (0);
		printf("ret : %d line :%s\n", ret, line);
		free(line);
	}
	printf("ret : %d line :%s\n", ret, line);
	free(line);
	printf("=================================\n");
	printf("=================================\n");
	printf("=============LEAKS===============\n");
	printf("=================================\n");
	printf("=================================\n");
	system("leaks a.out");
	return (0);
}

