/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:37:02 by apommier          #+#    #+#             */
/*   Updated: 2022/05/03 17:02:42 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int	quit_game(t_data *img)
{
	mlx_destroy_window(img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	if (img->mlx)
		free(img->mlx);
	free_double(img->map);
	exit(0);
}

void	ft_error(char *error_msg)
{
	/*int	i;

	i = 0;*/
	ft_putstr_fd(error_msg, 2);
	exit(1);
}

int	is_good(t_data *img, int type)
{
	printf("touche= %c\n", type);
	printf("vx= %f vy= %f\n", img->player.vx, img->player.vy);
	printf("player:       x= %f y= %f\n", img->player.x, img->player.y);
	if (type == 'w')
	{
		img->player.x += img->player.vx;
		img->player.y += img->player.vy;
	}
	else if (type == 's')
	{
		img->player.x -= img->player.vx;
		img->player.y -= img->player.vy;
	}
	else if (type == 'a')
	{
		img->player.x += img->player.vx * 5;
		//img->player.y -= img->player.vy;
	}
	else if (type == 'd')
	{
		img->player.x -= img->player.vx * 5;
		//img->player.y += img->player.vy;
	}
	else if (type == 65361)//fleche gauche
	{
		img->player.angle -=0.1;
		if (img->player.angle < 0)
			img->player.angle += 2 * PI;
		img->player.vx = cos(img->player.angle) * 5;
		img->player.vy = sin(img->player.angle) * 5;
	}
	else if (type == 65363)//fleche droite
	{
		img->player.angle +=0.1;
		if (img->player.angle > 2 * PI)
			img->player.angle -= 2 * PI;
		img->player.vx = cos(img->player.angle) * 5;
		img->player.vy = sin(img->player.angle) * 5;
	}
	else
		return (0);
	printf("after player: x= %f y= %f\n", img->player.x, img->player.y);
	return (1);
}

int	key_press(int code, t_data *img)
{
	if (code == 65307)
		quit_game(img);
	else
	{
		is_good(img, code);
		//printf("code = %d\n", code);
		//mlx_clear_window(img->mlx, img->mlx_win);
		print_map(img->map, img);
		print_player(img->player, img);
		print_ray(img);
	}
	return (1);
}
