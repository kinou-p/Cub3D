/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:37:02 by apommier          #+#    #+#             */
/*   Updated: 2022/06/15 18:52:18 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

double	deg_to_rad(double angle)
{
	return (angle * 3.14159265358979323846 / 180.0);
}

double	reset_angle(double angle)
{
	if (angle > 359)
		angle -= 360.0;
	if (angle < 0)
		angle += 360.0;
	return (angle);
}

void	ft_error(char *error_msg)
{
	ft_putendl_fd(error_msg, 2);
	exit(1);
}

void ft_exit(char *str, t_data *img)
{
	ft_putstr_fd(str, 2);
	quit_game(img);
}

void check_dir(char *path, t_data *img)
{
	int fd;

	fd = open(path, O_DIRECTORY);
    if (fd >= 0)
    {
        close(fd);
        ft_exit("Error\nTexture path is a directory\n", img);
    }
	close(fd);
}
