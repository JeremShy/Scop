#include <scop.h>

int8_t  init_data(t_d *data)
{
	ft_bzero(data, sizeof(t_d));
	return (1);
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s - errno = %d\n", description, error);
}

int8_t	init_glfw(t_d *data)
{
	if (!glfwInit())
		return (0);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetErrorCallback(error_callback);

	data->window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!data->window)
	{
		glfwTerminate();
		return (0);
	}
   glfwMakeContextCurrent(data->window);
   glfwGetWindowSize(data->window, &data->width, &data->height);
   printf("Window size : %d - %d\n", data->width, data->height);
   return (1);
}

int8_t  init_gl_and_draw(t_d *data)
{
	data->sizeof_vertices[0] = sizeof((float[])
		{0.0, 0.0, -1.0,  0.5, 0.0, -1.0,  0.0, 0.5, -1.0});

	data->vertices[0] = malloc(data->sizeof_vertices[0]);
	ft_memcpy(data->vertices[0],
		(float[])
			{0.0, 0.0, -1.0,  0.5, 0.0, -1.0,  0.0, 0.5, -1.0},
		data->sizeof_vertices[0]);
	return (1);
}

int8_t	init_all(t_d *data)
{
	if (!init_data(data))
		return (0);
	if (!init_glfw(data))
		return (0);
	if (!init_gl_and_draw(data))
		return (0);
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

void    init_vbo(t_d *data, float couleurs[], size_t sizeof_couleurs, int vbo_nbr)
{
	glGenBuffers(1, &(data->buffer[vbo_nbr]));
	glBindBuffer(GL_ARRAY_BUFFER, data->buffer[vbo_nbr]);
		glBufferData(GL_ARRAY_BUFFER, data->sizeof_vertices[vbo_nbr] + sizeof_couleurs, 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data->sizeof_vertices[vbo_nbr], data->vertices[vbo_nbr]);
		glBufferSubData(GL_ARRAY_BUFFER, data->sizeof_vertices[vbo_nbr], sizeof_couleurs, couleurs);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void    init_vao(t_d *data, int vao_nbr)
{
	ft_mat4x4_to_float_array(data->float_projection, data->projection);
	ft_mat4x4_to_float_array(data->float_modelview[vao_nbr], data->modelview[vao_nbr]);

	glGenVertexArrays(1, &data->vao[vao_nbr]);
	glUseProgram(data->program);
		glBindVertexArray(data->vao[vao_nbr]);
			glBindBuffer(GL_ARRAY_BUFFER, data->buffer[vao_nbr]);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(0); // vertices
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(data->sizeof_vertices[vao_nbr]));
				glEnableVertexAttribArray(1); // couleurs

				glUniformMatrix4fv(glGetUniformLocation(data->program, "modelview"), 1, GL_FALSE, data->float_modelview[vao_nbr]);
				glUniformMatrix4fv(glGetUniformLocation(data->program, "projection"), 1, GL_FALSE, data->float_projection);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	glUseProgram(0);
}

int main(void)
{
	t_d      data;

	init_all(&data);

	printf("OPengl version : %s\n", glGetString(GL_VERSION));

	float couleurs[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
	size_t  sizeof_couleurs = sizeof(couleurs);

	init_vbo(&data, couleurs, sizeof_couleurs, 0);
	if (!init_shaders(&data, "./srcs/shaders/default.frag", "./srcs/shaders/default.vert"))
		return (1);
	if (!(data.program = create_and_link_program(data.vertex_sh, data.fragment_sh)))
	{
		dprintf(2, "Error while trying to create and link program\n");
		return (1);
	}
	ft_mat4x4_set_projection(data.projection,
		(double[4]){70.0, (double)data.width / data.height, 1.0, 100.0});
	ft_mat4x4_set_identity(data.modelview[0]);

	ft_mat4x4_rotate_from_double_array(data.modelview[0], -45.0f, (double[3]){0.0, 0.0, 1.0});
	ft_mat4x4_translate_from_double_array(data.modelview[0], (double[3]){-0.5, -0.25, 0.0});
	ft_mat4x4_print(data.modelview[0]);
	init_vao(&data, 0);

	while (!glfwWindowShouldClose(data.window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(data.program);
			glBindVertexArray(data.vao[0]);
				glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(data.window);
		glfwPollEvents();

		// ft_mat4x4_to_float_array(data.float_projection, data.projection);
		// ft_mat4x4_to_float_array(data.float_modelview, data.modelview);
	}
	printf("Closing window.\n");

	glfwTerminate();
	return 0;
}
