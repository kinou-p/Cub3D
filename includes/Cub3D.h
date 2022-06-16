/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:30:59 by apommier          #+#    #+#             */
/*   Updated: 2022/06/16 16:38:18 by apommier         ###   ########.fr       */
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
	void		*image;
	t_map_info	map;
	t_player	player;
	t_to_free	to_be_free;
	int			err;
}				t_data;

typedef struct draw_ray_3D {
	double	line_height;
	double	line_offset;
	int		x;
	double	y;
	int		mx;
	int		my;
	int		color;
	double	gap;
	double	myy;
}				t_draw_ray_info;

typedef struct draw_ray_var {
	double	ray_angle;
	double	ray_y;
	double	ray_x;
	double	next_x;
	double	next_y;
	double	dist_v;
	double	dist_h;
	double	dist_f;
	double	vx;
	double	vy;
	int		count;
	double	tan;
	int		nb_ray;
	int		my;
	int		mx;
	int		mp;
	char	vertical_type;
	char	horizontal_type;
}				t_var_draw_ray;

char			*transform_map(char **double_map, t_data *img);
int				check_texture_color(char **tab, t_data *img);
int				check_map(char **av, t_data *img);
void			ft_exit(char *str, t_data *img);

void			find_angle(char c, t_data *img);
void			size_line(char *str, t_data *img);
void			check_inner(char **map, t_data *img);
void			check_border(char **tab, t_data *img);

void			verify_texture_color(t_data *img);
void			error_msg(t_data *img);
void			inter_map(char **split, char **tmp, t_data *img);
void			check_empty_line(char **split, t_data *img, int *i);
void			check_zero_one(char **split, t_data *img);

char			*charge_new(t_data *img, char **map, char **tmp_map);
char			**isafile(char **av, t_data *img);

void			set_back(t_data *img);
unsigned char	*get_texture(char type, char *path, t_data *img);
int				get_color(char one, char two, char three);
void			set_pixel(t_data *img, int color, int x, int y);
int				set_color_texture(t_ray *ray, t_sprite img);
void			get_file_size(char *path, t_data *img, int *count, int fd);
void			get_map_size(char *path, t_data *img, int *count, int fd);

char			next_space(char *str, int i);
int				next_space_index(char *str, int i);
double			reset_angle(double angle);
double			deg_to_rad(double angle);

void			draw_ray(t_data *img);
void			set_info_draw(t_var_draw_ray *info);
void			print_ray(t_data *img);

void			vertical_ray(t_var_draw_ray *vr, t_data *img);
void			horizontal_ray(t_var_draw_ray *hr, t_data *img);

int				update_pos(t_data *img);
//int				key_press(int code, t_data *img);
int				quit_game(t_data *img);
void			ft_error(char *error_msg);
void			check_dir(char *path, t_data *img);

int				key_pressed(int type, t_data *img);
int				key_released(int type, t_data *img);

#endif
