/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:37:02 by apommier          #+#    #+#             */
/*   Updated: 2022/06/11 20:39:44 by apommier         ###   ########.fr       */
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
	free(img->map.texture.north);
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

/*int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}*/
int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

void set_back(t_data *img)
{
	//int x = 0;
	//int y = 0;
	//int	*buffer;
	//int	color;

	//color = get_color(128, 128, 128);
	//printf("test= %d\n", img->buffer[0]);
	//img->buffer;
	
	
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
			img->buffer[x + 0] = img->map.floor.b;
			img->buffer[x + 1] = img->map.floor.g;
			img->buffer[x + 2] =img->map.floor.r;
			img->buffer[x + 3] = 0;
			//tmp = create_trgb(128, 128, 128, 0);
			img->buffer[x + 0] = 128;
    		img->buffer[x + 1] = 128;
    		img->buffer[x + 2] = 128;
    		img->buffer[x + 3] = 0;
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
	//img->buffer = (char *)tmp;
	/*while (x < 960)
	{
		y = 0;
		while (y < 512)
		{
			mlx_pixel_put(img->mlx, img->mlx_win, x , y, get_color(128, 128, 128));
			//img->buffer[1] = color;
			//mlx_pixel_put(img->mlx, img->mlx_win, x , y - 160, get_color(0, 255, 255));
			y++;
		}
		x++;
	}*/
}

int	key_press(int code, t_data *img)
{
	//printf("touche ");
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
			//set_back(img);
			draw_ray(img);
			//print_ray(img);
		}
	}
	return (1);
}