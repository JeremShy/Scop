#include <scop.h>

int	key_hook(int keycode, void *param)
{
	if (keycode == 53)
	{
		exit(1);
	}
	return (0);
}

int	hook(void *param)
{
	t_data *data;

	data = param;
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, data->vertexbuffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);

	mlx_opengl_swap_buffers(data->win);
	return (1);
}

int main()
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win = mlx_new_opengl_window(data.mlx_ptr, 640,480, "coucou");
	mlx_opengl_window_set_context(data.win);

	glClearColor(0.4f, 0.4f, 0.1f, 0.0f);
	mlx_loop_hook(data.mlx_ptr, hook, &data);
	mlx_key_hook(data.win, key_hook, &data);

	glGenVertexArrays(1, &data.VertexArrayID);
	glBindVertexArray(data.VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	GLfloat vertices[] = {
		0.0f,  0.5f, // Vertex 1 (X, Y)
        0.5f, -0.5f, // Vertex 2 (X, Y)
       -0.5f, -0.5f  // Vertex 3 (X, Y)
   	};

	glGenBuffers(1, &data.vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, data.vertexbuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const char* vertexSource = "#version 150 core\
\
	    in vec2 position;\
\
	    void main()\
	    {\
	        gl_Position = vec4(position, 0.0, 1.0);\
	    }";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		printf("compilation ok\n");
	}
	else
	{
		printf("compilation not ok\n");
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		return (0);
	}

	const char *fragmentSource = "#version 150 core\
	\
	out vec4 outColor;\
	\
	void main()\
	{\
	    outColor = vec4(1.0, 1.0, 1.0, 1.0);\
	}\
	";
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		printf("compilation fragment ok\n");
	}
	else
	{
		printf("compilation fragnebt not ok\n");
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		return (0);
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	mlx_loop (&data);
	return (0);
}
