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

void	ft_vec2_normalize(t_vec2 *vector)
{
	float	magnitude;

	if (!vector->x && !vector->y)
		return ;
	magnitude = ft_vec2_get_norme(*vector);
	vector->x = vector->x / magnitude;
	vector->y = vector->y / magnitude;
}
