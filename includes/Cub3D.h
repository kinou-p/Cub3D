/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:30:59 by apommier          #+#    #+#             */
/*   Updated: 2022/06/15 18:42:10 by apommier         ###   ########.fr       */
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
	int	size;
	int	height;
	int	error;
}				t_root;

typedef struct ray_info{
	double	ty;
	double	tx;
	double	mp;
	double	dist;
	int		index;
	int		wall_type;
	int		pixel;
	char	texture_type;

}				t_ray;

typedef struct all_wall_texture{
	unsigned char	*north;
	unsigned char	*east;
	unsigned char	*west;
	unsigned char	*south;
}				t_sprite;

typedef struct s_color{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				set;
}				t_color;

typedef struct map_information{
	char		**map;
	t_sprite	texture;
	t_color		floor;
	t_color		sky;
	char		*simple_map;
	int			size;
	int			x;
	int			y;
	int			max;
	int			error;
}				t_map_info;

typedef struct player_position
{
	double	x;
	double	y;
	double	angle;
	double	vx;
	double	vy;
	int		front;
	int		side;
	int		angle_side;
	int		shift;
}				t_player;

typedef struct need_to_be_free
{
	char			**tab;
	char			**tab_two;
	unsigned char	*str;
	char			*string;
	int				fd;
}				t_to_free;

typedef struct s_data {
	void		*mlx;
	void		*mlx_win;
	void		*mlx_test;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*buffer;
	void		*mlx_win_test;
	char		**double_map;
	t_map_info	map;
	t_player	player;
	t_to_free	to_be_free;
	int			err;
}				t_data;

int				update_pos(t_data *img);
char			*transform_map(char **double_map, t_data *img);
int				check_texture_color(char **tab, t_data *img);
int				check_map(char **av, t_data *img);
void			ft_exit(char *str, t_data *img);
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
void			print_player(t_player player, t_data *img);
void			print_map(t_map_info map, t_data *img);
void			check_dir(char *path, t_data *img);

int				key_pressed(int type, t_data *img);
int				key_released(int type, t_data *img);

#endif
