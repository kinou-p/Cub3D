#ifndef PARSERCUB3D
# define PARSERCUB3D

# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <sys/types.h>

typedef struct s_root {
	int size;
	int height;
	int error;
}				t_root;

int	main(int ac, char **av);

#endif
