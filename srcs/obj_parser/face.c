#include <scop.h>

static void		copy_ret_in_obj(uint ret[3], t_obj *obj)
{
	struct s_face	*face;

	if (ret[0] == 0)
		obj->error = 1;
	else if (ret[0] > obj->vertices_nbr || ret[1] > obj->tex_vertices_nbr || ret[2] > obj->normales_nbr)
		obj->error = 1;
	face = &obj->faces[obj->faces_curr];
	face->v_index[face->v_nbr] = ret[0] - 1;
	face->t_index[face->v_nbr] = ret[1] - 1;
	face->vn_index[face->v_nbr] = ret[2] - 1;
	face->v_nbr++;
	obj->indices_nbr++;
	if (face->v_nbr > MAX_VERTICES_FACE)
		obj->error = 1;
}

static uint8_t	fill_data_point(char **line, t_obj *obj)
{
	uint ret[3];
	int i;

	i = 0;
	t_vec3	v;

	ignore_whitespaces(line);
	if (obj->error || !(**line))
		return (0);
	ft_bzero(ret, sizeof(ret));
	while ((**line >= '0' && **line <= '9') || **line == '/')
	{
		if (**line == '/')
		{
			i++;
			if (i > 2)
			{
				obj->error = 1;
				printf("return 0 nbr 0\n");
				return (0);
			}
			(*line)++;
			continue ;
		}
		ret[i] *= 10;
		ret[i] += **line - '0';
		(*line)++;
	}
	copy_ret_in_obj(ret, obj);
	if (obj->error)
	{
		printf("return 0 nbr 1\n");
		return (0);
	}
	return(1);
}

void	handle_f(char *line, t_obj *ret)
{
	debut_handle(&line, ret, 1);
	if (ret->error)
		return ;
	ret->faces[ret->faces_curr].v_nbr = 0;
	while (fill_data_point(&line, ret))
		;
	ret->faces_curr++;
}

// a/b/c
// a
// a/b
// a//c
