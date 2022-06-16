/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:37:43 by apommier          #+#    #+#             */
/*   Updated: 2022/06/16 16:38:57 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

char	**fill_tab(char *swap, int count, char **ret, int fd)
{
	while (swap || !count)
	{
		swap = get_next_line(fd);
		if (ft_strlen(swap) >= 1 && swap[ft_strlen(swap) - 1] == '\n')
			swap[ft_strlen(swap) - 1] = 0;
		ret[count] = swap;
		count++;
	}
	return (ret);
}

char	**isafile(char **av, t_data *img)
{
	int		fd;
	char	**ret;
	int		count;
	int		pass;

	count = 0;
	get_map_size(av[1], img, &count, 0);
	ret = ft_calloc(sizeof(char *), count);
	if (!ret)
		quit_game(img);
	img->to_be_free.tab = ret;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_exit("Error\nBad texture file", img);
	ret = fill_tab(0, 0, ret, fd);
	close(fd);
	pass = check_texture_color(ret, img);
	check_zero_one(ret + pass, img);
	transform_map(ret + pass, img);
	free_double(ret);
	img->to_be_free.tab = 0;
	return (0);
}
