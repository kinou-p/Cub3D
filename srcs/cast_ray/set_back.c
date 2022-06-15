/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:46:05 by apommier          #+#    #+#             */
/*   Updated: 2022/06/15 18:46:55 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	set_back(t_data *img)
{
	int	x;

	x = 0;
	while (x < 512 * 960 * 4)
	{
		if (x > 512 * 960 * 2)
		{
			if (img->map.floor.b)
			{
				img->buffer[x + 0] = img->map.floor.b;
				img->buffer[x + 1] = img->map.floor.g;
				img->buffer[x + 2] = img->map.floor.r;
				img->buffer[x + 3] = 0;
			}
		}
		else
		{
			img->buffer[x + 0] = img->map.sky.b;
			img->buffer[x + 1] = img->map.sky.g;
			img->buffer[x + 2] = img->map.sky.r;
			img->buffer[x + 3] = 0;
		}
		x += 4;
	}
}