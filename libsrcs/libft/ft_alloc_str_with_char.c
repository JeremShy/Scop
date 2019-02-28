/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_str_with_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:01:29 by marnaud           #+#    #+#             */
/*   Updated: 2019/02/28 13:01:35 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_alloc_str_with_char(int c)
{
	char	*ret;

	ret = (char*)mallocp(2 * sizeof(char));
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}
