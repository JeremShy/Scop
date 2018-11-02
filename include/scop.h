#ifndef SCOP_H
# define SCOP_H

# include <stdio.h>
# include <libft.h>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <libftmatrices.h>

# define MAX_OBJECTS_NBR 16

#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

typedef struct s_d {
	GLFWwindow	*window;
	int			width;
	int			height;


	GLuint		vertex_sh;
	GLuint		fragment_sh;
	GLuint		program;

	size_t		nbr_of_objects;

	float		*vertices[MAX_OBJECTS_NBR];
	float		*colors[MAX_OBJECTS_NBR];
	size_t		sizeof_vertices[MAX_OBJECTS_NBR];
	size_t		sizeof_colors[MAX_OBJECTS_NBR];
	GLuint		buffer[MAX_OBJECTS_NBR];
	GLuint		vao[MAX_OBJECTS_NBR];
	t_mat4x4	projection;
	t_mat4x4	modelview[MAX_OBJECTS_NBR];

	float		float_projection[4 * 4];
	float		float_modelview[MAX_OBJECTS_NBR][4 * 4];
}					t_d;

typedef struct	s_obj {
	char	*name;

	char	*material;

	t_vec3	*vertices;
	int		vertices_nbr;

	t_vec3	*tex_vertices;
	int		tex_vertices_nbr;

	t_vec3	*normales;
	int		normales_nbr;

	int8_t	error;
}				t_obj;


GLuint	create_and_compile_shader(const char *filename, GLenum shaderType);
GLuint	create_and_link_program(GLuint vertex_sh, GLuint fragment_sh);

t_obj	obj_parser_main(char *file);


#endif
