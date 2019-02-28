/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:01:29 by marnaud           #+#    #+#             */
/*   Updated: 2019/02/28 13:01:35 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_alloc_str(const char *str)
{
	char	*truc;

	if (str == NULL)
		return (ft_alloc_str("(null)"));
	truc = (char*)mallocp(ft_strlen(str) + 1);
	ft_strcpy(truc, str);
	return (truc);
}
