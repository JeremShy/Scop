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

void	ft_mat4x4_rotate(t_mat4x4 matrice, float angle, const t_vec3 axis)
{
	t_mat4x4	rotation_matrix;

	ft_mat4x4_set_rotation(rotation_matrix, angle, axis);
	ft_mat4x4_mult(matrice, matrice, rotation_matrix);
}
