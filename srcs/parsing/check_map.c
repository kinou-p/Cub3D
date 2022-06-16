/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:26:58 by apommier          #+#    #+#             */
/*   Updated: 2022/06/16 16:29:06 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	close_or_not(char **tab, int i, int j, t_data *img)
{
	if (tab[i + 1][j] == '3' || tab[i - 1][j] == '3')
		img->map.error = 1;
	if (tab[i][j + 1] == '3' || tab[i][j - 1] == '3')
		img->map.error = 1;
	if (tab[i + 1][j + 1] == '3' || tab[i + 1][j - 1] == '3')
		img->map.error = 1;
	if (tab[i - 1][j + 1] == '3' || tab[i - 1][j - 1] == '3')
		img->map.error = 1;
	if (img->map.error != 1)
		img->map.error = 0;
}

void	check_border(char **tab, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '0' || tab[i][j] == 'W' || tab[i][j] == 'N'
				|| tab[i][j] == 'S' || tab[i][j] == 'E')
				close_or_not(tab, i, j, img);
			j++;
		}
		i++;
	}
}

int	check_inner_utils(char *line, t_data *img)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			find_angle(line[i], img);
			img->player.x = i * 64 - 32;
			player++;
		}
		else if (line[i] != '3' && line[i] != '0' && line[i] != '1')
			return (100);
		i++;
	}
	return (player);
}

void	check_inner(char **map, t_data *img)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		player += check_inner_utils(map[i], img);
		if (player == 1 && !img->player.y)
			img->player.y = i * 64 - 32;
		i++;
	}
	if (player == 0)
		img->map.error = 2;
	if (player > 1 && player < 100)
		img->map.error = 3;
	if (player >= 100)
		img->map.error = -1;
}
