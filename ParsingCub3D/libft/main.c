#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

// __attribute__((no_sanitize_address))
//__attribute__((destructor)) void	destructeur()
//{
//	while (1);
//}

int		main(int ac, char **av)
{
	(void)ac;
	int		fd = open(av[1], O_RDONLY);
	char	*line = NULL;
	int		i;

	i = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Ligne %d: %s\n", i, line);
		free(line);
		line = NULL;
		i++;
	}
	printf("Ligne %d: %s\n", i, line);
	free(line);
	close(fd);
	system("leaks a.out");
	// destructeur();
	return (0);
}
