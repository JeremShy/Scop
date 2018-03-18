#include <scop.h>

int8_t  init_data(t_d *data)
{
    ft_bzero(data, sizeof(t_d));
    return (1);
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
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
    ft_memcpy(data->vertices,
    (float[]){-0.5, 0.0, 0.0, 1.0, 0.5, 0.0,
        -0.5, 0.0, 0.5, 0.0, 0.0, -1.0},
    sizeof((float[]){-0.5, 0.0, 0.0, 1.0, 0.5, 0.0,
            -0.5, 0.0, 0.5, 0.0, 0.0, -1.0}));
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

int main(void)
{
    t_d      data;
    init_all(&data);

    printf("OPengl version : %s\n", glGetString(GL_VERSION));

    float couleurs[] = {1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0};

    GLuint vao;

    if (!(data.vertex_sh = create_and_compile_shader("./srcs/shaders/default_vertex_sh.c", GL_VERTEX_SHADER)))
    {
        dprintf(2, "Error while trying to create vertex shader.");
        return (1);
    }
    
    if (!(data.fragment_sh = create_and_compile_shader("./srcs/shaders/default_fragment_sh.c", GL_FRAGMENT_SHADER)))
    {
        dprintf(2, "Error while trying to create fragment shader.\n");
        return (1);
    }
    if (!(data.program = create_and_link_program(data.vertex_sh, data.fragment_sh)))
    {
        dprintf(2, "Error while trying to create and link program");
        return (1);
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
	    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, data.vertices);
	    glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 1, couleurs);
        glEnableVertexAttribArray(1);
        glUseProgram(data.program);
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(data.window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(data.program);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(0);

        glfwSwapBuffers(data.window);
        glfwPollEvents();
    }
    printf("Closing window.\n");

    glfwTerminate();
    return 0;
}
