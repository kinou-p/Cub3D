/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:55:39 by apommier          #+#    #+#             */
/*   Updated: 2022/06/16 14:28:47 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int	set_color_texture(t_ray *ray, t_sprite img)
{
	int	color;

	color = 0;
	if (ray->pixel >= 12290 || ray->pixel < 0)
		return (-1);
	else if (ray->pixel > 0)
	{
		if (ray->texture_type == 'N' && img.north)
			color = get_color(img.north[ray->pixel],
					img.north[ray->pixel + 1], img.north[ray->pixel + 2]);
		else if (ray->texture_type == 'S' && img.south)
			color = get_color(img.south[ray->pixel],
					img.south[ray->pixel + 1], img.south[ray->pixel + 2]);
		else if (ray->texture_type == 'W' && img.west)
			color = get_color(img.west[ray->pixel],
					img.west[ray->pixel + 1], img.west[ray->pixel + 2]);
		else if (ray->texture_type == 'E' && img.east)
			color = get_color(img.east[ray->pixel],
					img.east[ray->pixel + 1], img.east[ray->pixel + 2]);
	}
	return (color);
}
