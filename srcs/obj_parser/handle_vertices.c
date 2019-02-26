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

static int8_t	get_three_floats(char *line, t_vec3 *ret)
{
	char	**tab;
	int		i;

	if (!(tab = split_whitespace(line)))
		return (0);
	i = -1;
	while (tab[++i])
	{
		if (i == 3 && tab[i][0] != '#')
			return (free_str_dtab(tab));
		if (check_float(tab[i]))
		{
			if (i == 0)
				ret->x = atof(tab[i]);
			else if (i == 1)
				ret->y = atof(tab[i]);
			else if (i == 2)
				ret->z = atof(tab[i]);
			if (ft_strchr(tab[i], '#') && i < 3)
				return (free_str_dtab(tab));
		}
		else
			return (free_str_dtab(tab));
	}
	return (free_str_dtab(tab) + 1);
}

void			handle_v(char *line, t_obj *ret)
{
	t_vec3	v;

	debut_handle(&line, ret, 1);
	if (ret->error)
		return ;
	if (!get_three_floats(line, &v))
	{
		ret->error = 1;
		return ;
	}
	if (!ret->init)
	{
		ret->max = v;
		ret->min = v;
		ret->init = 1;
	}
	(v.x < ret->min.x) ? (ret->min.x = v.x) : 0;
	(v.x > ret->max.x) ? (ret->max.x = v.x) : 0;
	(v.y < ret->min.y) ? (ret->min.y = v.y) : 0;
	(v.y > ret->max.y) ? (ret->max.y = v.y) : 0;
	(v.z < ret->min.z) ? (ret->min.z = v.z) : 0;
	(v.z > ret->max.z) ? (ret->max.z = v.z) : 0;
	ret->vertices[ret->vertices_curr] = v;
	ret->vertices_curr++;
}

void			handle_vt(char *line, t_obj *ret)
{
	t_vec3	v;

	debut_handle(&line, ret, 2);
	if (ret->error)
		return ;
	if (!get_three_floats(line, &v))
	{
		ret->error = 1;
		return ;
	}
	ret->tex_vertices[ret->tex_vertices_curr].x = v.x;
	ret->tex_vertices[ret->tex_vertices_curr].y = v.y;
	ret->tex_vertices_curr++;
}

void			handle_vn(char *line, t_obj *ret)
{
	t_vec3	v;

	debut_handle(&line, ret, 2);
	if (ret->error)
		return ;
	if (!get_three_floats(line, &v))
	{
		ret->error = 1;
		return ;
	}
	ret->normales[ret->normales_curr] = v;
	ret->normales_curr++;
}
