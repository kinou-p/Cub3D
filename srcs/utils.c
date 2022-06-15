/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:37:02 by apommier          #+#    #+#             */
/*   Updated: 2022/06/15 12:33:07 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	free_texture(t_data *img)
{
	if (img->map.texture.north)
		free(img->map.texture.north);
	if (img->map.texture.south)
		free(img->map.texture.south);
	if (img->map.texture.east)
		free(img->map.texture.east);
	if (img->map.texture.west)
		free(img->map.texture.west);
	if (img->map.texture.basic)
		free(img->map.texture.basic);
}

int	quit_game(t_data *img)
{
	mlx_destroy_window(img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	if (img->mlx)
		free(img->mlx);
	free_texture(img);
	free(img->map.simple_map);
	//free(img->map.texture.north);
	//free_double(img->map);
	exit(0);
}

double deg_to_rad(double angle)
{
	return (angle * 3.14159265358979323846 / 180.0);
}

double reset_angle(double angle)
{
	if (angle > 359)
		angle -= 360.0;
	if (angle < 0)
		angle += 360.0;
	return (angle);
}

void	ft_error(char *error_msg)
{
	ft_putendl_fd(error_msg, 2);
	exit(1);
}

int	update_pos(t_data *img)
{
	int multiplicator;

	if (img->player.shift == 1)
		multiplicator = 4;
	else 
		multiplicator = 2;
	if (img->player.front == 1)
	{
		img->player.x += img->player.vx * multiplicator;
		img->player.y += img->player.vy * multiplicator;
	}
	else if (img->player.front == -1)
	{
		img->player.x -= img->player.vx * multiplicator;
		img->player.y -= img->player.vy * multiplicator;
	}
	if (img->player.side == 1)
	{
 		img->player.x -= img->player.vy ;
 		img->player.y += img->player.vx ;
	}
	else if (img->player.side == -1)
	{
		img->player.x += img->player.vy; //* 5;
		img->player.y -= img->player.vx; //* 5;
	}
	if (img->player.angle_side == -1)//fleche gauche
	{
		img->player.angle += 1;
		img->player.angle = reset_angle(img->player.angle);
		img->player.vx = cos(deg_to_rad(img->player.angle));
		img->player.vy = -sin(deg_to_rad(img->player.angle));
	}
	else if (img->player.angle_side == 1)//fleche droite
	{
		img->player.angle -= 1;
		img->player.angle = reset_angle(img->player.angle);
		img->player.vx = cos(deg_to_rad(img->player.angle));
		img->player.vy = -sin(deg_to_rad(img->player.angle));
	}
	return (0);
}

void set_back(t_data *img)
{
	int x;

	x = 0;
	while (x < 512 * 960 * 4)
	{
		if (x > 512 * 960 * 2)
		{
			if (img->map.floor.b)
			{
				img->buffer[x + 0] = img->map.floor.b;
				img->buffer[x + 1] = img->map.floor.g;
				img->buffer[x + 2] =img->map.floor.r;
				img->buffer[x + 3] = 0;
			}
		}
		else
		{
			img->buffer[x + 0] = img->map.sky.b;
			img->buffer[x + 1] = img->map.sky.g;
			img->buffer[x + 2] =img->map.sky.r;
			img->buffer[x + 3] = 0;
		}
		x += 4;
	}
}
