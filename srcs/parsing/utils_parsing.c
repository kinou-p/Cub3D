/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:34:49 by apommier          #+#    #+#             */
/*   Updated: 2022/06/16 16:25:36 by apommier         ###   ########.fr       */
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

void	find_angle(char c, t_data *img)
{
	if (c == 'N')
		img->player.angle = 90;
	if (c == 'E')
		img->player.angle = 0;
	if (c == 'S')
		img->player.angle = 270;
	if (c == 'W')
		img->player.angle = 180;
}

void	size_line(char *str, t_data *img)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > img->map.x)
		img->map.x = i;
}
