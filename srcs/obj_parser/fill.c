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

void		fill_ref(t_obj *obj, char *file, size_t size)
{
	char	*tmp;
	int		nb_array;

	nb_array = -1;
	while (size > 0)
	{
		size -= ignore_whitespaces(&file);
		if (size > 6 && !ft_strncmp(file, "newmtl", 6))
		{
			size -= 6;
			debut_handle(&file, obj, 6);
			obj->ref[++nb_array].ref = ft_strndup(file, find_next_line(file));
		}
		else if (size > 6 && !ft_strncmp(file, "map_Kd", 6))
		{
			size -= 6;
			debut_handle(&file, obj, 6);
			if ((size_t)(ft_strstr(file, ".bmp") - file) == ft_strlen(file))
				obj->error = 1;
			tmp = ft_strndup(file, ft_strstr(file, ".bmp") - file + 4);
			obj->ref[nb_array].img = ft_strjoin(obj->path, tmp);
			free(tmp);
		}
		next_line(&file, &size);
	}
}

void		create_ref(t_obj *obj, char *file, size_t size)
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

void		fill_mtl(t_obj *obj)
{
	uint	i;
	uint	j;

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

void		fill_point_from_face(t_obj *obj, uint i, int *curr)
{
	uint j;

	j = 0;
	while (j < obj->faces[i].v_nbr)
	{
		obj->indices[*curr] = *curr;
		obj->points[*curr].vertex = obj->vertices[obj->faces[i].v_index[j]];
		obj->points[*curr].normal = (t_vec3){0, 0, 0};
		obj->points[*curr].tex_vertex = (t_vec2){0, 0};
		if (obj->faces[i].vt_index[j] != -1)
			obj->points[*curr].tex_vertex = obj->tex_vertices[obj->
				faces[i].vt_index[j]];
		if (obj->faces[i].vn_index[j] != -1)
			obj->points[*curr].normal = obj->normales[obj->
				faces[i].vn_index[j]];
		obj->points[*curr].rand = (float)rand() / RAND_MAX;
		j++;
		(*curr)++;
	}
	obj->counts[i] = j;
}
