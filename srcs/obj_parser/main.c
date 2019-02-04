#include <scop.h>
#include <fcntl.h>

static struct s_obj_parsing obj_parsing[] = {
	{"mtllib", handle_mtllib},
	{"usemtl", handle_usemtl},
	{"s", handle_s},
	{"o", handle_o},
	{"vn", handle_vn},
	{"v", handle_v},
	{"f", handle_f},
	{NULL, NULL}
};


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

void	handle_usemtl(char *line, t_obj *ret)
{
	//ignore;
	(void)line;
	(void)ret;
}

void	handle_s(char *line, t_obj *ret)
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
	printf("handling line : [%s]\n", line);
	i = 0;
	while (obj_parsing[i].name)
	{
		if (ft_strncmp(line, obj_parsing[i].name, ft_strlen(obj_parsing[i].name)) == 0)
			return (obj_parsing[i].f(line, ret));
		i++;
	}
	ret->error = 1;
}

void	init_obj(t_obj *obj)
{
	int		i;
	int		j;
	int		curr;
	uint	count;

	i = 0;
	curr = 0;
	count = 0;
	printf("ON A : %u\n", obj->indices_nbr);

	obj->indices = malloc(sizeof(unsigned int) * obj->indices_nbr);
	obj->counts = malloc(sizeof(GLsizei) * obj->faces_nbr);
	obj->offset = malloc(sizeof(GLvoid *) * obj->faces_nbr);
	while (i < obj->faces_nbr)
	{
		j = 0;
		while (j < obj->faces[i].v_nbr)
		{
			obj->indices[curr] = obj->faces[i].v_index[j];
			printf("%d: indice add %d\n", curr, obj->indices[curr]);
			j++;
			curr++;
		}
		obj->counts[i] = j;
		obj->offset[i] = (GLvoid *)(count * sizeof(unsigned int));
		printf("count add %d\n",obj->counts[i]);
		i++;
		count += j;
	}
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
	init_obj(&ret);
	printf("[%s]\n", ret.material);
	printf("[%s]\n", ret.name);
	return (ret);
}
