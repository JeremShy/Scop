#include <scop.h>

static void		copy_ret_in_obj(uint ret[3], t_obj *obj)
{
	struct s_face	*face;

	if (ret[0] == 0)
		obj->error = 1;
	else if (ret[0] > obj->vertices_nbr || ret[1] > obj->tex_vertices_nbr
		|| ret[2] > obj->normales_nbr)
		obj->error = 1;
	face = &obj->faces[obj->faces_curr];
	face->v_index[face->v_nbr] = ret[0] - 1;
	face->vt_index[face->v_nbr] = ret[1] - 1;
	face->vn_index[face->v_nbr] = ret[2] - 1;
	face->v_nbr++;
	obj->indices_nbr++;
	if (face->v_nbr > MAX_VERTICES_FACE)
		obj->error = 1;
}

static	int		move_str_ptr(char **str)
{
	while ((**str >= '0' && **str <= '9') || **str == '-' || **str == '+')
		(*str)++;
	if (is_whitespace(**str))
		return (2);
	if (**str == '/')
		(*str)++;
	if ((**str >= '0' && **str <= '9') || **str == '-' || **str == '+' ||
		!**str || **str == '/')
		return (0);
	return (1);
}

static int		parse_indexes(int ret[3], int i, char **line, t_obj *obj)
{
	ret[i] = ft_atoi(*line);
	if (ret[i] < 0)
	{
		if (i == 0)
			ret[i] = obj->vertices_curr + ret[i] + 1;
		if (i == 1)
			ret[i] = obj->tex_vertices_curr + ret[i] + 1;
		if (i == 2)
			ret[i] = obj->normales_curr + ret[i] + 1;
	}
	return (move_str_ptr(line));
}

static uint8_t	fill_data_point(char **line, t_obj *obj)
{
	int ret[3];
	int i;
	int tmp;

	i = 0;
	ignore_whitespaces(line);
	if (obj->error || !(**line))
		return (0);
	ft_bzero(ret, sizeof(ret));
	while (i < 3 && **line)
	{
		tmp = parse_indexes(ret, i, line, obj);
		if (tmp == 1)
		{
			obj->error = 1;
			return (0);
		}
		if (tmp == 2)
			break ;
		i++;
	}
	copy_ret_in_obj((uint *)ret, obj);
	return (!obj->error);
}

void			handle_f(char *line, t_obj *ret)
{
	debut_handle(&line, ret, 1);
	if (ret->error)
		return ;
	ret->faces[ret->faces_curr].v_nbr = 0;
	while (fill_data_point(&line, ret))
		;
	ret->faces_curr++;
}
