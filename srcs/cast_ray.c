/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cast_ray.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: apommier <apommier@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/05/04 18:08:14 by apommier		  #+#	#+#			 */
/*   Updated: 2022/05/20 15:48:23 by apommier		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	print_ray2(t_data *img, double vx, double vy, double dist)
{
	int i = -1;
	int red = 0;

	red = red << 8;
	red +=255;
	red = red << 8;
	red = red << 8;
	while (++i < dist)
	{
		mlx_pixel_put(img->mlx_test, img->mlx_win_test, (img->player.x + (vx) * i) , (img->player.y + (vy) * i) , red);
		mlx_pixel_put(img->mlx_test, img->mlx_win_test, (img->player.x + (vx) * i) + 1, (img->player.y + (vy) * i) , red);
		mlx_pixel_put(img->mlx_test, img->mlx_win_test, (img->player.x + (vx) * i) , (img->player.y + (vy) * i) + 1, red);
	}
}

int get_color(char R, char G, char B)
{
	int color = 0;

	//printf("R= %d G= %d B= %d\n", R, G, B);
	color = color << 8;
	color += R;
	//printf("color= %d\n", color);
	color = color << 8;
	color += G;
	//printf("color= %d\n", color);
	color = color << 8;
	color += B;
	//printf("color= %d\n", color);
	return (color);
}

int get_red()
{
	int red = 0;

	red = red << 8;
	red +=255;
	red = red << 8;
	red = red << 8;
	return (red);
}

int get_dark_red()
{
	int red = 0;

	red = red << 8;
	red +=139;
	red = red << 8;
	red = red << 8;
	return (red);
}

void	set_pixel(t_data *img, int color, int x, int y)
{
	int pixel;

	if (y < 0 || y > 520 || x < 0 || x > 960)
		return ;
	pixel = (y * img->size_line) + (x * 4);
	if (img->endian == 1)		// Most significant (Alpha) byte first
	{
		img->buffer[pixel + 0] = 0;
		img->buffer[pixel + 1] = (color >> 16) & 0xFF;
		img->buffer[pixel + 2] = (color >> 8) & 0xFF;
		img->buffer[pixel + 3] = (color) & 0xFF;
	}
	else if (img->endian == 0)   // Least significant (Blue) byte first
	{
		img->buffer[pixel + 0] = (color) & 0xFF;
		img->buffer[pixel + 1] = (color >> 8) & 0xFF;
		img->buffer[pixel + 2] = (color >> 16) & 0xFF;
		img->buffer[pixel + 3] = 0;
	}
}

void	draw_ray3d(t_data *img, t_ray ray)
{
	double	line_height;
	double	line_offset;
	int		x = 0;
	double	y = 0;
	int		mx = 0;
	int		my = 0;
	int 	color;
	int		texture_size = 64;

	line_height = /*img->map.size*/64 * 960 / ray.dist;
	line_offset = 256 - ((int)line_height) / 2;
	double	gap = 1;
	double myy = 0;
		y = 0;
		my = 0;
		myy = 0;
		gap = (texture_size / line_height);
		mx = ((int)ray.mp) % texture_size;
		if (line_height > 512)
		{
			line_offset = 0;
			myy = gap * ((line_height - 512) / 2);
		}
		while (y < line_height - 8 && y < 512)
		{
			myy += gap;
			my = (int)myy;//gap;
			ray.pixel = ((my) * 64 + mx)* 3 + 1;
			x = -1;
			if (ray.pixel >= 12290 || ray.pixel < 0)//here read
				return ;
			else if (ray.pixel > 0)
			{
				if (ray.texture_type == 'N' && img->map.texture.north)
					color = get_color(img->map.texture.north[ray.pixel], img->map.texture.north[ray.pixel + 1], img->map.texture.north[ray.pixel + 2]);
				else if (ray.texture_type == 'S' && img->map.texture.south)
					color = get_color(img->map.texture.south[ray.pixel], img->map.texture.south[ray.pixel + 1], img->map.texture.south[ray.pixel + 2]);
				else if (ray.texture_type == 'W' && img->map.texture.west)
					color = get_color(img->map.texture.west[ray.pixel], img->map.texture.west[ray.pixel + 1], img->map.texture.west[ray.pixel + 2]);
				else if (ray.texture_type == 'E' && img->map.texture.east)
					color = get_color(img->map.texture.east[ray.pixel], img->map.texture.east[ray.pixel + 1], img->map.texture.east[ray.pixel + 2]);
			}
			else
				color = 0;
			while (++x < /*img->map.x / 2*/4)
			{
					set_pixel(img, color, ray.index * /*(img->map.x / 2)*/4 + x, y + line_offset);
			}
			y++;
		}
		x++;
}

