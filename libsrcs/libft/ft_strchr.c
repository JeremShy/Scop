/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:00:31 by marnaud           #+#    #+#             */
/*   Updated: 2015/11/25 20:06:53 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	int		i;
	char	*ret;

	ret = (char*)s;
	ch = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return (ret + i);
		i++;
	}
	if (ch == '\0')
		return (ret + i);
	return (NULL);
}
