/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:49:20 by magouin           #+#    #+#             */
/*   Updated: 2019/02/26 15:49:53 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	key_9(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 8)
		data->current = &objs[8];
}

void	equal(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (prev[F_OFFSET])
	{
		if (data->current)
		{
			data->current->scale *= 1.01;
		}
	}
	else
		data->depl *= 1.01;
}

void	minus(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (prev[F_OFFSET])
	{
		if (data->current)
		{
			data->current->scale *= 1 / 1.01;
		}
	}
	else
		data->depl /= 1.01;
}

void	w(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	transl = ft_vec3_scalar_mult(data->dir, -data->depl * delta / 1000);
	data->eye = ft_vec3_add(data->eye, transl);
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye,
		data->dir), data->cam.up);
}

void	s(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	transl = ft_vec3_scalar_mult(data->dir, data->depl * delta / 1000);
	data->eye = ft_vec3_add(data->eye, transl);
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye,
		data->dir), data->cam.up);
}
