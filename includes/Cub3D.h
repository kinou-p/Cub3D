/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:30:59 by apommier          #+#    #+#             */
/*   Updated: 2022/05/05 02:58:26 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# define PI 3.1415926535

typedef struct map_information{
	char	**map;
	int		floor;
	int		sky;
	char	*simple_map;
	int		size;
	int		x;
	int		y;
}				map_info;

typedef struct player_position
{
	float x;
	float y;
	float angle;
	float vx;
	float vy;
}				player;

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	char	**double_map;
	map_info map;
	player	player;
}				t_data;

int get_color(char one, char two, char three);
int reset_angle(int angle);
float deg_to_rad(int angle);
void	draw_ray(t_data *img);
void	print_ray(t_data *img);
int		key_press(int code, t_data *img);
int		quit_game(t_data *img);
void	ft_error(char *error_msg);
void	print_player(player player, t_data *img);
void	print_map(map_info map, t_data *img);

#endif