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

void	echap(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	glfwSetWindowShouldClose(data->window, 1);
}

void	key_0(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	data->current = NULL;
}

void	key_1(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 0)
		data->current = &objs[0];
}

void	key_2(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 1)
		data->current = &objs[1];
}

void	key_3(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 2)
		data->current = &objs[2];
}
