/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:17:25 by sadjigui          #+#    #+#             */
/*   Updated: 2022/05/24 14:49:21 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int parsing(char **av);
{
    char    *line;
    int     fd;
    int     i;

    i = 0;
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        ft_error("Error: Open call fail");
    line = get_next_line(fd);
    while (line != NULL)
        i++;
    close(fd);
    if (set_map_test)
        return (1);
    return (ret_map);
}

int set_map_test(char **av, int size)
{
    char    *line;
    char    **map;
    int     fd;
    int     i;

    i = 0;
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        ft_error("Error: Open call fail");
    map = malloc(sizeof(char *) * (size + 1));
    if (!map)
        return (0);
    line = get_next_line(fd);
    while (line != NULL)
    {
        map[i] = line;
        free(line);
        line = get_next_line(fd);
        i++;
    }
    map[i] = 0;
    test_map(map, size);
    // free map
    close(fd);
}

char   *out_of_map(int size)
{
    int i;
    char *str;

    i = 0;
    str = malloc(sizeof(char) * (size + 1));
    if (!str)
        return (NULL);
    while (i < size)
    {
        str[i] = '3';
        i++;
    }
    return (str);
}

int test_map(char **map, int height)
{
    char **tmp;
    int width;
    int i;

    i = 0;
    width = find_max(map);
    tmp = malloc(sizeof(char *) * (height + 3));
    if (!tmp)
        return (0);
    while (tmp[i])
    {
        tmp[i] = out_of_map(width);
    }
}
