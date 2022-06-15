/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 01:00:17 by apommier          #+#    #+#             */
/*   Updated: 2022/06/15 18:32:06 by apommier         ###   ########.fr       */
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

char	*transform_map(char **double_map, t_data *img)
{
	char	*map;
	int		i;
	int		j;
	int		index;

	i = -1;
	index = 0;
	img->map.size = img->map.x * img->map.y;
	map = ft_calloc(sizeof(char), img->map.size + 1);
	if (!map)
		quit_game(img);
	while (double_map[++i])
	{
		j = -1;
		while (double_map[i][++j])
		{
			map[i * img->map.x + j] = double_map[i][j];
			index++;
		}
	}
	img->map.simple_map = map;
	return (0);
}

void	set_texture_file(char *str, t_data *img, char c)
{
	int		index;

	index = next_space_index(str, 0);
	if (c == 'N')
	{
		if (str[index + 1] != 'O' || str[index + 2] != ' ')
			ft_exit("Error\nBad syntax in map file\n", img);
	}
	if (c == 'S')
	{
		if (str[index + 1] != 'O' || str[index + 2] != ' ')
			ft_exit("Error\nBad syntax in map file\n", img);
	}
	if (c == 'W')
	{
		if (str[index + 1] != 'E' || str[index + 2] != ' ')
			ft_exit("Error\nBad syntax in map file\n", img);
	}
	if (c == 'E')
	{
		if (str[index + 1] != 'A' || str[index + 2] != ' ')
			ft_exit("Error\nBad syntax in map file\n", img);
	}
	get_texture(c, str + index + 3, img);
}

void	check_value(char **tab, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (!ft_isdigit(tab[i][j]))
				ft_exit("Error\nRGB parameters need to be only digits\n", img);
			j++;
		}
		i++;
	}
}

void	set_color_utils(char **tab, t_color *rgb, t_data *img)
{
	if (ft_strlen(tab[0]) > 3 || !(ft_atoi(tab[0]) >= 0
			&& ft_atoi(tab[0]) <= 255))
		ft_exit("Error\nBad parameter in map file identifier(RGB)\n", img);
	if (ft_strlen(tab[0]) > 3 || !(ft_atoi(tab[1]) >= 0
			&& ft_atoi(tab[1]) <= 255))
		ft_exit("Error\nBad parameter in map file identifier(RGB)\n", img);
	if (ft_strlen(tab[0]) > 3 || !(ft_atoi(tab[2]) >= 0
			&& ft_atoi(tab[2]) <= 255))
		ft_exit("Error\nBad parameter in map file identifier(RGB)\n", img);
	check_value(tab, img);
	rgb->r = (unsigned char)ft_atoi(tab[0]);
	rgb->g = (unsigned char)ft_atoi(tab[1]);
	rgb->b = (unsigned char)ft_atoi(tab[2]);
	rgb->set = 1;
}

void	set_color(char *str, t_data *img)
{
	char	c;
	int		index;
	char	**tab;

	index = -1;
	while (str[++index])
	{
		if (str[index] == ',' && str[index + 1] == ',')
			ft_exit("Error\nBad syntax for RGB identifier\n", img);
	}
	c = next_space(str, 0);
	index = next_space_index(str + 1, 0);
	tab = ft_split(str + index + 1, ',');
	if (!tab)
		quit_game(img);
	img->to_be_free.tab_two = tab;
	if (c == 'F')
		set_color_utils(tab, &img->map.floor, img);
	if (c == 'C')
		set_color_utils(tab, &img->map.sky, img);
	free_double(tab);
	img->to_be_free.tab_two = 0;
}

int	check_texture_color(char **tab, t_data *img)
{
	int		next;
	int		index;

	index = 0;
	next = 0;
	while (tab && tab[next] && next_space(tab[next], 0) != '1')
		next++;
	if (!tab || !tab[next])
		ft_exit("Error\nBad syntax in map file (identifier)\n", img);
	while (index < next)
	{
		if (next_space(tab[index], 0) == 'N'
			|| next_space(tab[index], 0) == 'S'
			|| next_space(tab[index], 0) == 'W'
			|| next_space(tab[index], 0) == 'E')
			set_texture_file(tab[index], img, next_space(tab[index], 0));
		else if (next_space(tab[index], 0) == 'F'
			|| next_space(tab[index], 0) == 'C')
			set_color(tab[index], img);
		else if (next_space(tab[index], 0))
			ft_exit("Error\nBad syntax in map file (identifier)\n", img);
		index++;
	}
	return (next);
}
