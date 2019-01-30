#include <scop.h>
#include <cglm/cglm.h>   /* for inline */

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

void    init_vao(t_d *data, int vao_nbr, int first, int last)
{
	int	i;

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
	if (!init_shaders(&data, "./srcs/shaders/couleur3D.frag", "./srcs/shaders/couleur3D.vert"))
		return (1);
	if (!(data.program = create_and_link_program(data.vertex_sh, data.fragment_sh)))
		return (2);

	t_mat4x4 view;
	t_mat4x4 model;

	init_matrices(view, model, &data);


	printf("fovy : %f\n", (M_PI / 3) / ((float)data.width / data.height));
	printf("ratio : %f\n", (float) data.width / data.height);
	printf("near : %f\n", .1);
	printf("far : %f\n", 100.);


	t_mat4x4 modelview;
	ft_mat4x4_mult(modelview, view, model);

	GLfloat modelview_f[16];
	ft_mat4x4_to_float_array(modelview_f, modelview);

	GLfloat projection_f[16];
	ft_mat4x4_to_float_array(projection_f, data.projection);

	GLfloat view_f[16];
	ft_mat4x4_to_float_array(view_f, view);

	printf("modelview : \n");
	ft_mat4x4_print(modelview);
	printf("projection : \n");
	ft_mat4x4_print(data.projection);

	GLuint modelviewID = glGetUniformLocation(data.program, "modelview");
	GLuint projID = glGetUniformLocation(data.program, "projection");

	// add_vertex(&data, (float[]){0.0, 0.0,  1, 0.0,  0.0, 1}, 6, 0);
	// add_color(&data, (float[]){1.0, 0.0, 0.0,   0.0, 1.0, 0.0,   0.0, 0.0, 1.0}, 9, 0);

	add_vertex(&data, (float[]){-1.0, -1.0, -1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,     // Face 1
                    -1.0, -1.0, -1.0,   -1.0, 1.0, -1.0,   1.0, 1.0, -1.0,     // Face 1


                    1.0, -1.0, 1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,       // Face 2

                    1.0, -1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, -1.0,         // Face 2


                    -1.0, -1.0, 1.0,   1.0, -1.0, 1.0,   1.0, -1.0, -1.0,      // Face 3

                    -1.0, -1.0, 1.0,   -1.0, -1.0, -1.0,   1.0, -1.0, -1.0,    // Face 3


                    -1.0, -1.0, 1.0,   1.0, -1.0, 1.0,   1.0, 1.0, 1.0,        // Face 4

                    -1.0, -1.0, 1.0,   -1.0, 1.0, 1.0,   1.0, 1.0, 1.0,        // Face 4


                    -1.0, -1.0, -1.0,   -1.0, -1.0, 1.0,   -1.0, 1.0, 1.0,     // Face 5

                    -1.0, -1.0, -1.0,   -1.0, 1.0, -1.0,   -1.0, 1.0, 1.0,     // Face 5


                    -1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, -1.0,         // Face 6

                    -1.0, 1.0, 1.0,   -1.0, 1.0, -1.0,   1.0, 1.0, -1.0}
		, 108, 0);
	add_color(&data, (float[])
		{1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 1

                    1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 1


                    0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 2

                    0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 2


                    0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 3

                    0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 3


                    1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 4

                    1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 4


                    0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 5

                    0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 5


                    0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 6

                    0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0},
		108, 0);
	init_vbo_triangle(&data, 0);

	obj_parser_main("objects/test.obj");

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);

	glBindBuffer(GL_ARRAY_BUFFER, data.buffer[0]);
	glBindVertexArray(vao);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)data.sizeof_vertices[0]);
			glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// glm_mat4_mult(c_model, c_view, c_viewmodel);


	glClearColor(.2, .3, .3, 1);
	while (!glfwWindowShouldClose(data.window))
	{
		if (glfwGetKey(data.window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(data.window, true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(data.program);
		
		glBindVertexArray(vao);
			glUniformMatrix4fv(modelviewID, 1, GL_FALSE, modelview_f);
			glUniformMatrix4fv(projID, 1, GL_FALSE, projection_f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(data.window);
	}
	printf("Closing window.\n");

	glfwTerminate();
	return 0;
}
