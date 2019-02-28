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

void	ft_mat4x4_set_projection(t_mat4x4 m, const float array[4])
{
	float	fov;
	float	ratio;
	float	near;
	float	far;
	float	tan_half_fov;

	fov = array[0];
	ratio = array[1];
	near = array[2];
	far = array[3];
	ft_mat4x4_set_zero(m);
	tan_half_fov = tan(((M_PI / 180.) * fov) / 2);
	m[0][0] = 1 / (ratio * tan_half_fov);
	m[1][1] = 1 / tan_half_fov;
	m[2][2] = (-1 * (far + near)) / (far - near);
	m[3][2] = -1;
	m[2][3] = (-1 * (2 * far * near) / (far - near));
}
