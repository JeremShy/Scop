#include <scop.h>
#include <cglm/cglm.h>

void	echap(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	glfwSetWindowShouldClose(data->window, true);
}

void	key_0(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	data->current = NULL;
}

void	key_1(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 0)
		data->current = &objs[0];
}

void	key_2(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 1)
		data->current = &objs[1];
}

void	key_3(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 2)
		data->current = &objs[2];
}

void	key_4(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 3)
		data->current = &objs[3];
}

void	key_5(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 4)
		data->current = &objs[4];
}

void	key_6(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 5)
		data->current = &objs[5];
}

void	key_7(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 6)
		data->current = &objs[6];
}

void	key_8(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 7)
		data->current = &objs[7];
}

void	key_9(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (data->object_nbr > 8)
		data->current = &objs[8];
}

void	equal(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (prev[F_OFFSET])
	{
		if (data->current)
		{
			data->current->scale *= 1.01;
		}
	}
	else
		data->depl *= 1.01;
}

void	minus(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (prev[F_OFFSET])
	{
		if (data->current)
		{
			data->current->scale *= 1 / 1.01;
		}
	}
	else
		data->depl /= 1.01;
}

void	w(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	transl = ft_vec3_scalar_mult(data->dir, -data->depl * delta / 1000);
	data->eye = ft_vec3_add(data->eye, transl);
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye,
		data->dir), data->cam.up);
}

void	s(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	transl = ft_vec3_scalar_mult(data->dir, data->depl * delta / 1000);
	data->eye = ft_vec3_add(data->eye, transl);
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye,
		data->dir), data->cam.up);
}

void	a(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	transl = ft_vec3_cross(data->dir, (t_vec3){0, 1, 0});
	ft_vec3_normalize(&transl);
	transl = ft_vec3_scalar_mult(transl, data->depl * delta / 1000);
	data->eye = ft_vec3_add(data->eye, transl);
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye,
		data->dir), data->cam.up);
}

void	d(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	transl = ft_vec3_cross(data->dir, (t_vec3){0, 1, 0});
	ft_vec3_normalize(&transl);
	transl = ft_vec3_scalar_mult(transl, -data->depl * delta / 1000);
	data->eye = ft_vec3_add(data->eye, transl);
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye,
		data->dir), data->cam.up);
}

void	t(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (prev[T_OFFSET])
		return ;
	if (data->current)
		data->current->texOn ^= 1;
}

void	r(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	data->eye = (t_vec3){0, 0, -10};
	data->dir = (t_vec3){0, 0, -1};
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye,
		data->dir), data->cam.up);
	data->angle_y = 0;
}

void	v(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (prev[V_OFFSET])
		return ;
	!data->drawing_mode ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) :
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	data->drawing_mode = !data->drawing_mode;
}

void	o(t_d *data, t_obj *objs, uint delta, char *prev)
{
	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (prev[O_OFFSET])
		return ;
	if (data->current)
		data->current->rotOn ^= 1;
}

void	key_up(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (!prev[G_OFFSET])
		return ;
	if (!data->current)
		return ;
	transl = ft_vec3_cross(data->dir, ft_vec3_cross(data->dir, data->cam.up));
	ft_vec3_normalize(&transl);
	transl = ft_vec3_scalar_mult(transl, -data->depl * delta / 1000);
	data->current->pos = ft_vec3_add(data->current->pos, transl);
}

void	key_down(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (!prev[G_OFFSET])
		return ;
	if (!data->current)
		return ;
	transl = ft_vec3_cross(data->dir, ft_vec3_cross(data->dir, data->cam.up));
	ft_vec3_normalize(&transl);
	transl = ft_vec3_scalar_mult(transl, data->depl * delta / 1000);
	data->current->pos = ft_vec3_add(data->current->pos, transl);
}

void	key_right(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (!prev[G_OFFSET])
		return ;
	if (!data->current)
		return ;
	transl = ft_vec3_cross(data->dir, data->cam.up);
	ft_vec3_normalize(&transl);
	transl = ft_vec3_scalar_mult(transl, -data->depl * delta / 1000);
	data->current->pos = ft_vec3_add(data->current->pos, transl);
}

void	key_left(t_d *data, t_obj *objs, uint delta, char *prev)
{
	t_vec3	transl;

	(void)data;
	(void)objs;
	(void)delta;
	(void)prev;
	if (!prev[G_OFFSET])
		return ;
	if (!data->current)
		return ;
	transl = ft_vec3_cross(data->dir, data->cam.up);
	ft_vec3_normalize(&transl);
	transl = ft_vec3_scalar_mult(transl, data->depl * delta / 1000);
	data->current->pos = ft_vec3_add(data->current->pos, transl);
}
