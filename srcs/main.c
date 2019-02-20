#include <scop.h>
#include <cglm/cglm.h>   /* for inline */

#define STB_IMAGE_IMPLEMENTATION

struct s_key_event keys[] = {	
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
	{GLFW_KEY_LEFT, key_left},
								};

int8_t	init_data(t_d *data)
{
	ft_bzero(data, sizeof(t_d));
	data->depl = 1;
	data->ambient = 1;
	return (1);
}

void	error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s - errno = %d\n", description, error);
}

// void	resize_callback(GLFWwindow* window, int width, int height)
// {
// 	(void)window;
// 	printf("Resized : %d - %d\n", width, height);
// 	ft_mat4x4_set_projection(data.cam.proj, (float[]){45, (float)data.width / data.height, .1f, 1000.0f});
// 	glViewport(0, 0, width, height);
// 	// TODO : Reset matrix
// }

int8_t	init_glfw(t_d *data)
{
	if (!glfwInit())
		return (0);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 3);
	glfwSetErrorCallback(error_callback);

	data->window = glfwCreateWindow(1600, 900, "Hello World", NULL, NULL);
	if (!data->window)
	{
		glfwTerminate();
		return (0);
	}
	glfwSetInputMode(data->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glfwSetFramebufferSizeCallback(data->window, resize_callback);
	glfwMakeContextCurrent(data->window);
	glfwGetWindowSize(data->window, &data->width, &data->height);
	printf("Window size : %d - %d\n", data->width, data->height);
	// glViewport(0, 0, data->width, data->height);
	return (1);
}

int8_t	init_all(t_d *data)
{
	if (!init_data(data))
		return (0);
	if (!init_glfw(data))
		return (0);

	glEnable(GL_MULTISAMPLE); 
	glEnable(GL_DEPTH_TEST); 
	return (1);
}

int8_t    init_shaders(t_d *data, const char *frag, const char *vert)
{
	if (!(data->vertex_sh = create_and_compile_shader(vert, GL_VERTEX_SHADER)))
	{
		dprintf(2, "Error while trying to create vertex shader.\n");
		return (0);
	}
 	if (!(data->fragment_sh = create_and_compile_shader(frag, GL_FRAGMENT_SHADER)))
	{
		dprintf(2, "Error while trying to create fragment shader.\n");
		return (0);
	}
	return (1);
}



void	key_event(t_d *data, uint delta, t_obj *objs)
{
	// t_mat4x4 rotation;
	uint			i;
	static char *prev;

	if (!prev)
	{
		prev = malloc(sizeof(keys) / sizeof(struct s_key_event));
		ft_bzero(prev, sizeof(keys) / sizeof(struct s_key_event));
	}
	i = 0;
	while (i < sizeof(keys) / sizeof(struct s_key_event))
	{
		if (glfwGetKey(data->window, keys[i].key) && keys[i].func)
			keys[i].func(data, objs, delta, prev);
		prev[i] = glfwGetKey(data->window, keys[i].key);
		i++;
	}
	ft_mat4x4_to_float_array(data->cam.view_f, data->cam.view);
}

void rotation_cam(t_d *data, uint delta)
{
	double			x;
	double			y;
	static double	last_x = 0;
	static double	last_y = 0;
	float			rotx;
	t_vec3			tmp;

	glfwGetCursorPos(data->window, &x, &y);
	data->angle_y += (y - last_y) * delta / 1000;
	rotx = (last_x - x);
	data->dir = ft_vec3_rotate(data->dir, rotx * delta / 1000, (t_vec3){0, 1, 0});
	tmp = (t_vec3){data->dir.x, 0, data->dir.z};
	ft_vec3_normalize(&tmp);
	if (data->angle_y < 90 && data->angle_y > -90)
		data->dir = ft_vec3_rotate(tmp, data->angle_y, ft_vec3_cross(data->dir, (t_vec3){0, 1, 0}));
	else
		data->angle_y = data->angle_y >= 90 ? 90 : -90;
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);
	last_y = y;
	last_x = x;
}