void	draw_ray(t_data *img)
{
	double	ray_angle = 0; //ray angle
	double	ray_y = 0; //where ray touch x
	double	ray_x = 0; //where ray touch y
	double	next_x = 0;
	double	next_y = 0;
	double	dist_v;
	double	dist_h;
	double	dist_f;
	double	vx = 0;
	double	vy = 0;
	int		count = 0;
	double	aTan = 0;
	int		nb_ray = -1;
	int		my = 0;
	int		mx = 0;
	int		mp = 0;
	char	vertical_type;
	char	horizontal_type;
	//char texture_type;

	void *new_img;
	int bits_per_pixel = 0;
	int size_line = 0;
	int endian = 0;

	new_img = mlx_new_image(img->mlx, 960, 512);
	if (!new_img)
		ft_exit("Error\nmlx_new_image failed\n", img);
	//printf("newimg= %p\n", new_img);
	img->buffer = mlx_get_data_addr(new_img, &bits_per_pixel, &size_line, &endian);
	//img->buffer// = (char*)new_img;
	//printf("buffer= %p\n", img->buffer);
	//printf("buffer in string= %s\n", (char *)img->buffer);
	//printf("bits= %d line_size= %d endian = %d\n", bits_per_pixel, size_line, endian);
	//mlx_destroy_image(img->mlx, new_img);
	img->bits_per_pixel = bits_per_pixel;
	img->size_line = size_line;
	img->endian = endian;
	set_back(img);
	
	
	(void)dist_f;
	count = 0;
	ray_angle = reset_angle(img->player.angle + 30);
	while (++nb_ray < 240)
	{
		count = 0;
		dist_v = -1;
		dist_h = -1;
		//----------start vertical ray----------
		aTan = tan(deg_to_rad(ray_angle));
		if (cos(deg_to_rad(ray_angle)) > 0.001)//looking left
		{
			ray_x = (((int)img->player.x>>6)<<6) + 64;
			ray_y = (img->player.x - ray_x) * aTan + img->player.y;
			next_x = 64;
			next_y = -next_x * aTan;
			vertical_type = 'E';
		}
		else if (cos(deg_to_rad(ray_angle)) < -0.001)//looking right
		{
			ray_x = (((int)img->player.x>>6)<<6) - 0.0001;
			ray_y = (img->player.x - ray_x) * aTan + img->player.y;
			next_x = -64;
			next_y = -next_x * aTan;
			vertical_type = 'W';
		}
		else
		{
			ray_x = img->player.x;
			ray_y = img->player.y;
			count = img->map.max;
		}
		//printf("max= %d\n", img->map.max);
		while (count < img->map.max) 
		{ 
			//printf("count = %d\n", count);
			mx = (int)(ray_x)>>6;
			my = (int)(ray_y)>>6;
			mp = my * img->map.x + mx;
			//printf("mx=%d my=%d mp= %d\n", mx, my, mp);
			//printf("map= -%s- c= %c\n",img->map.simple_map, img->map.simple_map[mp]);
			if (mp > 0 && mp < img->map.size && img->map.simple_map[mp] == '1')//hit wall
			{
				count = img->map.max;
				//printf("vertical wall\n");
				dist_v = cos(deg_to_rad(ray_angle)) * (ray_x-img->player.x) - sin(deg_to_rad(ray_angle)) * (ray_y-img->player.y);
			}		 
			else
			{
				ray_x += next_x;
				ray_y += next_y;
				count += 1;
			}
		}
		//print_ray2(img, img->player.vx, img->player.vy, dist_v);
		vx = ray_x;
		vy = ray_y;
		//-------start horizontal ray---------
		count = 0;
		aTan = 1.0 / aTan; 
		if (sin(deg_to_rad(ray_angle)) > 0.001)//looking up 
		{
			ray_y = (((int)img->player.y>>6)<<6) - 0.0001;
			ray_x = (img->player.y - ray_y) * aTan + img->player.x;
			next_y = -64;
			next_x = -next_y * aTan;
			horizontal_type = 'N';
		}
		else if (sin(deg_to_rad(ray_angle))<-0.001)//looking down
		{
			ray_y = (((int)img->player.y>>6)<<6) + 64;
			ray_x = (img->player.y - ray_y) * aTan + img->player.x;
			next_y = 64;
			next_x = -next_y * aTan;
			horizontal_type = 'S';
		}
		else
		{
			ray_x = img->player.x;
			ray_y = img->player.y;
			count = img->map.max;
		}//looking straight left or right
		
		while (count < img->map.max)  
		{ 
			mx = (int)(ray_x)>>6;
			my = (int)(ray_y)>>6;
			mp = my * img->map.x + mx;		   
			if (mp > 0 && mp < img->map.size && img->map.simple_map[mp] == '1')//hit   
			{
				count = img->map.max;
				dist_h = cos(deg_to_rad(ray_angle)) * (ray_x - img->player.x) - sin(deg_to_rad(ray_angle)) * (ray_y - img->player.y);
			}	
			else
			{
				ray_x += next_x;
				ray_y += next_y;
				count += 1;
			}											   //check next horizontal
  		}
		int wall_type;
		t_ray	ray_info;
		
		wall_type = 0;
		ray_info.texture_type = 0;
		if (dist_h != -1 && (dist_h < dist_v || dist_v == -1))
		{
			//print_ray2(img, cos(deg_to_rad(ray_angle)), -sin(deg_to_rad(ray_angle)), fabs(dist_h));
			dist_f = dist_h;
			//printf("rx= %f ry= %f\n", ray_x, ray_y);
			ray_info.mp = ray_x;
			wall_type = 0;
			ray_info.texture_type = horizontal_type;
		}
		else if (dist_v != -1)
		{
			dist_f = dist_v;
			//printf("vx= %f vy= %f\n", vx, vy);
			ray_x = vx;
			ray_y = vy;
			ray_info.mp = vy;
			//print_ray2(img, cos(deg_to_rad(ray_angle)), -sin(deg_to_rad(ray_angle)), fabs(dist_v));
			wall_type = 1;
			ray_info.texture_type = vertical_type;
		}
		else
		{
			ray_info.mp = 0;
			dist_f = 0;
		}
		ray_info.ty = ray_y;
		ray_info.pixel = 0; 
		ray_info.tx = ray_x;
		ray_info.index = nb_ray;
		ray_info.wall_type = wall_type;
		int ca = reset_angle(img->player.angle - ray_angle); //fisheye
		dist_f = dist_f * cos(deg_to_rad(ca));	//fisheye
		ray_info.dist = dist_f;	
		if (dist_f > 0)	 
			draw_ray3d(img, ray_info);
		ray_angle = reset_angle(ray_angle - 0.25);
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, new_img, 0, 0);
	mlx_destroy_image(img->mlx, new_img);
}