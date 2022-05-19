/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:08:14 by apommier          #+#    #+#             */
/*   Updated: 2022/05/19 19:04:22 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	print_ray2(t_data *img, double vx, double vy, double dist)
{
	int i = -1;
	int red = 0;

	//printf("in print ray2\n");
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

int get_color(char one, char two, char three)
{
	int color = 0;

	color = color << 8;
	color += one;
	color = color << 8;
	color += two;
	color = color << 8;
	color += three;
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

void	draw_ray3d(t_data *img, ray ray)
{
	double	line_height;
	double	line_offset;
	int		x = 0;
	double	y = 0;
	int		mx = 0;
	int		my = 0;
	//int 	pixel;
	int 	color;
	int		texture_size = 64;
	//char	*wall;

	//wall = get_texture(1);
	/*for(y=0;y<lineH;y++)
  	{
		int pixel=((int)ty*32+(int)tx)*3+(hmt*32*32*3);
		int red   =All_Textures[pixel+0]*shade;
		int green =All_Textures[pixel+1]*shade;
		int blue  =All_Textures[pixel+2]*shade;
		glPointSize(8); glColor3ub(red,green,blue); glBegin(GL_POINTS); glVertex2i(r*8,y+lineOff); glEnd();
		ty+=ty_step;
	}*/


	// double ty=ty_off*ty_step;//+hmt*32;
 	// double tx;
	// if(shade==1)
	// {
	// 	tx=(int)(rx/2.0)%32;
	// 	if(ra>180)
	// 		tx=31-tx;
	// }  
	// else
	// {
	// 	tx=(int)(ry/2.0)%32;
	// 	if(ra>90 && ra<270)
	// 		tx=31-tx;
	// }

	
	//pixel = ((int)ty * 32 + (int)tx) * 3 + (hmt * 32 * 32 * 3);
	//int copy = ray.ty;
	
	//i = 0;
	line_height = img->map.size * 960 / ray.dist;
	//if (line_height > 512)
	//	line_height = 512;
	line_offset = 256 - line_height / 2;
	double	gap = 1;
	//double	old_y = 0;
	double myy = 0;
	//printf("mp= %f modulo texture_size= %d\n", ray.mp, ((int)ray.mp / 4) % texture_size);
	
	//while (x < 8)
	//{
		y = 0;
		my = 0;
		myy = 0;
		//double step = 1.0 * texHeight / lineHeight;
		gap = (texture_size / line_height);
		//old_y = 0;
	 	//ray.ty = ;
		mx = ((int)ray.mp) % texture_size;
		//int texX = int(wallX * double(texWidth));
    	//if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
    	//if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
		while (y < line_height)
		{
			//if (y > old_y + (16 / line_height)/*(line_height / 16)*/)
			//{
			//	gap++;
			//	old_y = y;
			//}
			//(x * 16 + y)* 3 + 1;
			//mp= x du mur
			
			//my = gap;
			myy += gap;
			my = (int)myy;//gap;
			//mx = ((int)ray.mp) % 16;
			//ray.pixel = ((((int)ray.mp) % 16) * 16 + gap /*+ x*/) * 3 + 1 ;
			ray.pixel = ((my) * texture_size + mx)* 3 - 1;
			x = -1;
			//printf("x= %d y= %f pixel= %d\n", ray.index /** 2 + 530 + x*/, y, ray.pixel);
			color = get_color(img->map.texture.north[ray.pixel], img->map.texture.north[ray.pixel + 1], img->map.texture.north[ray.pixel + 2]);
			while (++x < 4)
			{
				if (ray.wall_type)
					mlx_pixel_put(img->mlx, img->mlx_win, ray.index * 4 + x, y + line_offset , color);
				else
					mlx_pixel_put(img->mlx, img->mlx_win, ray.index * 4 + x, y + line_offset , (color >> 1) & 8355711);
			}
			//printf("pixel=%d   ", ray.pixel);
			//if (ray.wall_type)
			//int l = 0;
			//while (l < 8)
			//{
				//x = -1;
				//while (++x < 8)
					
				//l++;
			//}
			//else
			//	mlx_pixel_put(img->mlx, img->mlx_win, ray.index * 8 + 530 + x, y + line_offset , color);
			y++;
		}
		x++;
	//}
	//printf("\n");
	//ray.tx++;
	
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
	
	(void)dist_f;
	//printf("---NEW RAY----\n\n");
	//printf("\nENTER DRAW RAY\n");
	//while (++k < ft_strlen(img->map.simple_map))
	//	printf("%d--- %c\n", k, img->map.simple_map[k]);
	//printf("map = -%s-\n", img->map.simple_map);
	count = 0;
	ray_angle = reset_angle(img->player.angle + 30);
	//ray_angle = reset_angle(img->player.angle);
	while (++nb_ray < 240)
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
		//if (aTan != tan(deg_to_rad(ray_angle - 0.25)))
		//double test = 0.1111111111111;
		//printf("test= %f\n", test);
		//printf("ray_angle = %f\n", ray_angle);
		//printf("in atan= %f\n", deg_to_rad(ray_angle));
		//printf("atan= %f\n", aTan);
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
		
		while (count < 8)  
		{ 
			//printf("ray_y= %f ray_x= %f\n", ray_y, ray_x);
			mx = (int)(ray_x)>>6;
			my = (int)(ray_y)>>6;
			mp = my * img->map.x + mx;
			//printf("mx=%d my=%d mp= %d\n", mx, my, mp);              
			if (mp > 0 && mp < img->map.x * img->map.y && img->map.simple_map[mp] == '1')//hit   
			{
				count = 8;
				//printf ("horizontal wall\n");
				//printf("case: x= %d, y= %d mp= %d\n", mx, my, mp);
				dist_h = cos(deg_to_rad(ray_angle)) * (ray_x - img->player.x) - sin(deg_to_rad(ray_angle)) * (ray_y - img->player.y);
			}    
			else
			{
				ray_x += next_x;
				ray_y += next_y;
				count += 1;
			}                                               //check next horizontal
  		}
		//printf("dist_h= %f dist_v= %f\n", dist_h, dist_v);
		//vx = cos(deg_to_rad(ray_angle));
		//vy = -sin(deg_to_rad(ray_angle));
		//printf("vx= %f vy= %f\n rx= %f ry= %f", vx, vy, ray_x, ray_y);
		int wall_type;
		ray	ray_info;
		
		if (dist_h != -1 && (dist_h < dist_v || dist_v == -1))
		{
			//print_ray2(img, cos(deg_to_rad(ray_angle)), -sin(deg_to_rad(ray_angle)), fabs(dist_h));
			dist_f = dist_h;
			//printf("rx= %f ry= %f\n", ray_x, ray_y);
			ray_info.mp = ray_x;
			wall_type = 0;
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
		}
		else
			dist_f = 0;
		
		double tx;
		//double ty_off = 0;
		//double ty_step = 32.0/dist_f;
		//double ty = ;
		/*if(dist_f > 640)
		{
			ty_off = (dist_f - 320) / 2.0;
			dist_f = 320;
		} */
		//ty =  ty_off * 16.0 / dist_f; ;//+hmt*32;
		//tx = (int) (ray_y / 2.0) % 16;
		tx=(int)(ray_x/2.0) % 32; if(ray_angle>180){ tx=31-tx;}
		//if(ray_angle > 180)
		//	tx = 15 - tx;
		//ray_info.pixel = ((int)ty * 16 + (int)tx) * 3 + 3;
		//printf("nb_ray= %d\n", nb_ray);
		ray_info.ty = ray_y;
		ray_info.tx = ray_x;
		//ray_info.mp = ray_info.mp / 2;
		ray_info.index = nb_ray;
		ray_info.wall_type = wall_type;
		int ca = reset_angle(img->player.angle - ray_angle); //fisheye
		dist_f = dist_f * cos(deg_to_rad(ca));	
		ray_info.dist = dist_f;			 //fisheye
		draw_ray3d(img, ray_info);
		//ray_angle -= 0.5;
		//printf("entre ray_angle = %f\n", ray_angle);
		ray_angle = reset_angle(ray_angle - 0.25);
		//printf("after ray_angle = %f\n", ray_angle);
	}
}