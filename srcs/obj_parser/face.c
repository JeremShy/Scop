#include <scop.h>

static void		copy_ret_in_obj(uint ret[3], t_obj *obj)
{
	struct s_face	*face;

	printf("Trying to copy ret = {%u, %u, %u} in v_nbr : %d\n", ret[0], ret[1], ret[2], obj->faces[obj->faces_nbr].v_nbr);

	if (ret[0] == 0)
		obj->error = 1;
	else if (ret[0] > obj->vertices_nbr || ret[1] > obj->tex_vertices_nbr || ret[2] > obj->normales_nbr)
		obj->error = 1;
	face = &obj->faces[obj->faces_nbr];
	face->v_index[face->v_nbr] = ret[0];
	face->v_index[face->v_nbr] = ret[1];
	face->v_index[face->v_nbr] = ret[2];
	face->v_nbr++;
	if (face->v_nbr > MAX_VERTICES_FACE)
		obj->error = 1;
}

static uint8_t	fill_data_point(char **line, t_obj *obj)
{
	uint ret[3];
	int i;

	i = 0;
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
	if (**line == ' ')
	{
		printf("return 1 nbr 0\n");
		return (1);
	}
	else if (**line != '#' && **line != '\n' && **line != '\0')
		obj->error = 1;
	printf("return 0 nbr 2\n");
	return (0);
}

void	handle_f(char *line, t_obj *ret)
{
	printf("In handle_f, handling face nbr %d\n", ret->faces_nbr);
	debut_handle(&line, ret, 1);
	if (ret->error)
		return ;
	while (fill_data_point(&line, ret))
		;
	ret->faces_nbr++;
}

// a/b/c
// a
// a/b
// a//c
