/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:10:11 by apommier          #+#    #+#             */
/*   Updated: 2022/06/15 21:38:53 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	put_texture_in_struct(char type, unsigned char *texture, t_data *img)
{
	if (type == 'N')
	{
		if (img->map.texture.north)
			ft_exit("Error\nMultiple declaration of texture\n", img);
		img->map.texture.north = texture;
	}
	if (type == 'S')
	{
		if (img->map.texture.south)
			ft_exit("Error\nMultiple declaration of texture\n", img);
		img->map.texture.south = texture;
	}
	if (type == 'W')
	{
		if (img->map.texture.west)
			ft_exit("Error\nMultiple declaration of texture\n", img);
		img->map.texture.west = texture;
	}
	if (type == 'E')
	{
		if (img->map.texture.east)
			ft_exit("Error\nMultiple declaration of texture\n", img);
		img->map.texture.east = texture;
	}
}

int	is_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	get_file_size(char *path, t_data *img, int *count, int fd)
{
	char	*swap;

	swap = 0;
	if (!path)
		ft_exit("Error\nNo path for texture\n", img);
	check_dir(path, img);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit("Error\nBad path for texture\n", img);
	img->to_be_free.fd = fd;
	while (swap || !(*count))
	{
		if (swap)
			free(swap);
		(*count)++;
		swap = get_next_line(fd);
	}
	close(fd);
	img->to_be_free.fd = -1;
	if (*count != 12291)
		ft_exit("Error\nBad texture file (too much or not enough line)\n", img);
}

void	fill_ret(int count, t_data *img, unsigned char **ret, char *swap)
{
	while (swap || !count)
	{	
		if (swap)
			free(swap);
		swap = get_next_line(img->to_be_free.fd);
		if (!count)
		{
			free(swap);
			swap = get_next_line(img->to_be_free.fd);
		}
		if (swap)
			swap[ft_strlen(swap) - 1] = 0;
		if ((swap && is_nbr(swap) && ft_strlen(swap) <= 3
				&& ft_atoi(swap) <= 255 && ft_atoi(swap) >= 0) || !count)
			(*ret)[count] = (unsigned char)ft_atoi(swap);
		else if (swap)
		{
			get_next_line(-1);
			free(swap);
			ft_exit("Error\nBad texture file (not numbers or to high)\n", img);
		}
		count++;
	}
}

unsigned char	*get_texture(char type, char *path, t_data *img)
{
	int				fd;
	unsigned char	*ret;
	int				count;

	(void)type;
	count = 0;
	get_file_size(path, img, &count, 0);
	ret = ft_calloc(sizeof(char), count);
	if (!ret)
		quit_game(img);
	img->to_be_free.str = ret;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit("Error\nBad texture file", img);
	img->to_be_free.fd = fd;
	fill_ret(0, img, &ret, 0);
	close(fd);
	img->to_be_free.fd = -1;
	put_texture_in_struct(type, ret, img);
	img->to_be_free.str = 0;
	return (ret);
}
