#ifndef SCOP_H
# define SCOP_H

# include <stdio.h>
# include <libft.h>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

typedef struct s_d {
	GLFWwindow	*window;
	float		*vertices;
	size_t		sizeof_vertices;

	GLuint	vertex_sh;
	GLuint	fragment_sh;
	GLuint	program;
	GLuint	buffer;
}					t_d;

GLuint	create_and_compile_shader(const char *filename, GLenum shaderType);
GLuint create_and_link_program(GLuint vertex_sh, GLuint fragment_sh);

#endif
