/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:34:49 by apommier          #+#    #+#             */
/*   Updated: 2022/06/15 23:38:38 by apommier         ###   ########.fr       */
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
