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


void	init_matrices(t_mat4x4 view, t_mat4x4 model, t_d *data)
{
	ft_mat4x4_set_projection(data->projection, (float[]){60, (float)data->width / data->height, 0.1 ,100.0});
	// ft_mat4x4_set_identity(data->projection);
	ft_mat4x4_to_float_array(data->float_projection, data->projection);

	ft_mat4x4_set_look_at_from_float_array(view, (float[]){3, 3, 3}, (float[]){0, 0, 0}, (float[]){0, 1, 0});
	// ft_mat4x4_set_identity(view);

	ft_mat4x4_set_identity(model);
	// ft_mat4x4_rotate(model, 90, (float[]){0, 0, 1.});
	// ft_mat4x4_rotate(model, 60, (float[]){1., 0, 0});
}

int main(void)
{
	t_d		data;


	init_all(&data);
	printf("OPengl version : %s\n", glGetString(GL_VERSION));
	if (!init_shaders(&data, "./srcs/shaders/couleur2D.frag", "./srcs/shaders/couleur2D.vert"))
		return (1);
	if (!(data.program = create_and_link_program(data.vertex_sh, data.fragment_sh)))
		return (2);

	t_obj obj = obj_parser_main("objects/cube.obj");
	if (obj.error)
	{
		printf("ERROR !\n");
	}


	create_image_from_png(&data, 0, "../Doom_nukem/resources/stone_blocks.png");
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.img[0].w, data.img[0].h, 0, GL_BGRA, GL_UNSIGNED_BYTE, data.img[0].data);
		glGenerateMipmap(GL_TEXTURE_2D);

	// add_vertex(&data, (float[]){
 //    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 //     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
 //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 //    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

 //    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 //     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 //     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 //     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 //    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
 //    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

 //    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 //    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 //    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 //    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 //     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 //     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 //    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 //    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

 //    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 //     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 //    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
 //    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	// }, 36 * 5, 0);

		add_vertex(&data, (float[]){
			-.5f, -.5f, -.5f,
			-.5f, -.5f, .5f,
			-.5f, .5f, -.5f,
			-.5f, .5f, .5f,
			.5f, -.5f, -.5f,
			.5f, -.5f, .5f,
			.5f, .5f, -.5f,
			.5f, .5f, .5f,

    	}, 24, 0);

	unsigned int indices[] = {
		0, 2, 6, 4,
		2, 3, 7, 6,
		1, 3, 7, 5,
		0, 1, 5, 4,
		4, 5, 7, 6,
		0, 1, 3, 2,
	};

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	GLuint ebo = 0;
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &data.buffer[0]);
	glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, data.buffer[0]);
			glBufferData(GL_ARRAY_BUFFER, data.sizeof_vertices[0], data.vertices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// GLuint vao = 0;
	// glGenVertexArrays(1, &vao);

	// unsigned int ebo;
	// glGenBuffers(1, &ebo);



	// glGenBuffers(1, &data.buffer[0]);

	// glBindVertexArray(vao);
	// 	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// 	glBindBuffer(GL_ARRAY_BUFFER, data.buffer[0]);
			
	// 		// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
	// 		glBufferData(GL_ARRAY_BUFFER, data.sizeof_vertices[0], 0, GL_STATIC_DRAW);
	// 		// glBufferSubData(GL_ARRAY_BUFFER, 0, data.sizeof_vertices[0], data.vertices[0]);

	// 		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// 		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

	// 		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	// 		glEnableVertexAttribArray(0);
	// 		// glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// 		// glEnableVertexAttribArray(1);

	// glBindVertexArray(0);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);


	unsigned int transformLoc = glGetUniformLocation(data.program, "obj");

	t_mat4x4	model;
	GLfloat		model_f[16];

	ft_mat4x4_set_rotation(model, -55.0f, (t_vec3){1, 0, 0});
	ft_mat4x4_to_float_array(model_f, model);

	t_mat4x4	view;
	GLfloat	view_f[16];

	ft_mat4x4_set_translation(view, (t_vec3){0, 0, -3});
	ft_mat4x4_to_float_array(view_f, view);

	t_mat4x4	proj;
	GLfloat		proj_f[16];

	ft_mat4x4_set_projection(proj, (float[]){45, (float)data.width / data.height, .1f, 100.0f});
	ft_mat4x4_to_float_array(proj_f, proj);

	int modelLoc = glGetUniformLocation(data.program, "model");
	int viewLoc = glGetUniformLocation(data.program, "view");
	int projLoc = glGetUniformLocation(data.program, "projection");

	glClearColor(.2, .3, .3, 1);
	while (!glfwWindowShouldClose(data.window))
	{
		if (glfwGetKey(data.window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(data.window, true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(data.program);

		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vao);

		// ft_mat4x4_set_translation(model, cubePositions[i]);
		// float angle = 20.0f * i; 
		// ft_mat4x4_rotate(model, 0, (t_vec3){1, .3, .5});

		ft_mat4x4_to_float_array(model_f, model);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model_f);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view_f);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, proj_f);

		// int i;

		// i = 0;
		// while (i < 6)
		// {
		// 	glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
		// 	// glBegin(GL_TRIANGLE_FAN);
		// 	// 	glVertex3f(data.vertices[0][i]);
		// 	// 	glVertex3f(data.vertices[0][i + 1]);
		// 	// 	glVertex3f(data.vertices[0][i + 2]);
		// 	// 	glVertex3f(data.vertices[0][i + 3]);
		// 	// glEnd();

		// 	i++;
		// }

		// glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);
		GLsizei count[] = {4,4,4,4,4,4};
		const GLvoid * const indic[] = {0, 16, 32, 48, 64, 80};
		glMultiDrawElements(GL_TRIANGLE_FAN, count, GL_UNSIGNED_INT, indic, 6);
		// glDrawArrays(GL_TRIANGLE_FAN, 0, 12);
		glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(data.window);
	}
	printf("Closing window.\n");

	glfwTerminate();
	return 0;
}
