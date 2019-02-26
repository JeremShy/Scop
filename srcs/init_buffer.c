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

void	init_vbo(t_obj *obj)
{
	struct s_point	point;

	glBindBuffer(GL_ARRAY_BUFFER, obj->gl_buff.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct s_point) * obj->indices_nbr,
		obj->points, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct s_point),
		(GLvoid *)((void *)&point.vertex - (void *)&point));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(struct s_point),
		(GLvoid *)((void *)&point.tex_vertex - (void *)&point));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(struct s_point),
		(GLvoid *)((void *)&point.rand - (void *)&point));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(struct s_point),
		(GLvoid *)((void *)&point.normal - (void *)&point));
	glEnableVertexAttribArray(3);
}

void	init_vao(t_obj *obj)
{
	glGenVertexArrays(1, &obj->gl_buff.vao);
	glGenBuffers(1, &obj->gl_buff.ebo);
	glGenBuffers(1, &obj->gl_buff.vbo);
	glBindVertexArray(obj->gl_buff.vao);
	init_vbo(obj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->gl_buff.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(obj->indices[0])
		* obj->indices_nbr, obj->indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	init_uniform_data(t_d *data)
{
	data->eye = (t_vec3){0, 0, -10};
	data->dir = (t_vec3){0, 0, -1};
	data->cam.up = (t_vec3){0, 1, 0};
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye,
		data->dir), data->cam.up);
	ft_mat4x4_to_float_array(data->cam.view_f, data->cam.view);
	ft_mat4x4_set_projection(data->cam.proj, (float[]){45, (float)data->width
		/ data->height, .1f, 1000.0f});
	ft_mat4x4_to_float_array(data->cam.proj_f, data->cam.proj);
	data->viewloc = glGetUniformLocation(data->program, "view");
	data->projloc = glGetUniformLocation(data->program, "projection");
	data->ambloc = glGetUniformLocation(data->program, "ambientStrength");
	data->eyeloc = glGetUniformLocation(data->program, "viewPos");
	data->lightloc = glGetUniformLocation(data->program, "lightPos");
	data->lightcolorloc = glGetUniformLocation(data->program, "lightColor");
}

void	init_uniform_obj(t_d *data, t_obj *obj)
{
	obj->mid = ft_vec3_scalar_mult(ft_vec3_add(obj->min, obj->max), -0.5);
	ft_mat4x4_to_float_array(obj->model_f, obj->model);
	obj->modelloc = glGetUniformLocation(data->program, "model");
	obj->texonloc = glGetUniformLocation(data->program, "texOn");
	obj->deftex = glGetUniformLocation(data->program, "defTex");
}

void	init_frame(t_d *data, uint delta, t_obj *objs)
{
	key_event(data, delta, objs);
	rotation_cam(data, delta);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(data->program);
	glActiveTexture(GL_TEXTURE0);
	glUniformMatrix4fv(data->viewloc, 1, GL_FALSE, data->cam.view_f);
	glUniformMatrix4fv(data->projloc, 1, GL_FALSE, data->cam.proj_f);
	glUniform1f(data->ambloc, data->ambient);
	glUniform4f(data->viewloc, data->eye.x, data->eye.y, data->eye.z, 1.0);
	glUniform4f(data->lightloc, data->lightpos.x, data->lightpos.y,
		data->lightpos.z, 1.0);
	glUniform4f(data->lightcolorloc, data->lightcolor.x, data->lightcolor.y,
		data->lightcolor.z, 0.0);
}
