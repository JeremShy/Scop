/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:30:05 by jcamhi            #+#    #+#             */
/*   Updated: 2016/09/02 00:14:54 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strndup(const char *s1, size_t size)
{
	char	*res;
	uint	len;
	int		i;

	if (ft_strlen(s1) + 1 < size)
		len = (ft_strlen(s1) + 1);
	else
		len = (size + 1);
	res = (char*)malloc(len * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && size)
	{
		res[i] = s1[i];
		size--;
		i++;
	}
	res[i] = '\0';
	return (res);
}
