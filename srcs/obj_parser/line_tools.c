#include <scop.h>

static struct s_obj_parsing g_obj_parsing[] = {
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

void		debut_handle(char **line, t_obj *ret, int size)
{
	*line += size;
	ignore_whitespaces(line);
	if (*line[0] == '\0')
	{
		ret->error = 1;
		return ;
	}
}

void		next_line(char **file, size_t *size)
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

void		parse_line(char *line, t_obj *ret)
{
	int	i;

	ignore_whitespaces(&line);
	if (line[0] == '\0')
		return ;
	i = 0;
	while (g_obj_parsing[i].name)
	{
		if (ft_strncmp(line, g_obj_parsing[i].name, ft_strlen(
			g_obj_parsing[i].name)) == 0)
			return (g_obj_parsing[i].f(line, ret));
		i++;
	}
	ret->error = 1;
}
