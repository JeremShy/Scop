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

void	o(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (prev[O_OFFSET])
		return ;
	if (data->current)
		data->current->roton ^= 1;
}

void	key_up(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (!prev[G_OFFSET])
		return ;
	if (!data->current)
		return ;
	transl = ft_vec3_cross(data->dir, ft_vec3_cross(data->dir, data->cam.up));
	ft_vec3_normalize(&transl);
	transl = ft_vec3_scalar_mult(transl, -data->depl * delta / 1000);
	data->current->pos = ft_vec3_add(data->current->pos, transl);
}

void	key_down(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (!prev[G_OFFSET])
		return ;
	if (!data->current)
		return ;
	transl = ft_vec3_cross(data->dir, ft_vec3_cross(data->dir, data->cam.up));
	ft_vec3_normalize(&transl);
	transl = ft_vec3_scalar_mult(transl, data->depl * delta / 1000);
	data->current->pos = ft_vec3_add(data->current->pos, transl);
}

void	key_right(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (!prev[G_OFFSET])
		return ;
	if (!data->current)
		return ;
	transl = ft_vec3_cross(data->dir, data->cam.up);
	ft_vec3_normalize(&transl);
	transl = ft_vec3_scalar_mult(transl, -data->depl * delta / 1000);
	data->current->pos = ft_vec3_add(data->current->pos, transl);
}

void	key_left(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (!prev[G_OFFSET])
		return ;
	if (!data->current)
		return ;
	transl = ft_vec3_cross(data->dir, data->cam.up);
	ft_vec3_normalize(&transl);
	transl = ft_vec3_scalar_mult(transl, data->depl * delta / 1000);
	data->current->pos = ft_vec3_add(data->current->pos, transl);
}
