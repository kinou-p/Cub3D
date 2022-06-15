/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:54:25 by sadjigui          #+#    #+#             */
/*   Updated: 2022/06/15 15:26:12 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void ft_exit(char *str, t_data *img)
{
	ft_putstr_fd(str, 2);
	quit_game(img);
}

void	verifie_texture_color(t_data *img)
{
	if (img->map.texture.north == NULL)
		ft_exit("Error\nTexture isn't loaded properly\n", img);
	if (img->map.texture.east == NULL)
		ft_exit("Error\nTexture isn't loaded properly\n", img);
	if (img->map.texture.south == NULL)
		ft_exit("Error\nTexture isn't loaded properly\n", img);
	if (img->map.texture.west == NULL)
		ft_exit("Error\nTexture isn't loaded properly\n", img);
	if (img->map.floor.set != 1)
		ft_exit("Error\nColor not set properly\n", img);
	if (img->map.sky.set != 1)
		ft_exit("Error\nColor not set properly\n", img);
}

void error_msg(t_data *img)
{
	if (img->map.error == 1)
		ft_exit("Error: Map isn't closed\n", img);
	if (img->map.error == 2)
		ft_exit("Error: Missing player\n", img);
	if (img->map.error == 3)
		ft_exit("Error: Too many players\n", img);
	if (img->map.error == -1)
		ft_exit("Error: Bad character in map\n", img);
}

void size_line(char *str, t_data *img)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (i > img->map.x)
		img->map.x = i;
}

char *charge_new(t_data *img, char **map, char **tmp_map)
{
	char *str;
	int i;

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

void inter_map(char **split, char **tmp, t_data *img)
{
	int i;
	int j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while(split[i][j])
		{
			if (split[i][j] == '3')
				img->map.error = -1;
			else if (split[i][j] != ' ')
				tmp[i + 1][j + 1] = split[i][j];
			j++;
		}
		i++;
	}
}

void close_or_not(char **tab, int i, int j, t_data *img)
{
	if(tab[i + 1][j] == '3' || tab[i - 1][j] == '3')
		img->map.error = 1;
	if(tab[i][j + 1] == '3' || tab[i][j - 1] == '3')
		img->map.error = 1;
	if(tab[i + 1][j + 1] == '3' || tab[i + 1][j - 1] == '3')
		img->map.error = 1;
	if(tab[i - 1][j + 1] == '3' || tab[i - 1][j - 1] == '3')
		img->map.error = 1;
	if (img->map.error != 1)
		img->map.error = 0;
}

void	find_angle(char c, t_data *img)
{
	if (c == 'N')
		img->player.angle = 90;
	if (c == 'E')
		img->player.angle = 0;
	if (c == 'S')
		img->player.angle = 270;
	if (c == 'W')
		img->player.angle = 180;
}

int	check_inner_utils(char *line, t_data *img)
{
	int	i;
	int player;

	i = 0;
	player = 0;
	while (line[i])
	{
		// if (line[i] == '0' || line[i] == '1' || line[i] == '3' || line[i] == '\n')
		// 	i++;
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			find_angle(line[i], img);
			//img->player.x = (i - 1) * 64;
			img->player.x = i * 64 - 32;
			player++;
		}
		else if (line[i] != '3' && line[i] != '0' && line[i] != '1')
			return (100);
		// else
		// 	return (2);
		i++;
	}
	return (player);
}

void check_inner(char **map, t_data *img)//fonction bizarre
{
	int i;
	int player;

	i = 0;
	player = 0;
	while (map[i])
	{
		player += check_inner_utils(map[i], img);
		if (player == 1 && !img->player.y)
			img->player.y = i * 64 - 32;
			//img->player.y = (i - 1) * 64;
		i++;
	}
	if (player == 0)
		img->map.error = 2;
	if (player > 1 && player < 100)//?????? pk 3 et -1?
		img->map.error = 3;
	if (player >= 100)
		img->map.error = -1;
}

void check_border(char **tab, t_data *img)
{
	int i;
	int j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '0' || tab[i][j] == 'W' || tab[i][j] == 'N' || tab[i][j] == 'S' || tab[i][j] == 'E')
				close_or_not(tab, i, j, img);
			j++;
		}
		i++;
	}
}

void	check_zero_one(char **split, t_data *img)
{
	char **tmp;
	int i;

	i = 0;
	while (split[i])
	{
		size_line(split[i], img);
		i++;
	}
	img->map.y = i;
	tmp = malloc(sizeof(char *) * (i + 3));
	if (!tmp)
	{
		free_double(split);
		quit_game(img);
	}
	i = 0;
	while(i < img->map.y + 2)
	{
		tmp[i] = charge_new(img, split, tmp);
		i++;
	}
	tmp[i] = NULL;
	inter_map(split, tmp, img);
	if (img->map.error == -1)
		return;
	check_border(tmp, img);
	check_inner(tmp, img);
	free_double(tmp);
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

char	**isafile(char **av, t_data *img)
{

	int		fd;
	char	*line;
	char	*str;
	char	*tmp;
	char	**split;

	img->err = 0;
	fd = open(av[1], O_RDONLY);
	img->to_be_free.fd = fd;
	str = NULL;
	tmp = NULL;
	if (fd == - 1)
		ft_exit("Error: File doesn't exist\n", img);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] != '\n' && img->err == 0)
		{
			if (detect_map_line(line))
				img->err = 1;
			if (line[0] == '\n' && img->err == 1)
				img->err = 2;
		}
		tmp = ft_strjoin(str, line);
		free(line);
		line = NULL;
		if (str != NULL)
			free(str);
		if (!tmp)
			quit_game(img);
		str = tmp;
	}
	if (img->err == 2)
	{
		free(str);
		ft_exit("Error\nBad texture file\n", img);
	}
	split = ft_split(str, '\n');
	img->to_be_free.tab = split;
	free(str);
	free(line);
	close(fd);
	img->to_be_free.fd = -1;
	int pass = 0;
	pass = check_texture_color(split, img);
	check_zero_one(split + pass, img);
	//leaks here -- normalement c bon
	transform_map(split + pass, img);
	free_double(split);
	img->to_be_free.tab = 0;
	return (0);
}

int check_map(char **av, t_data *img)
{
	img->map.x = 0;
	img->map.y = 0;
	img->map.error = 0;

	if (reverse_comp(av[1], ".cub") || (ft_strlen(av[1]) == ft_strlen(".cub")))
	{
		ft_exit("Error: Not a valid file \".cub\"\n", img);
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
		quit_game(img);//surely leak???
	}
	verifie_texture_color(img);
	return (0);
}

/*int		main(int ac, char **av)
{
	t_root img;

	if (check_map(av, &img))
		return (0);
	else
		printf("map is clean\n");
}*/
