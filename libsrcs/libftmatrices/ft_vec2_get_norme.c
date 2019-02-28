/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 18:52:58 by marnaud           #+#    #+#             */
/*   Updated: 2016/08/31 18:53:03 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

float	ft_vec2_get_norme(const t_vec2 vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y));
}
