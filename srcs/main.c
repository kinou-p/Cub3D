/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:42:55 by apommier          #+#    #+#             */
/*   Updated: 2022/05/03 17:13:33 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	print_ray(t_data *img)
{
	int i = -1;
	while (++i < 15)	
	{
		mlx_pixel_put(img->mlx, img->mlx_win, (img->player.x + (img->player.vx / 5) * i) + 2, (img->player.y + (img->player.vy / 5) * i) + 2, 255);
	}
}

char	**set_map(char **argv)
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
}

void	print_case(char type, t_data *img, int y, int x)
{
	int	*buffer = 0;
	int	img_width;
	int	img_height;

	if (type == '1')
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/snow_tree.xpm",
				&img_width, &img_height);
	else
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/back.xpm",
				&img_width, &img_height);
	if (!buffer)
		ft_error("no buffer");
	mlx_put_image_to_window(img->mlx, img->mlx_win, buffer, x, y);
	mlx_destroy_image(img->mlx, buffer);
}

void	print_map(char **map, t_data *img)
{
	int	i;
	int	j;
	int	x = 0;
	int	y = 0;

	i = 0;
	j = 0;
	while (map[j])
	{
		x = 0;
		i = 0;
		while (map[j][i])
		{
			print_case(map[j][i], img, (j * 32) + y, (i * 32) + x);
			i++;
			x++;
		}
		j++;
		y++;
	}
}

void	print_player(player player, t_data *img)
{
	int	*buffer = 0;
	int	img_width;
	int	img_height;
	
	buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/player.xpm",
				&img_width, &img_height);
	mlx_put_image_to_window(img->mlx, img->mlx_win, buffer, player.x, player.y);
	mlx_destroy_image(img->mlx, buffer);
}

int	main(int argc, char **argv)
{
	t_data	img;

	if (argc != 2)
		ft_error("Error: bad number of arguments");
	img.mlx = mlx_init();
	if (!img.mlx)
		ft_error("Error: mlx_init fail");
	img.map = set_map(argv);
	img.mlx_win = mlx_new_window(img.mlx, 1024, 512, "Cub3D");
	img.player.x = 250;
	img.player.y = 250;
	img.player.vx = PI / 2;
	img.player.vy = PI / 2;
	img.player.angle = 0;
	print_map(img.map, &img);
	print_player(img.player, &img);
	mlx_hook(img.mlx_win, 2, 1L << 0, &key_press, &img);
	mlx_hook(img.mlx_win, 17, 0L, &quit_game, &img);
	mlx_loop(img.mlx);
}
