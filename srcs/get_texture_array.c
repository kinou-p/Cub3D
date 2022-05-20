/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:10:11 by apommier          #+#    #+#             */
/*   Updated: 2022/05/20 14:11:29 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

unsigned char *get_texture(int type)
{
	int		fd;
	unsigned char		*ret;
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
	printf("count= %d\n", count);
	ret = ft_calloc(sizeof(char), count);
	fd = open("./sprite/brick_wall.ppm", O_RDONLY);
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
	close(fd);
	return (ret);
}