/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:16:18 by apommier          #+#    #+#             */
/*   Updated: 2022/05/02 18:16:28 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	double_size(char **tab)
{
	int	i;

	i = 0;
	if (tab == 0)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

void	free_double(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
}

void	print_double_fd(char **tab, int fd)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			ft_putstr_fd(tab[i], fd);
			ft_putstr_fd("\n", fd);
			i++;
		}
	}
}