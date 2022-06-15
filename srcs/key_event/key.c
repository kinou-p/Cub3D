/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:40:33 by apommier          #+#    #+#             */
/*   Updated: 2022/06/15 18:45:35 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

int	key_pressed(int type, t_data *img)
{
	if (type == 65307)
		quit_game(img);
	if (type == 'w')
		img->player.front = 1;
	else if (type == 's')
		img->player.front = -1;
	else if (type == 'a')
		img->player.side = -1;
	else if (type == 'd')
		img->player.side = 1;
	else if (type == 65361)
		img->player.angle_side = -1;
	else if (type == 65363)
		img->player.angle_side = 1;
	else if (type == 65505)
		img->player.shift = 1;
	return (0);
}

int	key_released(int type, t_data *img)
{
	if (type == 'w')
		img->player.front = 0;
	else if (type == 's')
		img->player.front = 0;
	else if (type == 'a')
		img->player.side = 0;
	else if (type == 'd')
		img->player.side = 0;
	else if (type == 65361)
		img->player.angle_side = 0;
	else if (type == 65363)
		img->player.angle_side = 0;
	else if (type == 65505)
		img->player.shift = 0;
	return (0);
}

void	update_side(t_data *img)
{
	if (img->player.side == 1)
	{
		img->player.x -= img->player.vy;
		img->player.y += img->player.vx;
	}
	else if (img->player.side == -1)
	{
		img->player.x += img->player.vy;
		img->player.y -= img->player.vx;
	}	
}

void	update_angle_side(t_data *img)
{
	if (img->player.angle_side == -1)
	{
		img->player.angle += 1;
		img->player.angle = reset_angle(img->player.angle);
		img->player.vx = cos(deg_to_rad(img->player.angle));
		img->player.vy = -sin(deg_to_rad(img->player.angle));
	}
	else if (img->player.angle_side == 1)
	{
		img->player.angle -= 1;
		img->player.angle = reset_angle(img->player.angle);
		img->player.vx = cos(deg_to_rad(img->player.angle));
		img->player.vy = -sin(deg_to_rad(img->player.angle));
	}
}

int	update_pos(t_data *img)
{
	int	multiplicator;

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
	update_angle_side(img);
	update_side(img);
	return (0);
}