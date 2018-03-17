#include <scop.h>

int8_t  init_data(t_d *data)
{
    ft_bzero(data, sizeof(t_d));
    return (1);
}

int8_t	init_glfw(t_d *data)
{
    if (!glfwInit())
        return (0);

    data->window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!data->window)
    {
        glfwTerminate();
        return (0);
    }
   glfwMakeContextCurrent(data->window);
   return (1);
}

int8_t  init_gl_and_draw(t_d *data)
{
    data->vertices = malloc(sizeof((float[])
    {-0.5, 0.0, 0.0, 1.0, 0.5, 0.0,
        -0.5, 0.0, 0.5, 0.0, 0.0, -1.0}));
    ft_memcpy(data->vertices, (float[])
    {-0.5, 0.0, 0.0, 1.0, 0.5, 0.0,
        -0.5, 0.0, 0.5, 0.0, 0.0, -1.0}, sizeof((float[])
    {-0.5, 0.0, 0.0, 1.0, 0.5, 0.0,
        -0.5, 0.0, 0.5, 0.0, 0.0, -1.0}));
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

int main(void)
{
    t_d      data;

    init_all(&data);

    int vao;

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
	    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, data.vertices);
	    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(data.window))
    {
	glClear(GL_COLOR_BUFFER_BIT);


	glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glfwSwapBuffers(data.window);
	glfwPollEvents();
    }
    printf("Closing window.\n");

    glfwTerminate();
    return 0;
}
