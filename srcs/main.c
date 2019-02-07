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

	data->window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!data->window)
	{
		glfwTerminate();
		return (0);
	}
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
	float depl;
	float rot;

	depl = 10;
	rot = 30;
	if (glfwGetKey(data->window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(data->window, true);
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
		transl = ft_vec3_scalar_mult(transl, depl * delta / 1000);
		data->eye = ft_vec3_add(data->eye, transl);
		ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);

	}
	if (glfwGetKey(data->window, GLFW_KEY_D))
	{
		printf("D\n");
		transl = ft_vec3_cross(data->dir, (t_vec3){0,1,0});
		transl = ft_vec3_scalar_mult(transl,  -depl * delta / 1000);
		data->eye = ft_vec3_add(data->eye, transl);
		ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);
	}
	if (glfwGetKey(data->window, GLFW_KEY_LEFT))
	{
		printf("LEFT\n");
		data->dir = ft_vec3_rotate(data->dir, rot * delta / 1000, (t_vec3){0,1,0});
		ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);

	}
	if (glfwGetKey(data->window, GLFW_KEY_RIGHT))
	{
		printf("RIGHT\n");
		data->dir = ft_vec3_rotate(data->dir,  -rot * delta / 1000, (t_vec3){0,1,0});
		ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);
	}
	if (glfwGetKey(data->window, GLFW_KEY_UP))
	{
		printf("UP\n");
		data->dir = ft_vec3_rotate(data->dir,  -rot * delta / 1000, ft_vec3_cross(data->dir, (t_vec3){0,1,0}));
		ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);

	}
	if (glfwGetKey(data->window, GLFW_KEY_DOWN))
	{
		printf("DOWN\n");
		data->dir = ft_vec3_rotate(data->dir, rot * delta / 1000, ft_vec3_cross(data->dir, (t_vec3){0,1,0}));
		ft_mat4x4_set_look_at(data->cam.view, data->eye, ft_vec3_sub(data->eye, data->dir), data->cam.up);
	}
	ft_mat4x4_to_float_array(data->cam.view_f, data->cam.view);
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
	
	printf("OPengl version : %s\n", glGetString(GL_VERSION));
	if (!init_shaders(&data, "./srcs/shaders/couleur2D.frag", "./srcs/shaders/couleur2D.vert"))
		return (1);
	if (!(data.program = create_and_link_program(data.vertex_sh, data.fragment_sh)))
		return (2);
	printf("nb = %zu\n", data.texture_nbr);
	data.imgs = malloc(sizeof(t_img) * data.texture_nbr);
	texs = malloc(sizeof(uint) * data.texture_nbr); 
	// glGenTextures(1, texs);
	glGenTextures(data.texture_nbr, texs);
	
	// uint n = 0;
	// while (n < data.texture_nbr)
	// {
	// 	printf("%d\n", texs[n]);
	// 	n++;
	// }
	
	uint	i_tex;

	 unsigned int *texture1;
	 texture1 = malloc(sizeof(unsigned int) * 4);

	i = 0;
	i_tex = 0;
	while (i < data.object_nbr)
	{
		j = 0;
		printf("obj[i].mtl_nbr = %d\n", obj[i].mtl_nbr);
		while (j < obj[i].mtl_nbr)
		{
			printf("obj[i].mtls[j].img_file = %s\n", obj[i].mtls[j].img_file);
			if (obj[i].mtls[j].img_file)
			{
				printf("i_tex = %u\nname = %s\n", i_tex, obj[i].mtls[j].img_file);
				printf("texs[i_tex] = %d\n", texs[i_tex]);
				glBindTexture(GL_TEXTURE_2D, texs[i_tex]);
				create_image_from_png(&data, i_tex, obj[i].mtls[j].img_file);

				// printf("w = %d, h = %d\n", data.imgs[i_tex].w, data.imgs[i_tex].h);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.imgs[i_tex].w, data.imgs[i_tex].h, 0, GL_BGRA, GL_UNSIGNED_BYTE, data.imgs[i_tex].data);
				// printf("-\n");
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// printf("*\n");
				i_tex++;
			}
			j++;
		}
		i++;
	}

	// glGenTextures(2, texture1);
 //    glBindTexture(GL_TEXTURE_2D, texture1[0]); 
 //     // set the texture wrapping parameters
 //    // set texture filtering parameters
 //    // load image, create texture and generate mipmaps

 //    create_image_from_png(&data, 0, obj[0].mtls[0].img_file);
 //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.imgs[0].w, data.imgs[0].h, 0, GL_RGB, GL_UNSIGNED_BYTE, data.imgs[0].data);
 //    glGenerateMipmap(GL_TEXTURE_2D);

 //    glBindTexture(GL_TEXTURE_2D, texture1[1]); 
 //     // set the texture wrapping parameters
 //    // set texture filtering parameters
 //    // load image, create texture and generate mipmaps

 //    create_image_from_png(&data, 1, obj[0].mtls[1].img_file);
 //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.imgs[1].w, data.imgs[1].h, 0, GL_RGB, GL_UNSIGNED_BYTE, data.imgs[1].data);
 //    glGenerateMipmap(GL_TEXTURE_2D);

 //    glBindTexture(GL_TEXTURE_2D, texture1[2]); 
 //     // set the texture wrapping parameters
 //    // set texture filtering parameters
 //    // load image, create texture and generate mipmaps

 //    create_image_from_png(&data, 2, obj[0].mtls[2].img_file);
 //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.imgs[2].w, data.imgs[2].h, 0, GL_RGB, GL_UNSIGNED_BYTE, data.imgs[2].data);
 //    glGenerateMipmap(GL_TEXTURE_2D);

 //    glBindTexture(GL_TEXTURE_2D, texture1[3]); 
 //     // set the texture wrapping parameters
 //    // set texture filtering parameters
 //    // load image, create texture and generate mipmaps

 //    create_image_from_png(&data, 3, obj[0].mtls[3].img_file);
 //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.imgs[3].w, data.imgs[3].h, 0, GL_RGB, GL_UNSIGNED_BYTE, data.imgs[3].data);
 //    glGenerateMipmap(GL_TEXTURE_2D);



	// create_image_from_png(&data, 0, "textures/Cat_diffuse.png");
	// create_image_from_png(&data, 0, "textures/Cat_diffuse.png");

	// int q = 0;
	// while (q < obj[0].indices_nbr)
	// {
	// 	printf("#%d: %f %f\n", q, obj[0].textures[q].x, obj[0].textures[q].y);
	// 	q++;
	// }

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	GLuint ebo = 0;
	GLuint tex = 0;
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &data.buffer[0]);
	glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, data.buffer[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3) * obj[0].vertices_nbr + sizeof(t_vec2) * obj[0].tex_vertices_nbr, 0, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(t_vec3) * obj[0].vertices_nbr, obj[0].vertices);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(t_vec3) * obj[0].vertices_nbr, sizeof(t_vec2) * obj[0].tex_vertices_nbr, obj[0].tex_vertices);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid*)(sizeof(t_vec3) * obj[0].vertices_nbr));
			glEnableVertexAttribArray(1);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(obj[0].indices[0]) * obj[0].indices_nbr, obj[0].indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// rot = 180;
	// ft_mat4x4_set_rotation(model, 0, (t_vec3){1, 0, 0});
	// ft_mat4x4_set_translation(model, (t_vec3){0, 0, 1});
	data.eye = (t_vec3){0, 0, -10};
	data.dir = (t_vec3){0, 0, -1};

	ft_mat4x4_set_identity(data.cam.model);
	ft_mat4x4_to_float_array(data.cam.model_f, data.cam.model);



	// dir = ft_vec4_to_vec3(ft_mat4x4_mult_with_vec4(model, (t_vec4){0, 0, 0, 1}));
	data.cam.up = (t_vec3){0,1,0};
	ft_mat4x4_set_look_at(data.cam.view, data.eye, ft_vec3_sub(data.eye, data.dir), data.cam.up);
	// ft_mat4x4_translate(data.cam.view, (t_vec3){0, 0, -50});
	ft_mat4x4_to_float_array(data.cam.view_f, data.cam.view);


	ft_mat4x4_set_projection(data.cam.proj, (float[]){45, (float)data.width / data.height, .1f, 1000.0f});
	ft_mat4x4_to_float_array(data.cam.proj_f, data.cam.proj);

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

	printf("tex = %d\n", texs[0]);
	while (!glfwWindowShouldClose(data.window))
	{
		delta = (tp.tv_sec * 1000 + tp.tv_usec / 1000) - last;
		last = (tp.tv_sec * 1000 + tp.tv_usec / 1000);

		key_event(&data, delta);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(data.program);


		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao);

		// ft_mat4x4_set_rotation(cam.model, rot + 90 * delta / 1000.0, (t_vec3){1, 0, 0});
		// // ft_mat4x4_scale(cam.model, (t_vec3){0.5, 0.5, 0.5});
		// // ft_mat4x4_translate(cam.model, (t_vec3){0, 0, 0});
		// ft_mat4x4_to_float_array(cam.model_f, cam.model);
		// rot += 90 * delta / 1000.0;

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, data.cam.model_f);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, data.cam.view_f);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, data.cam.proj_f);


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

		glBindVertexArray(0);
		glfwPollEvents();
		glfwSwapBuffers(data.window);
		gettimeofday(&tp, NULL);
	}
	printf("Closing window.\n");

	glfwTerminate();
	return 0;
}
