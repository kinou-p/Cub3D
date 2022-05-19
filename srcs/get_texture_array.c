/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:10:11 by apommier          #+#    #+#             */
/*   Updated: 2022/05/19 19:11:07 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int *get_texture(int type)
{
	int		fd;
	int		*ret;
	int		count;
	char	*swap = 0;

	(void)type;
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
	fd = open("./sprite/brick_wall.ppm", O_RDONLY);
	if (!ret)
		return (0);
	ret[count] = -1;
	count = 0;
	while (swap || !count)
	{	
		if (swap)
			free(swap);
		swap = get_next_line(fd);
		ret[count] = (int)ft_atoi(swap);
		count++;
		
	}
	close(fd);
	return (ret);
}