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

void	ft_mat4x4_set_scale(t_mat4x4 matrix, const t_vec3 scale)
{
	ft_mat4x4_set_identity(matrix);
	matrix[0][0] = scale.x;
	matrix[1][1] = scale.y;
	matrix[2][2] = scale.z;
}
