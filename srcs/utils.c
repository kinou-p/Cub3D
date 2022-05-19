/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:37:02 by apommier          #+#    #+#             */
/*   Updated: 2022/05/19 15:32:21 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	quit_game(t_data *img)
{
	mlx_destroy_window(img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	if (img->mlx)
		free(img->mlx);
	free(img->map.simple_map);
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
	/*int	i;

	i = 0;*/
	ft_putendl_fd(error_msg, 2);
	exit(1);
}

int	is_good(t_data *img, int type)
{
	//printf("touche= %c\n", type);
	//printf("vx= %d vy= %d\n", img->player.vx, img->player.vy);
	//printf("player:       x= %d y= %d\n", img->player.x, img->player.y);

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
	//printf("after player: x= %d y= %d\n", img->player.x, img->player.y);
	return (1);
}

void print_back(t_data *img)
{
	int x = 0;
	int y = 0;

	while (x < 1024)
	{
		y = 0;
		while (y < 512)
		{
			mlx_pixel_put(img->mlx, img->mlx_win, x , y, get_color(128, 128, 128));
			//mlx_pixel_put(img->mlx, img->mlx_win, x , y - 160, get_color(0, 255, 255));
			y++;
		}
		x++;
	}
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
			//print_map(img->map, img);
			//print_player(img->player, img);
			print_back(img);
			draw_ray(img);
			//print_ray(img);
		}
	}



	// int y = 0;
	// int x = 0;
	// int	pixel = 0;
	// int color;
	//printf("pixel=%d   ", ray.pixel);
	/*while (x < 16)
	{
		y = 0;
		while (y < 16)
		{
			//printf("test\n");
			pixel = (x * 16 + y)* 3 + 1;
			color = get_color(img->map.texture.north[pixel], img->map.texture.north[pixel + 1], img->map.texture.north[pixel + 2]);
			mlx_pixel_put(img->mlx, img->mlx_win, x, y, color);
			y++;	
		}
		x++;
	}*/





	
	return (1);
}
