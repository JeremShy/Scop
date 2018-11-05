#include <scop.h>
#include <fcntl.h>

int8_t	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '#')
		return (1);
	else
		return (0);
}

void	ignore_whitespaces(char **line)
{
	while (**line != '\0')
	{
		if (**line == ' ' || ** line == '\t')
			(*line)++;
		else if (**line == '#')
		{
			while (**line)
				(*line)++;
			break;
		}
		else
			break ;
	}
}

int		find_next_ignored_char(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (is_whitespace(line[i]))
			return (i);
		else
			i++;
	}
	return (i);
}

int8_t	ignored_line(char *line)
{
	if (line[0] == '\0')
		return (1);
	else
		return (0);
}

void	debut_handle(char **line, t_obj *ret, int size)
{
	*line += size;
	if (!is_whitespace(*line[0]))
	{
		ret->error = 1;
		return ;
	}
	ignore_whitespaces(line);
	if (*line[0] == '\0')
	{
		ret->error = 1;
		return ;
	}
}

void	handle_mtllib(char *line, t_obj *ret)
{
	int	len;

	debut_handle(&line, ret, 6);
	len = find_next_ignored_char(line);
	ret->material = ft_strsub(line, 0, len);
	line += len;
	ignore_whitespaces(&line);
	if (line[0] != '\0')
		ret->error = 1;
}

void	handle_o(char *line, t_obj *ret)
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

void	handle_v(char *line, t_obj *ret)
{
	t_vec3	v;
	char	**tab;
	int	i;

	debut_handle(&line, ret, 1);
	if (ret->error)
		return ;
	tab = split_whitespace(line);
	if (!tab)
	{
		ret->error = 1;
		return ;
	}
	i = 0;
	while (tab[i])
	{
		if (i == 3 && tab[i][0] != '#')
		{
			ret->error = 1;
			return ;
		}
		if (check_float(tab[i]))
		{
			v[i] = atof(tab[i]);
			if (ft_strchr(tab[i], '#') && i < 3)
			{
				ret->error = 1;
				return ;
			}
		}
		else
		{
			ret->error = 1;
			return ;
		}
		i++;
	}
	ft_vec3_copy(ret->vertices[ret->vertices_nbr], v);
	ft_vec3_print(ret->vertices[ret->vertices_nbr]);
	ret->vertices_nbr++;
}

void parse_line(char *line, t_obj *ret)
{
	ignore_whitespaces(&line);
	if (line[0] == '\0')
		return ;
	printf("handling line : [%s]\n", line);
	if (ft_strncmp(line, "mtllib", 6) == 0)
		handle_mtllib(line, ret);
	else if (ft_strncmp(line, "o", 1) == 0) // /!\ Order lul
		handle_o(line, ret);
	else if (ft_strncmp(line, "v", 1) == 0) // /!\ Order lul
		handle_v(line, ret);

	// else
	// 	ret->error = 1;
}

t_obj	obj_parser_main(char *file)
{
	int fd;
	char *line;
	t_obj	ret;

	ft_bzero(&ret, sizeof(t_obj));
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		dprintf(2, "Error OBJ file not found\n");
		ret.error = 1;
		return (ret);
	}
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(line, &ret);
		if (ret.error)
		{
			dprintf(2, "ERROR !\n");
			printf("[%s]\n", ret.material);
			printf("[%s]\n", ret.name);
			return (ret);
		}
		free(line);
	}
	printf("[%s]\n", ret.material);
	printf("[%s]\n", ret.name);
	return (ret);
}
