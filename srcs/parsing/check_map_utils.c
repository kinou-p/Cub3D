/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:30:52 by apommier          #+#    #+#             */
/*   Updated: 2022/06/16 16:32:55 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	verify_texture_color(t_data *img)
{
	if (img->map.texture.north == NULL)
		ft_exit("Error\nTexture isn't loaded properly\n", img);
	if (img->map.texture.east == NULL)
		ft_exit("Error\nTexture isn't loaded properly\n", img);
	if (img->map.texture.south == NULL)
		ft_exit("Error\nTexture isn't loaded properly\n", img);
	if (img->map.texture.west == NULL)
		ft_exit("Error\nTexture isn't loaded properly\n", img);
	if (img->map.floor.set != 1)
		ft_exit("Error\nColor not set properly\n", img);
	if (img->map.sky.set != 1)
		ft_exit("Error\nColor not set properly\n", img);
}

void	error_msg(t_data *img)
{
	if (img->map.error == 1)
		ft_exit("Error\nMap isn't closed\n", img);
	if (img->map.error == 2)
		ft_exit("Error\nMissing player\n", img);
	if (img->map.error == 3)
		ft_exit("Error\nToo many players\n", img);
	if (img->map.error == -1)
		ft_exit("Error\nBad character in map\n", img);
}

void	inter_map(char **split, char **tmp, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == '3')
				img->map.error = -1;
			else if (split[i][j] != ' ')
				tmp[i + 1][j + 1] = split[i][j];
			j++;
		}
		i++;
	}
}

void	check_empty_line(char **split, t_data *img, int *i)
{
	while (split[*i])
	{
		if (!ft_strchr(split[*i], '1'))
			ft_exit("Error\nInvalid line in map file\n", img);
		size_line(split[*i], img);
		(*i)++;
	}
}

void	check_zero_one(char **split, t_data *img)
{
	char	**tmp;
	int		i;

	i = 0;
	check_empty_line(split, img, &i);
	img->map.y = i;
	tmp = malloc(sizeof(char *) * (i + 3));
	if (!tmp)
		quit_game(img);
	i = 0;
	while (i < img->map.y + 2)
	{
		tmp[i] = charge_new(img, split, tmp);
		i++;
	}
	tmp[i] = NULL;
	inter_map(split, tmp, img);
	if (img->map.error == -1)
	{
		free_double(tmp);
		return ;
	}
	check_border(tmp, img);
	check_inner(tmp, img);
	free_double(tmp);
}
