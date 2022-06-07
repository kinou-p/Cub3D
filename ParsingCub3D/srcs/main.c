/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:54:25 by sadjigui          #+#    #+#             */
/*   Updated: 2022/06/07 20:19:32 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsercub3D.h"

void size_line(char *str, t_root *global)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (i > global->size)
		global->size = i;
	else
		return;
}

char *charge_new(t_root *global)
{
	char *str;
	int i;

	i = 0;
	str = malloc(sizeof(char) * (global->size + 3));
	if (!str)
		return (NULL);
	while (i < global->size + 2)
	{
		str[i] = '3';
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	reverse_comp(char *s1, char *s2)
{
	int	size_s1;
	int	size_s2;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	while (size_s2 >= 0)
	{
		if (!(s2[size_s2] == s1[size_s1]))
			return (1);
		size_s1--;
		size_s2--;
	}
	return (0);
}

void inter_map(char **split, char **tmp)
{
	int i;
	int j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while(split[i][j])
		{
			if (ft_isalnum(split[i][j]))
				tmp[i + 1][j + 1] = split[i][j];
			j++;
		}
		i++;
	}
}

void close_or_not(char **tab, int i, int j, t_root *global)
{
	if(tab[i + 1][j] == '3' || tab[i - 1][j] == '3')
		global->error++;
	if(tab[i][j + 1] == '3' || tab[i][j - 1] == '3')
		global->error++;
	if(tab[i + 1][j + 1] == '3' || tab[i + 1][j - 1] == '3')
		global->error++;
	if(tab[i - 1][j + 1] == '3' || tab[i - 1][j - 1] == '3')
		global->error++;
}

int	check_inner_utils(char *line)
{
	int	i;
	int player;

	i = 0;
	player = 0;
	while (line[i])
	{
		// if (line[i] == '0' || line[i] == '1' || line[i] == '3' || line[i] == '\n')
		// 	i++;
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			player++;
		else if (line[i] != 'W' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != '3' && line[i] != '0' && line[i] != '1')
			return (2);
		// else
		// 	return (2);
		i++;
	}
	return (player);
}

void check_inner(char **map, t_root *global)
{
	int i;
	int player;

	i = 0;
	player = 0;
	while (map[i])
	{
		player += check_inner_utils(map[i]);
		i++;
	}
	if (player != 1)
		global->error++;
}

void check_border(char **tab, t_root *global)
{
	int i;
	int j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '0')
				close_or_not(tab, i, j, global);
			j++;
		}
		i++;
	}
}

void	check_zero_one(char **split, t_root *global)
{
	char **tmp;
	int i;

	i = 0;
	while (split[i])
		i++;
	global->height = i;
	tmp = malloc(sizeof(char *) * (i + 3));
	if (!tmp)
		return ;
	i = 0;
	while(i < global->height + 3)
	{
		tmp[i] = charge_new(global);
		i++;
	}
	tmp[i] = NULL;
	inter_map(split, tmp);
	check_border(tmp, global);
	check_inner(tmp, global);
}

char	**isafile(char **av, t_root *global)
{
	int		fd;
	char	*line;
	char	*str;
	char	*tmp;
	char	**split;

	fd = open(av[1], O_RDONLY);
	str = NULL;
	tmp = NULL;
	if (fd == - 1)
		exit(1);
	while ((line = get_next_line(fd)) != NULL)
	{
		tmp = ft_strjoin(str, line);
		if (str != NULL)
			free(str);
		str = tmp;
		size_line(line, global);
		free(line);
		line = NULL;
	}
	split = ft_split(str, '\n');
	free(line);
	free(str);
	close(fd);
	check_zero_one(split, global);
	return (split);
}

int check_map(char **av, t_root *global)
{
	char	**map;

	global->size = 0;
	global->height = 0;
	global->error = 0;

	map = NULL;
	if (reverse_comp(av[1], ".cub") || (ft_strlen(av[1]) == ft_strlen(".cub")))
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	map = isafile(av, global);
	if (global->error != 0)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_root global;

	if (check_map(av, &global))
		return (0);
	else
		printf("map is clean\n");
}