t_obj*	get_all_obj(t_d *data, int ac, char **av)
{
	t_obj*			objs;
	uint i;
	uint j;

	objs = malloc(sizeof(t_obj) * (ac - 1));
	data->texture_nbr = 1;
	av++;
	i = 0;
	while (*av)
	{
		objs[i] = obj_parser_main(*av);
		objs[i].scale = 1;
		j = 0;
		printf("obj #%d :\n\tname = %s\n", i, objs[i].name);
		while (j < objs[i].mtl_nbr)
		{
			if (objs[i].mtls[j].img_file)
			{
				objs[i].textures_nbr++;
				data->texture_nbr++;
			}
			printf("\tmtls[%d].ref = %s\n", j, objs[i].mtls[j].ref);
			printf("\tmtls[%d].img_file = %s\n", j, objs[i].mtls[j].img_file);
			printf("\tmtls[%d].index = %d\n", j, objs[i].mtls[j].index);
			j++;
		}
		if (!objs[i].error)
			i++;
		av++;
	}
	data->object_nbr = i;
	return (objs);
}

void init_vbo(t_obj *obj)
{
	glBindBuffer(GL_ARRAY_BUFFER, obj->gl_buff.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct s_point) * obj->indices_nbr, obj->points, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct s_point), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(struct s_point), (void*)sizeof(t_vec3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(struct s_point), (void*)sizeof(t_vec3) + sizeof(t_vec2));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(struct s_point), (void*)(2 * sizeof(t_vec3) + sizeof(t_vec2)));
	glEnableVertexAttribArray(3);
}

void init_vao(t_obj *obj)
{
	glGenVertexArrays(1, &obj->gl_buff.vao);
	glGenBuffers(1, &obj->gl_buff.ebo);
	glGenBuffers(1, &obj->gl_buff.vbo);
	glBindVertexArray(obj->gl_buff.vao);
	init_vbo(obj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->gl_buff.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(obj->indices[0]) * obj->indices_nbr, obj->indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void get_glTexImage(uint *texs, uint *i_tex, t_d *data, char *file)
{
	glBindTexture(GL_TEXTURE_2D, texs[*i_tex]);
	create_image_from_png(data, *i_tex, file);
	printf("i = %d %d %d\n", *i_tex, data->imgs[*i_tex].w, data->imgs[*i_tex].h);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->imgs[*i_tex].w, data->imgs[*
	i_tex].h, 0, GL_BGRA, GL_UNSIGNED_BYTE, data->imgs[*i_tex].data);
	glGenerateMipmap(GL_TEXTURE_2D);
	(*i_tex)++;
}

uint *init_texs(t_d *data, t_obj *objs)
{
	uint		*texs;
	uint	i_tex;
	uint	i;
	uint	j;

	data->imgs = malloc(sizeof(t_img) * data->texture_nbr);
	texs = malloc(sizeof(uint) * data->texture_nbr); 
	glGenTextures(data->texture_nbr, texs);
	i = -1;
	i_tex = 0;
	get_glTexImage(texs, &i_tex, data, "./textures/bien.png");
	while (++i < data->object_nbr)
	{
		j = -1;
		while (++j < objs[i].mtl_nbr)
		{
			objs[i].texOn = 1;
			if (objs[i].mtls[j].img_file)
				get_glTexImage(texs, &i_tex, data, objs[i].mtls[j].img_file);
		}
	}
	return(texs);
}

void	init_uniform_data(t_d *data)
{
	data->eye = (t_vec3){0, 0, -10};
	data->dir = (t_vec3){0, 0, -1};
	data->cam.up = (t_vec3){0,1,0};
	ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);
	ft_mat4x4_to_float_array(data->cam.view_f, data->cam.view);
	ft_mat4x4_set_projection(data->cam.proj, (float[]){45, (float)data->width / data->height, .1f, 1000.0f});
	ft_mat4x4_to_float_array(data->cam.proj_f, data->cam.proj);
	data->viewLoc = glGetUniformLocation(data->program, "view");
	data->projLoc = glGetUniformLocation(data->program, "projection");
	data->ambLoc = glGetUniformLocation(data->program, "ambient");
}

void	init_uniform_obj(t_d *data, t_obj *obj)
{
	obj->mid = ft_vec3_scalar_mult(ft_vec3_add(obj->min, obj->max), -0.5);
	// ft_mat4x4_set_identity(obj->model);
	ft_mat4x4_to_float_array(obj->model_f, obj->model);
	obj->modelLoc = glGetUniformLocation(data->program, "model");
	obj->texOnLoc = glGetUniformLocation(data->program, "texOn");
	obj->defTex = glGetUniformLocation(data->program, "defTex");
}

