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

void	ft_mat4x4_set_look_at(t_mat4x4 matrice, const t_vec3 eye,
	const t_vec3 target, const t_vec3 up)
{
	t_vec3	xaxis;
	t_vec3	yaxis;
	t_vec3	zaxis;

	zaxis = ft_vec3_sub(eye, target);
	ft_vec3_normalize(&zaxis);
	xaxis = ft_vec3_cross(up, zaxis);
	ft_vec3_normalize(&xaxis);
	yaxis = ft_vec3_cross(zaxis, xaxis);
	matrice[0][0] = xaxis.x;
	matrice[1][0] = yaxis.x;
	matrice[2][0] = zaxis.x;
	matrice[3][0] = 0;
	matrice[0][1] = xaxis.y;
	matrice[1][1] = yaxis.y;
	matrice[2][1] = zaxis.y;
	matrice[3][1] = 0;
	matrice[0][2] = xaxis.z;
	matrice[1][2] = yaxis.z;
	matrice[2][2] = zaxis.z;
	matrice[3][2] = 0;
	matrice[0][3] = -1 * ft_vec3_dot(xaxis, eye);
	matrice[1][3] = -1 * ft_vec3_dot(yaxis, eye);
	matrice[2][3] = -1 * ft_vec3_dot(zaxis, eye);
	matrice[3][3] = 1;
}

void	ft_mat4x4_set_look_at_from_float_array(t_mat4x4 matrice,
	const float eye[3], const float target[3], const float up[3])
{
	t_vec3	vec_eye;
	t_vec3	vec_target;
	t_vec3	vec_up;

	vec_eye = ft_vec3_init(eye);
	vec_target = ft_vec3_init(target);
	vec_up = ft_vec3_init(up);
	ft_mat4x4_set_look_at(matrice, vec_eye, vec_target, vec_up);
}
