/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:37:02 by apommier          #+#    #+#             */
/*   Updated: 2022/06/15 21:39:46 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int	get_color(char R, char G, char B)
{
	int	color;

	color = 0;
	color = color << 8;
	color += R;
	color = color << 8;
	color += G;
	color = color << 8;
	color += B;
	return (color);
}

void	set_pixel(t_data *img, int color, int x, int y)
{
	int	pixel;

	if (y < 0 || y > 520 || x < 0 || x > 960)
		return ;
	pixel = (y * img->size_line) + (x * 4);
	if (img->endian == 1)
	{
		img->buffer[pixel + 0] = 0;
		img->buffer[pixel + 1] = (color >> 16) & 0xFF;
		img->buffer[pixel + 2] = (color >> 8) & 0xFF;
		img->buffer[pixel + 3] = (color) & 0xFF;
	}
	else if (img->endian == 0)
	{
		img->buffer[pixel + 0] = (color) & 0xFF;
		img->buffer[pixel + 1] = (color >> 8) & 0xFF;
		img->buffer[pixel + 2] = (color >> 16) & 0xFF;
		img->buffer[pixel + 3] = 0;
	}
}

void	get_map_size(char *path, t_data *img, int *count, int fd)
{
	char	*swap;

	swap = 0;
	if (!path)
		ft_exit("Error\nNo path for map\n", img);
	check_dir(path, img);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit("Error\nBad path for map\n", img);
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
}
