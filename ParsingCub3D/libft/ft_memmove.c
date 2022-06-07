/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:14:39 by sadjigui          #+#    #+#             */
/*   Updated: 2021/12/08 19:22:11 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	size_t	i;

	i = 0;
	if (src == dest)
		return (dest);
	if (dest > src)
	{
		while (size > 0)
		{
			*(char *)(dest + (size - 1)) = *(char *)(src + (size - 1));
			size--;
		}
		return (dest);
	}
	while (i < size)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}
