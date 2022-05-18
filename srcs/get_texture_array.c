/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:10:11 by apommier          #+#    #+#             */
/*   Updated: 2022/05/17 23:49:38 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int *get_texture(int type)
{
	int		fd;
	int		*ret;
	//int		start = 1;
	int		count;
	int		len;
	char	*swap = 0;

	//line = 0;
	count = 0;
	fd = open("./sprite/brick_wall.ppm", O_RDONLY);
	while (swap || !count)
	{
		if (swap)
			free(swap);
		count++;
		swap = get_next_line(fd);
	}
	close(fd);
	ret = ft_calloc(sizeof(int), count + 1);
	//char **ret2 = ft_calloc(sizeof(ret), count + 1);
	fd = open("./sprite/brick_wall.ppm", O_RDONLY);
	if (!ret)
		return (0);
	ret[count] = -1;
	len = count;
	count = 0;
	while (swap || !count)
	{	
		if (swap)
			free(swap);
		swap = get_next_line(fd);
		//printf("swap= %s\n", swap);
		ret[count] = (int)ft_atoi(swap);
		count++;
		
	}
	int k = 0;
	/*while (len)
	{
		printf("nbr= %d", ret[len--]);
	}*/
	printf("nrb3= %d\n", ret[1]);
	//print_double_fd(ret2, 1);
	//free_double(ret2);
	close(fd);


	/*int v = 0;
	int b = 0;
	int	pixel = 0;
	//printf("pixel=%d   ", ray.pixel);
	while (v < 16)
	{
		while (b < 16)
		{
			pixel = (v * 3) + b;
			int color = get_color(ret[pixel], ret[pixel + 1], ret[pixel + 2]);
			mlx_pixel_put(img->mlx, img->mlx_win, v, b, color);
			b++;	
		}
		v++;
	}*/





	
	return (ret);
}