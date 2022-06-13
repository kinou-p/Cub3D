/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:10:11 by apommier          #+#    #+#             */
/*   Updated: 2022/06/13 01:49:43 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	put_texture_in_struct(char type, unsigned char *texture, t_data *img)
{
	if (type == 'N')
	{
		if (img->map.texture.north)
			ft_exit("Error\nMultiple declaration of texture\n");
		img->map.texture.north = texture;
	}
	if (type == 'S')
	{
		if (img->map.texture.south)
			ft_exit("Error\nMultiple declaration of texture\n");
		img->map.texture.south = texture;
	}
	if (type == 'W')
	{
		if (img->map.texture.west)
			ft_exit("Error\nMultiple declaration of texture\n");
		img->map.texture.west = texture;
	}
	if (type == 'E')
	{
		if (img->map.texture.east)
			ft_exit("Error\nMultiple declaration of texture\n");
		img->map.texture.east = texture;
	}
}

unsigned char *get_texture(char type, char *path, t_data *img)
{
	int		fd;
	unsigned char		*ret;
	int		count;
	char	*swap = 0;

	if (!path)
	{
		printf("no path\n");
		path = ft_strjoin("./sprite/brick_wall.ppm", 0);
	}
	(void)type;
	count = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit("Error\nBad texture file\n");
	while (swap || !count)
	{
		if (swap)
			free(swap);
		count++;
		swap = get_next_line(fd);
	}
	close(fd);
	//printf("count= %d\n", count);
	ret = ft_calloc(sizeof(char), count);
	fd = open(path, O_RDONLY);
	if (!ret)
		return (0);
	//ret[count] = -1;
	count = 0;
	while (swap || !count)
	{	
		if (swap)
			free(swap);
		swap = get_next_line(fd);
		if (!count)
		{
			free(swap);
			swap = get_next_line(fd);
		}
		//printf("c= %d ", (unsigned char)ft_atoi(swap));
		if (swap)
			ret[count] = (unsigned char)ft_atoi(swap);
		//if (swap)
		//	printf("c= %d ", ret[count]);
		count++;
	}
	printf("texture size = %d\n", count);
	close(fd);
	put_texture_in_struct(type, ret, img);
	return (ret);
}