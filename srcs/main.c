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

struct s_key_event g_keys[] = {
	{GLFW_KEY_G, NULL},
	{GLFW_KEY_T, t},
	{GLFW_KEY_V, v},
	{GLFW_KEY_O, o},
	{GLFW_KEY_F, NULL},
	{GLFW_KEY_ESCAPE, echap},
	{GLFW_KEY_0, key_0},
	{GLFW_KEY_1, key_1},
	{GLFW_KEY_2, key_2},
	{GLFW_KEY_3, key_3},
	{GLFW_KEY_4, key_4},
	{GLFW_KEY_5, key_5},
	{GLFW_KEY_6, key_6},
	{GLFW_KEY_7, key_7},
	{GLFW_KEY_8, key_8},
	{GLFW_KEY_9, key_9},
	{GLFW_KEY_MINUS, minus},
	{GLFW_KEY_EQUAL, equal},
	{GLFW_KEY_W, w},
	{GLFW_KEY_S, s},
	{GLFW_KEY_A, a},
	{GLFW_KEY_D, d},
	{GLFW_KEY_R, r},
	{GLFW_KEY_UP, key_up},
	{GLFW_KEY_DOWN, key_down},
	{GLFW_KEY_RIGHT, key_right},
	{GLFW_KEY_LEFT, key_left}};

void	key_event(t_d *data, uint delta, t_obj *objs)
{
	uint		i;
	static char	*prev;

	if (!prev)
	{
		prev = malloc(sizeof(g_keys) / sizeof(struct s_key_event));
		ft_bzero(prev, sizeof(g_keys) / sizeof(struct s_key_event));
	}
	i = 0;
	while (i < sizeof(g_keys) / sizeof(struct s_key_event))
	{
		if (glfwGetKey(data->window, g_keys[i].key) && g_keys[i].func)
			g_keys[i].func(data, objs, delta, prev);
		prev[i] = glfwGetKey(data->window, g_keys[i].key);
		i++;
	}
	ft_mat4x4_to_float_array(data->cam.view_f, data->cam.view);
}

void	rotation_cam(t_d *data, uint delta)
{
	double			x;
	double			y;
	static t_vec2	last = {0, 0};
	float			rotx;
	t_vec3			tmp;

	glfwGetCursorPos(data->window, &x, &y);
	data->angle_y += (y - last.y) * delta / 1000;
	rotx = (last.x - x);
	data->dir = ft_vec3_rotate(data->dir, rotx * delta / 1000,
		(t_vec3){0, 1, 0});
	tmp = (t_vec3){data->dir.x, 0, data->dir.z};
	ft_vec3_normalize(&tmp);
	if (data->angle_y < 90 && data->angle_y > -90)
		data->dir = ft_vec3_rotate(tmp, data->angle_y, ft_vec3_cross(data->dir,
			(t_vec3){0, 1, 0}));
	else
		data->angle_y = data->angle_y >= 90 ? 90 : -90;
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye,
		data->dir), data->cam.up);
	last.y = y;
	last.x = x;
}

void	update_time(t_d *data, t_obj *objs, uint *delta, struct timeval *tp)
{
	static uint				last = 0;

	*delta = (tp->tv_sec * 1000 + tp->tv_usec / 1000) - last;
	last = (tp->tv_sec * 1000 + tp->tv_usec / 1000);
	init_frame(data, *delta, objs);
}

void	update_frame(t_d *data, t_obj *objs, uint *texs)
{
	uint					x;
	uint					delta;
	static struct timeval	tp = {0, 0};
	size_t					i;
	static float			angle = 0;

	update_time(data, objs, &delta, &tp);
	x = 1;
	i = -1;
	while (++i < data->object_nbr)
	{
		objs[i].texfade += objs[i].texon ? ((1 / 1.5) * delta / 1000.0)
			: -((1 / 1.5) * delta / 1000.0);
		fclamp(&objs[i].texfade, 0, 1);
		draw_obj(&objs[i], angle, &x, texs);
		glDisable(GL_PRIMITIVE_RESTART);
		glBindVertexArray(0);
	}
	angle += 90 * delta / 1000.0;
	glfwPollEvents();
	glfwSwapBuffers(data->window);
	gettimeofday(&tp, NULL);
}

int		main(int ac, char **av)
{
	t_d				data;
	t_obj			*objs;
	uint			*texs;
	size_t			i;

	init_all(&data);
	objs = get_all_obj(&data, ac, av);
	if (!objs || objs[0].error || !init_shaders(&data, "./srcs/shaders/couleur\
2D.frag", "./srcs/shaders/couleur2D.vert") || !(
	data.program = create_and_link_program(data.vertex_sh, data.fragment_sh)))
		return (1);
	texs = init_texs(&data, objs);
	init_uniform_data(&data);
	i = -1;
	while (++i < data.object_nbr)
	{
		init_vao(&objs[i]);
		init_uniform_obj(&data, &objs[i]);
	}
	while (!glfwWindowShouldClose(data.window))
		update_frame(&data, objs, texs);
	glfwTerminate();
	return (0);
}
