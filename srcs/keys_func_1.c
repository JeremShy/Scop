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

void	key_4(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 3)
		data->current = &objs[3];
}

void	key_5(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 4)
		data->current = &objs[4];
}

void	key_6(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 5)
		data->current = &objs[5];
}

void	key_7(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 6)
		data->current = &objs[6];
}

void	key_8(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 7)
		data->current = &objs[7];
}
