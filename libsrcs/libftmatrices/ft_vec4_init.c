/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 18:52:58 by magouin           #+#    #+#             */
/*   Updated: 2016/08/31 18:53:03 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

t_vec4	ft_vec4_init(const float tab[4])
{
	t_vec4	vec;

	vec.x = tab[0];
	vec.y = tab[1];
	vec.z = tab[2];
	vec.w = tab[3];
	return (vec);
}
