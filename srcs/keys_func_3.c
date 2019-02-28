/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:49:20 by marnaud           #+#    #+#             */
/*   Updated: 2019/02/26 15:49:53 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	a(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	transl = ft_vec3_cross(data->dir, (t_vec3){0, 1, 0});
	ft_vec3_normalize(&transl);
	transl = ft_vec3_scalar_mult(transl, data->depl * delta / 1000);
	data->eye = ft_vec3_add(data->eye, transl);
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye,
		data->dir), data->cam.up);
}

void	d(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	transl = ft_vec3_cross(data->dir, (t_vec3){0, 1, 0});
	ft_vec3_normalize(&transl);
	transl = ft_vec3_scalar_mult(transl, -data->depl * delta / 1000);
	data->eye = ft_vec3_add(data->eye, transl);
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye,
		data->dir), data->cam.up);
}

void	t(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (prev[T_OFFSET])
		return ;
	if (data->current)
		data->current->texon ^= 1;
}

void	r(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	data->eye = (t_vec3){0, 0, -10};
	data->dir = (t_vec3){0, 0, -1};
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye,
		data->dir), data->cam.up);
	data->angle_y = 0;
}

void	v(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (prev[V_OFFSET])
		return ;
	!data->drawing_mode ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) :
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	data->drawing_mode = !data->drawing_mode;
}
