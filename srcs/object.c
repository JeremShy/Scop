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

t_obj	*get_all_obj(t_d *data, int ac, char **av)
{
	t_obj	*objs;
	uint	i;
	uint	j;

	if (ac == 1)
		return (NULL);
	objs = malloc(sizeof(t_obj) * (ac - 1));
	data->texture_nbr = 1;
	i = 0;
	while (*(++av))
	{
		objs[i] = obj_parser_main(*av);
		objs[i].scale = 1;
		j = -1;
		while (++j < objs[i].mtl_nbr)
			if (objs[i].mtls[j].img_file)
			{
				objs[i].textures_nbr++;
				data->texture_nbr++;
			}
		if (!objs[i].error)
			i++;
	}
	data->object_nbr = i;
	return (objs);
}

void	get_glteximage(uint *texs, uint *i_tex, t_d *data, char *file)
{
	glBindTexture(GL_TEXTURE_2D, texs[*i_tex]);
	create_image_from_png(data, *i_tex, file);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->imgs[*i_tex].w, data->imgs
		[*i_tex].h, 0, GL_BGRA, GL_UNSIGNED_BYTE, data->imgs[*i_tex].data);
	glGenerateMipmap(GL_TEXTURE_2D);
	(*i_tex)++;
}

uint	*init_texs(t_d *data, t_obj *objs)
{
	uint	*texs;
	uint	i_tex;
	uint	i;
	uint	j;

	data->imgs = malloc(sizeof(t_img) * data->texture_nbr);
	texs = malloc(sizeof(uint) * data->texture_nbr);
	glGenTextures(data->texture_nbr, texs);
	i = -1;
	i_tex = 0;
	get_glteximage(texs, &i_tex, data, "./textures/kitten.png");
	while (++i < data->object_nbr)
	{
		j = -1;
		while (++j < objs[i].mtl_nbr)
		{
			objs[i].texon = 1;
			if (objs[i].mtls[j].img_file)
				get_glteximage(texs, &i_tex, data, objs[i].mtls[j].img_file);
		}
	}
	return (texs);
}

void	draw_part_obj(t_obj *obj, uint *x, uint *texs)
{
	uint	y;
	int		nb_face;

	y = 0;
	while (y < obj->mtl_nbr)
	{
		if (y + 1 == obj->mtl_nbr)
			nb_face = obj->faces_nbr - obj->mtls[y].index;
		else
			nb_face = obj->mtls[y + 1].index - obj->mtls[y].index;
		if (obj->mtls[y].img_file)
		{
			glBindTexture(GL_TEXTURE_2D, texs[*x]);
			(*x)++;
		}
		else
			glBindTexture(GL_TEXTURE_2D, texs[0]);
		glMultiDrawElements(GL_TRIANGLE_FAN, &(obj->counts[obj->mtls[y].
		index]), GL_UNSIGNED_INT, (const GLvoid *const *)(&(obj->offset[
		obj->mtls[y].index])), nb_face);
		y++;
	}
}

void	draw_obj(t_obj *obj, float angle, uint *x, uint *texs)
{
	glUniform1i(obj->texonloc, obj->texon);
	glUniform1i(obj->deftex, obj->textures_nbr == 0 ? 1 : 0);
	glBindVertexArray(obj->gl_buff.vao);
	ft_mat4x4_set_translation(obj->model, obj->pos);
	ft_mat4x4_translate(obj->model,
		ft_vec3_scalar_mult(obj->mid, -obj->scale));
	if (obj->roton)
		ft_mat4x4_rotate(obj->model, angle, (t_vec3){0, 1, 0});
	ft_mat4x4_translate(obj->model, ft_vec3_scalar_mult(obj->mid, obj->scale));
	ft_mat4x4_scale(obj->model, (t_vec3){obj->scale, obj->scale, obj->scale});
	ft_mat4x4_to_float_array(obj->model_f, obj->model);
	glUniformMatrix4fv(obj->modelloc, 1, GL_FALSE, obj->model_f);
	if (!obj->mtl_nbr)
	{
		glBindTexture(GL_TEXTURE_2D, texs[0]);
		glMultiDrawElements(GL_TRIANGLE_FAN, obj->counts, GL_UNSIGNED_INT,
			(const GLvoid *const *)obj->offset, obj->faces_nbr);
	}
	else
		draw_part_obj(obj, x, texs);
}
