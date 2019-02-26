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

void		*open_file(char *file, size_t *size)
{
	int						fd;
	struct stat				buf;
	void					*ret;

	ret = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (fstat(fd, &buf) == -1)
		close(fd);
	else
	{
		*size = buf.st_size;
		if ((ret = mmap(0, buf.st_size + 1000, PROT_READ | PROT_WRITE
			| PROT_EXEC, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (NULL);
	}
	((char *)ret)[buf.st_size] = 0;
	close(fd);
	return (ret);
}

int			get_values_for_malloc(t_obj *ret, char *file)
{
	int		fd;
	char	*line;
	int		i;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		ret->error = 1;
		return (0);
	}
	while (get_next_line(fd, &line) > 0)
	{
		i = ignore_whitespaces(&line);
		if (*line == 'f')
			ret->faces_nbr++;
		else if (*line == 'v' && *(line + 1) == 't')
			ret->tex_vertices_nbr++;
		else if (*line == 'v' && *(line + 1) == 'n')
			ret->normales_nbr++;
		else if (*line == 'v')
			ret->vertices_nbr++;
		else if (!ft_strncmp(line, "usemtl", 6))
			ret->mtl_nbr++;
		free(line - i);
	}
	return (1);
}

t_obj		obj_parser_main(char *file)
{
	int		fd;
	char	*line;
	t_obj	ret;

	ft_bzero(&ret, sizeof(t_obj));
	if (!init_path(file, &ret))
	{
		ret.error = 1;
		return (ret);
	}
	init_malloc(&ret, file);
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		ret.error = 1;
		return (ret);
	}
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(line, &ret);
		if (ret.error)
			return (ret);
		free(line);
	}
	init_obj(&ret);
	return (ret);
}
