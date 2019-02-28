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

t_vec4		ft_mat4x4_mult_with_vec4(const t_mat4x4 m1, const t_vec4 vec)
{
	t_vec4 rez;

	rez.x = vec.x * m1[0][0] + vec.y * m1[0][1] + vec.z * m1[0]
[2] + vec.w * m1[0][3];
	rez.y = vec.x * m1[1][0] + vec.y * m1[1][1] + vec.z * m1[1]
[2] + vec.w * m1[1][3];
	rez.z = vec.x * m1[2][0] + vec.y * m1[2][1] + vec.z * m1[2]
[2] + vec.w * m1[2][3];
	rez.w = vec.x * m1[3][0] + vec.y * m1[3][1] + vec.z * m1[3]
[2] + vec.w * m1[3][3];
	return (rez);
}
