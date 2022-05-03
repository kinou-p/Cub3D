/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:30:59 by apommier          #+#    #+#             */
/*   Updated: 2022/05/03 16:48:27 by apommier         ###   ########.fr       */
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

# define PI 3.14159265359

typedef struct map_information{
	char **map;
	int floor;
	int sky;
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
	char	**map;
	player	player;
}				t_data;

void	print_ray(t_data *img);
int		key_press(int code, t_data *img);
int		quit_game(t_data *img);
void	ft_error(char *error_msg);
void	print_player(player player, t_data *img);
void	print_map(char **map, t_data *img);

#endif