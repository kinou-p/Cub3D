/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:42:55 by apommier          #+#    #+#             */
/*   Updated: 2022/06/14 15:59:20 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

/*void	print_ray(t_data *img)
{
	int i = -1;
	while (++i < 15)	
	{
		mlx_pixel_put(img->mlx_test, img->mlx_win_test, (img->player.x + (img->player.vx) * i), (img->player.y + (img->player.vy) * i) , 255 << 8);
		mlx_pixel_put(img->mlx_test, img->mlx_win_test, (img->player.x + (img->player.vx) * i) + 1, (img->player.y + (img->player.vy) * i) , 255 << 8);
		mlx_pixel_put(img->mlx_test, img->mlx_win_test, (img->player.x + (img->player.vx) * i), (img->player.y + (img->player.vy) * i) + 1, 255 << 8);
	}
}*/

void	set_map(t_data *img)
{
	img->map.texture.north = 0;
	img->map.texture.east = 0;
	img->map.texture.south = 0;
	img->map.texture.west = 0;
}

/*void	print_case(char type, t_data *img, int y, int x)
{
	int	*buffer = 0;
	int	img_width;
	int	img_height;

	//printf("type= %c\n", type);
	if (type == '1')
		buffer = mlx_xpm_file_to_image(img->mlx_test, "./sprite/wall.xpm",
				&img_width, &img_height);
	else if (type == '0')
		buffer = mlx_xpm_file_to_image(img->mlx_test, "./sprite/back.xpm",
				&img_width, &img_height);
	if (!buffer)
		ft_error("no buffer");
	mlx_put_image_to_window(img->mlx_test, img->mlx_win_test, buffer, x, y);
	mlx_destroy_image(img->mlx_test, buffer);
}

void	print_map(map_info map, t_data *img)
{
	int	i = 0;
	int	j;
	int	x = 0;
	int	y = 0;

	while (i < map.size)
	{
		j = -1;
		x = 0;
		while (++j < 8)
		{
			print_case(map.[i], img, (y * 64), (x * 64));
			i++;
			x++;
		}
		y++;
	}
}

void	print_line(t_data *img, double x, double y)
{
	double i = -1;
	int j = -1;
	while (++i < x && ++j < y)
		mlx_pixel_put(img->mlx_test, img->mlx_win_test, (img->player.x + (img->player.vx / 5) * i) + 2, (img->player.y + (img->player.vy / 5) * i) + 2, 65);
}*/

/*void	print_player(player player, t_data *img)
{
	int	*buffer = 0;
	int	img_width;
	int	img_height;
	
	buffer = mlx_xpm_file_to_image(img->mlx_test, "./sprite/player.xpm",
				&img_width, &img_height);
	mlx_put_image_to_window(img->mlx_test, img->mlx_win_test, buffer, player.x - 3.5	, player.y -3.5);
	mlx_destroy_image(img->mlx_test, buffer);
}*/

int	key_pressed(int type, t_data *img)
{
	if (code == 65307)
		quit_game(img);
	if (type == 'w')
		img->player.front = 1;
	else if (type == 's')
		img->player.front = -1;
	else if (type == 'a')
		img->player.side = -1;
	else if (type == 'd')
		img->player.side = 1;
	else if (type == 65361)//fleche gauche
		img->player.angle_side = -1;
	else if (type == 65363)//fleche droite
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
	else if (type == 65361)//fleche gauche
		img->player.angle_side = 0;
	else if (type == 65363)//fleche droite
		img->player.angle_side = 0;
	else if (type == 65505)
		img->player.shift = 0;
	return (0);
}

int	loop(t_data *img)
{
	update_pos(img);
	draw_ray(img);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	img;
	//sprite	texture;

	//texture.north = get_texture(1, 0, img);
	//int index= -1;
	/*while (texture.north[++index] != -1)
	{
		printf("element= %d\n", texture.north[index]);
	}
	printf("end element= %d\n", texture.north[index]);*/
	if (argc != 2)
		ft_error("Error: bad number of arguments, only need a map");
	set_map(&img);
	img.player.x = 0;
	img.player.y = 0;
	if (check_map(argv, &img))
		return (0);
	img.map.texture.basic = get_texture(0, 0, &img);
	printf("size= %d\n", img.map.size);
	img.mlx = mlx_init();
	if (!img.mlx)
		ft_error("Error: mlx_init fail");
	img.mlx_win = mlx_new_window(img.mlx, 960, 512, "Cub3D");
	//img.player.x = 64 * 3 + 32;
	//img.player.y = 64 + 32;
	//img.player.angle = 90;
	img.player.vx = cos(deg_to_rad(img.player.angle));
	img.player.vy = sin(deg_to_rad(img.player.angle));
	img.player.front = 0;
	img.player.side = 0;
	img.player.angle_side = 0;
	img.player.shift = 0;
	
	//print_map(img.map, &img);
	//print_player(img.player, &img);
	//print_ray(&img);


	mlx_hook(img.mlx_win, 2, 1L << 0, key_pressed, &img);
	mlx_hook(img.mlx_win, 3, 1L << 1, key_released, &img);
	mlx_loop_hook(img.mlx, loop, &img);
	mlx_hook(img.mlx_win, 17, 0L, &quit_game, &img);
	
	mlx_loop(img.mlx);
}
