/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:08:14 by apommier          #+#    #+#             */
/*   Updated: 2022/05/04 21:06:34 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	print_ray2(t_data *img, float vx, float vy, float dist)
{
	int i = -1;
	while (++i < dist)
	{
		mlx_pixel_put(img->mlx, img->mlx_win, (img->player.x + (vx) * i) , (img->player.y + (vy) * i) , 500);
		mlx_pixel_put(img->mlx, img->mlx_win, (img->player.x + (vx) * i) + 1, (img->player.y + (vy) * i) , 500);
		mlx_pixel_put(img->mlx, img->mlx_win, (img->player.x + (vx) * i) , (img->player.y + (vy) * i) + 1, 500);
	}
}

void	draw_ray(t_data *img)
{
	float	ray_angle = 0; //ray angle
	float	ray_y = 0; //where ray touch x
	float	ray_x = 0; //where ray touch y
	float	next_x = 0;
	float	next_y = 0;
	float	dist_v;
	float	dist_h;
	float	dist_f;
	float	vx = 0;
	float	vy = 0;
	int		count = 0;
	float	aTan = 0;
	int		nb_ray = -1;
	int		my = 0;
	int		mx = 0;
	int		mp = 0;
	
	(void)dist_f;
	//printf("\nENTER DRAW RAY\n");
	//while (++k < ft_strlen(img->map.simple_map))
	//	printf("%d--- %c\n", k, img->map.simple_map[k]);
	//printf("map = -%s-\n", img->map.simple_map);
	count = 0;
	ray_angle = reset_angle(img->player.angle + 30);
	//ray_angle = reset_angle(img->player.angle);
	while (++nb_ray < 60)
	{
		//if (nb_ray)
		//	ray_angle -= 30;
		count = 0;
		dist_v = -1;
		dist_h = -1;
		//printf("------RAY N0 %d-------\n", nb_ray);
		//printf("player_angle= %f ray_angle= %f\n", img->player.angle, ray_angle);
		//----------start vertical ray----------
		aTan = tan(deg_to_rad(ray_angle));
		if (cos(deg_to_rad(ray_angle)) > 0.001)//looking left
		{
			ray_x = (((int)img->player.x>>6)<<6) + 64;
			ray_y = (img->player.x - ray_x) * aTan + img->player.y;
			next_x = 64;
			next_y = -next_x * aTan;
		}
		else if (cos(deg_to_rad(ray_angle)) < -0.001)//looking right
		{
			ray_x = (((int)img->player.x>>6)<<6) - 0.0001;
			ray_y = (img->player.x - ray_x) * aTan + img->player.y;
			next_x = -64;
			next_y = -next_x * aTan;
		}
		else
		{
			ray_x = img->player.x;
			ray_y = img->player.y;
			count = 8;
		}
		//if (next_x > 0)
		//	printf("for hroizon looking left\n");
		//else
		//	printf("for hroizon looking right\n");
		//printf("\nray_y= %f ray_x= %f\n", ray_y, ray_x);
		//printf("next_y= %f next_x= %f\n", next_y, next_x);
		//printf("BASE p_y= %f p_x= %f\n", img->player.y, img->player.x);
		while (count < 8) 
		{ 
			//printf("count = %d\n", count);
			mx = (int)(ray_x)>>6;
			my = (int)(ray_y)>>6;
			mp = my * img->map.x + mx;
			//printf("mx=%d my=%d mp= %d\n", mx, my, mp);                  
			if (mp > 0 && mp < img->map.x * img->map.y && img->map.simple_map[mp] == '1')//hit wall
			{
				count = 8;
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
		}
		else if (sin(deg_to_rad(ray_angle))<-0.001)//looking down
		{
			ray_y = (((int)img->player.y>>6)<<6) + 64;
			ray_x = (img->player.y - ray_y) * aTan + img->player.x;
			next_y = 64;
			next_x = -next_y * aTan;
		}
		else
		{
			ray_x = img->player.x;
			ray_y = img->player.y;
			count = 8;
		}//looking straight left or right
		
		while (count<8) 
		{ 
			//printf("ray_y= %f ray_x= %f\n", ray_y, ray_x);
			mx = (int)(ray_x)>>6;
			my = (int)(ray_y)>>6;
			mp = my * img->map.x + mx;
			//printf("mx=%d my=%d mp= %d\n", mx, my, mp);              
			if (mp > 0 && mp < img->map.x * img->map.y && img->map.simple_map[mp] == '1')
			{
				count = 8;
				//printf ("horizontal wall\n");
				//printf("case: x= %d, y= %d mp= %d\n", mx, my, mp);
				dist_h = cos(deg_to_rad(ray_angle)) * (ray_x - img->player.x) - sin(deg_to_rad(ray_angle)) * (ray_y - img->player.y);
			}//hit       
			else
			{
				ray_x += next_x;
				ray_y += next_y;
				count += 1;
			}                                               //check next horizontal
  		}
		//printf("dist_h= %f dist_v= %f\n", dist_h, dist_v);
		vx = cos(deg_to_rad(ray_angle));
		vy = -sin(deg_to_rad(ray_angle));
		//printf("player.vx= %f vx= %f player.vy= %f vy= %f\n", img->player.vx, vx, img->player.vy, vy);
		if (dist_h != -1 && (dist_h < dist_v || dist_v == -1))
		{
			print_ray2(img, vx, vy, fabs(dist_h));
			dist_f = dist_h;
		}
		else if (dist_v != -1)
		{
			dist_f = dist_v;
			print_ray2(img, vx, vy, fabs(dist_v));
		}
		else
			dist_f = 0;
		ray_angle = reset_angle(ray_angle - 1);
	}
}