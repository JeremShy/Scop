/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <magouin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 09:02:45 by magouin           #+#    #+#             */
/*   Updated: 2016/09/01 18:01:03 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

void	ft_putstr(char *s)
{
	int i;

	if (s == NULL)
	{
		ft_putstr("(null)");
		return ;
	}
	i = ft_strlen(s);
	write(1, s, i);
}
