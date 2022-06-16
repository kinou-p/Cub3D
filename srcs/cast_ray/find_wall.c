/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:15:16 by apommier          #+#    #+#             */
/*   Updated: 2022/06/16 16:21:20 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	find_horizontal_wall(t_var_draw_ray *info, t_data *img)
{
	while (info->count < img->map.max)
	{
		info->mx = (int)(info->ray_x) >> 6;
		info->my = (int)(info->ray_y) >> 6;
		info->mp = info->my * img->map.x + info->mx;
		if (info->mp > 0 && info->mp < img->map.size
			&& img->map.simple_map[info->mp] == '1')
		{
			info->count = img->map.max;
			info->dist_h = cos(deg_to_rad(info->ray_angle))
				* (info->ray_x - img->player.x)
				- sin(deg_to_rad(info->ray_angle))
				* (info->ray_y - img->player.y);
		}	
		else
		{
			info->ray_x += info->next_x;
			info->ray_y += info->next_y;
			info->count += 1;
		}
	}
}

void	horizontal_ray(t_var_draw_ray *hr, t_data *img)
{
	hr->count = 0;
	hr->tan = 1.0 / hr->tan;
	if (sin(deg_to_rad(hr->ray_angle)) > 0.001)
	{
		hr->ray_y = (((int)img->player.y >> 6) << 6) - 0.0001;
		hr->ray_x = (img->player.y - hr->ray_y) * hr->tan + img->player.x;
		hr->next_y = -64;
		hr->next_x = -hr->next_y * hr->tan;
		hr->horizontal_type = 'N';
	}
	else if (sin(deg_to_rad(hr->ray_angle)) < -0.001)
	{
		hr->ray_y = (((int)img->player.y >> 6) << 6) + 64;
		hr->ray_x = (img->player.y - hr->ray_y) * hr->tan + img->player.x;
		hr->next_y = 64;
		hr->next_x = -hr->next_y * hr->tan;
		hr->horizontal_type = 'S';
	}
	else
	{
		hr->ray_x = img->player.x;
		hr->ray_y = img->player.y;
		hr->count = img->map.max;
	}
	find_horizontal_wall(hr, img);
}

void	find_vertical_wall(t_var_draw_ray *info, t_data *img)
{
	while (info->count < img->map.max)
	{
		info->mx = (int)(info->ray_x) >> 6;
		info->my = (int)(info->ray_y) >> 6;
		info->mp = info->my * img->map.x + info->mx;
		if (info->mp > 0 && info->mp < img->map.size
			&& img->map.simple_map[info->mp] == '1')
		{
			info->count = img->map.max;
			info->dist_v = cos(deg_to_rad(info->ray_angle))
				* (info->ray_x - img->player.x)
				- sin(deg_to_rad(info->ray_angle))
				* (info->ray_y - img->player.y);
		}
		else
		{
			info->ray_x += info->next_x;
			info->ray_y += info->next_y;
			info->count += 1;
		}
	}
	info->vx = info->ray_x;
	info->vy = info->ray_y;
}

void	vertical_ray(t_var_draw_ray *vr, t_data *img)
{
	vr->tan = tan(deg_to_rad(vr->ray_angle));
	if (cos(deg_to_rad(vr->ray_angle)) > 0.001)
	{
		vr->ray_x = (((int)img->player.x >> 6) << 6) + 64;
		vr->ray_y = (img->player.x - vr->ray_x) * vr->tan + img->player.y;
		vr->next_x = 64;
		vr->next_y = -vr->next_x * vr->tan;
		vr->vertical_type = 'E';
	}
	else if (cos(deg_to_rad(vr->ray_angle)) < -0.001)
	{
		vr->ray_x = (((int)img->player.x >> 6) << 6) - 0.0001;
		vr->ray_y = (img->player.x - vr->ray_x) * vr->tan + img->player.y;
		vr->next_x = -64;
		vr->next_y = -vr->next_x * vr->tan;
		vr->vertical_type = 'W';
	}
	else
	{
		vr->ray_x = img->player.x;
		vr->ray_y = img->player.y;
		vr->count = img->map.max;
	}
	find_vertical_wall(vr, img);
}

void	set_info_draw(t_var_draw_ray *info)
{
	info->ray_angle = 0;
	info->ray_y = 0;
	info->ray_x = 0;
	info->next_x = 0;
	info->next_y = 0;
	info->dist_v = 0;
	info->dist_h = 0;
	info->dist_f = 0;
	info->vx = 0;
	info->vy = 0;
	info->count = 0;
	info->tan = 0;
	info->nb_ray = -1;
	info->my = 0;
	info->mx = 0;
	info->mp = 0;
	info->vertical_type = 0;
	info->horizontal_type = 0;
}
