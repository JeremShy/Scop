#include <scop.h>
#include <cglm/cglm.h>   /* for inline */

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int8_t  init_data(t_d *data)
{
	ft_bzero(data, sizeof(t_d));
	return (1);
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s - errno = %d\n", description, error);
}

void resize_callback(GLFWwindow* window, int width, int height)
{
	printf("Resized : %d - %d\n", width, height);
	glViewport(0, 0, width, height);
	// TODO : Reset matrix
}

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

	data->window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!data->window)
	{
		glfwTerminate();
		return (0);
	}
	glfwSetFramebufferSizeCallback(data->window, resize_callback);
	glfwMakeContextCurrent(data->window);
	glfwGetWindowSize(data->window, &data->width, &data->height);
	printf("Window size : %d - %d\n", data->width, data->height);
	glViewport(0, 0, data->width, data->height);
	return (1);
}

void  add_vertex(t_d *data, float vertex[], size_t nbr, size_t index)
{
	data->sizeof_vertices[index] = nbr * sizeof(float);
	data->vertices[index] = malloc(nbr * sizeof(float));
	ft_memcpy(data->vertices[index], vertex, nbr * sizeof(float));
}

void  add_color(t_d *data, float color[], size_t nbr, size_t index)
{
	data->sizeof_colors[index] = nbr * sizeof(float);
	data->colors[index] = malloc(nbr * sizeof(float));
	ft_memcpy(data->colors[index], color, nbr * sizeof(float));
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

void    init_vbo_triangle(t_d *data, int vbo_nbr)
{
	glGenBuffers(1, &(data->buffer[vbo_nbr]));

	glBindBuffer(GL_ARRAY_BUFFER, data->buffer[vbo_nbr]);
		glBufferData(GL_ARRAY_BUFFER, data->sizeof_vertices[vbo_nbr] + data->sizeof_colors[vbo_nbr], 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data->sizeof_vertices[vbo_nbr], data->vertices[vbo_nbr]);
		glBufferSubData(GL_ARRAY_BUFFER, data->sizeof_vertices[vbo_nbr], data->sizeof_colors[vbo_nbr], data->colors[vbo_nbr]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


// void	init_matrices(t_mat4x4 view, t_mat4x4 model, t_d *data)
// {
// 	ft_mat4x4_set_projection(data->projection, (float[]){60, (float)data->width / data->height, 0.1 ,100.0});
// 	// ft_mat4x4_set_identity(data->projection);
// 	ft_mat4x4_to_float_array(data->float_projection, data->projection);

// 	ft_mat4x4_set_look_at_from_float_array(view, (float[]){3, 3, 3}, (float[]){0, 0, 0}, (float[]){0, 1, 0});
// 	// ft_mat4x4_set_identity(view);

// 	ft_mat4x4_set_identity(model);
// 	// ft_mat4x4_rotate(model, 90, (float[]){0, 0, 1.});
// 	// ft_mat4x4_rotate(model, 60, (float[]){1., 0, 0});
// }


void	key_event(t_d *data, struct s_cam *cam)
{
	// t_mat4x4 rotation;
	t_vec3	transl;

	if (glfwGetKey(data->window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(data->window, true);
	if (glfwGetKey(data->window, GLFW_KEY_W))
	{
		printf("W\n");
		transl = ft_vec3_scalar_mult(data->dir, -1);
		data->eye = ft_vec3_add(data->eye, transl);
		ft_mat4x4_set_look_at(cam->view, data->eye, ft_vec3_sub(data->eye, data->dir), cam->up);

	}
	if (glfwGetKey(data->window, GLFW_KEY_S))
	{
		printf("S\n");
		transl = ft_vec3_scalar_mult(data->dir, 1);
		data->eye = ft_vec3_add(data->eye, transl);
		ft_mat4x4_set_look_at(cam->view, data->eye, ft_vec3_sub(data->eye, data->dir), cam->up);
	}
	if (glfwGetKey(data->window, GLFW_KEY_A))
	{
		printf("A\n");

		transl = ft_vec3_cross(data->dir, (t_vec3){0,1,0});
		transl = ft_vec3_scalar_mult(transl, 1);
		data->eye = ft_vec3_add(data->eye, transl);
		ft_mat4x4_set_look_at(cam->view, data->eye, ft_vec3_sub(data->eye, data->dir), cam->up);

	}
	if (glfwGetKey(data->window, GLFW_KEY_D))
	{
		printf("D\n");
		transl = ft_vec3_cross(data->dir, (t_vec3){0,1,0});
		transl = ft_vec3_scalar_mult(transl, -1);
		data->eye = ft_vec3_add(data->eye, transl);
		ft_mat4x4_set_look_at(cam->view, data->eye, ft_vec3_sub(data->eye, data->dir), cam->up);
	}
	if (glfwGetKey(data->window, GLFW_KEY_LEFT))
	{
		printf("LEFT\n");
		data->dir = ft_vec3_rotate(data->dir, 1, (t_vec3){0,1,0});
		ft_mat4x4_set_look_at(cam->view, data->eye, ft_vec3_sub(data->eye, data->dir), cam->up);

	}
	if (glfwGetKey(data->window, GLFW_KEY_RIGHT))
	{
		printf("RIGHT\n");
		data->dir = ft_vec3_rotate(data->dir, -1, (t_vec3){0,1,0});
		ft_mat4x4_set_look_at(cam->view, data->eye, ft_vec3_sub(data->eye, data->dir), cam->up);
	}
	if (glfwGetKey(data->window, GLFW_KEY_UP))
	{
		printf("UP\n");
		data->dir = ft_vec3_rotate(data->dir, -1, ft_vec3_cross(data->dir, (t_vec3){0,1,0}));
		ft_mat4x4_set_look_at(cam->view, data->eye, ft_vec3_sub(data->eye, data->dir), cam->up);

	}
	if (glfwGetKey(data->window, GLFW_KEY_DOWN))
	{
		printf("DOWN\n");
		data->dir = ft_vec3_rotate(data->dir, 1, ft_vec3_cross(data->dir, (t_vec3){0,1,0}));
		ft_mat4x4_set_look_at(cam->view, data->eye, ft_vec3_sub(data->eye, data->dir), cam->up);
	}
	ft_mat4x4_to_float_array(cam->view_f, cam->view);
}

int main(int ac, char **av)
{
	t_d				data;
	uint 			last;
	uint 			delta;
	struct timeval	tp;
	float			rot;
	struct s_cam 	cam;

	init_all(&data);
	printf("OPengl version : %s\n", glGetString(GL_VERSION));
	if (!init_shaders(&data, "./srcs/shaders/couleur2D.frag", "./srcs/shaders/couleur2D.vert"))
		return (1);
	if (!(data.program = create_and_link_program(data.vertex_sh, data.fragment_sh)))
		return (2);

	t_obj obj = obj_parser_main(av[1]);
	if (obj.error)
	{
		printf("ERROR !\n");
		exit(EXIT_FAILURE);
	}


	create_image_from_png(&data, 0, "textures/Cat_diffuse.png");
	// create_image_from_png(&data, 0, "textures/Cat_diffuse.png");

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.img[0].w, data.img[0].h, 0, GL_BGRA, GL_UNSIGNED_BYTE, data.img[0].data);
		glGenerateMipmap(GL_TEXTURE_2D);

	// int q = 0;
	// while (q < obj.indices_nbr)
	// {
	// 	printf("#%d: %f %f\n", q, obj.textures[q].x, obj.textures[q].y);
	// 	q++;
	// }

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	GLuint ebo = 0;
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &data.buffer[0]);
	glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, data.buffer[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3) * (obj.vertices_nbr) + sizeof(t_vec2) * obj.indices_nbr, 0, GL_STATIC_DRAW);
			// glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3) * obj.tex_vertices_nbr, obj.tex_vertices, GL_STATIC_DRAW);
			
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(t_vec3) * obj.vertices_nbr, obj.vertices);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(t_vec3) * obj.vertices_nbr, sizeof(t_vec2) * obj.indices_nbr, obj.textures);
			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), sizeof(t_vec3) * obj.vertices_nbr);
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * obj.indices_nbr, obj.indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	unsigned int transformLoc = glGetUniformLocation(data.program, "obj");

	// rot = 180;
	// ft_mat4x4_set_rotation(model, 0, (t_vec3){1, 0, 0});
	// ft_mat4x4_set_translation(model, (t_vec3){0, 0, 1});
	data.eye = (t_vec3){0, 0, 300};
	data.dir = (t_vec3){0, 0, 1};

	ft_mat4x4_set_identity(cam.model);
	ft_mat4x4_to_float_array(cam.model_f, cam.model);



	// dir = ft_vec4_to_vec3(ft_mat4x4_mult_with_vec4(model, (t_vec4){0, 0, 0, 1}));
	cam.up = (t_vec3){0,1,0};
	ft_mat4x4_set_look_at(cam.view, data.eye, ft_vec3_sub(data.eye, data.dir), cam.up);
	// ft_mat4x4_translate(cam.view, (t_vec3){0, 0, -50});
	ft_mat4x4_to_float_array(cam.view_f, cam.view);


	ft_mat4x4_set_projection(cam.proj, (float[]){45, (float)data.width / data.height, .1f, 1000.0f});
	ft_mat4x4_to_float_array(cam.proj_f, cam.proj);

	int modelLoc = glGetUniformLocation(data.program, "model");
	int viewLoc = glGetUniformLocation(data.program, "view");
	int projLoc = glGetUniformLocation(data.program, "projection");

	glClearColor(.2, .3, .3, 1);
	gettimeofday(&tp, NULL);
	last = (tp.tv_sec * 1000 + tp.tv_usec / 1000);

	// t_vec3			*tex_vertices;
	// int				tex_vertices_nbr;
	// int				tex_vertices_curr;

	// int q = 0;
	// while (q < obj.tex_vertices_nbr)
	// {
	// 	printf("vt #%d: %f %f %f\n", q, obj.tex_vertices[q].x, obj.tex_vertices[q].y, obj.tex_vertices[q].z);
	// 	q++;
	// }

	while (!glfwWindowShouldClose(data.window))
	{
		delta = (tp.tv_sec * 1000 + tp.tv_usec / 1000) - last;
		last = (tp.tv_sec * 1000 + tp.tv_usec / 1000);

		key_event(&data, &cam);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(data.program);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vao);

		// ft_mat4x4_set_rotation(cam.model, rot + 90 * delta / 1000.0, (t_vec3){1, 0, 0});
		// // ft_mat4x4_scale(cam.model, (t_vec3){0.5, 0.5, 0.5});
		// // ft_mat4x4_translate(cam.model, (t_vec3){0, 0, 0});
		// ft_mat4x4_to_float_array(cam.model_f, cam.model);
		// rot += 90 * delta / 1000.0;

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, cam.model_f);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, cam.view_f);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, cam.proj_f);


		glMultiDrawElements(GL_TRIANGLE_FAN, obj.counts, GL_UNSIGNED_INT, obj.offset, obj.faces_nbr);
		glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(data.window);
		gettimeofday(&tp, NULL);
	}
	printf("Closing window.\n");

	glfwTerminate();
	return 0;
}
