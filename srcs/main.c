#include <scop.h>
#include <cglm/cglm.h>   /* for inline */

#define STB_IMAGE_IMPLEMENTATION

int8_t	init_data(t_d *data)
{
	ft_bzero(data, sizeof(t_d));
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
	glViewport(0, 0, data->width, data->height);
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

void	key_event(t_d *data, uint delta)
{
	// t_mat4x4 rotation;
	t_vec3	transl;
	static float depl = 1;
	static float rot = 30;

	if (glfwGetKey(data->window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(data->window, true);
	if (glfwGetKey(data->window, GLFW_KEY_MINUS))
	{
		printf("minus\n");
		depl /= 1.01;
	}
	if (glfwGetKey(data->window, GLFW_KEY_EQUAL))
	{
		printf("plus\n");
		depl *= 1.01;
	}
	if (glfwGetKey(data->window, GLFW_KEY_W))
	{
		printf("W\n");
		transl = ft_vec3_scalar_mult(data->dir, -depl * delta / 1000);
		data->eye = ft_vec3_add(data->eye, transl);
		ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);

	}
	if (glfwGetKey(data->window, GLFW_KEY_S))
	{
		printf("S\n");
		transl = ft_vec3_scalar_mult(data->dir, depl * delta / 1000);
		data->eye = ft_vec3_add(data->eye, transl);
		ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);
	}
	if (glfwGetKey(data->window, GLFW_KEY_A))
	{
		printf("A\n");

		transl = ft_vec3_cross(data->dir, (t_vec3){0,1,0});
		ft_vec3_normalize(&transl);
		transl = ft_vec3_scalar_mult(transl, depl * delta / 1000);
		data->eye = ft_vec3_add(data->eye, transl);
		ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);

	}
	if (glfwGetKey(data->window, GLFW_KEY_D))
	{
		printf("D\n");
		transl = ft_vec3_cross(data->dir, (t_vec3){0,1,0});
		ft_vec3_normalize(&transl);
		transl = ft_vec3_scalar_mult(transl,  -depl * delta / 1000);
		data->eye = ft_vec3_add(data->eye, transl);
		ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);
	}
	if (glfwGetKey(data->window, GLFW_KEY_V) == GLFW_RELEASE && data->last_state[GLFW_KEY_V] == GLFW_PRESS)
	{
		!data->drawing_mode ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		data->drawing_mode = !data->drawing_mode;
	}
	if (glfwGetKey(data->window, GLFW_KEY_R) == GLFW_RELEASE && data->last_state[GLFW_KEY_R] == GLFW_PRESS)
	{
		data->eye = (t_vec3){0, 0, -10};
		data->dir = (t_vec3){0, 0, -1};
		ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);
		data->angle_y = 0;
	}
	if (glfwGetKey(data->window, GLFW_KEY_T) == GLFW_RELEASE && data->last_state[GLFW_KEY_T] == GLFW_PRESS)
	{
		printf("Texture\n");
		data->texture_on = (data->texture_on + 1) % 2;
	}
	data->last_state[GLFW_KEY_V] = glfwGetKey(data->window, GLFW_KEY_V);
	data->last_state[GLFW_KEY_T] = glfwGetKey(data->window, GLFW_KEY_T);
	data->last_state[GLFW_KEY_R] = glfwGetKey(data->window, GLFW_KEY_R);
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

