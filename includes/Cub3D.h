/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:30:59 by apommier          #+#    #+#             */
/*   Updated: 2022/06/13 23:22:21 by apommier         ###   ########.fr       */
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

typedef struct s_root {
	int size;
	int height;
	int error;
}				t_root;

typedef struct ray_info{
	double	ty;
	double	tx;
	double	mp;
	double	dist;
	int 	index;
	int		wall_type;
	int		pixel;
	char	texture_type;
	
}				ray;

typedef struct all_wall_texture{
	unsigned char	*north;
	unsigned char	*east;
	unsigned char	*west;
	unsigned char	*south;
	unsigned char	*basic;
}				sprite;

typedef struct s_color{
	//unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				color;

typedef struct map_information{
	char	**map;
	sprite	texture;
	color	floor;
	color	sky;
	char	*simple_map;
	int		size;
	int		x;
	int		y;
	int		max;
	int		error;
}				map_info;

typedef struct player_position
{
	double x;
	double y;
	double angle;
	double vx;
	double vy;
	int		front;
	int		side;
	int		angle_side;
}				player;

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	void	*mlx_test;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*buffer;
	void	*mlx_win_test;
	char	**double_map;
	map_info map;
	player	player;
}				t_data;

char			*transform_map(char **double_map, t_data *img);
int				check_texture_color(char **tab, t_data *img);
int				check_map(char **av, t_data *img);
void			ft_exit(char *str);
void			set_back(t_data *img);
unsigned char	*get_texture(char type, char *path, t_data *img);
int				get_color(char one, char two, char three);
double			reset_angle(double angle);
double			deg_to_rad(double angle);
void			draw_ray(t_data *img);
void			print_ray(t_data *img);
int				key_press(int code, t_data *img);
int				quit_game(t_data *img);
void			ft_error(char *error_msg);
void			print_player(player player, t_data *img);
void			print_map(map_info map, t_data *img);

#endif