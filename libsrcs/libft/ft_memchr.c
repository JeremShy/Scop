/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:40:54 by marnaud           #+#    #+#             */
/*   Updated: 2015/11/25 20:38:28 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	int			i;
	const char	*str;

	i = 0;
	str = s;
	while (i < (int)n)
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((void*)s + i);
		i++;
	}
	return (NULL);
}
