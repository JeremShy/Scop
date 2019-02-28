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

void		handle_mtllib(char *line, t_obj *obj)
{
	char	*file;
	size_t	size;
	char	*l;
	char	*tmp;

	if (obj->ref)
		return ;
	debut_handle(&line, obj, 6);
	tmp = ft_strndup(line, find_next_line(line));
	file = ft_strjoin(obj->path, tmp);
	free(tmp);
	l = open_file(file, &size);
	if (!l)
	{
		obj->error = 1;
		return ;
	}
	create_ref(obj, l, size);
	fill_ref(obj, l, size);
	munmap(l, size);
}

void		handle_usemtl(char *line, t_obj *obj)
{
	char	*tmp;

	debut_handle(&line, obj, 6);
	tmp = ft_strndup(line, find_next_line(line));
	obj->mtls[obj->mtl_curr].index = obj->faces_curr;
	obj->mtls[obj->mtl_curr].ref = tmp;
	obj->mtl_curr++;
	return ;
}

void		handle_s(char *line, t_obj *ret)
{
	(void)line;
	(void)ret;
}

void		handle_g(char *line, t_obj *ret)
{
	(void)line;
	(void)ret;
}

void		handle_o(char *line, t_obj *ret)
{
	int	len;

	debut_handle(&line, ret, 1);
	len = find_next_ignored_char(line);
	ret->name = ft_strsub(line, 0, len);
	line += len;
	ignore_whitespaces(&line);
	if (line[0] != '\0')
		ret->error = 1;
}
