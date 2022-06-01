/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:42:55 by apommier          #+#    #+#             */
/*   Updated: 2022/06/01 18:04:29 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	print_ray(t_data *img)
{
	int i = -1;
	while (++i < 15)	
	{
		mlx_pixel_put(img->mlx_test, img->mlx_win_test, (img->player.x + (img->player.vx) * i), (img->player.y + (img->player.vy) * i) , 255 << 8);
		mlx_pixel_put(img->mlx_test, img->mlx_win_test, (img->player.x + (img->player.vx) * i) + 1, (img->player.y + (img->player.vy) * i) , 255 << 8);
		mlx_pixel_put(img->mlx_test, img->mlx_win_test, (img->player.x + (img->player.vx) * i), (img->player.y + (img->player.vy) * i) + 1, 255 << 8);
	}
}

map_info	set_map(char **argv)
{
	//char	**map_tab;
	char	*map;
	char	*del;
	char	*swap;
	int		fd;
	map_info ret_map;

	map = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("Error: Open call fail");
	swap = get_next_line(fd);
	while (swap)
	{
		del = map;
		if (swap[ft_strlen(swap) - 1] == '\n')
			swap[ft_strlen(swap) - 1] = 0;
		map = ft_strjoin(map, swap);
		free(swap);
		swap = get_next_line(fd);
		free(del);
	}
	close(fd);
	ret_map.simple_map = map;
	//ret_map.floor = ;
	//ret_map.sky = ;
	ret_map.x = 8;
	ret_map.y = 8;
	ret_map.size = ret_map.x * ret_map.y;
	return (ret_map);
}

void	print_case(char type, t_data *img, int y, int x)
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
			print_case(map.simple_map[i], img, (y * 64), (x * 64));
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
}

void	print_player(player player, t_data *img)
{
	int	*buffer = 0;
	int	img_width;
	int	img_height;
	
	buffer = mlx_xpm_file_to_image(img->mlx_test, "./sprite/player.xpm",
				&img_width, &img_height);
	mlx_put_image_to_window(img->mlx_test, img->mlx_win_test, buffer, player.x - 3.5	, player.y -3.5);
	mlx_destroy_image(img->mlx_test, buffer);
}

int	main(int argc, char **argv)
{
	t_data	img;
	sprite	texture;

	texture.north = get_texture(1);
	//int index= -1;
	/*while (texture.north[++index] != -1)
	{
		printf("element= %d\n", texture.north[index]);
	}
	printf("end element= %d\n", texture.north[index]);*/
	if (argc != 2)
		ft_error("Error: bad number of arguments, only need a map");
	img.mlx = mlx_init();
	
	if (!img.mlx)
		ft_error("Error: mlx_init fail");
	
	img.map = set_map(argv);
	img.mlx_win = mlx_new_window(img.mlx, 960, 512, "Cub3D");
	
	
	//img.mlx_test = mlx_init();
	//img.mlx_win_test = mlx_new_window(img.mlx, 512, 512, "Cub3D_test");


	//img->player.x=150; img->player.y=400; pa=90;
 	//pdx=cos(deg_to_rad(pa)); pdy=-sin(deg_to_rad(pa));
	img.map.texture = texture;
	img.player.x = 150;
	img.player.y = 400;
	img.player.angle = 90;
	img.player.vx = cos(deg_to_rad(img.player.angle));
	img.player.vy = sin(deg_to_rad(img.player.angle));
	//print_map(img.map, &img);
	//print_player(img.player, &img);
	//print_ray(&img);
	mlx_hook(img.mlx_win, 2, 1L << 0, &key_press, &img);
	mlx_hook(img.mlx_win, 17, 0L, &quit_game, &img);
	mlx_loop(img.mlx);
}