void	draw_part_obj(t_obj *obj, uint *x, uint *texs)
{
	uint	y;
	int	nb_face;
	
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
		index]), GL_UNSIGNED_INT, (const GLvoid * const *)(&(obj->offset[
		obj->mtls[y].index])), nb_face);
		y++;
	}
}

void	draw_obj(t_obj *obj, float angle, uint *x, uint *texs)
{

	glUniform1i(obj->texOnLoc, obj->texOn);
	glUniform1i(obj->defTex, obj->textures_nbr == 0 ? 1 : 0);
	glBindVertexArray(obj->gl_buff.vao);
	ft_mat4x4_set_translation(obj->model, obj->pos);
	ft_mat4x4_translate(obj->model, ft_vec3_scalar_mult(obj->mid, -1));
	if (obj->rotOn)
		ft_mat4x4_rotate(obj->model, angle, (t_vec3){0, 1, 0});
	ft_mat4x4_translate(obj->model, obj->mid);
	ft_mat4x4_scale(obj->model, (t_vec3){obj->scale, obj->scale, obj->scale});
	ft_mat4x4_to_float_array(obj->model_f, obj->model);
	glUniformMatrix4fv(obj->modelLoc, 1, GL_FALSE, obj->model_f);
	if (!obj->mtl_nbr)
	{
		glBindTexture(GL_TEXTURE_2D, texs[0]);
		glMultiDrawElements(GL_TRIANGLE_FAN, obj->counts, GL_UNSIGNED_INT,
			(const GLvoid * const *)obj->offset, obj->faces_nbr);
	}
	else
		draw_part_obj(obj, x, texs);
}

void	init_frame(t_d *data, uint delta, t_obj *objs)
{
	key_event(data, delta, objs);
	rotation_cam(data, delta);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(data->program);
	glActiveTexture(GL_TEXTURE0);
	glUniformMatrix4fv(data->viewLoc, 1, GL_FALSE, data->cam.view_f);
	glUniformMatrix4fv(data->projLoc, 1, GL_FALSE, data->cam.proj_f);
	glUniform1f(data->ambLoc, data->ambient);
}

void	update_frame(t_d *data, t_obj *objs, uint *texs)
{
	uint						x;
	uint					delta;
	static struct timeval	tp = {0, 0};
	static uint				last = 0;
	size_t						i;
	static float angle = 0;

	delta = (tp.tv_sec * 1000 + tp.tv_usec / 1000) - last;
	last = (tp.tv_sec * 1000 + tp.tv_usec / 1000);
	init_frame(data, delta, objs);
	x = 1;
	i = -1;
	while (++i < data->object_nbr)
	{
		draw_obj(&objs[i], angle, &x, texs);
		glDisable(GL_PRIMITIVE_RESTART);
		glBindVertexArray(0);
	}
	angle += 90 * delta / 1000.0;
	glfwPollEvents();
	glfwSwapBuffers(data->window);
	gettimeofday(&tp, NULL);
}

int main(int ac, char **av)
{
	t_d				data;
	t_obj*			objs;
	uint			*texs;
	size_t				i;

	init_all(&data);
	objs = get_all_obj(&data, ac, av);
	if (objs[0].error)
	{
		printf("ERROR !\n");
		exit(EXIT_FAILURE);
	}
	printf("OPengl version : %s\n", glGetString(GL_VERSION));
	if (!init_shaders(&data, "./srcs/shaders/couleur2D.frag", "./srcs/shaders/couleur2D.vert"))
		return (1);
	if (!(data.program = create_and_link_program(data.vertex_sh, data.fragment_sh)))
		return (2);
	printf("nb = %zu\n", data.texture_nbr);
	texs = init_texs(&data, objs);
	init_uniform_data(&data);
	i = 0;
	printf("data.object_nbr = %zu\n", data.object_nbr);
	while (i < data.object_nbr)
	{
		init_vao(&objs[i]);
		init_uniform_obj(&data, &objs[i]);
		i++;
	}
	glClearColor(0.3, 0.3, 0.3, 1);
	data.drawing_mode = 0;
	while (!glfwWindowShouldClose(data.window))
	{
		update_frame(&data, objs, texs);
	}
	printf("Closing window.\n");

	glfwTerminate();
	return 0;
}
