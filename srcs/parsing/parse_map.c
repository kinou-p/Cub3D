/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:54:25 by sadjigui          #+#    #+#             */
/*   Updated: 2022/06/16 16:38:05 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

char	*charge_new(t_data *img, char **map, char **tmp_map)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (img->map.x + 3));
	if (!str)
	{
		free_double(map);
		free_double(tmp_map);
		quit_game(img);
	}
	while (i < img->map.x + 2)
	{
		str[i] = '3';
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	reverse_comp(char *s1, char *s2)
{
	int	size_s1;
	int	size_s2;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	while (size_s2 >= 0)
	{
		if (!(s2[size_s2] == s1[size_s1]))
			return (1);
		size_s1--;
		size_s2--;
	}
	return (0);
}

int	is_in_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	detect_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (*line == '\0')
		return (0);
	while (line[i])
	{
		if (is_in_charset(line[i], " 01NSEW\n") == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_map(char **av, t_data *img)
{
	img->map.x = 0;
	img->map.y = 0;
	img->map.error = 0;
	if (reverse_comp(av[1], ".cub") || (ft_strlen(av[1]) == ft_strlen(".cub")))
	{
		ft_exit("Error\nNot a valid file \".cub\"\n", img);
		return (1);
	}
	isafile(av, img);
	if (img->map.x > img->map.y)
		img->map.max = img->map.x;
	else
		img->map.max = img->map.y;
	if (img->map.error != 0)
	{
		error_msg(img);
		quit_game(img);
	}
	verify_texture_color(img);
	return (0);
}
