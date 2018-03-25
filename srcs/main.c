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

void    init_vao(t_d *data, int vao_nbr, int first, int last)
{
	int	i;

	ft_mat4x4_to_float_array(data->float_projection, data->projection);
	i = first;
	while (i <= last)
	{
		ft_mat4x4_to_float_array(data->float_modelview[i], data->modelview[i]);
		i++;
	}

	glGenVertexArrays(1, &data->vao[vao_nbr]);
	glUseProgram(data->program);
		glBindVertexArray(data->vao[vao_nbr]);
				i = first;
				while (i <= last)
				{
					glBindBuffer(GL_ARRAY_BUFFER, data->buffer[i]);
					glVertexAttribPointer(i * 2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
					glEnableVertexAttribArray(i * 2); // vertices
					glVertexAttribPointer(i * 2 + 1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(data->sizeof_vertices[i]));
					glEnableVertexAttribArray(i * 2 + 1); // couleurs
					glUniformMatrix4fv(glGetUniformLocation(data->program, "modelview"), 1, GL_FALSE, data->float_modelview[i]);
					glUniformMatrix4fv(glGetUniformLocation(data->program, "projection"), 1, GL_FALSE, data->float_projection);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					i++;
				}
		glBindVertexArray(0);
	glUseProgram(0);
}

int main(void)
{
	t_d      data;

	init_all(&data);
	printf("OPengl version : %s\n", glGetString(GL_VERSION));

	add_vertex(&data, (float[]){0.0, 0.0, -1.0,  0.5, 0.0, -1.0,  0.0, 0.5, -1.0}, 9, 0);
	add_color(&data, (float[]){1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 9, 0);
	init_vbo_triangle(&data, 0);

	add_vertex(&data, (float[]){0.0, 0.0, -1.0,  0.5, 0.0, -1.0,  0.0, 0.5, -1.0}, 9, 1);
	add_color(&data, (float[]){1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 9, 1);
	init_vbo_triangle(&data, 1);


	if (!init_shaders(&data, "./srcs/shaders/default.frag", "./srcs/shaders/default.vert"))
		return (1);
	if (!(data.program = create_and_link_program(data.vertex_sh, data.fragment_sh)))
		return (2);
	ft_mat4x4_set_projection(data.projection, (double[4]){12.0, (double)data.width / data.height, 1.0, 100.0});

	ft_mat4x4_set_identity(data.modelview[0]);
	ft_mat4x4_rotate_from_double_array(data.modelview[0], -45.0f, (double[3]){0.0, 0.0, 1.0});
	ft_mat4x4_translate_from_double_array(data.modelview[0], (double[3]){-0.5, -0.25, 0.0});

	ft_mat4x4_set_identity(data.modelview[1]);


	init_vao(&data, 1, 1, 1);

	while (!glfwWindowShouldClose(data.window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(data.program);
			glBindVertexArray(data.vao[1]);
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
