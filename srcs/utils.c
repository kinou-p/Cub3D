/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:37:02 by apommier          #+#    #+#             */
/*   Updated: 2022/06/14 16:27:38 by apommier         ###   ########.fr       */
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
	/*int	i;

	i = 0;*/
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

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

void set_back(t_data *img)
{
	/*for(int y = 0; y < 512; ++y)
	for(int x = 0; x < 960; ++x)
	{
    	int pixel = (y * img->size_line) + (x * 4);

    	if (endian == 1)        // Most significant (Alpha) byte first
    	{
    	    buffer[pixel + 0] = (color >> 24);
    	    buffer[pixel + 1] = (color >> 16) & 0xFF;
    	    buffer[pixel + 2] = (color >> 8) & 0xFF;
    	    buffer[pixel + 3] = (color) & 0xFF;
    	}
    	//else if (endian == 0)   // Least significant (Blue) byte first
    	//{
    	    img->buffer[pixel + 0] = (color) & 0xFF;
    	    img->buffer[pixel + 1] = (color >> 8) & 0xFF;
    	    img->buffer[pixel + 2] = (color >> 16) & 0xFF;
    	    img->buffer[pixel + 3] = (color >> 24);
    	//}
	}*/
	int x = 0;
	//int tmp;
	
	//tmp = (int *)img->buffer;
	img->map.floor.r = 128;
	img->map.floor.g = 128;
	img->map.floor.b = 128;
	img->map.sky.r = 0;
	img->map.sky.g = 191;
	img->map.sky.b = 255;
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
			//tmp = create_trgb(128, 128, 128, 0);
			else
			{
				img->buffer[x + 0] = 128;
    			img->buffer[x + 1] = 128;
    			img->buffer[x + 2] = 128;
    			img->buffer[x + 3] = 0;
			}
		}
		else
		{
			img->buffer[x + 0] = img->map.sky.b;
			img->buffer[x + 1] = img->map.sky.g;
			img->buffer[x + 2] =img->map.sky.r;
			img->buffer[x + 3] = 0;
			//tmp = create_trgb(255, 191, 0, 0);
			/*img->buffer[x + 0] = 255;
    		img->buffer[x + 1] = 191;
    		img->buffer[x + 2] = 0;
    		img->buffer[x + 3] = 0;*/
		}
		x += 4;
	}
}
