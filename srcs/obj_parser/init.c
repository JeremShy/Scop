#include <scop.h>

void		init_obj(t_obj *obj)
{
	uint		i;
	int			curr;
	uint		count;

	i = 0;
	curr = 0;
	count = 0;
	obj->points = malloc(sizeof(struct s_point) * obj->indices_nbr);
	obj->indices = malloc(sizeof(uint) * obj->indices_nbr);
	obj->counts = malloc(sizeof(GLsizei) * obj->faces_nbr);
	obj->offset = malloc(sizeof(GLvoid *) * obj->faces_nbr);
	while (i < obj->faces_nbr)
	{
		fill_point_from_face(obj, i, &curr);
		obj->offset[i] = (GLvoid *)(count * sizeof(unsigned int));
		count += obj->counts[i];
		i++;
	}
	fill_mtl(obj);
}

int			init_path(char *param, t_obj *obj)
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

void		init_malloc(t_obj *ret, char *file)
{
	get_values_for_malloc(ret, file);
	ret->mtls = malloc(sizeof(struct s_mtl) * ret->mtl_nbr);
	ft_bzero(ret->mtls, sizeof(struct s_mtl) * ret->mtl_nbr);
	ret->faces = malloc(sizeof(struct s_face) * ret->faces_nbr);
	ret->tex_vertices = malloc(sizeof(t_vec3) * ret->tex_vertices_nbr);
	ret->normales = malloc(sizeof(t_vec3) * ret->normales_nbr);
	ret->vertices = malloc(sizeof(t_vec3) * ret->vertices_nbr);
}
