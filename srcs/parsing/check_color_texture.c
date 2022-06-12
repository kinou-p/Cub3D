/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 01:00:17 by apommier          #+#    #+#             */
/*   Updated: 2022/06/11 17:33:45 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

char	next_space(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (str[i]);
}

int	next_space_index(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

/*char	next_line_space(char **tab, int i)
{
	while (!next_space(tab[i], 0))
		i++;
	return (tab[i]);
}*/

char *transform_map(char **double_map, t_data *img)
{
	char	*map;
	int		i;
	int		j;
	int		index;

	i = -1;
	index = 0;
	print_double_fd(double_map, 1);
	img->map.size = img->map.x * img->map.y;
	printf("x= %d y= %d\n", img->map.x, img->map.y);
	map = ft_calloc(sizeof(char), img->map.size + 1);
	while (double_map[++i])
	{
		j = -1;
		while (double_map[i][++j])
		{
			//printf("INDEX= %d\n", i * img->map.x + j);
			map[i * img->map.x + j] = double_map[i][j];
			map[index] = double_map[i][j];
			//printf("index= %d\n", index);
			index++;
		}
	}
	
	img->map.simple_map = map;
	printf("map = -%s-\n", map);
	return (0);	
}

void	set_texture_file(char *str, t_data *img, char c)
{
	int		index;

	index = next_space_index(str, 0);
	if (c == 'N')
	{
		if (str[index + 1] != 'O' || str[index + 2] != ' ')
			ft_exit("Error\nBad syntax in map file\n");
	}
	if (c == 'S')
	{
		if (str[index + 1] != 'O' || str[index + 2] != ' ')
			ft_exit("Error\nBad syntax in map file\n");
	}
	if (c == 'W')
	{
		if (str[index + 1] != 'E' || str[index + 2] != ' ')
			ft_exit("Error\nBad syntax in map file\n");
	}
	if (c == 'E')
	{
		if (str[index + 1] != 'A' || str[index + 2] != ' ')
			ft_exit("Error\nBad syntax in map file\n");
	}
	printf("path= -%s-\n", str + index + 3);
	get_texture(c, str + index + 3, img);
}

void	set_color(char *str, t_data *img)
{
	char	c;
	int		index;

	c = next_space(str, 0);
	index = next_space_index(str, 0);
	if (c == 'F')
	{
		if (str[index + 1] != ' ')
			ft_exit("Error\nBad syntax in map file\n");
	}
	if (c == 'C')
	{
		if (str[index + 1] != ' ')
			ft_exit("Error\nBad syntax in map file\n");
	}
}

int check_texture_color(char **tab, t_data *img)
{
	int		next;
	int		index;
	char	line;

	index = 0;
	next = 0;
	int i = 0;
	while (tab[i])
		printf("%s\n", tab[i++]);
	while (next_space(tab[next], 0) != '1' && tab[next])
		next++;
	if (!tab[next])
		ft_exit("Error\nBad syntax in map file\n");
	while (index < next)
	{
		if (next_space(tab[index], 0) == 'N' || next_space(tab[index], 0) == 'S' || next_space(tab[index], 0) == 'W' || next_space(tab[index], 0) == 'E')
			set_texture_file(tab[index], img, next_space(tab[index], 0));
		else if (next_space(tab[index], 0) == 'F' || next_space(tab[index], 0) == 'C')
			set_color(tab[index], img);
		else if (next_space(tab[index], 0))
			ft_exit("Error\nBad syntax in map file\n");
		index++;
	}
	return (next);
}