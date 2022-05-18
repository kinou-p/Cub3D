/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:42:55 by apommier          #+#    #+#             */
/*   Updated: 2022/05/17 23:52:27 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	print_ray(t_data *img)
{
	int i = -1;
	while (++i < 15)	
	{
		mlx_pixel_put(img->mlx, img->mlx_win, (img->player.x + (img->player.vx) * i), (img->player.y + (img->player.vy) * i) , 255 << 8);
		mlx_pixel_put(img->mlx, img->mlx_win, (img->player.x + (img->player.vx) * i) + 1, (img->player.y + (img->player.vy) * i) , 255 << 8);
		mlx_pixel_put(img->mlx, img->mlx_win, (img->player.x + (img->player.vx) * i), (img->player.y + (img->player.vy) * i) + 1, 255 << 8);
	}
}

/*map_info	set_map(char **argv)  //simple local allocation
{
	map_info	map;
	char		ret_map[]=
	{
		'1','1','1','1','1','1','1','1',
		'1','0','1','0','0','0','0','1',
		'1','0','1','0','0','0','0','1',
		'1','0','0','0','0','0','0','1',
		'1','0','0','0','0','0','0','1',
		'1','0','1','0','0','1','0','1',
		'1','0','0','0','0','1','0','1',
		'1','1','1','1','1','1','1','1',
	};
	map.simple_map = ret_map;
	map.x = 8;
	map.y = 8;
	map.size = map.x * map.y;
	return (map);
}*/

/*map_info	set_map(char **argv)
{
	char	**map_tab;
	char	*map;
	char	*del;
	char	*swap;
	int		fd;

	map = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("Error: Open call fail");
	swap = get_next_line(fd);
	while (swap)
	{
		del = map;
		map = ft_strjoin(map, swap);
		free(swap);
		swap = get_next_line(fd);
		free(del);
	}
	close(fd);
	map_tab = ft_split(map, '\n');
	free(map);
	if (!map_tab)
		ft_error("Error: Map file is empty");
	return (map_tab);
}*/

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
	ret_map.x = 8;
	ret_map.y = 8;
	ret_map.size = ret_map.x * ret_map.y;
	//map_tab = ft_split(map, '\n');
	//free(map);
	//if (!map_tab)
	//	ft_error("Error: Map file is empty");
	return (ret_map);
}

void	print_case(char type, t_data *img, int y, int x)
{
	int	*buffer = 0;
	int	img_width;
	int	img_height;

	//printf("type= %c\n", type);
	if (type == '1')
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/wall.xpm",
				&img_width, &img_height);
	else if (type == '0')
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/back.xpm",
				&img_width, &img_height);
	if (!buffer)
		ft_error("no buffer");
	mlx_put_image_to_window(img->mlx, img->mlx_win, buffer, x, y);
	mlx_destroy_image(img->mlx, buffer);
}

void	print_map(map_info map, t_data *img)
{
	int	i = 0;
	int	j;
	int	x = 0;
	int	y = 0;

	//printf("map= -%s-\n", map.simple_map);
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

	/*i = 0;
	j = 0;
	while (map[j])
	{
		x = 0;
		i = 0;
		while (map[j][i])
		{
			print_case(map[j][i], img, (j * 64), (i * 64));
			i++;
			x++;
		}
		j++;
		y++;
	}*/
}

void	print_line(t_data *img, float x, float y)
{
	float i = -1;
	int j = -1;
	while (++i < x && ++j < y)
		mlx_pixel_put(img->mlx, img->mlx_win, (img->player.x + (img->player.vx / 5) * i) + 2, (img->player.y + (img->player.vy / 5) * i) + 2, 65);
}

void	print_player(player player, t_data *img)
{
	int	*buffer = 0;
	int	img_width;
	int	img_height;
	
	buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/player.xpm",
				&img_width, &img_height);
	mlx_put_image_to_window(img->mlx, img->mlx_win, buffer, player.x - 3.5	, player.y -3.5);
	mlx_destroy_image(img->mlx, buffer);
}

int	main(int argc, char **argv)
{
	t_data	img;
	sprite	texture;

	texture.north = get_texture(1);
	if (argc != 2)
		ft_error("Error: bad number of arguments, only need a map");
	img.mlx = mlx_init();
	if (!img.mlx)
		ft_error("Error: mlx_init fail");
	
	img.map = set_map(argv);
	img.mlx_win = mlx_new_window(img.mlx, 1024, 512, "Cub3D");
	//img->player.x=150; img->player.y=400; pa=90;
 	//pdx=cos(deg_to_rad(pa)); pdy=-sin(deg_to_rad(pa));
	img.map.texture = texture;
	img.player.x = 150;
	img.player.y = 400;
	img.player.angle = 90;
	img.player.vx = cos(deg_to_rad(img.player.angle));
	img.player.vy = sin(deg_to_rad(img.player.angle));
	print_map(img.map, &img);
	print_player(img.player, &img);





	
	//print_ray(&img);
	mlx_hook(img.mlx_win, 2, 1L << 0, &key_press, &img);
	mlx_hook(img.mlx_win, 17, 0L, &quit_game, &img);
	mlx_loop(img.mlx);
}
