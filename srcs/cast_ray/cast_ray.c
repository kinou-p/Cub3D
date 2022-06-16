/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:56:03 by apommier          #+#    #+#             */
/*   Updated: 2022/06/16 16:18:48 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	set_draw_info(t_draw_ray_info *info, t_ray *ray)
{
	info->line_height = 64 * 960 / ray->dist;
	info->line_offset = 256 - ((int)info->line_height) / 2;
	info->x = 0;
	info->y = 0;
	info->mx = ((int)ray->mp) % 64;
	info->my = 0;
	info->gap = (64 / info->line_height);
	info->myy = 0;
	if (info->line_height > 512)
	{
		info->line_offset = 0;
		info->myy = info->gap * ((info->line_height - 512) / 2);
	}
}

void	draw_ray3d(t_data *img, t_ray ray)
{
	t_draw_ray_info	info;

	set_draw_info(&info, &ray);
	while (info.y < info.line_height - 8 && info.y < 512)
	{
		info.myy += info.gap;
		info.my = (int)info.myy;
		ray.pixel = ((info.my) * 64 + info.mx) * 3 + 1;
		info.color = set_color_texture(&ray, img->map.texture);
		if (info.color == -1)
			return ;
		info.x = -1;
		while (++info.x < 4)
			set_pixel(img, info.color, ray.index * 4 + info.x,
				info.y + info.line_offset);
		info.y++;
	}
	info.x++;
}

void	set_dist_ray(t_var_draw_ray *info, t_ray *ray_info, t_data *img)
{
	ray_info->ty = info->ray_y;
	ray_info->pixel = 0;
	ray_info->tx = info->ray_x;
	ray_info->index = info->nb_ray;
	info->dist_f = info->dist_f
		* cos(deg_to_rad(reset_angle(img->player.angle - info->ray_angle)));
	ray_info->dist = info->dist_f;
	if (info->dist_f > 0)
		draw_ray3d(img, *ray_info);
	info->ray_angle = reset_angle(info->ray_angle - 0.25);
}

void	set_ray_info(t_var_draw_ray *info, t_data *img)
{
	t_ray	ray_info;

	ray_info.texture_type = 0;
	if (info->dist_h != -1 && (info->dist_h < info->dist_v
			|| info->dist_v == -1))
	{
		info->dist_f = info->dist_h;
		ray_info.mp = info->ray_x;
		ray_info.texture_type = info->horizontal_type;
	}
	else if (info->dist_v != -1)
	{
		info->dist_f = info->dist_v;
		info->ray_x = info->vx;
		info->ray_y = info->vy;
		ray_info.mp = info->vy;
		ray_info.texture_type = info->vertical_type;
	}
	else
	{
		ray_info.mp = 0;
		info->dist_f = 0;
	}
	set_dist_ray(info, &ray_info, img);
}

void	draw_ray(t_data *img)
{
	t_var_draw_ray	info;

	set_info_draw(&info);
	img->image = mlx_new_image(img->mlx, 960, 512);
	if (!img->image)
		ft_exit("Error\nmlx_new_image failed\n", img);
	img->buffer = mlx_get_data_addr(img->image, &img->bits_per_pixel,
			&img->size_line, &img->endian);
	set_back(img);
	info.count = 0;
	info.ray_angle = reset_angle(img->player.angle + 30);
	while (++info.nb_ray < 240)
	{
		info.count = 0;
		info.dist_v = -1;
		info.dist_h = -1;
		vertical_ray(&info, img);
		horizontal_ray(&info, img);
		set_ray_info(&info, img);
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->image, 0, 0);
	mlx_destroy_image(img->mlx, img->image);
}
