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

#ifndef LIBFTMATRICES_H
# define LIBFTMATRICES_H
# include <libft.h>
# include <stdio.h>
# include <math.h>

# ifndef M_PI
#  define M_PI 3.1415926535897932384626
# endif

# define DEGREES_TO_RADIANS(angle) (angle * M_PI / 180.0)
# define RADIANS_TO_DEGREES(angle) (angle * 180.0 / M_PI)

typedef float	t_mat4x4[4][4];

typedef struct	s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_vec4;

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct	s_vec2 {
	float	x;
	float	y;
}				t_vec2;

void			ft_mat4x4_set_identity(t_mat4x4 matrice);
void			ft_mat4x4_set_zero(t_mat4x4 m);
void			ft_mat4x4_set_projection(t_mat4x4 m, const float array[4]);
void			ft_mat4x4_set_translation(t_mat4x4 m, const t_vec3 v);
void			ft_mat4x4_set_look_at(t_mat4x4 matrice, const t_vec3 eye,
	const t_vec3 target, const t_vec3 up);
void			ft_mat4x4_set_look_at_from_float_array(t_mat4x4 matrice,
	const float eye[3], const float target[3], const float up[3]);
void			ft_mat4x4_set_rotation(t_mat4x4 matrice,
	float angle, const t_vec3 axis);
void			ft_mat4x4_set_scale(t_mat4x4 matrix, const t_vec3 scale);

void			ft_mat4x4_print(const t_mat4x4 matrice);
void			ft_mat4x4_mult(t_mat4x4 ret, const t_mat4x4 m1,
	const t_mat4x4 m2);
void			ft_mat4x4_copy(t_mat4x4 dest, const t_mat4x4 src);
void			ft_mat4x4_mult_with_real(t_mat4x4 rez, const t_mat4x4 m,
	float r);
t_vec4			ft_mat4x4_mult_with_vec4(const t_mat4x4 m1, const t_vec4 vec);

void			ft_mat4x4_translate(t_mat4x4 m, const t_vec3 v);
void			ft_mat4x4_rotate(t_mat4x4 matrice, float angle,
	const t_vec3 axis);
void			ft_mat4x4_scale(t_mat4x4 matrice, const t_vec3 scale);
void			ft_mat4x4_translate_from_float_array(t_mat4x4 m,
	const float array[3]);
void			ft_mat4x4_rotate_from_float_array(t_mat4x4 matrice,
	float angle, const float array[3]);
void			ft_mat4x4_scale_from_float_array(t_mat4x4 matrice,
	const float array[3]);

void			ft_mat4x4_to_float_array(float dest[16],
	const t_mat4x4 matrice);

t_vec4			ft_vec4_init(const float tab[4]);
void			ft_vec4_print(const t_vec4 v);
t_vec3			ft_vec4_to_vec3(const t_vec4 vector);

t_vec3			ft_vec3_init(const float tab[3]);
void			ft_vec3_print(const t_vec3 v);
t_vec3			ft_vec3_add(const t_vec3 v1, const t_vec3 v2);
t_vec3			ft_vec3_sub(const t_vec3 v1, const t_vec3 v2);
t_vec3			ft_vec3_cross(const t_vec3 v1, const t_vec3 v2);
float			ft_vec3_dot(const t_vec3 u, const t_vec3 v);
float			ft_vec3_get_norme(const t_vec3 vector);
void			ft_vec3_normalize(t_vec3 *vector);
t_vec4			ft_vec3_to_vec4(const t_vec3 vector);
t_vec3			ft_vec3_rotate(t_vec3 vec, float angle, t_vec3 axis);
t_vec3			ft_vec3_scalar_mult(t_vec3 v, float f);

void			ft_vec2_print(const t_vec2 v);
t_vec2			ft_vec2_add(const t_vec2 v1, const t_vec2 v2);
t_vec2			ft_vec2_sub(const t_vec2 v1, const t_vec2 v2);
float			ft_vec2_dot(const t_vec2 u, const t_vec2 v);
float			ft_vec2_get_norme(const t_vec2 vector);
void			ft_vec2_normalize(t_vec2 *vector);
t_vec2			ft_vec2_get_normal(t_vec2 v);

#endif
