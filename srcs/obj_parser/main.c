#include <scop.h>
#include <fcntl.h>

static struct s_obj_parsing obj_parsing[] = {
	{"mtllib", handle_mtllib},
	{"usemtl", handle_usemtl},
	{"s", handle_s},
	{"o", handle_o},
	{"g", handle_g},
	{"vn", handle_vn},
	{"vt", handle_vt},
	{"v", handle_v},
	{"f", handle_f},
	{NULL, NULL}
};

size_t	find_next_line(char *line)
{
	size_t	s;

	s = 0;
	while (*line && *line != '\xd' && *line != '\n')
	{
		line++;
		s++;
	}
	return (s);
}

int8_t	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\xd')
		return (1);
	else
		return (0);
}

int	ignore_whitespaces(char **line)
{
	int i;

	i = 0;
	while (**line)
	{
		if (is_whitespace(**line))
		{
			(*line)++;
			i++;
		}
		else if (**line == '#')
		{
			while (**line && **line != '\n')
			{
				i++;
				(*line)++;
			}
			return (i);
		}
		else
			return (i);
	}
	return (i);
}

int		find_next_ignored_char(char *line)
{
	int		i;
	uint8_t escape;

	i = 0;
	escape = 0;
	while (line[i] && line[i] != '\n')
	{
		if (is_whitespace(line[i]) && !escape)
			return (i);
		if (escape)
			escape = 0;
		else if (line[i] == '\\')
			escape = 1;
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
	ignore_whitespaces(line);
	if (*line[0] == '\0')
	{
		ret->error = 1;
		return ;
	}
}

void	*open_file(char *file, size_t *size)
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
		if ((ret = mmap(0, buf.st_size + 1000, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (NULL);
	}
	((char *)ret)[buf.st_size] = 0;
	close(fd);
	return (ret);
}

void	next_line(char **file, size_t *size)
{
	int i;

	i = 0;
	while (*size && **file != '\n')
	{
		(*size)--;
		(*file)++;
	}
	if ((*size))
	{
		(*size)--;
		(*file)++;
	}
}

void	fill_ref(t_obj *obj, char *file, size_t size)
{
	char *tmp;
	int nb_array;

	nb_array = -1;
	while (size > 0)
	{
		size -= ignore_whitespaces(&file);
		if (size > 6 && !ft_strncmp(file, "newmtl", 6))
		{
			nb_array++;
			size -= 6;
			debut_handle(&file, obj, 6);
			obj->ref[nb_array].ref = ft_strndup(file, find_next_line(file));
		}
		else if (size > 6 && !ft_strncmp(file, "map_Kd", 6))
		{
			size -= 6;
			debut_handle(&file, obj, 6);
			if ((size_t)(ft_strstr(file, ".png") - file) == ft_strlen(file)) ////////////////////////TODO
				obj->error = 1;
			tmp = ft_strndup(file, ft_strstr(file, ".png") - file + 4);
			obj->ref[nb_array].img = ft_strjoin(obj->path, tmp);
			free(tmp);
		}
		next_line(&file, &size);
	}
}

void	create_ref(t_obj *obj, char *file, size_t size)
{
	uint			nb_array;

	nb_array = 0;
	while (size > 0)
	{
		size -= ignore_whitespaces(&file);
		if (size > 6 && !ft_strncmp(file, "newmtl", 6))
			nb_array++;
		next_line(&file, &size);
	}
	obj->ref_nbr = nb_array;
	obj->ref = malloc(sizeof(struct s_ref) * nb_array);
	ft_bzero(obj->ref, sizeof(struct s_ref) * nb_array);
}

void	handle_mtllib(char *line, t_obj *obj)
{
	char	*file;
	size_t 	size;
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

void	handle_usemtl(char *line, t_obj *obj)
{
	char	*tmp;

	debut_handle(&line, obj, 6);
	tmp = ft_strndup(line, find_next_line(line));
	obj->mtls[obj->mtl_curr].index = obj->faces_curr;
	obj->mtls[obj->mtl_curr].ref = tmp;
	obj->mtl_curr++;
	return ;
}

void	handle_s(char *line, t_obj *ret)
{
	//ignore;
	(void)line;
	(void)ret;
}

void	handle_g(char *line, t_obj *ret)
{
	//ignore;
	(void)line;
	(void)ret;
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

void parse_line(char *line, t_obj *ret)
{
	int	i;

	ignore_whitespaces(&line);
	if (line[0] == '\0')
		return ;
	i = 0;
	while (obj_parsing[i].name)
	{
		if (ft_strncmp(line, obj_parsing[i].name, ft_strlen(obj_parsing[i].name)) == 0)
			return (obj_parsing[i].f(line, ret));
		i++;
	}
	ret->error = 1;
}

void	fill_mtl(t_obj *obj)
{
	uint i;
	uint j;

	i = 0;
	while (i < obj->mtl_nbr)
	{
		j = 0;
		while (j < obj->ref_nbr)
		{
			if (!ft_strcmp(obj->ref[j].ref, obj->mtls[i].ref))
				obj->mtls[i].img_file = obj->ref[j].img;
			j++;
		}
		i++;
	}
}

void	init_obj(t_obj *obj)
{
	uint		i;
	uint		j;
	int		curr;
	uint	count;

	i = 0;
	curr = 0;
	count = 0;
	obj->points = malloc(sizeof(struct s_point) * obj->indices_nbr);
	obj->indices = malloc(sizeof(uint) * obj->indices_nbr);
	obj->counts = malloc(sizeof(GLsizei) * obj->faces_nbr);
	obj->offset = malloc(sizeof(GLvoid *) * obj->faces_nbr);
	while (i < obj->faces_nbr)
	{
		j = 0;
		while (j < obj->faces[i].v_nbr)
		{
			obj->indices[curr] = curr;
			obj->points[curr].vertex = obj->vertices[obj->faces[i].v_index[j]];
			if (obj->faces[i].vt_index[j] == -1)
				obj->points[curr].tex_vertex = (t_vec2){0, 0};
			else
				obj->points[curr].tex_vertex = obj->tex_vertices[obj->faces[i].vt_index[j]];
			if (obj->faces[i].vn_index[j] == -1)
				obj->points[curr].normal = (t_vec3){0, 0, 0};
			else
				obj->points[curr].normal = obj->normales[obj->faces[i].vn_index[j]];
			obj->points[curr].rand = (float)rand() / RAND_MAX;
			j++;
			curr++;
		}
		obj->counts[i] = j;
		obj->offset[i] = (GLvoid *)(count * sizeof(unsigned int));
		i++;
		count += j;
	}
	fill_mtl(obj);
}

int	init_path(char *param, t_obj *obj)
{
	int c;
	int	end;

	c = 0;
	if (param)
	{
		end = 0;
		while (param[c])
		{
			if (param[c] == '/' && (c == 0 || param[c - 1] != '\\'))
				end = c;
			c++;
		}
		if (!(obj->path = malloc(end + 2)))
			return (0);
		if (end != 0)
			end++;
		ft_strncpy(obj->path, param, end);
	}
	return (1);
}

t_obj	obj_parser_main(char *file)
{
	int		fd;
	char	*line;
	t_obj	ret;
	int		i;

	ft_bzero(&ret, sizeof(t_obj));
	if (!init_path(file, &ret))
	{
		ret.error = 1;
		return (ret);
	}
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		dprintf(2, "Error OBJ file not found\n");
		ret.error = 1;
		return (ret);
	}
	while (get_next_line(fd, &line) > 0)
	{
		i = ignore_whitespaces(&line);
		if (*line == 'f')
			ret.faces_nbr++;
		else if (*line == 'v' && *(line + 1) == 't')
			ret.tex_vertices_nbr++;
		else if (*line == 'v' && *(line + 1) == 'n')
			ret.normales_nbr++;
		else if (*line == 'v')
			ret.vertices_nbr++;
		else if (!ft_strncmp(line, "usemtl", 6))
			ret.mtl_nbr++;
		free(line - i);
	}
	ret.mtls = malloc(sizeof(struct s_mtl) * ret.mtl_nbr);
	ft_bzero(ret.mtls, sizeof(struct s_mtl) * ret.mtl_nbr);
	ret.faces = malloc(sizeof(struct s_face) * ret.faces_nbr);
	ret.tex_vertices = malloc(sizeof(t_vec3) * ret.tex_vertices_nbr);
	ret.normales = malloc(sizeof(t_vec3) * ret.normales_nbr);
	ret.vertices = malloc(sizeof(t_vec3) * ret.vertices_nbr);
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		dprintf(2, "Error OBJ file not found\n");
		ret.error = 1;
		return (ret);
	}
	while (get_next_line(fd, &line) > 0)
	{
		// printf("Voici la liggne : %s\n", line);
		parse_line(line, &ret);
		if (ret.error)
		{
			printf("(line = %s)\n", line);
			dprintf(2, "ERROR !\n");
			printf("[%s]\n", ret.name);
			return (ret);
		}
		free(line);
	}
	init_obj(&ret);
	// printf("[%s]\n", ret.name);
	return (ret);
}
