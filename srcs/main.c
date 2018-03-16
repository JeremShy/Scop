#include <scop.h>

int	key_hook(int keycode, void *param)
{
	if (keycode == 53)
	{
		printf("Leaving.\n");
		exit(0);
	}
	return (0);
}

void	create_shader(t_data *data)
{
	GLenum	error_check_value = glGetError();

	data->vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(data->vertex_shader_id, 1, &data->vertex_shader, NULL);
	glCompileShader(data->vertex_shader_id);

	GLint status;
	glGetShaderiv(data->vertex_shader_id, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		printf("compilation nbr 1 ok.\n");
	}
	else
	{
		printf("compilation not ok\n");
		GLchar buffer[512];
		glGetShaderInfoLog(data->vertex_shader_id, 512, NULL, buffer);
		return ;
	}


	data->fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(data->fragment_shader_id, 1, &data->fragment_shader, NULL);
	glCompileShader(data->fragment_shader_id);

	glGetShaderiv(data->fragment_shader_id, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		printf("compilation nbr 2 ok.\n");
	}
	else
	{
		printf("compilation not ok\n");
		GLchar buffer[512];
		glGetShaderInfoLog(data->fragment_shader_id, 512, NULL, buffer);
		return ;
	}


	data->program_id = glCreateProgram();
	glAttachShader(data->program_id, data->vertex_shader_id);
	glAttachShader(data->program_id, data->fragment_shader_id);
	glLinkProgram(data->program_id);
	glUseProgram(data->program_id);

	error_check_value = glGetError();
	if (error_check_value != GL_NO_ERROR)
	{
		printf("Error ! could not create a vbo. error number : %d\n", error_check_value);
		exit(2);
	}
}

void	destroy_shaders(t_data *data)
{
	//TODO;
}

void	create_vbo(t_data *data)
{
	GLfloat vertices[] = {
    -0.8f, -0.8f, 0.0f, 1.0f,
     0.0f,  0.8f, 0.0f, 1.0f,
     0.8f, -0.8f, 0.0f, 1.0f
	};

	GLfloat	colors[] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f
	};

	GLenum error_check_value = glGetError();

	glGenVertexArrays(1, &data->vao_id);
	glBindVertexArray(data->vao_id);

	glGenBuffers(1, &data->vbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, data->vbo_id);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &data->color_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, data->color_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	error_check_value = glGetError();
	if (error_check_value != GL_NO_ERROR)
	{
		printf("Error ! could not create a vbo. error number : %d\n", error_check_value);
		exit(2);
	}
}

void	destroy_vbo(t_data *data)
{
	//TODO
}



void	loop_hook(t_data *data)
{
	printf("in loop_hook !\n");

	glDrawArrays(GL_TRIANGLES, 0, 3);
	printf("arrays drawn.\n");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	printf("colors cleared.\n");

	mlx_opengl_swap_buffers(data->win);
	printf("buffer swapped.\n");
}

void	init_window(t_data *data)
{
	data->mlx_ptr = mlx_init();

	// MLX initialization
	data->win = mlx_new_opengl_window(data->mlx_ptr, 1280, 960, "coucou");
	mlx_opengl_window_set_context(data->win);
	glClearColor(0.8f, 0.0f, 0.0f, 0.0f); // Sets the color that will be used when clearing pixels.

	mlx_loop_hook(data->mlx_ptr, loop_hook, &data);
	mlx_key_hook(data->win, key_hook, &data);
}

void init(t_data *data)
{
	data->vertex_shader = 
	"#version 400\n"\
	"layout(location=0) in vec4 in_Position;\n"\
	"layout(location=1) in vec4 in_Color;\n"\
	"out vec4 ex_Color;\n"\

	"void main(void)\n"\
	"{\n"\
	"  gl_Position = in_Position;\n"\
	"  ex_Color = in_Color;\n"\
	"}\n";

	data->fragment_shader = 
	"#version 400\n"\
	"in vec4 ex_Color;\n"\
	"out vec4 out_Color;\n"\

	"void main(void)\n"\
	"{\n"\
	"  out_Color = ex_Color;\n"\
	"}\n";

	init_window(data);
	printf("window inited.\n");

	create_vbo(data);
	printf("vbo inited.\n");	

	create_shader(data);
	printf("shaders inited.\n");
}

int main()
{
	t_data	data;

	init(&data);
	printf("Opengl Version : %s\n", glGetString(GL_VERSION));
	mlx_loop(data.mlx_ptr);

	return (0);
}