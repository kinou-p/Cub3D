/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:44:01 by apommier          #+#    #+#             */
/*   Updated: 2022/05/06 19:29:27 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *save, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save && !s2)
		return (0);
	dest = malloc(ft_strlen(save) + ft_strlen(s2) + 1);
	while (save && save[i])
	{
		dest[j] = save[i];
		j++;
		i++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		dest[j] = s2[i];
		j++;
		i++;
	}
	dest[j] = 0;
	return (dest);
}

char	*ft_strjoin_delete(char *save, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save && !s2)
		return (0);
	dest = malloc(ft_strlen(save) + ft_strlen(s2) + 1);
	while (save && save[i])
		dest[j++] = save[i++];
	i = 0;
	while (s2 && s2[i])
		dest[j++] = s2[i++];
	dest[j] = 0;
	if (save)
		free(save);
	if (s2)
		free(s2);
	return (dest);
}