int main(int ac, char **av)
{
	t_d				data;
	uint			last;
	uint			delta;
	struct timeval	tp;
	t_obj*			obj;
	uint			j;
	uint			i;
	unsigned int	*texs;
	GLuint ebo = 0;
	GLuint vao = 0;
	uint	i_tex;
	int x;
	int nb_face;

	i = 0;
	init_all(&data);
	obj = malloc(sizeof(t_obj) * (ac - 1));
	av++;
	while (*av)
	{
		obj[i] = obj_parser_main(*av);
		j = 0;
		printf("obj #%d :\n\tname = %s\n", i, obj[i].name);
		while (j < obj[i].mtl_nbr)
		{
			if (obj[i].mtls[j].img_file)
				data.texture_nbr++;
			printf("\tmtls[%d].ref = %s\n", j, obj[i].mtls[j].ref);
			printf("\tmtls[%d].img_file = %s\n", j, obj[i].mtls[j].img_file);
			printf("\tmtls[%d].index = %d\n", j, obj[i].mtls[j].index);
			j++;
		}
		if (!obj[i].error)
			i++;
		av++;
	}
	data.object_nbr = i;
	if (obj[0].error)
	{
		printf("ERROR !\n");
		exit(EXIT_FAILURE);
	}
	data.texture_nbr++;
	
	printf("OPengl version : %s\n", glGetString(GL_VERSION));
	if (!init_shaders(&data, "./srcs/shaders/couleur2D.frag", "./srcs/shaders/couleur2D.vert"))
		return (1);
	if (!(data.program = create_and_link_program(data.vertex_sh, data.fragment_sh)))
		return (2);
	printf("nb = %zu\n", data.texture_nbr);
	data.imgs = malloc(sizeof(t_img) * data.texture_nbr);
	if (data.texture_nbr)
	{
		printf("nb_text = %zu\n", data.texture_nbr);
		texs = malloc(sizeof(uint) * data.texture_nbr); 
		glGenTextures(data.texture_nbr, texs);

		i = 0;
		i_tex = 0;
		while (i < data.object_nbr)
		{
			j = 0;
			printf("obj[i].mtl_nbr = %d\n", obj[i].mtl_nbr);
			while (j < obj[i].mtl_nbr)
			{
				data.texture_on = 1;
				printf("obj[i].mtls[j].img_file = %s\n", obj[i].mtls[j].img_file);
				if (obj[i].mtls[j].img_file)
				{
					printf("i_tex = %u\nname = %s\n", i_tex, obj[i].mtls[j].img_file);
					printf("texs[i_tex] = %d\n", texs[i_tex]);
					glBindTexture(GL_TEXTURE_2D, texs[i_tex]);
					create_image_from_png(&data, i_tex, obj[i].mtls[j].img_file);

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.imgs[i_tex].w, data.imgs[i_tex].h, 0, GL_BGRA, GL_UNSIGNED_BYTE, data.imgs[i_tex].data);
					glGenerateMipmap(GL_TEXTURE_2D);
					i_tex++;
				}
				j++;
			}
			i++;
		}
		glBindTexture(GL_TEXTURE_2D, texs[i_tex]);
		create_image_from_png(&data, i_tex, "./textures/wall.png");

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.imgs[i_tex].w, data.imgs[i_tex].h, 0, GL_BGRA, GL_UNSIGNED_BYTE, data.imgs[i_tex].data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	
	float	tab[obj[0].vertices_nbr];

	int q = 0;
	while (q < obj[0].vertices_nbr)
	{
		tab[q] = (float)rand() / RAND_MAX;
		q++;
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &data.buffer[0]);
	glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, data.buffer[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3) * obj[0].vertices_nbr + sizeof(t_vec2) * obj[0].tex_vertices_nbr + sizeof(float) * obj[0].vertices_nbr, 0, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(t_vec3) * obj[0].vertices_nbr, obj[0].vertices);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(t_vec3) * obj[0].vertices_nbr, sizeof(t_vec2) * obj[0].tex_vertices_nbr, obj[0].tex_vertices);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(t_vec3) * obj[0].vertices_nbr + sizeof(t_vec2) * obj[0].tex_vertices_nbr, sizeof(float) * obj[0].vertices_nbr, tab);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid*)(sizeof(t_vec3) * obj[0].vertices_nbr));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), (GLvoid*)(sizeof(t_vec3) * obj[0].vertices_nbr + sizeof(t_vec2) * obj[0].tex_vertices_nbr));
			glEnableVertexAttribArray(2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(obj[0].indices[0]) * obj[0].indices_nbr, obj[0].indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	data.eye = (t_vec3){0, 0, -10};
	data.dir = (t_vec3){0, 0, -1};
	t_vec3 mid;

	mid = ft_vec3_scalar_mult(ft_vec3_add(obj[0].min, obj[0].max), -0.5);
	ft_mat4x4_set_identity(data.cam.model);
	ft_mat4x4_to_float_array(data.cam.model_f, data.cam.model);

	data.cam.up = (t_vec3){0,1,0};
	ft_mat4x4_set_look_at(data.cam.view, data.eye, ft_vec3_sub(data.eye, data.dir), data.cam.up);
	ft_mat4x4_to_float_array(data.cam.view_f, data.cam.view);

	ft_mat4x4_set_projection(data.cam.proj, (float[]){45, (float)data.width / data.height, .1f, 1000.0f});
	ft_mat4x4_to_float_array(data.cam.proj_f, data.cam.proj);

	int modelLoc = glGetUniformLocation(data.program, "model");
	int viewLoc = glGetUniformLocation(data.program, "view");
	int projLoc = glGetUniformLocation(data.program, "projection");

	glClearColor(.2, .3, .3, 1);
	gettimeofday(&tp, NULL);
	last = (tp.tv_sec * 1000 + tp.tv_usec / 1000);

	data.drawing_mode = 0;
	int	texOn = glGetUniformLocation(data.program, "texOn");
	int	defTex = glGetUniformLocation(data.program, "defTex");
	printf("data.texture_on = %d\n", data.texture_on);
	while (!glfwWindowShouldClose(data.window))
	{

		glUniform1i(texOn, data.texture_on);
		glUniform1i(defTex, data.texture_nbr == 1 ? 1 : 0);
		
		delta = (tp.tv_sec * 1000 + tp.tv_usec / 1000) - last;
		last = (tp.tv_sec * 1000 + tp.tv_usec / 1000);

		key_event(&data, delta);
		rotation_cam(&data, delta);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(data.program);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao);

		ft_mat4x4_translate(data.cam.model, ft_vec3_scalar_mult(mid, -1));
		ft_mat4x4_rotate(data.cam.model, 90 * delta / 1000.0, (t_vec3){0, 1, 0});
		ft_mat4x4_translate(data.cam.model, mid);
		
		ft_mat4x4_to_float_array(data.cam.model_f, data.cam.model);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, data.cam.model_f);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, data.cam.view_f);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, data.cam.proj_f);

		if (!obj[0].mtl_nbr)
			glMultiDrawElements(GL_TRIANGLE_FAN, obj[0].counts, GL_UNSIGNED_INT, (const GLvoid * const *)obj[0].offset, obj[0].faces_nbr);

		else
		{
			int x;
		
			x = 0;
			while (x < obj[0].mtl_nbr)
			{
				glBindTexture(GL_TEXTURE_2D, texs[x]);
				int nb_face;
	
				if (x + 1 == obj[0].mtl_nbr)
					nb_face = obj[0].faces_nbr - obj[0].mtls[x].index;
				else
					nb_face = obj[0].mtls[x + 1].index - obj[0].mtls[x].index;
				glMultiDrawElements(GL_TRIANGLE_FAN, &(obj[0].counts[obj[0].mtls[x].index]), GL_UNSIGNED_INT, (const GLvoid * const *)(&(obj[0].offset[obj[0].mtls[x].index])), nb_face);
				x++;
			}
		}
		glDisable(GL_PRIMITIVE_RESTART);
		glBindVertexArray(0);
		glfwPollEvents();
		glfwSwapBuffers(data.window);
		gettimeofday(&tp, NULL);
	}
	printf("Closing window.\n");

	glfwTerminate();
	return 0;
}
