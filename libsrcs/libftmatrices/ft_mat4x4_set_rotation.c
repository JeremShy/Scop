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

void	ft_mat4x4_set_rotation(t_mat4x4 matrice, float angle, const t_vec3 axis)
{
	t_vec3	v;
	float	c;
	float	s;

	c = cos(DEGREES_TO_RADIANS(angle));
	s = sin(DEGREES_TO_RADIANS(angle));
	v = axis;
	ft_vec3_normalize(&v);
	matrice[0][0] = v.x * v.x * (1 - c) + c;
	matrice[0][1] = v.x * v.y * (1 - c) - v.z * s;
	matrice[0][2] = v.x * v.z * (1 - c) + v.y * s;
	matrice[0][3] = 0;
	matrice[1][0] = v.x * v.y * (1 - c) + v.z * s;
	matrice[1][1] = v.y * v.y * (1 - c) + c;
	matrice[1][2] = v.y * v.z * (1 - c) - v.x * s;
	matrice[1][3] = 0;
	matrice[2][0] = v.x * v.z * (1 - c) - v.y * s;
	matrice[2][1] = v.y * v.z * (1 - c) + v.x * s;
	matrice[2][2] = v.z * v.z * (1 - c) + c;
	matrice[2][3] = 0;
	matrice[3][0] = 0;
	matrice[3][1] = 0;
	matrice[3][2] = 0;
	matrice[3][3] = 1;
}
