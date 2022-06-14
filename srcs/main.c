/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:42:55 by apommier          #+#    #+#             */
/*   Updated: 2022/06/14 16:25:41 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	set_map(t_data *img)
{
	img->map.texture.north = 0;
	img->map.texture.east = 0;
	img->map.texture.south = 0;
	img->map.texture.west = 0;
}

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

	if (argc != 2)
		ft_error("Error: bad number of arguments, only need a map");
	set_map(&img);
	img.player.x = 0;
	img.player.y = 0;
	if (check_map(argv, &img))
		return (0);
	img.map.texture.basic = get_texture(0, 0, &img);
	img.mlx = mlx_init();
	if (!img.mlx)
		ft_error("Error: mlx_init fail");
	img.mlx_win = mlx_new_window(img.mlx, 960, 512, "Cub3D");
	img.player.vx = sin(deg_to_rad(img.player.angle));
	img.player.vy = cos(deg_to_rad(img.player.angle));
	img.player.front = 0;
	img.player.side = 0;
	img.player.angle_side = 0;
	img.player.shift = 0;
	mlx_hook(img.mlx_win, 2, 1L << 0, key_pressed, &img);
	mlx_hook(img.mlx_win, 3, 1L << 1, key_released, &img);
	mlx_loop_hook(img.mlx, loop, &img);
	mlx_hook(img.mlx_win, 17, 0L, &quit_game, &img);
	
	mlx_loop(img.mlx);
}
