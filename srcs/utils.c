/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:37:02 by apommier          #+#    #+#             */
/*   Updated: 2022/05/04 18:07:18 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	quit_game(t_data *img)
{
	mlx_destroy_window(img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	if (img->mlx)
		free(img->mlx);
	//free_double(img->map);
	exit(0);
}

float deg_to_rad(int angle)
{
	return (angle * M_PI / 180.0);
}

int reset_angle(int angle)
{
	if (angle > 359)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return (angle);
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
	//printf("touche= %c\n", type);
	//printf("vx= %f vy= %f\n", img->player.vx, img->player.vy);
	//printf("player:       x= %f y= %f\n", img->player.x, img->player.y);

//
 /*if(key=='a'){ pa+=5; pa=FixAng(pa); pdx=cos(deg_to_rad(pa)); pdy=-sin(deg_to_rad(pa));} 	
 if(key=='d'){ pa-=5; pa=FixAng(pa); pdx=cos(deg_to_rad(pa)); pdy=-sin(deg_to_rad(pa));} 
 if(key=='w'){ img->player.x+=pdx*5; img->player.y+=pdy*5;}
 if(key=='s'){ img->player.x-=pdx*5; img->player.y-=pdy*5;}*/
//	
	if (type == 'w')
	{
		img->player.x += img->player.vx * 5;
		img->player.y += img->player.vy * 5;
	}
	else if (type == 's')
	{
		img->player.x -= img->player.vx * 5;
		img->player.y -= img->player.vy * 5;
	}
	else if (type == 'a')
	{
		img->player.x += img->player.vy * 5;
		img->player.y -= img->player.vx * 5;
	}
	else if (type == 'd')
	{
		img->player.x -= img->player.vy * 5;
		img->player.y += img->player.vx * 5;
	}
	else if (type == 65361)//fleche gauche
	{
		img->player.angle += 5;
		img->player.angle = reset_angle(img->player.angle);
		img->player.vx = cos(deg_to_rad(img->player.angle));
		img->player.vy = -sin(deg_to_rad(img->player.angle));
	}
	else if (type == 65363)//fleche droite
	{
		img->player.angle -= 5;
		img->player.angle = reset_angle(img->player.angle);
		img->player.vx = cos(deg_to_rad(img->player.angle));
		img->player.vy = -sin(deg_to_rad(img->player.angle));
	}
	else
		return (0);
	//printf("after player: x= %f y= %f\n", img->player.x, img->player.y);
	return (1);
}

int	key_press(int code, t_data *img)
{
	if (code == 65307)
		quit_game(img);
	else
	{
		if (is_good(img, code))
		{
			//printf("code = %d\n", code);
			//mlx_clear_window(img->mlx, img->mlx_win);
			print_map(img->map, img);
			print_player(img->player, img);
			print_ray(img);
			draw_ray(img);
		}
	}
	return (1);
}
